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
 *  alged_update()  update mean force
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


/* return the correction: (-1/2) d < dx^2 > / dx
 * the updating seeks the fixed point:
 *    < dx + corr. > = 0
 * where
 *    corr. =  - (1/2) d < dx^2 > / dx
 * the mean force f = d (log rho) / dx is updated as
 *   f += alpha (dx + corr.)
 *
 * the formula is derived from the detail balance
 *   rho(x) p(x, eps) = rho(x + eps) p(x + eps, -eps)
 * if rho(x) == rho(x + eps), then
 *   \int p(x, eps) eps = \int p(x, -eps) eps + \int dp/dx eps^2
 * which is < eps > = -<eps> + d < eps^2 > / dx
 *
 * `mindata' is the minimal number of data points to use the corrections
 *  since the correction uses numerical differentiation, insufficient
 *  data points makes the correction unreliable
 *
 * the smooth boundary condition is effected by the two parameters
 * `derm' and `derp', which are the absolute values of the offsets
 * to the mean force that discourage moves reaching out of (xmin, xmax)
 * */
INLINE double alged_getcorr(const alged_t *al, int i,
    double mindata, int refl, double derm, double derp)
{
  int im = i - 1, ip = i + 1;
  double e2o, e2n, dx = 2 * al->dx;

  /* the correction is adjusted by the boundary conditions
   * for a reflective boundary, we simply set it to be zero
   * for a smooth boundary, we try to use `derm' and `derp',
   * which are to be gauged carefully by experimenting,
   * to the make the distribution continuous */
  if (im < 0) {
    /* an artifically negative `f' makes more negative
      * which encourages a positive `dx' to get back in range */
    if (!refl) return -derm; /* else return 0; */
    /* for a reflective boundary, it's okay to return 0 */
    im = 0; ip = 1; dx = al->dx;
  } else if (ip >= al->n) {
    if (!refl) return derp; /* else return 0; */
    im = al->n - 2; ip = al->n - 1; dx = al->dx;
  }

  if (al->cc[im] < mindata || al->cc[ip] < mindata)
    return 0; /* set the correction to zero if too few data points */
  e2o = al->e2[im]/al->cc[im];
  e2n = al->e2[ip]/al->cc[ip];
  return -0.5f * (e2n - e2o) / dx;
}


/* update data and mean force
 * `x0' is the start point, `dx_l' is the logical change of `x'
 * the mean force updating amplitude is min{`a0', `ac'/cc}
 * `mindata' is the minimal number of data points to apply
 *    the correction, see _getcorr()
 * `refl' mean if the boundary condition is reflective
 *    if `refl' == 0, `derm' and `derp' are used for the corrections
 *    at the boundaries, otherwise the two are unused
 * `mfmax' is the maximal allowed mean force amplitude
 * `*alpha' is the updating amplitude
 * `*corr' is the O(1/N) mean-force correction */
INLINE double alged_update(alged_t *al, double x0, double dx_l,
    double a0, double ac,
    double mindata, int refl, double derm, double derp,
    double mfmax, double *alpha, double *corr)
{
  double alf, dxc;
  double dxmax = dblmax(fabs(dx_l), al->dx);
  int id = alged_getidx(al, x0);

  /* in reflective boundary, x0 shouldn't be out of boundary
   * we don't let this to pollute the data */
  if (refl && (x0 < al->xmin || x0 > al->xmax)) return 0;

  /* update data */
  al->cc[id] += 1;
  al->e2[id] += dx_l * dx_l;

  /* get the updating amplitude */
  alf = alged_getalpha(al, id, a0, ac);
  if (alpha) *alpha = alf;

  /* compute the O(1/N) correction */
  dxc = alged_getcorr(al, id, mindata, refl, derm, derp);
  dxc = dblconfine(dxc, -dxmax, dxmax);
  if (corr) *corr = dxc;

  al->f[id] += alf * (dx_l + dxc);
  if (mfmax > 0) return al->f[id] = dblconfine(al->f[id], -mfmax, mfmax);
  else return al->f[id] = dblmax(al->f[id], 0);
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

