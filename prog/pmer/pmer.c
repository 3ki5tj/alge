/* 2D distribution on 7-mer */
#define ZCOM_PICK
#define ZCOM_ARGOPT
#define ZCOM_AV
#define ZCOM_MD
#define ZCOM_HIST
#include "zcom.h"
#include "alged2.h"
#include "pch.h"

real tp = 1.f;
int nequil  = 10000;
int nsteps  = 100000000;
int seglen  = 100;
int nevery  = 50000;
int nreport = 5000000;
real mddt = 0.002f;
char *fnout = "dih.xy";
char *fnhis = "xy.his";

/* polymer model */
int npoly = 7;
real r0 = 1.f;
real kb = 10.f;
real ang0 = 109.4712206344907; /* acos(-1.0/3) in degrees */
real ka = 1.f;
real sig = 1.f;
real eps = 1.f;

/* handle input arguments */
static void doargs(int argc, char **argv)
{
  argopt_t *ao = argopt_open(0);
  argopt_add(ao, "-T", "%r", &tp,    "temperature");
  argopt_add(ao, "-0", "%d", &nequil, "number of equilibration steps");
  argopt_add(ao, "-1", "%d", &nsteps, "number of simulation steps");
  argopt_add(ao, "-l", "%d", &seglen, "the number of steps to be treated as a perturbation");
  argopt_add(ao, "-d", "%r", &mddt,   "molecular dynamics");
  argopt_add(ao, "-o", NULL, &fnout,  "output file");
  argopt_add(ao, "-H", NULL, &fnhis,  "histogram file");
  argopt_add(ao, "-n", "%d", &npoly, "# of particles in the chain");
  argopt_add(ao, "--r0", "%r", &r0,  "reference distance");
  argopt_add(ao, "--kb", "%r", &kb,    "kb");
  argopt_add(ao, "--a0", "%r", &ang0,  "reference angle in degrees");
  argopt_add(ao, "--ka", "%r", &ka,    "ka");
  argopt_add(ao, "--sig", "%r", &sig, "sig");
  argopt_add(ao, "--eps", "%r", &eps, "eps");
  argopt_add(ao, "--every",   "%d", &nevery,  "interval of printing messages");
  argopt_add(ao, "--report",  "%d", &nreport, "interval of saving data");
  argopt_addhelp(ao, "-h");
  argopt_parse(ao, argc, argv);

  argopt_dump(ao);
  argopt_close(ao);

  ang0 *= M_PI/180.f;
}

/* wrap coordinates to (-pi, pi) */
INLINE double WRAP(double x) {
  while (x < -M_PI) x += 2*M_PI;
  while (x >= M_PI) x -= 2*M_PI;
  return x;
}

/* return the difference */
INLINE double DIFF(double x, double y)
{
  double dx = x - y;

  while (dx > M_PI) dx -= 2 * M_PI;
  while (dx < -M_PI) dx += 2 * M_PI;
  return dx;
}

/* return the dihedral of the middle dihedrals */
static void pch_getdihf(rv3_t *x, real *phi, real *psi, rv3_t *fx, rv3_t *fy)
{
/*
  *phi = rv3_dih(x[0], x[1], x[2], x[3], fx[0], fx[1], fx[2], fx[3]);
  *psi = rv3_dih(x[1], x[2], x[3], x[4], fy[0], fy[1], fy[2], fy[3]);
*/
  dihcalc_t dc[2];
  int i;
  
  memset(dc, 0, sizeof(dc[0]) * 2);
  dc[0].szreal = dc[1].szreal = sizeof(real);
  *phi = rv3_calcdih(dc, x[0], x[1], x[2], x[3], DIH_FOUR|DIH_GRAD);
  for (i = 0; i < 4; i++) rv3_copy(fx[i], dc[0].g[i]);
  *psi = rv3_calcdih(dc+1, x[1], x[2], x[3], x[4], DIH_FOUR|DIH_GRAD);
  for (i = 0; i < 4; i++) rv3_copy(fy[i], dc[1].g[i]);
}

/* velocity verlet */
INLINE int pch_vv(pch_t *p, real fscal, real dt,
    real *phi, real *psi, ad2_t *al)
{
  int i, id, n = p->n, idih0 = (p->n - 1)/2 - 2;
  real dtf = dt * .5f * fscal, fx, fy;
  rv3_t gx[4], gy[4];

  for (i = 0; i < n; i++) {
    rv3_sinc(p->v[i], p->f[i], dtf);
    rv3_sinc(p->x[i], p->v[i], dt);
  }
  p->epot = pch_force(p, p->x, p->f);
  
  /* compute the dihedral and the gradients */
  pch_getdihf(p->x + idih0, phi, psi, gx, gy);
  /* get the amplitude of the dihedral force */
  id = ad2_getid(al, *phi, *psi);
  fx = al->fx[id];
  fy = al->fy[id];
  /* add the dihedral force */
  for (i = 0; i < 4; i++) {
    rv3_sinc(p->f[idih0 + i], gx[i], fx);
    rv3_sinc(p->f[idih0 + 1 + i], gy[i], fy);
  }
  
  for (i = 0; i < n; i++) {
    rv3_sinc(p->v[i], p->f[i], dtf);
  }
  p->ekin = md_ekin((real *) p->v, n * 3, p->dof, NULL);
  return 0;
}

/* run md simulation */
static int run(void)
{
  int t, id;
  real phi, psi;
  rv3_t gx[4], gy[4];
  double x0 = 0, y0 = 0, x1 = 0, y1 = 0, dx, dy, alf = 0;
  pch_t *pch;
  ad2_t *al;
  hist2_t *hs;

  pch = pch_open(npoly, r0, kb, ang0, ka, sig, eps);
  al = ad2_open(-M_PI, M_PI, M_PI/9.999, -M_PI, M_PI, M_PI/9.999,
     0.001, 1.0, 0.0, 0.0);
  hs = hs2_opensqr1(-M_PI, M_PI, M_PI/9.999);

  pch->epot = pch_force(pch, pch->x, pch->f);
  pch_getdihf(pch->x, &phi, &psi, gx, gy);
  id = ad2_getid(al, phi, psi);

  for (t = 1; t <= nsteps; t++) {
    pch_vv(pch, 1.f, mddt, &phi, &psi, al);
    hs2_add1ez(hs, phi, psi, 0);
    //printf("t %d, phi %g, psi %g\n", t, phi, psi);// getchar();

    /* register */
    if (t % seglen == 0) {
      static const double fcmax = 1000000000.0;

      x1 = phi;
      y1 = psi;
      dx = DIFF(x1, x0);
      dy = DIFF(y1, y0);
      ad2_add(al, id, dx, dy);
/*
      ad2_getcorr(al, id, &delx, &dely);
      dx += delx;
      dy += dely;
*/
      if (fabs(dx) > 2 || fabs(dy) > 2) {
        //printf("large dx %g, dy %g\n", dx, dy);
      }
      alf = 0.02;
      al->fx[id] = dblconfine(al->fx[id] + dx * alf, -fcmax, fcmax);
      al->fy[id] = dblconfine(al->fy[id] + dy * alf, -fcmax, fcmax);

      /* set the new start point */
      x0 = x1;
      y0 = y1;
      id = ad2_getid(al, x0, y0);

      if (t % nevery == 0) {
        printf("t %d, phi %g, psi %g\n", t, phi, psi);
      }
      if (t % nreport == 0) {
        ad2_save(al, fnout);
        pch_writepos(pch, pch->x, pch->v, "pch.pos");
      }
    }
  }
  ad2_close(al);
  hs2_save(hs, "xy.his", 0);
  pch_close(pch);
  return 0;
}

int main(int argc, char **argv)
{
  doargs(argc, argv);
  run();
  return 0;
}
