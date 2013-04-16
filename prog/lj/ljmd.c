/* multicanonical Lennard-Jones molecular dynamics simulation */
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
real tp0 = 1.0f; /* temperature */
real mddt = 0.002f; /* time step for molecular dynamics */
real thermdt = 0.01f; /* thermostat step size */
int nsteps = 1000000;
int nequil = 10000;
int nevery = 1000;  /* print message every this number of steps */
int nreport = 100000; /* save data every this number of steps */

/* algorithm E stuff */
double epmin = -500, epmax = -300, epdel = 5;
int seglen = 5; /* segment length for a perturbation */
double alf0 = 0.1, alfc = 1.0; 
int boundary = 1; /* 0: smooth boundary, 1: reflective */
double delmax = 10.0;
double mfmax = 100.0; /* maximal magnitude of tp0/tp */

char *fnout = "lj.e";
char *fnhis = "ep.his";

/* handle input arguments */
static void doargs(int argc, char **argv)
{
  argopt_t *ao = argopt_open(0);
  argopt_add(ao, "-n", "%d",  &N,         "number of particles");
  argopt_add(ao, "-T", "%r",  &tp0,       "temperature");
  argopt_add(ao, "-r", "%r",  &rho,       "density");
  argopt_add(ao, "-c", "%r",  &rcdef,     "cutoff distance");
  argopt_add(ao, "-0", "%d",  &nequil,    "number of equilibration steps");
  argopt_add(ao, "-1", "%d",  &nsteps,    "number of simulation steps");
  argopt_add(ao, "-e", "%d",  &nevery,    "interval of computing temperatures");

  argopt_add(ao, "-l", "%d",  &seglen,    "the number of steps to be treated as a perturbation");
  argopt_add(ao, "-b", "%d",  &boundary,  "boundary condition, 0: smooth, 1: reflective (hard)");

  argopt_add(ao, "-d", "%r",  &mddt,      "time step for molecular dynamics");
  argopt_add(ao, "-q", "%r",  &thermdt,   "thermostat time step");
  argopt_add(ao, "--a0", "%lf", &alf0,    "initial updating magnitude");
  argopt_add(ao, "--ac", "%lf", &alfc,    "updating magnitude");
  argopt_add(ao, "-o", NULL, &fnout,      "output file");
  argopt_add(ao, "-H", NULL, &fnhis,      "histogram file");  
  argopt_add(ao, "--every",   "%d", &nevery,  "interval of printing messages");
  argopt_add(ao, "--report",  "%d", &nreport, "interval of saving data");
  argopt_addhelp(ao, "-h");
  argopt_parse(ao, argc, argv);

  argopt_dump(ao);
  argopt_close(ao);
}

/* multicaonical molecular dynamics simulation */
static void domd(lj_t *lj)
{
  int t;
  alged_t *al;
  hist_t *hs;
  double k, u0, u1, du = 0, alf = 0, ave2 = 0;

  al = alged_open(epmin, epmax, epdel, 1/tp0, 
      0 /* zeroth order mean force extrapolation */);
  hs = hs_open1(-800, 0, 1.0);

  /* equilibrate the system by regular MD at tp0
   * till the potential energy falls in (xmin, xmax) */
  for (t = 1; t <= nequil; t++) {
    lj_vv(lj, mddt);
    lj_shiftcom(lj, lj->v);
    lj_vrescalex(lj, tp0, thermdt);
    if (lj->epots > al->xmin && lj->epots < al->xmax)
      break;
  }
  die_if (lj->epots < al->xmin || lj->epots > al->xmax,
    "too hard to equilibrate the system, epot %g\n", lj->epots);
  printf("equilibrated at t %d, epot %g\n", t, lj->epots);

  /* Note: lj->epots may be replaced by lj->epot
   * but it may significantly change f */
  u0 = lj->epots;

  /* real simulation */
  for (t = 1; t <= nsteps; t++) {
    k = alged_getf(al, lj->epots);
    if (boundary == 1 && (lj->epots < epmin || lj->epots > epmax))
      k = 1.;
    k = dblmax(k, 0.05/tp0); /* the minimal scaling */

    lj_vvx(lj, k, mddt);
    lj_shiftcom(lj, lj->v);
    lj_vrescalex(lj, tp0, thermdt);
    hs_add1ez(hs, lj->epots, 0);

    if (t % seglen == 0) {
      u1 = lj->epots;
      du = u1 - u0;
      alged_fupdate(al, u0, du, alf0, alfc, &alf, 
          delmax, &ave2, 0, mfmax);
      u0 = u1; /* set the new start point */
    }

    if (t % nevery == 0) {
      printf("t %g, ep %.2f, du %+.3f, k %g, alf %g, e^2 %g\n",
        1.*t, lj->epots, du, k, alf, ave2);

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

  domd(lj);

  lj_close(lj);
  return 0;
}
