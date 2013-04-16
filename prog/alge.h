#ifndef ALGE_H__
#define ALGE_H__

typedef struct {
  int xmin, xmax, dx;
  int n;
  double *f; /* dH/dE */
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


/* return the energy index, extended */
INLINE int alge_getidx(const alge_t *al, int x)
{
  if (x < al->xmin) return 0;
  else if (x > al->xmax) return al->n - 1;
  else return (x - al->xmin)/al->dx;
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
 * `*alpha' is the updating amplitude
 * `delmax' is maximal amount of the allowed 2 e / < e^2 >
 * `*denom' is the used < e^2 >
 * (`mfmin', `mfmax') is the allowed mean force range */
INLINE double alge_fupdate(alge_t *al, int x0, int dx_l,
    double a0, double ac, double *alpha, double delmax, 
    double *denom, double mfmin, double mfmax)
{
  double alf, den;
  int id = alge_getidx(al, x0), idn = alge_getidx(al, x0 + dx_l);

  /* in reflective boundary, x0 shouldn't be out of boundary
   * we don't let this to pollute the data */
  if (x0 < al->xmin || x0 >= al->xmax) return 0;

  /* update data */
  al->cc[id] += 1;
  al->e2[id] += dx_l * dx_l;

  /* get the updating amplitude */
  alf = alge_getalpha(al, id, a0, ac);
  if (alpha) *alpha = alf;

  /* compute the denominator < e^2 > */
  den = alge_getden(al, id, idn);
  if (denom) *denom = den;

  al->f[id] += alf * dblconfine(2.0*dx_l/den, -delmax, delmax);
  return al->f[id] = dblconfine(al->f[id], mfmin, mfmax);
}


#define alge_getdh alge_getdh0

/* return the F difference, zeroth order */
static double alge_getdh0(const alge_t *al, int en, int eo)
{
  int ien, ieo, ie, sgn = 1;
  double f = 0.;

  if (eo == en) return 0.;
  if (en < al->xmin) {
    f += (en - al->xmin)*al->f[0];
    en = al->xmin;
  } else if (en >= al->xmax) {
    f += (en - al->xmax + 1)*al->f[al->n - 1];
    en = al->xmax - 1;
  }
  if (eo == en) return f;
  if (eo > en) { /* ensure eo < en */
    sgn = eo, eo = en, en = sgn;
    sgn = -1;
  }
  ieo = (eo - al->xmin)/al->dx;
  ien = (en - al->xmin)/al->dx;
  if (ieo == ien) { /* within a bin */
    f += sgn*(en - eo)*al->f[ieo];
  } else { /* cross several bins */
    f += sgn*(al->xmin + (ieo+1)*al->dx - eo)*al->f[ieo];
    f += sgn*(en - al->xmin - ien*al->dx)*al->f[ien];
    for (ie = ieo + 1; ie < ien; ie++)
      f += sgn*al->dx*al->f[ie];
  }
  return f;
}


/* return the acceptance rates
 * the logical rate `*acc_l' indicates if a move x0 -> x1 were to be
 *    accepted as if there were no boundaries
 * the boundary-adjusted rate `*acc_b' rejects a move out of (xmin, xmax)
 * with a reflective boundary condition (`refl' = 1), return `*acc_b'
 *    or `acc_l' otherwise */
INLINE int alge_getacc(const alge_t *al, int x1, int x0, int refl,
   int *acc_l, int *dx_l, int *acc_b, double *dlnrho)
{
  int accb, accl;

  /* compute the Metropolis acceptance rate
   * dv = d log(rho) = \int^1_0 al->f
   * dv > 0 means moving to a more populated region
   * which therefore should be biased against */
  double dv = alge_getdh(al, x1, x0);
  if (dlnrho) *dlnrho = dv;
  accl = (dv <= 0 || rnd0() < exp(-dv));
  if (acc_l) *acc_l = accl;
  if (dx_l) *dx_l = (accl ? x1 - x0 : 0);

  /* reflective boundary conditions */
  if (x0 < al->xmin) { /* swoop in from the left */
    accb = (x1 >= x0);
  } else if (x0 > al->xmax) { /* swoop in from the right */
    accb = (x1 <= x0);
  } else { /* currently in range */
    accb = (x1 >= al->xmin && x1 <= al->xmax) ? accl : 0;
  }
  if (acc_b) *acc_b = accb;
  return refl ? accb : accl;
}


/* save dh/de file */
static int alge_save(alge_t *al, const char *fn)
{
  FILE *fp;
  int i;
  double lng = 0., cc, e2, f, sc;

  xfopen(fp, fn, "w", return -1);

  for (sc = 0, i = 0; i < al->n; i++)
    sc += al->cc[i];
  sc = 1.0/(al->dx * sc);

  fprintf(fp, "# %d %d %d\n", al->n, al->xmin, al->dx);
  for (i = 0; i < al->n; i++) {
    cc = e2 = f = 0;
    if (i < al->n) {
      cc = al->cc[i];
      if (cc > 0.0) e2 = al->e2[i]/cc;
      f = al->f[i];
    }
    fprintf(fp, "%d %.6f %.6f %g %.6f %g\n",
      al->xmin + i * al->dx, f, lng, cc, e2, cc * sc);
    lng += al->f[i] * al->dx;
  }
  fclose(fp);
  return 0;
}

#endif

