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

double mindata = 1000.f;
/* boundary limiting strength, larger causes better confinement */
double derm = 1, derp = 2;

/* algorithm E stuff */
int seglen = 5; /* segment length for a perturbation */
double epmin = -500, epmax = -300, epdel = 5;
int flathis = 1;
double alfmax = 0.001, alfc = 0.3;

char *fnout = "lj.e";
char *fnhis = "epot.his";

/* handle input arguments */
static void doargs(int argc, char **argv)
{
  argopt_t *ao = argopt_open(0);
  argopt_add(ao, "-n", "%d", &N,        "number of particles");
  argopt_add(ao, "-T", "%r", &tp0,      "temperature");
  argopt_add(ao, "-r", "%r", &rho,      "density");
  argopt_add(ao, "-c", "%r", &rcdef,    "cutoff distance");
  argopt_add(ao, "-0", "%d", &nequil,   "number of equilibration steps");
  argopt_add(ao, "-1", "%d", &nsteps,   "number of simulation steps");
  argopt_add(ao, "-e", "%d", &nevery,   "interval of computing temperatures");
  argopt_add(ao, "-l", "%d", &seglen,   "the number of steps to be treated as a perturbation");
  argopt_add(ao, "-d", "%r", &mddt,     "time step for molecular dynamics");
  argopt_add(ao, "-q", "%r", &thermdt,  "thermostat time step");
  argopt_add(ao, "-9", "%lf",&mindata,  "minimal number of data points");
  argopt_add(ao, "--a0", "%lf", &alfmax,"initial updating magnitude");
  argopt_add(ao, "--ac", "%lf", &alfc,  "updating magnitude");
  argopt_add(ao, "--km", "%lf", &derm,  "correction for x < xmin");
  argopt_add(ao, "--kp", "%lf", &derp,  "correction for x > xmax");
  argopt_add(ao, "-o", NULL, &fnout,    "output file");
  argopt_add(ao, "-H", NULL, &fnhis,    "histogram file");  
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
  int ie, t;
  alged_t *al;
  hist_t *hs;
  double k, u0, u1, du = 0, duc = 0, alf = 0;

  al = alged_open(epmin, epmax, epdel, alfmax, alfc,
    1.0/tp0, 0, flathis, mindata, derm, derp);
  hs = hs_open(1, -800, 0, 1.0);

  /* try to equilibrate the system by running MD at tp0 */
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
  ie = alged_getidx(al, u0);

  /* real simulation */
  for (t = 1; t <= nsteps; t++) {
    k = alged_getf(al, lj->epots);

    lj_vvx(lj, k, mddt);
    lj_shiftcom(lj, lj->v);
    
    lj_vrescalex(lj, tp0, thermdt);
    hs_add1ez(hs, lj->epots, HIST_VERBOSE);

    if (t % seglen == 0) {
      u1 = lj->epots;
      du = u1 - u0;

      al->cc[ie] += 1.0;
      al->e2[ie] += du * du;
      alf = alged_getalpha(al, ie);

      duc = alged_getcorr1(al, ie);
      duc = dblconfine(duc, -.5 * fabs(du), .5 * fabs(du));
      du += duc;

      al->f[ie] = dblmax(al->f[ie] + alf * du, 0.001);

      /* set the new start point */
      u0 = u1;
      ie = alged_getidx(al, u0);
    }

    if (t % nevery == 0) {
      printf("t %d, ep %g, du %g, %g, k %g, ie %d, alf %g, ek %g\n",
        t, lj->epots/lj->n, du, duc, k, ie, alf, lj->ekin);

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
