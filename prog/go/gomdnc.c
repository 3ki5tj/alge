/* sample a flat number-of-contacts histogram in MD */
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
double hmcmutr = 1.0; /* velocity mutation rate */

/* for SH3 domain (1KIK), if rcc = 4.5 --> then Tc = 1.07
 * the double-peak structure can be seen from the potential-energy,
 * RMSD, and number of contact distributions */
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
double alf0 = 0.01, alfc = 1.0;
int boundary = 1; /* how to handle boundary conditions,
    0: smooth (requires proper `derm' and `derp' values)
    1: reflective or hard (no out-of-boundary-transitions) */
double mf0 = 0; /* initial mean force */
double delmax = 10.0; /* maximal 2 e / < e^2 > */ 
double mfmax = 1.0; /* maximal mean force magnitude */

/* handle command-line arguments */
static void doargs(int argc, char **argv)
{
  argopt_t *ao = argopt_open(0);
  argopt_add(ao, "-f", NULL,  &fnpdb,     "PDB file");
  argopt_add(ao, "-Z", "%b",  &fromrand,  "start from random configuration");
  argopt_add(ao, "-G", "%lf", &ncgam,     "distance-scaling factor for counting formed contacts");
  argopt_add(ao, "-T", "%r",  &tp,        "temperature");
  argopt_add(ao, "-1", "%lf", &nsteps,    "number of simulation steps");
  argopt_add(ao, "-d", "%r",  &mddt,      "MD time step size");
  argopt_add(ao, "-q", "%r",  &thermdt,   "time step for mc-vrescaling thermostat");
  argopt_add(ao, "-c", "%r",  &rcc,       "cutoff distance for defining contacts");
  argopt_add(ao, "-m", "%d",  &hmcmethod, "hybrid MC method, 0: random; 1: random matrix");
  argopt_add(ao, "-r", "%lf", &hmcmutr,   "probability of mutating velocities");

  /* algorithm-E parameters */
  argopt_add(ao, "-l", "%d",  &seglen,    "segment length");
  argopt_add(ao, "-b", "%d",  &boundary,  "boundary condition, 0: smooth, 1: reflective (hard)");
  argopt_add(ao, "-F", "%lf", &mf0,       "initial mean force");
  argopt_add(ao, "--a0",  "%lf", &alf0,   "initial updating magnitude");
  argopt_add(ao, "--ac",  "%lf", &alfc,   "updating magnitude");
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
  double alf, dv, ave2;
  /* the actual, logical and boundary-adjusted acceptance rates */
  int acc = 0, acc_l = 0, acc_a = 0;
  double mf = 0; /* current mean force */
  int nc0 = 0, nc0bk = 0, nc1 = 0, dnc_a = 0;
  double dnc_l = 0;
  double segtot = 1e-6, segacc = 0;

  /* hybrid MC start point */
  rv3_t *x0, *v0;
  real epot0;

  go = cago_open(fnpdb, kb, ka, kd1, kd3, nbe, nbc, rcc);
  cago_initmd(go, fromrand ? -0.1 : 0.1, tp);

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
  al = alged_open(contmin, contmax, contdel, mf0,
      0 /* zeroth order mean force extrapolation */);

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
    cago_vv(go, 1.f, mddt);
    cago_rmcom(go, go->x, go->v);
    cago_vrescale(go, tp, thermdt);

    /* keep doing basic MD */
    if (++it % seglen != 0) continue;

    go->rmsd = cago_rmsd(go, go->x, NULL);
    nc = cago_ncontacts(go, go->x, ncgam, NULL, NULL);

    /* hybrid MC trajectory manipulation */
    nc0bk = nc0;
    nc1 = nc;
    dnc_a = nc1 - nc0;

    segtot += 1;
    /* `acc_l' indicates if a move *should* be accepted by the
     * natural mean force, it can, however, be rejected due to
     * the boundary conditions, indicated by `acc_a' */
    acc = alged_getacc(al, nc1, nc0, boundary,
        &acc_l, &dnc_l, &acc_a, &dv);      

    if (acc) { /* keep it */
      segacc += 1;
      cago_copyvec(go, x0, go->x);
      cago_copyvec(go, v0, go->v);
      nc0 = nc1;
      epot0 = go->epot;
    } else { /* revert */
      cago_copyvec(go, go->x, x0);
      cago_copyvec(go, go->v, v0);
    }

    if (hmcmethod == 0) {
      md_mutv3d(go->v, go->n, tp, hmcmutr);
    } else if (hmcmethod == 1) {
      md_unimatv3d(go->v, go->n);
    }

    /* update alge data */
    mf = alged_fupdate(al, nc0bk, dnc_l, alf0, alfc, &alf,
        delmax, &ave2, -mfmax, mfmax);

    /* set the new start point */
    nc = nc0;
    go->epot = epot0;

    hs_add1ez(hsep, go->epot, 0);
    hs_add1ez(hsrmsd, go->rmsd, HIST_VERBOSE);
    hs_add1ez(hscont, nc, HIST_VERBOSE);

    if (it % nevery == 0) {
      printf("t %g, T %.3f(%.3f), ep %.2f/%.2f, rmsd %.2f/%.2f, Q %d/%d=%.2f(%.2f), "
          "alf %.6f, mf %.3f, nc %d%+.0f(%+d, dv %.3f, <e^2> %g), segacc %2.0f\n",
        t, go->tkin, tp,
        go->epot, hs_getave(hsep, 0, NULL, NULL),
        go->rmsd, hs_getave(hsrmsd, 0, NULL, NULL),
        nc, go->ncont, 1.0*nc/go->ncont,
        hs_getave(hscont, 0, NULL, NULL)/go->ncont,
        alf, mf, nc0bk, dnc_l, dnc_a, dv, ave2, 100.*segacc/segtot);
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

