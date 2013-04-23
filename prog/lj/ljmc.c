/* multicaonical Lennard-Jones Monte Carlo simulation
 * approximate Monte Carlo to mimic molecular dynamics */
#define ZCOM_PICK
#define ZCOM_LJ
#define ZCOM_AV
#define ZCOM_ARGOPT
#include "zcom.h"
#include "alged.h"

#define D 3

int N = 108;
real rho = 0.7f;
real rcdef = 2.5f; /* cut-off distance */
real tpstat = 1.0f; /* temperature */
int nsteps = 100000000;
int nequil = 10000;
int nevery  = 100000;  /* print message every this number of steps */
int nreport = 10000000; /* save data every the number of steps */

real mcamp = 0.2f;

/* algorithm E stuff */
double epmin = -550, epmax = -350, epdel = 5;
int seglen = 10; /* segment length for a perturbation */
double alf0 = 0.1, alfc = 1.0;
int boundary = 1; /* 0: smooth boundary, 1: reflective; the former requires
    a small `alf0' < 0.01, the latter is more stable, but has boundary artifacts */
double tpmin = 1., tpmax = 3.; /* temperature of the two outer boundaries,
    used only in the reflective (1) boundary condition */
double delmax = 10.0;
double mfmax = 100.0; /* maximal magnitude of 1/tp */
double mfmin = 0.05; /* minimal magnitude of 1/tp */

char *fnout = "lj.e";
char *fnhis = "ep.his";

/* handle input arguments */
static void doargs(int argc, char **argv)
{
  argopt_t *ao = argopt_open(0);
  argopt_add(ao, "-n", "%d",  &N,         "number of particles");
  argopt_add(ao, "-T", "%r",  &tpstat,    "thermostat temperature");
  argopt_add(ao, "-r", "%r",  &rho,       "density");
  argopt_add(ao, "-c", "%r",  &rcdef,     "cutoff distance");
  argopt_add(ao, "-0", "%d",  &nequil,    "number of equilibration steps");
  argopt_add(ao, "-1", "%d",  &nsteps,    "number of simulation steps");

  argopt_add(ao, "-l", "%d",  &seglen,    "the number of steps to be treated as a perturbation");
  argopt_add(ao, "-b", "%d",  &boundary,  "boundary condition, 0: smooth, 1: reflective (hard)");

  argopt_add(ao, "-a", "%r",  &mcamp,     "Monte Carlo move size");
  argopt_add(ao, "--a0",  "%lf", &alf0,   "initial updating magnitude");
  argopt_add(ao, "--ac",  "%lf", &alfc,   "updating magnitude");
  argopt_add(ao, "--u0",  "%lf", &epmin,  "minimal potential energy");
  argopt_add(ao, "--u1",  "%lf", &epmax,  "maximal potential energy");
  argopt_add(ao, "--du",  "%lf", &epdel,  "potential energy bin size");
  argopt_add(ao, "--T0",  "%lf", &tpmin,  "temperature of the left boundary");
  argopt_add(ao, "--T1",  "%lf", &tpmax,  "temperature of the right boundary");
  argopt_add(ao, "-o", NULL, &fnout,      "output file");
  argopt_add(ao, "-H", NULL, &fnhis,      "histogram file");
  argopt_add(ao, "--every",   "%d", &nevery,  "interval of printing messages");
  argopt_add(ao, "--report",  "%d", &nreport, "interval of saving data");
  argopt_addhelp(ao, "-h");
  argopt_parse(ao, argc, argv);

  /* by default, set `tpmin' and `tpmax' to `tpstat' */
  if (tpmin <= 0) tpmin = tpstat;
  if (tpmax <= 0) tpmax = tpstat;

  argopt_dump(ao);
  argopt_close(ao);
}

/* multicanoical Monte Carlo simulation */
static void domc(lj_t *lj)
{
  int t;
  alged_t *al;
  hist_t *hs;
  double k, u0 = 0, u1 = 0, du = 0, alf = 0, ave2 = 0;
  double macc = 0, mtot = 1e-6;

  al = alged_open(epmin, epmax, epdel, 1/tpmin, 1/tpmax);
  hs = hs_open1(-7.*lj->n, 0, 1.0);

  /* try to equilibrate the system by running MD at tpstat */
  for (t = 1; t <= nequil; t++) {
    lj_metro(lj, mcamp, 1.f/tpstat);
    if (lj->epot >= epmin && lj->epot < epmax)
      break;
  }
  die_if (lj->epot < epmin || lj->epot >= epmax,
    "too hard to equilibrate the system, epot %g\n", lj->epot);
  printf("equilibrated at t %d, epot %g\n", t, lj->epot);

  u0 = lj->epot;

  /* real simulation */
  for (t = 1; t <= nsteps; t++) {
    k = tpstat * alged_getf(al, lj->epot);
    if (boundary == 1) {
      if (lj->epot < epmin) k = tpstat / tpmin;
      if (lj->epot >= epmax) k = tpstat / tpmax;
    }
    k = dblmax(k, 0.05); /* the minimal scaling */

    mtot += 1;
    macc += lj_metro(lj, mcamp, k/tpstat);
    hs_add1ez(hs, lj->epot, 0);

    if (t % seglen == 0) {
      u1 = lj->epot;
      du = u1 - u0;
      alged_fupdate(al, u0, du, alf0, alfc, &alf,
          delmax, &ave2, mfmin, mfmax);
      u0 = u1;
    }

    if (t % nevery == 0) {
      printf("t %g, ep %.2f, du %.3f, k %g, alf %g, <e2> %g, acc %2.0f%%\n",
        1.*t, lj->epot, du, k, alf, ave2, 100*macc/mtot);

      if (t % nreport == 0) {
        alged_save(al, fnout);
        hs_save(hs, fnhis, HIST_ADDAHALF);
      }
    }
  }
  alged_close(al);
}

int main(int argc, char **argv)
{
  lj_t *lj;

  doargs(argc, argv);
  lj = lj_open(N, D, rho, rcdef);

  domc(lj);

  lj_close(lj);
  return 0;
}
