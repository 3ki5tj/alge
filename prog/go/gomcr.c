/* achieves a flat RMSD histogram */
#define ZCOM_PICK
#define ZCOM_ARGOPT
#define ZCOM_HIST
#define ZCOM_CAGO
#include "zcom.h"

#include "alged.h"

/* alpha-carbon Go model parameters */
real kb = (real) 200.;
real ka = (real) 40.;
real kd1 = (real) 1;
real kd3 = (real) .5;
real nbe = (real) 1.;
real nbc = (real) 4.;
real rcc = (real) 5.;

double nsteps  = 1e10;
int nevery  = 100000;
int nreport = 10000000;
real tp = 1.;
real mcamp = 0.3;
real mf0 = 0.f;
char *fnpdb = "pdb/1VII.pdb";
char *fnpos = "go.pos";
char *fnhis = "rmsd.his";

int seglen = 1000; /* segment length */
double rmsdmin = 2.0, rmsdmax = 18, rmsddel = 0.5;
double alf0 = 1.0, alfc = 100.0;
double mindata = 100.0, derm = 0.2, derp = 0.5;
double mfmax = 100.0; /* maximal mean force */

int doargs(int argc, char **argv)
{
  argopt_t *ao = argopt_open(0);

  argopt_add(ao, "-1", "%lf", &nsteps, "number of simulation steps");
  argopt_add(ao, "-T", "%r", &tp, "temperature");
  argopt_add(ao, "-a", "%r", &mcamp, "MC amplitude");
  argopt_add(ao, "-l", "%d", &seglen, "segment length");
  argopt_add(ao, "-F", "%r", &mf0, "default mean force");
  argopt_add(ao, "-f", NULL, &fnpdb, "name of the PDB file");
  argopt_add(ao, "-9", "%lf",&mindata,  "minimal number of data points");
  argopt_add(ao, "--r0", "%lf", &rmsdmin, "minimal rmsd");
  argopt_add(ao, "--r1", "%lf", &rmsdmax, "maximal rmsd");
  argopt_add(ao, "--dr", "%lf", &rmsddel, "rmsd interval");
  argopt_add(ao, "--a0", "%lf", &alf0, "initial updating magnitude");
  argopt_add(ao, "--ac", "%lf", &alfc, "updating magnitude");
  argopt_add(ao, "--km", "%lf", &derm, "correction for x < xmin");
  argopt_add(ao, "--kp", "%lf", &derp, "correction for x > xmax");
  argopt_add(ao, "--every", "%d", &nevery, "print messages every this number of steps");
  argopt_add(ao, "--report", "%d", &nreport, "save data every this number of steps");
  argopt_parse(ao, argc, argv);
  argopt_dump(ao);
  return 0;
}

void run(void)
{
  cago_t *go;
  rv3_t *x0; /* hybrid MC start point */
  real rmsd0, rmsd1, drmsd = 0, epot0;
  hist_t *hsrmsd;
  double t, etot = 0, eacc = 0;
  double segtot = 1e-6, segacc = 0;
  int it = 0;

  alged_t *al;
  double alf, dv, duc;
  int idx;

  al = alged_open(rmsdmin, rmsdmax, rmsddel, mf0);

  go = cago_open(fnpdb, kb, ka, kd1, kd3, nbe, nbc, rcc);
  cago_initmd(go, 0.1, tp);
  printf("init rmsd %g\n", go->rmsd);

  go->dof = 3 * go->n; /* because we are doing mc */

  xnew(x0, go->n);

  /* save the start point */
  cago_copyvec(go, x0, go->x);
  epot0 = go->epot;
  rmsd0 = cago_rmsd(go, x0, NULL);
  idx = alged_getidx(al, rmsd0);

  hsrmsd = hs_open1(0, 100.0, 0.01);

  for (t = 1; t <= nsteps; t++) {
    etot += 1;
    eacc += cago_metro(go, mcamp, 1.f/tp);
    if (++it % seglen == 0) {
      cago_rmcom(go, go->x, NULL);
      rmsd1 = cago_rmsd(go, go->x, go->x1);
      drmsd = rmsd1 - rmsd0;

      segtot += 1;
      //dv = alged_getf(al, rmsd0) * rmsd0;
      dv = alged_dh(al, rmsd1, rmsd0);

      if (rnd0() < exp(-dv)) { /* keep it */
        /* set the new start point */
        segacc += 1;
        cago_copyvec(go, x0, go->x);
        epot0 = go->epot;
        rmsd0 = rmsd1;
      } else { /* revert */
        cago_copyvec(go, go->x, x0);
        drmsd = 0;
      }

      al->cc[ idx ] += 1;
      al->e2[ idx ] += drmsd * drmsd;

      alf = alged_getalpha(al, idx);

      duc = alged_getcorr1(al, idx);
      duc = dblconfine(duc, -.5 * fabs(drmsd), .5 * fabs(drmsd));
      drmsd += duc;

      al->f[idx] = dblconfine(al->f[idx] + alf * drmsd, -mfmax, mfmax);

      /* new start point */
      idx = alged_getidx(al, rmsd0);

      go->rmsd = rmsd0;
      go->epot = epot0;

      hs_add1ez(hsrmsd, go->rmsd, HIST_VERBOSE);

      if (it % nevery == 0) {
        printf("t %g, rmsd %g, acc %g, segacc %g, alf %g\n",
          t, go->rmsd, 1.*eacc/etot, 1.*segacc/segtot, alf);
      }
      if (it % nreport == 0 || t >= nsteps) {
        hs_save(hsrmsd, fnhis, HIST_ADDAHALF);
        cago_writepos(go, go->x, NULL, fnpos);
        alged_save(al, "go.e");
        it = 0;
      }
    }
  }
  cago_close(go);
  free(x0);
  alged_close(al);
}

int main(int argc, char **argv)
{
  doargs(argc, argv);
  run();
  return 0;
}

