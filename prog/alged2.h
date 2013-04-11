/* two dimensional mean force from perturbation
 * assuming periodic structure */

typedef struct {
  double xmin, xmax, dx;
  double ymin, ymax, dy;
  int n, m;
  double fx0, fy0;
  double *fx, *fy;
  avn_t **sxy; /* various correlation functions */
  double a0, ac; /* alpha */
} ad2_t;

static ad2_t *ad2_open(double xmin, double xmax, double dx,
    double ymin, double ymax, double dy,
    double a0, double ac, double fx0, double fy0)
{
  ad2_t *al;
  int i, nm;
  
  xnew(al, 1);
  al->xmin = xmin;
  al->dx = dx; /* interval size */
  al->n = (int)((xmax - xmin)/dx + .9999); /* number of n intervals */
  al->xmax = al->xmin + al->n * al->dx;
  al->ymin = ymin;
  al->dy = dy;
  al->m = (int)((ymax - ymin)/dy + .9999); /* number of m intervals */
  al->ymax = al->ymin + al->m * al->dy;
  al->fx0 = fx0;
  al->fy0 = fy0;
  nm = al->n * al->m;
  xnew(al->fx, nm + 1);
  xnew(al->fy, nm + 1);
  xnew(al->sxy, nm + 1);
  for (i = 0; i <= nm; i++) {
    al->fx[i] = fx0;
    al->fy[i] = fy0;
    al->sxy[i] = avn_open(2);
  }
  al->a0 = a0;
  al->ac = ac;
  return al;
}

static void ad2_close(ad2_t *al)
{
  int i;
  
  free(al->fx);
  free(al->fy);
  for (i = 0; i < al->n * al->m + 1; i++) {
    avn_close( al->sxy[i] );
  }
  free(al->sxy);
  free(al);
}

/* return the energy index */
INLINE int ad2_getid(const ad2_t *al, double x, double y)
{
  int ix, iy;
  
  if (x < al->xmin || x >= al->xmax || y < al->ymin || y >= al->ymax) {
    fprintf(stderr, "bad index, x %g, y %g\n", x, y);
    return -1;
  }
  ix = (int) ( (x - al->xmin)/al->dx ) % al->n;
  iy = (int) ( (y - al->ymin)/al->dy ) % al->m;
  return ix * al->m + iy;
}

/* add an entry */
INLINE void ad2_add(const ad2_t *al, int id, double dx, double dy)
{
  avn_addw(al->sxy[id], 1., dx, dy);
}

/* return the current f, zeroth order */
INLINE void ad2_getf(const ad2_t *al, double x, double y,
    double *fx, double *fy)
{
  int id;
  *fx = *fy = 0;
  id = ad2_getid(al, x, y);
  if (id >= 0) {
    *fx = al->fx[id];
    *fy = al->fy[id];
  }
}

#define MINDATA 1000.0

INLINE int ad2_getcorr(const ad2_t *al, int id, double *delx, double *dely)
{
  int ix, iy, idx, idy;
  
  ix = id / al->m; /* the outer dimension */
  iy = id % al->m;
  /* idx and idy */
  idx = ((ix + 1) % al->n) * al->m + iy;
  idy = ix * al->m + (iy + 1) % al->m;
  *delx = *dely = 0;
  if (al->sxy[id]->s > MINDATA 
      && al->sxy[idx]->s > MINDATA
      && al->sxy[idy]->s > MINDATA) {
    /* d < ex^2 > / dX */
    *delx = (avn_getvar(al->sxy[id], 0, 0)
           - avn_getvar(al->sxy[idx], 0, 0)) / al->dx;
    /* d < ex ey > / d Y */
    *delx += (avn_getvar(al->sxy[id], 0, 1)
            - avn_getvar(al->sxy[idy], 0, 1)) / al->dy;
    /* d < ex ey > / d x */
    *dely = (avn_getvar(al->sxy[id], 0, 1)
           - avn_getvar(al->sxy[idx], 0, 1)) / al->dx;
    /* d < ey^2 > / d y */
    *dely = (avn_getvar(al->sxy[id], 1, 1)
           - avn_getvar(al->sxy[idy], 1, 1)) / al->dy;
    return 0;
  } else {
    return 1;
  }
} 

/* return the proper upating magnitude: alpha */
INLINE double ad2_getalpha(const ad2_t *al, int id)
{
  return dblmin(al->a0, al->ac/al->sxy[id]->s);
}

/* save dh/de file */
static int ad2_save(ad2_t *al, const char *fn)
{
  FILE *fp;
  int i, j, id;
  double xx, xy, yy, cc, sc;
  
  xfopen(fp, fn, "w", return -1);
  fprintf(fp, "# %d %g %g %d %g %g\n",
    al->n, al->xmin, al->dx, al->m, al->ymin, al->dy);
  
  /* compute the normalization factor */
  for (cc = 1e-6, id = 0; id < al->n * al->m; id++)
    cc += al->sxy[id]->s;
  sc = 1.0/(cc * al->dx * al->dy);
  
  for (i = 0; i < al->n; i++) {
    for (j = 0; j < al->m; j++) {
      id = i * al->m + j;
      cc = al->sxy[id]->s;
      xx = avn_getvar(al->sxy[id], 0, 0);
      xy = avn_getvar(al->sxy[id], 0, 1);
      yy = avn_getvar(al->sxy[id], 1, 1);
      fprintf(fp, "%g %g %g %g %.6f %.6f %.6f %.6f %.6f\n", 
        al->xmin + i * al->dx, al->ymin + j * al->dy, 
        cc, cc * sc, al->fx[id], al->fy[id], /* 6 parameters */
        xx, xy, yy);
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
  return 0;
}

