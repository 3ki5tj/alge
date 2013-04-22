#ifndef ALGED_H__
#define ALGED_H__

typedef struct {
  double xmin, xmax, dx;
  int n; /* number of bins */
  double *f; /* mean force array */
  double *cc, *e2; /* histogram, sum of e^2 */
} alged_t;


/* summary of functions
 *
 * basic:
 *  alged_open()
 *  alged_close()
 *  alged_save()
 *
 * (hybrid) MC:
 *  alged_getacc()  get acceptance rate for a move
 *  alged_fupdate()  update mean force
 *
 * low level MD/MC:
 *  alged_getf()    get mean force, for MD
 *  alged_getdh()   get mean force integral, for MC
 * */


/* open an alge object
 * `f0' is the mean force
 * see the `alged_t' description for other parameters */
static alged_t *alged_open(double xmin, double xmax, double dx, double f0)
{
  alged_t *al;
  int i;

  xnew(al, 1);
  al->xmin = xmin;
  al->dx = dx; /* interval size */
  al->n = (int)((xmax - xmin)/dx + .5); /* number of intervals */
  al->xmax = al->xmin + al->n * al->dx;
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


static void alged_close(alged_t *al)
{
  free(al->f);
  free(al->cc);
  free(al->e2);
  free(al);
}


/* return the index */
INLINE int alged_getidx(const alged_t *al, double x)
{
  if (x < al->xmin) return 0;
  else if (x >= al->xmax) return al->n - 1;
  else return (int) ( (x - al->xmin) / al->dx );
}


/* return the current mean force */
INLINE double alged_getf(const alged_t *al, double x)
{
  return al->f[ alged_getidx(al, x) ];
}


/* return the proper upating magnitude  alpha = min{a0, ac/cc}
 * where cc is the number of data points in the bin */
INLINE double alged_getalpha(const alged_t *al, int i, double a0, double ac)
{
  return dblmin(a0, ac/al->cc[i]);
}


/* return the average < e^2 > at bin `i0' and `i1' */
INLINE double alged_getden(const alged_t *al, int i0, int i1)
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
INLINE double alged_fupdate(alged_t *al, double x0, double dx_l,
    double a0, double ac, double *alf, double delmax, 
    double *den, double mfmin, double mfmax)
{
  int id, idn;

  /* no update if the move starts from the outside */
  if (x0 < al->xmin || x0 >= al->xmax) return 0;

  id = alged_getidx(al, x0);
  idn = alged_getidx(al, x0 + dx_l);
  
  /* update the histogram and e^2 */
  al->cc[id] += 1;
  al->e2[id] += dx_l * dx_l;

  /* update the mean force */
  *alf = alged_getalpha(al, id, a0, ac); /* compute the amplitude */
  *den = alged_getden(al, id, idn); /* compute < e^2 > */
  al->f[id] += (*alf) * dblconfine(2.0 * dx_l / (*den), -delmax, delmax);
  return al->f[id] = dblconfine(al->f[id], mfmin, mfmax);
}


/* return the H difference, zeroth order */
INLINE double alged_getdh(const alged_t *al, double xn, double xo)
{
  int ixn, ixo, ix, sgn = 1;
  double dh = 0.;
  double tol = 1e-6 * al->dx;

  if (xo > xn) { /* make sure xn > xo */
    dblswap(xo, xn);
    sgn = -1;
  }

  if (xo < al->xmin) { /* change `xo' such that xo >= xmin */
    if (xn < al->xmin) return sgn * (xn - xo) * al->f[0];
    dh += (al->xmin - xo) * al->f[0];
    xo = al->xmin;
  }
  if (xn >= al->xmax) { /* change `xn' such that xn < xmax */
    if (xo >= al->xmax) return sgn * (xn - xo) * al->f[al->n - 1];
    dh += (xn - al->xmax + tol) * al->f[al->n - 1];
    xn = al->xmax - tol;
  }

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
INLINE int alged_getacc(alged_t *al, double x1, double x0, int refl,
   double *dx_l, double *ds, int *acc_l, int *acc_b)
{
  /* compute the logical Metropolis acceptance rate
   * ds = d log(rho) = \int^1_0 al->f
   * ds > 0 means moving to a more populated region
   * which therefore should be biased against */
  *ds = alged_getdh(al, x1, x0);
  *acc_l = (*ds <= 0 || rnd0() < exp(-(*ds)));
  *dx_l = (*acc_l) ? x1 - x0 : 0;

  /* reflective boundary conditions */
  if (x0 < al->xmin) /* swoop in from the left */
    *acc_b = (x1 > x0 - 1e-6);
  else if (x0 >= al->xmax) /* swoop in from the right */
    *acc_b = (x1 < x0 + 1e-6);
  else /* currently in range */
    *acc_b = (x1 >= al->xmin && x1 < al->xmax) ? *acc_l : 0;
  return refl ? *acc_b : *acc_l;
}


/* save mean force and its integral */
static int alged_save(alged_t *al, const char *fn)
{
  FILE *fp;
  int i;
  double lng = 0, f = 0, cc = 0, e2 = 0, sc;

  xfopen(fp, fn, "w", return -1);
  fprintf(fp, "# %d %g %g\n", al->n, al->xmin, al->dx);

  /* compute the normalization factor */
  for (sc = 0, i = 0; i < al->n; i++)
    sc += al->cc[i];
  sc = 1.0/(sc * al->dx);

  for (i = 0; i <= al->n; i++) {
    if (i < al->n) {
      f = al->f[i];
      cc = al->cc[i];
      e2 = (cc > 0) ? al->e2[i] / cc : 0;
    } /* if i == al->n, assume the values of the last bin */
    fprintf(fp, "%g %.6f %.6f %g %.6f %g\n",
      al->xmin + i * al->dx, f, lng, cc, e2, cc * sc);
    if (i < al->n) lng += al->f[i] * al->dx;
  }
  fclose(fp);
  return 0;
}

#endif

