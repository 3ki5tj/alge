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
real tpstat = 1.0f; /* temperature */
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
  argopt_add(ao, "-e", "%d",  &nevery,    "interval of computing temperatures");

  argopt_add(ao, "-l", "%d",  &seglen,    "the number of steps to be treated as a perturbation");
  argopt_add(ao, "-b", "%d",  &boundary,  "boundary condition, 0: smooth, 1: reflective (hard)");

  argopt_add(ao, "-d", "%r",  &mddt,      "time step for molecular dynamics");
  argopt_add(ao, "-q", "%r",  &thermdt,   "thermostat time step");
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

#ifdef HMC
  die_if (boundary != 1,
      "HMC version only supports reflective boundary not %d", boundary);
#endif

  argopt_dump(ao);
  argopt_close(ao);
}

/* multicaonical molecular dynamics simulation */
static void domd(void)
{
  int t;
  alged_t *al;
  hist_t *hs;
  double k, u0, u1, du = 0, alf = 0, ave2 = 0;
  lj_t *lj = lj_open(N, D, rho, rcdef);
#ifdef HMC
  rv3_t *x0, *v0, *f0;
#endif

  al = alged_open(epmin, epmax, epdel, 1/tpmin, 1/tpmax);
  hs = hs_open1(-7.*lj->n, 0, 1.0);

  /* equilibrate the system by regular MD at tpstat
   * till the potential energy falls in (xmin, xmax) */
  for (t = 1; t <= nequil; t++) {
    lj_vv(lj, mddt);
    lj_shiftcom(lj, lj->v);
    lj_vrescalex(lj, tpstat, thermdt);
    if (lj->epots >= epmin && lj->epots < epmax)
      break;
  }
  die_if (lj->epots < epmin || lj->epots >= epmax,
    "cannot equilibrate the system, ep %g\n", lj->epots);
  printf("equilibrated at t %d, epot %g\n", t, lj->epots);

  /* Note: lj->epots may be replaced by lj->epot
   * but it may significantly change f */
  u0 = lj->epots;

#ifdef HMC
  /* back up the starting point */
  xnew(x0, lj->n);
  xnew(v0, lj->n);
  xnew(f0, lj->n);
  lj_copyvec(lj, x0, lj->x);
  lj_copyvec(lj, v0, lj->v);
  lj_copyvec(lj, f0, lj->f);
#endif HMC

  /* real simulation */
  for (t = 1; t <= nsteps; t++) {
    k = tpstat * alged_getf(al, lj->epots);
    if (boundary == 1) {
      if (lj->epots < epmin) k = tpstat / tpmin;
      if (lj->epots >= epmax) k = tpstat / tpmax;
    }
    k = dblmax(k, 0.05); /* the minimal scaling */

    lj_vvx(lj, k, mddt);
    lj_shiftcom(lj, lj->v);
    lj_vrescalex(lj, tpstat, thermdt);
    hs_add1ez(hs, lj->epots, 0);

    if (t % seglen == 0) {
      u1 = lj->epots;
      du = u1 - u0;
      alged_fupdate(al, u0, du, alf0, alfc, &alf,
          delmax, &ave2, mfmin, mfmax);
#ifdef HMC
      if ((u0 >= epmin || u0 <  epmax) 
       && (u1 <  epmin || u1 >= epmax) ) { /* reject the move */
        int ii;

        lj->epots = u1 = u0;
        lj_copyvec(lj, lj->x, x0);
        lj_copyvec(lj, lj->v, v0);
        lj_copyvec(lj, lj->f, f0);
        for (ii = 0; ii < lj->n * lj->d; ii++)
          lj->v[ii] = -lj->v[ii];
      } else {
        lj_copyvec(lj, x0, lj->x);
        lj_copyvec(lj, v0, lj->v);
        lj_copyvec(lj, f0, lj->f);
      }
#endif
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
#ifdef HMC
  free(x0); free(v0); free(f0);
#endif
  alged_close(al);
  lj_close(lj);
}

int main(int argc, char **argv)
{
  doargs(argc, argv);
  domd();
  return 0;
}
