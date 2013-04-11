/* polymer chain */
#ifndef PCH_H__
#define PCH_H__

typedef struct pch_t {
  int n; /* number of particles */
  int dof;
  rv3_t *x, *v, *f;
  real r0, kb, ang0, ka, sig2, eps;
  real epot, ekin;
} pch_t;

INLINE pch_t *pch_open(int n, real r0, real kb, real ang0, real ka,
    real sig, real eps)
{
  pch_t *p;
  int i;

  xnew(p, 1);
  p->n = n;
  p->dof = n * 3 - 6;
  xnew(p->x, n);
  xnew(p->v, n);
  xnew(p->f, n);
  for (i = 0; i < n; i++) {
    rv3_make(p->x[i], i + 0.1 * rnd0(), 0.1 * rnd0(), 0.1 * rnd0());
    rv3_smul(p->x[i], r0);
  }
  p->r0 = r0;
  p->kb = kb;
  p->ang0 = ang0;
  p->ka = ka;
  p->sig2 = sig * sig;
  p->eps = eps;
  return p;
}

INLINE void pch_close(pch_t *p)
{
  free(p->x);
  free(p->v);
  free(p->f);
  free(p);
}

/* compute the force and potential energy */
INLINE real pch_force(pch_t *p, rv3_t *x, rv3_t *f)
{
  real r, dr, epb, epa, epnb, amp, ang, r2, invr2, invr6;
  rv3_t dx, g[3];
  int i, j, n = p->n;

  if (f != NULL) {
    for (i = 0; i < n; i++)
      rv3_zero(f[i]);
  }

  /* bonded forces */
  for (epb = 0, i = 0; i < n - 1; i++) {
    rv3_diff(dx, x[i], x[i+1]);
    r = rv3_norm(dx);
    dr = r - p->r0;
    epb += .5f * p->kb * dr * dr;
    amp = p->kb * dr / r;
    if (f != NULL) {
      rv3_sinc(f[i],   dx, -amp);
      rv3_sinc(f[i+1], dx,  amp);
    }
  }

  /* angle forces */
  for (epa = 0, i = 1; i < n - 1; i++) {
    ang = rv3_ang(x[i-1], x[i], x[i+1], g[0], g[1], g[2]);
    dr = ang - p->ang0;
    epa += .5f * p->ka * dr * dr;
    amp = -p->ka * dr;
    if (f != NULL) {
      rv3_sinc(f[i-1], g[0], amp);
      rv3_sinc(f[i],   g[1], amp);
      rv3_sinc(f[i+1], g[2], amp);
    }
  }

  /* nonbonded */
  for (epnb = 0, i = 0; i < n - 3; i++) {
    for (j = i + 3; j < n; j++) {
      rv3_diff(dx, x[i], x[j]);
      r2  = rv3_sqr(dx);
      invr2 = p->sig2/r2;
      invr6 = invr2 * invr2 * invr2;
      amp = p->eps * invr6 * (48.f * invr6 - 24.f) / r2;
      epnb += 4 * p->eps * invr6 * (invr6 - 1);
      if (f != NULL) {
        rv3_sinc(f[i], dx,  amp);
        rv3_sinc(f[j], dx, -amp);
      }
    }
  }

  return epb + epa + epnb;
}

/* write position/velocity file */
INLINE int pch_writepos(pch_t *pch, rv3_t *x, rv3_t *v, const char *fn)
{
  FILE *fp;
  int i, n = pch->n;

  if (fn == NULL) fn = "pch.pos";
  xfopen(fp, fn, "w", return -1);

  fprintf(fp, "# %d %d\n", n, (v != NULL));
  for (i = 0; i < n; i++) {
    fprintf(fp, "%16.12f %16.12f %16.12f ", x[i][0], x[i][1], x[i][2]);
    if (v)
      fprintf(fp, "%16.12f %16.12f %16.12f ", v[i][0], v[i][1], v[i][2]);
    fprintf(fp, "\n");
  }
  fclose(fp);
  return 0;
}

/* read position/velocity file */
INLINE int pch_readpos(pch_t *pch, rv3_t *x, rv3_t *v, const char *fn)
{
  char s[1024], *p;
  FILE *fp;
  int i, hasv = 0, next, n = pch->n;
  const char *fmt;
  real vtmp[3], *vi;

  if (fn == NULL) fn = "pch.pos";
  xfopen(fp, fn, "r", return -1);

  if (fgets(s, sizeof s, fp) == NULL || s[0] != '#') {
    fprintf(stderr, "Warning: %s has no information line\n", fn);
    rewind(fp);
  } else {
    if (2 != sscanf(s+1, "%d%d", &i, &hasv) || i != n ) {
      fprintf(stderr, "first line is corrupted:\n%s", s);
      goto ERR;
    }
  }

  if (sizeof(double) == sizeof(real))
    fmt = "%lf%lf%lf%n";
  else
    fmt = "%f%f%f%n";
  for (i = 0; i < n; i++) {
    fgets(s, sizeof s, fp);
    if (strlen(s) < 10) goto ERR;
    if (3 != sscanf(s, fmt, &x[i][0], &x[i][1], &x[i][2], &next)) {
      fprintf(stderr, "cannot read x, i = %d\n", i);
      goto ERR;
    }
    p = s+next;
    if (hasv) {
      vi = (v != NULL) ? v[i] : vtmp;
      if (3 != sscanf(p, fmt, &vi[0], &vi[1], &vi[2], &next)) {
        fprintf(stderr, "cannot read v, i = %d\n", i);
        goto ERR;
      }
    }
  }
  fclose(fp);
  return 0;

ERR:
  fprintf(stderr, "position file [%s] appears to be broken on line %d!\n%s\n", fn, i, s);
  fclose(fp);
  return -1;
}



#endif
