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
real thermdt = 0.1f;
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

int seglen = 1000; /* trajectory segment length */
double rmsdmin = 2.0, rmsdmax = 18, rmsddel = 0.5;
double alf0 = 2.0, alfc = 200.0;
double mindata = 100.0, derm = 0.2, derp = 0.5;
double mf0 = 0;

int doargs(int argc, char **argv)
{
  argopt_t *ao = argopt_open(0);

  argopt_add(ao, "-f", NULL,  &fnpdb,     "PDB file"); 
  argopt_add(ao, "-T", "%r",  &tp,        "temperature");
  argopt_add(ao, "-1", "%lf", &nsteps,    "number of simulation steps");
  argopt_add(ao, "-d", "%r",  &mddt,      "MD time step size");
  argopt_add(ao, "-q", "%r",  &thermdt,   "time step for mc-vrescaling thermostat");
  argopt_add(ao, "-c", "%r",  &rcc,       "cutoff distance for defining contacts");
  argopt_add(ao, "-m", "%d",  &hmcmethod, "hybrid MC method, 0: random, 1: random matrix, 2: random rotation, 4: random reflection");

  /* algorithm-E parameters */
  argopt_add(ao, "-l", "%d",  &seglen,    "segment length");
  argopt_add(ao, "-F", "%lf", &mf0,       "initial mean force");
  argopt_add(ao, "-9", "%lf", &mindata,   "minimal number of data points to apply correction");
  argopt_add(ao, "--a0", "%lf", &alf0,    "initial updating magnitude");
  argopt_add(ao, "--ac", "%lf", &alfc,    "updating magnitude");
  argopt_add(ao, "--km", "%lf", &derm,    "correction for x < xmin");
  argopt_add(ao, "--kp", "%lf", &derp,    "correction for x > xmax");  
  argopt_add(ao, "--r0", "%lf", &rmsdmin, "minimal rmsd");
  argopt_add(ao, "--r1", "%lf", &rmsdmax, "maximal rmsd");
  argopt_add(ao, "--dr", "%lf", &rmsddel, "rmsd interval");
  
  argopt_add(ao, "--every",   "%d", &nevery,  "print messages every this number of steps");
  argopt_add(ao, "--report",  "%d", &nreport, "save data every this number of steps");
  argopt_addhelp(ao, "-h");
  argopt_parse(ao, argc, argv);

  argopt_dump(ao);
  argopt_close(ao);
  return 0;
} 

/* mutate velocities by random rotation */
INLINE int md_rotv3d(rv3_t *v, int n)
{
  int i;
  real mat[3][3], v1[3], axis[3], ang;

  rv3_normalize(rv3_rnd(axis, -.5f, 1.f));
  ang = 2 * M_PI * rnd0(); /* amplitude has to be 2 * pi */
  rm3_mkrot(mat, axis, ang);
  for (i = 0; i < n; i++) {
    rm3_mulvec(v1, mat, v[i]);
    rv3_copy(v[i], v1);
  }
  return 0;
}

/* mutate velocities by random reflection */
INLINE int md_refv3d(rv3_t *v, int n)
{
  int i;
  real axis[3], dot;

  rv3_normalize(rv3_rnd(axis, -.5f, 1.f));
  for (i = 0; i < n; i++) {
    dot = rv3_dot(axis, v[i]);
    rv3_sinc(v[i], axis, -2*dot);
  }
  return 0;
}

void run(void)
{
  cago_t *go;
  int it, nc;
  double t;
  hist_t *hsep, *hsrmsd, *hscont;
  
  alged_t *al;
  double alf, dv, duc;
  int idx; /* index of the current RMSD */
  real rmsd0, rmsd1, drmsd = 0, rmsd0bk, drmsdbk;
  double segtot = 1e-6, segacc = 0;

  /* hybrid MC start point */
  rv3_t *x0, *v0;
  real epot0;

  go = cago_open(fnpdb, kb, ka, kd1, kd3, nbe, nbc, rcc);
  cago_initmd(go, 0.1, 1.f/tp);
  
  /* hybrid MC: save the start point */
  xnew(x0, go->n);
  xnew(v0, go->n);
  cago_copyvec(go, x0, go->x);
  cago_copyvec(go, v0, go->v);
  epot0 = go->epot;
  rmsd0 = cago_rmsd(go, x0, NULL);

  printf("epot %g (ref %g), rmsd %g\n",
      go->epot, go->epotref, go->rmsd);

  /* open the alge object */
  al = alged_open(rmsdmin, rmsdmax, rmsddel, alf0, alfc, mf0,
    0 /* zeroth order mean force extrapolation */, 
    1 /* aiming at a flat histogram */, mindata, derm, derp);
  idx = alged_getidx(al, rmsd0);

  if (hmcmethod == 0) {
    go->dof = 3 * go->n;
  } else if (hmcmethod == 4) { /* a reflection conserves the zero angular and linear momentum */
    go->dof = 3 * go->n - 6;
  } else { /* if a rotation is involved, the total angular momentum
    is not conserved upon a universal rotation,
    but the linear momentum is still conserved */
    go->dof = 3 * go->n - 3;
  }

  hsep = hs_open1(2*go->epotref, 5*fabs(go->epotref), 0.1);
  hsrmsd = hs_open1(0, 100.0, 0.01);
  hscont = hs_open1(0, go->ncont + 1, 1);
  
  for (it = 0, t = 1; t < nsteps + .1; t++) {
    cago_vv(go, 1.f, mddt);
    cago_rmcom(go, go->x, go->v);
    cago_vrescale(go, tp, thermdt);

    go->rmsd = cago_rmsd(go, go->x, NULL);
    nc = cago_ncontacts(go, go->x, ncgam, NULL, NULL);
    
    if (++it % seglen == 0) {
      rmsd0bk = rmsd0;
      rmsd1 = go->rmsd;
      drmsdbk = drmsd = rmsd1 - rmsd0;

      segtot += 1;
      //dv = alged_getf(al, rmsd0) * drmsd;
      dv = alged_dh(al, rmsd1, rmsd0);

      if (dv <= 0 || rnd0() < exp(-dv)) { /* keep it */
        /* set the new start point */
        segacc += 1;
        cago_copyvec(go, x0, go->x);
        cago_copyvec(go, v0, go->v);
        rmsd0 = rmsd1;
        epot0 = go->epot;
      } else { /* revert */
        cago_copyvec(go, go->x, x0);
        cago_copyvec(go, go->v, v0);
        drmsd = 0;
      }

      /* we mutate the velocities even if the trajectory is continued */
      if (hmcmethod == 0) {
        md_mutv3d(go->v, go->n, tp);
      } else if (hmcmethod == 1) {
        md_unimatv3d(go->v, go->n);
      } else {
        if (hmcmethod & 2) md_rotv3d(go->v, go->n);
        if (hmcmethod & 4) md_refv3d(go->v, go->n);
      }
      
      /* update alge data */
      al->cc[ idx ] += 1;
      al->e2[ idx ] += drmsd * drmsd;

      alf = alged_getalpha(al, idx);
 
      duc = alged_getcorr1(al, idx);
      duc = dblconfine(duc, -.5 * fabs(drmsd), .5 * fabs(drmsd));
      drmsd += duc;

      al->f[idx] = dblconfine(al->f[idx] + alf * drmsd, -100.0, 100.0);
      
      /* set the new start point */
      idx = alged_getidx(al, rmsd0);
      go->rmsd = rmsd0;
      go->epot = epot0;

      hs_add1ez(hsep, go->epot, 0);
      hs_add1ez(hsrmsd, go->rmsd, HIST_VERBOSE);
      hs_add1ez(hscont, nc, HIST_VERBOSE);
 
      if (it % nevery == 0) {
        printf("t %g, T %.3f, ep %.2f/%.2f, rmsd %.2f/%.2f, Q %d/%d=%.2f(%.2f), "
            "alf %.6f, mf %.3f, nc %.2f%+.2f (%+.2f, dv %.3f), segacc %.3f\n",
          t, go->tkin,
          go->epot, hs_getave(hsep, 0, NULL, NULL), 
          go->rmsd, hs_getave(hsrmsd, 0, NULL, NULL),
          nc, go->ncont, 1.0*nc/go->ncont,
          hs_getave(hscont, 0, NULL, NULL)/go->ncont,
          alf, al->f[idx], rmsd0bk, drmsd, drmsdbk, dv, segacc/segtot);

        printf("t %g, rmsd %g, del %g, segacc %g, alf %g\n",
          t, go->rmsd, drmsd, segacc/segtot, alf);
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
