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
int seglen  = 1;
int nevery  = 50000;
int nreport = 5000000;
real mcamp = 0.3f;
char *fnout = "dih.xy";
char *fnhis = "xy.his";

/* polymer model */
int npoly = 7;
real r0 = 1.f;
real kb = 100.f;
real ang0 = 109.4712206344907; /* acos(-1.0/3) in degrees */
real ka = 10.f;
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
  argopt_add(ao, "-a", "%r", &mcamp,  "Monte Carlo amplitude");
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
static void pch_getdih(rv3_t *x, real *phi, real *psi)
{
  *phi = rv3_dih(x[0], x[1], x[2], x[3], NULL, NULL, NULL, NULL);
  *psi = rv3_dih(x[1], x[2], x[3], x[4], NULL, NULL, NULL, NULL);
}

/* metroplis algorithm */
INLINE int pch_metro(pch_t *p, real amp, real bet,
    real *phi, real *psi, ad2_t *al)
{
  int i, j, id, n = p->n, idih0 = (p->n - 1)/2 - 2;
  real epot1, dep, fx, fy;
  real phi0, psi0, phi1, psi1;

  for (i = 0; i < n; i++) {
    for (j = 0; j < 3; j++) {
      p->v[i][j] = p->x[i][j];
    }
  }
  i = (int) (n * rnd0());
  for (j = 0; j < 3; j++) {
    p->v[i][j] += amp * (2 * rnd0() - 1);
  }

  epot1 = pch_force(p, p->v, NULL);

  dep = bet * (epot1 - p->epot);

  /* compute the dihedral and the gradients */
  pch_getdih(p->x + idih0, &phi0, &psi0);
  pch_getdih(p->v + idih0, &phi1, &psi1);

  /* get the amplitude of the dihedral force */
  id = ad2_getid(al, phi0, psi0);
  fx = al->fx[id];
  fy = al->fy[id];

  dep += fx * (phi1 - phi0) + fy * (psi1 - psi0);
  if (dep < 0 || rnd0() < exp(-dep)) {
    for (i = 0; i < n; i++)
      rv3_copy(p->x[i], p->v[i]);
    md_shiftcom3d(p->x, n);
    p->epot = epot1;
    *phi = phi1;
    *psi = psi1;
    return 1;
  } else {
    *phi = phi0;
    *psi = psi0;
    return 0;
  }
}


/* run md simulation */
static int run(void)
{
  int t, id, etot = 0, eacc = 0;
  real phi, psi;
  double x0 = 0, y0 = 0, x1 = 0, y1 = 0, dx, dy, alf = 0;
  pch_t *pch;
  ad2_t *al;
  hist2_t *hs;

  pch = pch_open(npoly, r0, kb, ang0, ka, sig, eps);
  al = ad2_open(-M_PI, M_PI, M_PI/9.999, -M_PI, M_PI, M_PI/9.999,
     0.001, 1.0, 0.0, 0.0);
  hs = hs2_opensqr1(-M_PI, M_PI, M_PI/9.999);

  pch->epot = pch_force(pch, pch->x, pch->f);
  pch_getdih(pch->x, &phi, &psi);
  id = ad2_getid(al, phi, psi);

  for (t = 1; t <= nsteps; t++) {
    etot += 1;
    eacc += pch_metro(pch, mcamp, 1.f/tp, &phi, &psi, al);
    hs2_add1ez(hs, phi, psi, 0);
    //printf("t %d, phi %g, psi %g\n", t, phi, psi);// getchar();

    /* register */
    if (t % seglen == 0) {
      static const double fcmax = 1000.0;

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
      alf = 0.1;
      al->fx[id] = dblconfine(al->fx[id] + dx * alf, -fcmax, fcmax);
      al->fy[id] = dblconfine(al->fy[id] + dy * alf, -fcmax, fcmax);

      /* set the new start point */
      x0 = x1;
      y0 = y1;
      id = ad2_getid(al, x0, y0);

      if (t % nevery == 0) {
        printf("t %d, phi %g, psi %g, acc %g\n", t, phi, psi, 1.*eacc/etot);
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
