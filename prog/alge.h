#ifndef ALGE_H__
#define ALGE_H__

typedef struct {
  int xmin, xmax, dx;
  int n;
  int flat; /* try to make histogram flat */
  double *dh; /* dH/dE */
  double *cc, *e2; /* histogram, sum of e^2 */
  double a0, ac; /* alpha */
  double mindata; /* minimal # of data points for the correction formula */
  double derm, derp; /* converging factors at the two boundaries */
} alge_t;

static alge_t *alge_open(int xmin, int xmax, int dx, double a0, double ac,
    double bet0, int flat, double mindata, double derm, double derp)
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
    printf("Warning xmax %d - xmin %d is not a multiple of dx %d\n",
      xmax, xmin, dx);
  }
  al->flat = flat;
  al->mindata = mindata;
  al->derm = derm;
  al->derp = derp;
  xnew(al->dh, al->n + 1);
  xnew(al->cc, al->n + 1);
  xnew(al->e2, al->n + 1);
  for (i = 0; i <= al->n; i++) {
    al->dh[i] = bet0;
    al->cc[i] = 0.;
    al->e2[i] = 0.;
  }
  al->a0 = a0;
  al->ac = ac;
  return al;
}

static void alge_close(alge_t *al)
{
  free(al->dh);
  free(al->cc);
  free(al->e2);
  free(al);
}

/* return the energy index */
/*
INLINE int alge_getid(const alge_t *al, int x)
{
  return (x - al->xmin)/al->dx;
}
*/

/* return the energy index, extended */
INLINE int alge_getidx(const alge_t *al, int x)
{
  if (x < al->xmin) return 0;
  else if (x > al->xmax) return al->n - 1;
  else return (x - al->xmin)/al->dx;
}

/* return the proper alpha */
INLINE double alge_getalpha(const alge_t *al, int i)
{
  return dblmin(al->a0, al->ac/al->cc[i]);
}

/* return the correction term (deprecated) */
/*
INLINE double alge_getcorr(const alge_t *al, int i)
{
  int im = i - 1, ip = i + 1;
  double e2o, e2n;
  
  if (im < 0 || ip >= al->n || al->cc[im] < al->mindata || al->cc[ip] < al->mindata)
    return 0;
  e2o = al->e2[im]/al->cc[im];
  e2n = al->e2[ip]/al->cc[ip];
  return -0.5f * (e2n - e2o) / (2. * al->dx);
}
*/

/* return the correction term */
INLINE double alge_getcorr1(const alge_t *al, int i)
{
  int im = i - 1, ip = i + 1;
  double e2o, e2n;
  
  if (im < 0) {
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

/* return the F difference zeroth order */
static double alge_dh0(const alge_t *al, int en, int eo)
{
  int ien, ieo, ie, sgn = 1;
  double dh = 0.;
  
  if (eo == en) return 0.;
  if (en < al->xmin) {
    dh += (en - al->xmin)*al->dh[0];
    en = al->xmin;
  } else if (en >= al->xmax) {
    dh += (en - al->xmax + 1)*al->dh[al->n - 1];
    en = al->xmax - 1;
  }
  if (eo == en) return dh;
  if (eo > en) { /* ensure eo < en */
    sgn = eo, eo = en, en = sgn;
    sgn = -1;
  }
  ieo = (eo - al->xmin)/al->dx;
  ien = (en - al->xmin)/al->dx;
  if (ieo == ien) { /* within a bin */
    dh += sgn*(en - eo)*al->dh[ieo];
  } else { /* cross several bins */
    dh += sgn*(al->xmin + (ieo+1)*al->dx - eo)*al->dh[ieo];
    dh += sgn*(en - al->xmin - ien*al->dx)*al->dh[ien];
    for (ie = ieo + 1; ie < ien; ie++)
      dh += sgn*al->dx*al->dh[ie];
  }
  return dh;
}

/* save dh/de file */
static int alge_save(alge_t *al, const char *fn)
{
  FILE *fp;
  int i;
  double lng = 0., cc, e2, dh, sc;
  
  xfopen(fp, fn, "w", return -1);
 
  for (sc = 0, i = 0; i < al->n; i++)
    sc += al->cc[i];
  sc = 1.0/(al->dx * sc);
  
  fprintf(fp, "# %d %d %d\n", al->n, al->xmin, al->dx);
  for (i = 0; i < al->n; i++) {
    cc = e2 = dh = 0;
    if (i < al->n) {
      cc = al->cc[i];
      if (cc > 0.0) e2 = al->e2[i]/cc;
      dh = al->dh[i];
    }
    fprintf(fp, "%d %.6f %.6f %g %.6f %g\n", 
      al->xmin + i * al->dx, dh, lng, cc, e2, cc * sc);
    lng += al->dh[i] * al->dx;
  }
  fclose(fp);
  return 0;
}

#endif
