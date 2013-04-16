#ifndef ALGED_H__
#define ALGED_H__

typedef struct {
  double xmin, xmax, dx;
  int n; /* number of bins */
  int order; /* the order of mean force interpolation (currently only 0)
                0th order for constant mean force within a bin
                1st order for linear mean force */
  double *f; /* mean force array */
  double *cc, *e2; /* histogram, sum of e^2 (diffusivity) */
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
static alged_t *alged_open(double xmin, double xmax, double dx,
    double f0, int order)
{
  alged_t *al;
  int i;

  xnew(al, 1);
  al->xmin = xmin;
  al->dx = dx; /* interval size */
  al->n = (int)((xmax - xmin)/dx + .5); /* number of intervals */
  al->xmax = al->xmin + al->n * al->dx;
  al->order = order;
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


/* return the index (extended) */
INLINE int alged_getidx(const alged_t *al, double x)
{
  if (x < al->xmin) return 0;
  else if (x >= al->xmax) return al->n - 1;
  else return (int) ( (x - al->xmin) / al->dx );
}


/* return the current f, zeroth order */
INLINE double alged_getf0(const alged_t *al, double x)
{
  if (x < al->xmin) return al->f[0];
  else if (x > al->xmax) return al->f[al->n - 1];
  else return al->f[ (int) ( (x - al->xmin) / al->dx ) ];
}


/* return the current f, first order */
INLINE double alged_getf1(const alged_t *al, double x)
{
  int i;
  double x0, y;

  if (x < al->xmin) return al->f[0];
  else if (x > al->xmax) return al->f[al->n];
  i = (int) ( (x - al->xmin) / al->dx );
  /* linear interpolation between f[i] and f[i + 1]; */
  x0 = al->xmin + al->dx * i;
  y = (x - x0)/al->dx;
  return al->f[i] * (1 - y) + al->f[i+1] * y;
}


/* return the current f */
INLINE double alged_getf(const alged_t *al, double x)
{
  return (al->order == 0) ? alged_getf0(al, x) : alged_getf1(al, x);
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
 * `*alpha' is the updating amplitude
 * `delmax' is maximal amount of the allowed 2 e / < e^2 >
 * `*denom' is the used < e^2 >
 * (`mfmin', `mfmax') is the allowed mean force range */
INLINE double alged_fupdate(alged_t *al, double x0, double dx_l,
    double a0, double ac, double *alpha, double delmax, 
    double *denom, double mfmin, double mfmax)
{
  double alf, den;
  int id = alged_getidx(al, x0), idn = alged_getidx(al, x0 + dx_l);

  /* in reflective boundary, x0 shouldn't be out of boundary
   * we don't let this to pollute the data */
  if (x0 < al->xmin || x0 >= al->xmax) return 0;

  /* update data */
  al->cc[id] += 1;
  al->e2[id] += dx_l * dx_l;

  /* get the updating amplitude */
  alf = alged_getalpha(al, id, a0, ac);
  if (alpha) *alpha = alf;

  /* compute the denominator < e^2 > */
  den = alged_getden(al, id, idn);
  if (denom) *denom = den;

  al->f[id] += alf * dblconfine(2.0*dx_l/den, -delmax, delmax);
  return al->f[id] = dblconfine(al->f[id], mfmin, mfmax);
}


#define alged_getdh alged_getdh0

/* return the F difference zeroth order */
INLINE double alged_getdh0(const alged_t *al, double xn, double xo)
{
  int ixn, ixo, ix, sgn = 1;
  double dh = 0.;

  if (xn < al->xmin) {
    if (xo < al->xmin)
      return (xn - xo) * al->f[0];
    dh += (xn - al->xmin)*al->f[0];
    xn = al->xmin;
  } else if (xn >= al->xmax) {
    if (xo > al->xmax)
      return (xn - xo) * al->f[al->n - 1];
    dh += (xn - al->xmax + 1)*al->f[al->n - 1];
    xn = al->xmax - 1e-7;
  }
  if (xo > xn) { /* ensure xo < xn */
    dblswap(xo, xn);
    sgn = -1;
  }
  ixo = (xo - al->xmin)/al->dx;
  ixn = (xn - al->xmin)/al->dx;
  if (ixo == ixn) { /* within a bin */
    dh += sgn*(xn - xo)*al->f[ixo];
  } else { /* cross several bins */
    dh += sgn*(al->xmin + (ixo+1)*al->dx - xo)*al->f[ixo];
    dh += sgn*(xn - al->xmin - ixn*al->dx)*al->f[ixn];
    for (ix = ixo + 1; ix < ixn; ix++)
      dh += sgn*al->dx*al->f[ix];
  }
  return dh;
}


/* return the acceptance rates
 * the logical rate `*acc_l' indicates if a move x0 -> x1 were to be
 *    accepted as if there were no boundaries
 * the boundary-adjusted rate `*acc_b' rejects a move out of (xmin, xmax)
 * with a reflective boundary condition (`refl' = 1), return `*acc_b'
 *    or `acc_l' otherwise */
INLINE int alged_getacc(alged_t *al, double x1, double x0, int refl,
   int *acc_l, double *dx_l, int *acc_b, double *dlnrho)
{
  int accb, accl;

  /* compute the Metropolis acceptance rate
   * dv = d log(rho) = \int^1_0 al->f
   * dv > 0 means moving to a more populated region
   * which therefore should be biased against */
  double dv = alged_getdh(al, x1, x0);
  if (dlnrho) *dlnrho = dv;
  accl = (dv <= 0 || rnd0() < exp(-dv));
  if (acc_l) *acc_l = accl;
  if (dx_l) *dx_l = (accl ? x1 - x0 : 0);

  /* reflective boundary conditions */
  if (x0 < al->xmin) { /* swoop in from the left */
    accb = (x1 > x0 - 1e-6);
  } else if (x0 > al->xmax) { /* swoop in from the right */
    accb = (x1 < x0 + 1e-6);
  } else { /* currently in range */
    accb = (x1 > al->xmin && x1 < al->xmax) ? accl : 0;
  }
  if (acc_b) *acc_b = accb;
  return refl ? accb : accl;
}


/* save dh/de file */
static int alged_save(alged_t *al, const char *fn)
{
  FILE *fp;
  int i;
  double lng = 0., e2, cc, sc;

  xfopen(fp, fn, "w", return -1);
  fprintf(fp, "# %d %g %g\n", al->n, al->xmin, al->dx);

  /* compute the normalization factor */
  for (cc = 0, i = 0; i < al->n; i++)
    cc += al->cc[i];
  sc = 1.0/(cc * al->dx);

  for (i = 0; i < al->n; i++) {
    if (i > 0) {
      if (al->order) lng += al->f[i-1] * al->dx;
      else lng += (al->f[i-1] + al->f[i]) * .5 * al->dx;
    }
    e2 = 0;
    if (al->cc[i] > 0.0) e2 = al->e2[i]/al->cc[i];
    fprintf(fp, "%g %.6f %.6f %g %.6f %g\n",
      al->xmin + i * al->dx, al->f[i], lng, al->cc[i], e2, /* 5 param. */
      al->cc[i] * sc);
  }
  fclose(fp);
  return 0;
}

#endif

