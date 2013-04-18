#ifndef ALGE_H__
#define ALGE_H__

typedef struct {
  int xmin, xmax, dx;
  int n; /* number of bins */
  double *f; /* mean force array */
  double *cc, *e2; /* histogram, sum of e^2 */
} alge_t;


/* summary of functions
 *
 * basic:
 *  alge_open()
 *  alge_close()
 *  alge_save()
 *
 * (hybrid) MC:
 *  alge_getacc()  get acceptance rate for a move
 *  alge_fupdate()  update mean force
 *
 * low level MD/MC:
 *  alge_getf()    get mean force, for MD
 *  alge_getdh()   get mean force integral, for MC
 * */


static alge_t *alge_open(int xmin, int xmax, int dx, double f0)
{
  alge_t *al;
  int i;

  xnew(al, 1);
  al->xmin = xmin;
  al->xmax = xmax;
  al->dx = dx; /* interval size */
  al->n = (xmax - xmin)/dx; /* number of intervals */
  if (al->dx * al->n + xmin != xmax) {
    al->xmax = al->xmin + al->n * al->dx;
    fprintf(stderr, "fix xmax, s.t. dx %d divides xmax %d - xmin %d\n",
      dx, xmax, xmin);
  }
  xnew(al->f, al->n + 1);
  xnew(al->cc, al->n + 1);
  xnew(al->e2, al->n + 1);
  for (i = 0; i <= al->n; i++) {
    al->f[i] = f0;
    al->cc[i] = 0.;
    al->e2[i] = 0.;
  }
  return al;
}


static void alge_close(alge_t *al)
{
  free(al->f);
  free(al->cc);
  free(al->e2);
  free(al);
}


/* return the index */
INLINE int alge_getidx(const alge_t *al, int x)
{
  if (x < al->xmin) return 0;
  else if (x >= al->xmax) return al->n - 1;
  else return (x - al->xmin)/al->dx;
}


/* return the current mean force */
INLINE double alge_getf(const alge_t *al, int x)
{
  return al->f[ alge_getidx(al, x) ];
}


/* return the proper upating magnitude  alpha = min{a0, ac/cc}
 * where cc is the number of data points in the bin */
INLINE double alge_getalpha(const alge_t *al, int i, double a0, double ac)
{
  return dblmin(a0, ac/al->cc[i]);
}


/* return the average < e^2 > at bin `i0' and `i1' */
INLINE double alge_getden(const alge_t *al, int i0, int i1)
{
  double cc = al->cc[i0] + al->cc[i1];
  double e2 = al->e2[i0] + al->e2[i1];
  /* (e20 + e21) / (cc0 + cc1) is roughly < e2 >_x of `x' in the middle
   * even if the distribution is slightly tilded, the shift in `x'
   * for positive and negative `eps' should still sum to the full `eps'
   * returns unity by default */
  return (cc > 0 && e2 > 0) ? (e2 / cc) : 1.0;
}


/* fractional update data and mean force, with the denominator < e^2 >
 * `x0' is the start point, `dx_l' is the logical change of `x'
 * the mean force updating amplitude is min{`a0', `ac'/cc}
 * `*alf' is the updating amplitude
 * `delmax' is maximal amount of the allowed 2 e / < e^2 >
 * `*den' is the used < e^2 >
 * (`mfmin', `mfmax') is the allowed mean force range */
INLINE double alge_fupdate(alge_t *al, int x0, int dx_l,
    double a0, double ac, double *alf, double delmax, 
    double *den, double mfmin, double mfmax)
{
  int id, idn;

  /* no update if the move starts from the outside */
  if (x0 < al->xmin || x0 >= al->xmax) return 0;

  id = alge_getidx(al, x0);
  idn = alge_getidx(al, x0 + dx_l);

  /* update the histogram and e^2 */
  al->cc[id] += 1;
  al->e2[id] += dx_l * dx_l;
 
  /* update the mean force */ 
  *alf = alge_getalpha(al, id, a0, ac); /* compute amplitude */
  *den = alge_getden(al, id, idn); /* compute < e^2 > */
  al->f[id] += (*alf) * dblconfine(2.0 * dx_l / (*den), -delmax, delmax);
  return al->f[id] = dblconfine(al->f[id], mfmin, mfmax);
}


/* return the H difference, zeroth order */
static double alge_getdh(const alge_t *al, int xn, int xo)
{
  int ixn, ixo, ix, sgn = 1;
  double dh = 0.;

  if (xo == xn) {
    return 0.;
  } else if (xo > xn) { /* make sure xn > xo */
    intswap(xo, xn);
    sgn = -1;
  }

  if (xo < al->xmin) { /* change `xo' such that xo >= xmin */
    if (xn < al->xmin) return sgn * (xn - xo) * al->f[0]; 
    dh += (al->xmin - xo)*al->f[0];
    xo = al->xmin;
  }
  if (xn >= al->xmax) { /* change `xn' such that xn < xmax */
    if (xo >= al->xmax) return sgn * (xn - xo) * al->f[al->n - 1];
    dh += (xn - al->xmax + 1) * al->f[al->n - 1];
    xn = al->xmax - 1;
  }
  if (xo == xn) return sgn * dh; /* may happen after the trimming */
  
  ixo = (xo - al->xmin)/al->dx;
  ixn = (xn - al->xmin)/al->dx;
  if (ixo == ixn) { /* within a bin */
    dh += (xn - xo) * al->f[ixo];
  } else { /* cross several bins */
    dh += (al->xmin + (ixo+1)*al->dx - xo) * al->f[ixo]
        + (xn - al->xmin - ixn*al->dx) * al->f[ixn];
    for (ix = ixo + 1; ix < ixn; ix++)
      dh += al->dx * al->f[ix];
  }
  return sgn * dh;
}


/* return the acceptance rates
 * the logical rate `*acc_l' indicates if a move x0 -> x1 were to be
 *    accepted as if there were no boundaries
 * the boundary-adjusted rate `*acc_b' rejects a move out of (xmin, xmax)
 * with a reflective boundary condition (`refl' = 1), return `*acc_b'
 *    or `acc_l' otherwise */
INLINE int alge_getacc(const alge_t *al, int x1, int x0, int refl,
   int *dx_l, double *ds, int *acc_l, int *acc_b)
{
  /* compute the logical Metropolis acceptance rate
   * ds = d log(rho) = \int^1_0 al->f
   * ds > 0 means moving to a more populated region
   * which therefore should be biased against */
  *ds = alge_getdh(al, x1, x0);
  *acc_l = (*ds <= 0 || rnd0() < exp(-(*ds)));
  *dx_l = (*acc_l) ? x1 - x0 : 0;

  /* reflective boundary conditions */
  if (x0 < al->xmin) /* swoop in from the left */
    *acc_b = (x1 >= x0);
  else if (x0 >= al->xmax) /* swoop in from the right */
    *acc_b = (x1 <= x0);
  else /* currently in range */
    *acc_b = (x1 >= al->xmin && x1 < al->xmax) ? *acc_l : 0;
  return refl ? *acc_b : *acc_l;
}


/* save mean force, and its integral */
static int alge_save(alge_t *al, const char *fn)
{
  FILE *fp;
  int i;
  double lng = 0, f = 0, cc = 0, e2 = 0, sc;

  xfopen(fp, fn, "w", return -1);

  for (sc = 0, i = 0; i < al->n; i++)
    sc += al->cc[i];
  sc = 1.0/(sc * al->dx);

  fprintf(fp, "# %d %d %d\n", al->n, al->xmin, al->dx);
  for (i = 0; i <= al->n; i++) {
    if (i < al->n) {
      f = al->f[i];
      cc = al->cc[i];
      e2 = (cc > 0) ? al->e2[i] / cc : 0;
    } /* if i == al->n, assume the values of the last bin */
    fprintf(fp, "%d %.6f %.6f %g %.6f %g\n",
      al->xmin + i * al->dx, f, lng, cc, e2, cc * sc);
    if (i < al->n) lng += al->f[i] * al->dx;
  }
  fclose(fp);
  return 0;
}

#endif

