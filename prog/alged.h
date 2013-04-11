typedef struct {
  double xmin, xmax, dx;
  int n;
  int order; /* the order of mean force interpolation (currently only 0)
                0th order for fixed mean force within a bin 
                1st order for linear mean force */
  int flat; /* try to make histogram flat */
  double mindata; /* minimal number of data points to adopt the corrections */
  double derm; /* the absolute value of the mean force correction for the left side 
                  it is applied as a negative value */
  double derp; /* the absolute value of the mean force correction for the right side
                  it is applied as a positive value */
  double a0; /* initial updating amplitude */
  double ac; /* use the formula ac/t to reduce the amplitude */
  double *f; /* mean force array */
  double *cc, *e2; /* histogram, sum of e^2 (diffusivity) */
} alged_t;

/* open an alge object
 * `f0' is the mean force
 * `flat' is 1 for a flat distribution (with the correction)
 *    or 0 for the diffusivity adjusted version (without the correction)
 * see the `alge_t' description for other parameters */
static alged_t *alged_open(double xmin, double xmax, double dx,
    double a0, double ac, double f0,
    int order, int flat, double mindata,
    double derm, double derp)
{
  alged_t *al;
  int i;
  
  xnew(al, 1);
  al->xmin = xmin;
  al->dx = dx; /* interval size */
  al->n = (int)((xmax - xmin)/dx + .5); /* number of intervals */
  al->xmax = al->xmin + al->n * al->dx;
  al->order = order;
  al->flat = flat;
  al->mindata = mindata;
  al->derm = derm;
  al->derp = derp;
  xnew(al->f, al->n + 1);
  xnew(al->cc, al->n + 1);
  xnew(al->e2, al->n + 1);
  for (i = 0; i <= al->n; i++) {
    al->f[i] = f0;
    al->cc[i] = 0.;
    al->e2[i] = 0.;
  }
  al->a0 = a0;
  al->ac = ac;
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

/* return the proper upating magnitude: alpha */
INLINE double alged_getalpha(const alged_t *al, int i)
{
  return dblmin(al->a0, al->ac/al->cc[i]);
}

/* return the correction: (-1/2) d < e^2 > / dx 
 * the updating to the force stops at the fixed point:
 *    < dx + corr. > = 0
 * the mean force f = d (log rho) / dx is updated as
 *   f += alpha (dx + corr.)       */
INLINE double alged_getcorr1(const alged_t *al, int i)
{
  int im = i - 1, ip = i + 1;
  double e2o, e2n;
  
  if (im < 0) {
    /* an artifically negative `f' makes more negative
     * which encourages a positive `dx' to get back in range */
    return -al->derm;
  } else if (ip >= al->n) {
    return al->derp;
  } else {
    if (al->cc[im] < al->mindata || al->cc[ip] < al->mindata)
      return 0;
    e2o = al->e2[im]/al->cc[im];
    e2n = al->e2[ip]/al->cc[ip];
    return -0.5f * (e2n - e2o) / (2. * al->dx);
  }
}

#define alged_dh alged_dh0

/* return the F difference zeroth order */
INLINE double alged_dh0(const alged_t *al, double xn, double xo)
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

/* return acceptance probabilities */
static double alged_getacc(alged_t *al, double x1, double x0,
    double *dv, double *acc0)
{
  double acc1;

  *dv = alged_dh0(al, x1, x0);
  *acc0 = (dv <= 0 || rnd0() < exp(-dv));
  acc1 = *acc0;
  return acc1;
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

