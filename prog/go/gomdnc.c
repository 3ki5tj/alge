/* sampling flat # of contact histogram */
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
real rcc = (real) 4.5;
/* start from a random initial structure */
int fromrand = 0;
/* in counting formed contacts in a configuration
 * a contact is considered as formed if the pair distance is shorter
 * than the `ncgam' * the distance in the reference structure */
double ncgam = 1.2;


double nsteps = 1e9;
int nevery = 10000;
int nreport = 500000;
real tp = 1.07f;
real mddt = 0.002f;
real thermdt = 0.1f; /* thermostat dt */
int hmcmethod = 0;


/* for SH3 domain (1KIK), if rcc = 4.5 --> then Tc = 1.07
 * the double-peak structure can be seen from the potential-energy,
 * rmsd, and number of contact distributions */
char *fnpdb = "pdb/1KIK.pdb";
char *fnalge = "go.e";
char *fnpos = "go.pos";
char *fnephis = "ep.his";
char *fnrmsdhis = "rmsd.his";
char *fnconthis = "nc.his";

/* algorithm E parameters */
double Qmin = 0.1;
double Qmax = 0.9;
double Qdel = 0.05;
int contmin, contmax, contdel; /* to be determined */

int seglen = 200; /* trajectory segment length */
double alf0 = 0.001, alfc = 0.5;
double mindata = 100.0, derm = 1.0, derp = 2.0;
double mf0 = 0; /* initial mean force */
double mfmax = 1.0; /* maximal mean force */

/* handle input arguments */
static void doargs(int argc, char **argv)
{
  argopt_t *ao = argopt_open(0);
  argopt_add(ao, "-f", NULL,  &fnpdb,     "PDB file");
  argopt_add(ao, "-Z", "%b",  &fromrand,  "start from random configuration");
  argopt_add(ao, "-G", "lf",  &ncgam,     "distance-scaling factor for counting formed contacts");
  argopt_add(ao, "-T", "%r",  &tp,        "temperature");
  argopt_add(ao, "-1", "%lf", &nsteps,    "number of simulation steps");
  argopt_add(ao, "-d", "%r",  &mddt,      "MD time step size");
  argopt_add(ao, "-q", "%r",  &thermdt,   "time step for mc-vrescaling thermostat");
  argopt_add(ao, "-c", "%r",  &rcc,       "cutoff distance for defining contacts");
  argopt_add(ao, "-m", "%d",  &hmcmethod, "hybrid MC method, 0: random; 1: random matrix");

  /* algorithm-E parameters */
  argopt_add(ao, "-l", "%d",  &seglen,    "segment length");
  argopt_add(ao, "-F", "%lf", &mf0,       "initial mean force");
  argopt_add(ao, "-9", "%lf", &mindata,   "minimal number of data points to apply correction");
  argopt_add(ao, "--a0",  "%lf", &alf0,   "initial updating magnitude");
  argopt_add(ao, "--ac",  "%lf", &alfc,   "updating magnitude");
  argopt_add(ao, "--km",  "%lf", &derm,   "correction for x < xmin");
  argopt_add(ao, "--kp",  "%lf", &derp,   "correction for x > xmax");
  argopt_add(ao, "--Q0",  "%lf", &Qmin,   "minimal contact fraction");
  argopt_add(ao, "--Q1",  "%lf", &Qmax,   "maximal contact fraction");
  argopt_add(ao, "--dQ",  "%lf", &Qdel,   "contact fraction interval");

  argopt_add(ao, "--every",   "%d", &nevery,  "print messages every this number of steps");
  argopt_add(ao, "--report",  "%d", &nreport, "save data every this number of steps");
  argopt_addhelp(ao, "-h");
  argopt_parse(ao, argc, argv);

  argopt_dump(ao);
  argopt_close(ao);
}

static void run(void)
{
  cago_t *go;
  int it, nc;
  double t;
  hist_t *hsep, *hsrmsd, *hscont;

  alged_t *al;
  double alf, dv, duc;
  int idx; /* index of the current contact number `nc' */
  int nc0, nc1, dnc = 0, nc0bk, dncbk;
  double segtot = 1e-6, segacc = 0;

  /* hybrid MC start point */
  rv3_t *x0, *v0;
  real epot0;

  go = cago_open(fnpdb, kb, ka, kd1, kd3, nbe, nbc, rcc);
  cago_initmd(go, fromrand ? -0.1 : 0.1, 0.0);

  /* hybrid MC: save the start point */
  xnew(x0, go->n);
  xnew(v0, go->n);
  cago_copyvec(go, x0, go->x);
  cago_copyvec(go, v0, go->v);
  epot0 = go->epot;
  nc0 = cago_ncontacts(go, go->x, ncgam, NULL, NULL);

  printf("epot %g (ref %g), rmsd %g, nc %d/%d = %g\n",
      go->epot, go->epotref, go->rmsd, nc0, go->ncont, 1.*nc0/go->ncont);

  /* open the alge object */
  contmin = go->ncont * Qmin;
  contmax = go->ncont * Qmax;
  if ((contdel = go->ncont * Qdel) < 1) contdel = 1;
  al = alged_open(contmin, contmax, contdel, alf0, alfc, mf0,
      0 /* zeroth order mean force extrapolation */,
      1 /* aiming at a flat histogram */, mindata, derm, derp);
  idx = alged_getidx(al, nc0);

  if (hmcmethod == 0) { /* random velocities */
    go->dof = 3 * go->n;
  } else if (hmcmethod == 1) { /* apply a random matrix */
    go->dof = 3 * go->n - 3;
  }

  /* collect several histograms */
  hsep = hs_open1(2*go->epotref, 5*fabs(go->epotref), 0.1);
  hsrmsd = hs_open1(0, 100.0, 0.1);
  hscont = hs_open1(0, go->ncont + 1, 1);

  for (it = 0, t = 1; t < nsteps + .1; t++) {
    cago_vv(go, 1.0f, mddt);
    cago_rmcom(go, go->x, go->v);
    cago_vrescale(go, tp, thermdt);

    go->rmsd = cago_rmsd(go, go->x, NULL); /* compute rmsd */
    nc = cago_ncontacts(go, go->x, ncgam, NULL, NULL);

    ++it;
    if (it % seglen == 0) { /* attempt to do trajectory manipulation */
      nc0bk = nc0;
      nc1 = nc;
      dncbk = dnc = nc1 - nc0;

      segtot += 1;
      /* dv = d log(rho) = \int^1_0 mf
       * dv > 0 means moving to a more populated region
       * which therefore should be biased against */
      //dv = alged_getf(al, nc0) * dnc;
      dv = alged_dh(al, nc1, nc0);

      if (dv <= 0 || rnd0() < exp(-dv)) { /* keep it */
        segacc += 1;
        cago_copyvec(go, x0, go->x);
        cago_copyvec(go, v0, go->v);
        nc0 = nc1;
        epot0 = go->epot;
      } else { /* revert */
        cago_copyvec(go, go->x, x0);
        cago_copyvec(go, go->v, v0);
        dnc = 0;
      }

      if (hmcmethod == 0) {
        md_mutv3d(go->v, go->n, tp);
      } else if (hmcmethod == 1) {
        md_unimatv3d(go->v, go->n);
      }

      /* update alge data */
      al->cc[ idx ] += 1;
      al->e2[ idx ] += dnc * dnc;

      alf = alged_getalpha(al, idx);
      duc = alged_getcorr1(al, idx);
      duc = dblconfine(duc, -.5 * fabs(dnc), .5 * fabs(dnc));

      /* the fixed point is located at < dnc + duc > = 0 */
      al->f[idx] = dblconfine(al->f[idx] + alf * (dnc + duc), -mfmax, mfmax);

      /* set the new start point */
      idx = alged_getidx(al, nc0);
      nc = nc0;
      go->epot = epot0;

      hs_add1ez(hsep, go->epot, 0);
      hs_add1ez(hsrmsd, go->rmsd, HIST_VERBOSE);
      hs_add1ez(hscont, nc, HIST_VERBOSE);

      if (it % nevery == 0) {
        printf("t %g, T %.3f, ep %.2f/%.2f, rmsd %.2f/%.2f, Q %d/%d=%.2f(%.2f), "
            "alf %.6f, mf %.3f, nc %d%+d (%+d, dv %.3f), segacc %.3f\n",
          t, go->tkin,
          go->epot, hs_getave(hsep, 0, NULL, NULL),
          go->rmsd, hs_getave(hsrmsd, 0, NULL, NULL),
          nc, go->ncont, 1.0*nc/go->ncont,
          hs_getave(hscont, 0, NULL, NULL)/go->ncont,
          alf, al->f[idx], nc0bk, dnc, dncbk, dv, segacc/segtot);
      }
      if (it % nreport == 0 || t >= nsteps - 0.1) {
        printf("saving %s, %s, %s, %s\n", fnalge, fnephis, fnrmsdhis, fnpos);
        alged_save(al, fnalge);
        hs_save(hsep, fnephis, HIST_ADDAHALF);
        hs_save(hsrmsd, fnrmsdhis, HIST_ADDAHALF);
        hs_save(hscont, fnconthis, 0);
        cago_writepos(go, go->x, NULL, fnpos);
        it = 0;
      }
    }
  }
  cago_close(go);
  hs_close(hsep);
  hs_close(hsrmsd);
  hs_close(hscont);
  alged_close(al);
  free(x0); free(v0);
}

int main(int argc, char **argv)
{
  doargs(argc, argv);
  run();
  return 0;
}

