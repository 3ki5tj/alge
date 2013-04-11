/* multicaonical Lennard-Jones Monte Carlo simulation */
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
int nsteps = 100000000;
int nequil = 10000;
int nevery  = 100000;  /* print message every this number of steps */
int nreport = 10000000; /* save data every the number of steps */

real mcamp = 0.2f;
double mindata = 1000.f;

/* boundary limiting strength, larger causes better confinement */
double derm = 1, derp = 2;

/* algorithm E stuff */
int seglen = 10; /* segment length for a perturbation */
double epmin = -550, epmax = -350, epdel = 5;
int flathis = 1;
int forder = 0;
double alfmax = 0.001, alfc = 0.3;

char *fnout = "lj.e";
char *fnhis = "epot.his";

/* handle input arguments */
static void doargs(int argc, char **argv)
{
  argopt_t *ao = argopt_open(0);
  argopt_add(ao, "-n", "%d", &N,      "number of particles");
  argopt_add(ao, "-T", "%r", &tp0,    "temperature");
  argopt_add(ao, "-r", "%r", &rho,    "density");
  argopt_add(ao, "-c", "%r", &rcdef,  "cutoff distance");
  argopt_add(ao, "-0", "%d", &nequil, "number of equilibration steps");
  argopt_add(ao, "-1", "%d", &nsteps, "number of simulation steps");
  argopt_add(ao, "-l", "%d", &seglen, "the number of steps to be treated as a perturbation");
  argopt_add(ao, "-a", "%r", &mcamp,  "Monte Carlo move size");
  argopt_add(ao, "-q", "%lf", &mindata, "minimal number of data points");
  argopt_add(ao, "--a0", "%lf", &alfmax, "initial updating magnitude");
  argopt_add(ao, "--ac", "%lf", &alfc, "updating magnitude");
  argopt_add(ao, "--km", "%lf", &derm, "correction for x < xmin");
  argopt_add(ao, "--kp", "%lf", &derp, "correction for x > xmax");  
  argopt_add(ao, "-o", NULL, &fnout,  "output file");
  argopt_add(ao, "-H", NULL, &fnhis,  "histogram file");
  argopt_add(ao, "--every",   "%d", &nevery,  "interval of printing messages");
  argopt_add(ao, "--report",  "%d", &nreport, "interval of saving data");
  argopt_addhelp(ao, "-h");
  argopt_parse(ao, argc, argv);

  argopt_dump(ao);
  argopt_close(ao);
}

/* multicanoical Monte Carlo simulation */
static void domc(lj_t *lj)
{
  int ie, t;
  alged_t *al;
  hist_t *hs;
  double k, u0 = 0, u1 = 0, du = 0, duc = 0, alf = 0;
  double macc = 0, mtot = 1e-6;

  al = alged_open(epmin, epmax, epdel, alfmax, alfc,
    1.0/tp0, forder, flathis, mindata, derm, derp);
  hs = hs_open(1, -800, 0, 1.0);

  /* try to equilibrate the system by running MD at tp0 */
  for (t = 1; t <= nequil; t++)
    lj_metro(lj, mcamp, 1.f/tp0);
  die_if (lj->epot < al->xmin || lj->epot > al->xmax,
    "too hard to equilibrate the system, epot %g\n", lj->epot);
  printf("equilibrated at t %d, epot %g\n", t, lj->epot);

  u0 = lj->epot;
  ie = alged_getidx(al, u0);

  /* real simulation */
  for (t = 1; t <= nsteps; t++) {
    k = alged_getf(al, lj->epot);

    mtot += 1;
    macc += lj_metro(lj, mcamp, k/tp0);
    hs_add1ez(hs, lj->epot, HIST_VERBOSE);

    if (t % seglen == 0) {
      u1 = lj->epot;
      du = u1 - u0;

      al->cc[ie] += 1.0;
      al->e2[ie] += du * du;
      alf = alged_getalpha(al, ie);

      /* correction term */
      du += duc = alged_getcorr1(al, ie);

      al->f[ie] = dblmax(al->f[ie] + alf * du, 0.001);

      /* set the new start point */
      u0 = u1;
      ie = alged_getidx(al, u0);
    }

    if (t % nevery == 0) {
      printf("t %d, ep %g, du %g, %g, k %g, ie %d, alf %g, ek %g, acc %g\n",
        t, lj->epot/lj->n, du, duc, k, ie, alf, lj->ekin, macc/mtot);

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
