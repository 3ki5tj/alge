/* algrihtm E on Potts model */
#define PT2_LB 5
#define PT2_Q  10
#define L (1 << PT2_LB)
#define N (L*L)
#define EMIN (-2*N)
#define EMAX (0)
#define EDEL 1
#define ECNT ((EMAX - EMIN)/EDEL + 1)

#define ZCOM_PICK
#define ZCOM_ARGOPT
#define ZCOM_POTTS2
#include "zcom.h"
#include "alge.h"

int epmin = -1920, epmax = -800, epdel = 16, order = 0;
double nsweeps = 1000000, nsteps;
double alf0 = 5e-4, alfc = 5.0, beta0 = 1.4;
double mindata = 1000.0;
int nevery  = 1000000;
int nreport = 100000000;
char *fnhis = "ep.his";
char *fnout = "pt.e";
int seglen = 10;
int boundary = 0; /* 0: smooth; 1: reflective */
double derm = 0.05f, derp = 0.1f;
double dermax = 10.f;

/* handle input arguments */
static void doargs(int argc, char **argv)
{
  argopt_t *ao = argopt_open(0);

  argopt_add(ao, "-1", "%lf", &nsweeps,   "number of simulation SWEEPS");
  argopt_add(ao, "-d", "%d",  &order,     "order");
  argopt_add(ao, "-(", "%d",  &epmin,     "minimal energy");
  argopt_add(ao, "-)", "%d",  &epmax,     "maximal energy");
  argopt_add(ao, "-:", "%d",  &epdel,     "energy interval");
  argopt_add(ao, "-l", "%d",  &seglen,    "the number of steps to be treated as a perturbation");
  argopt_add(ao, "-q", "%lf", &mindata,   "minimal number of data points");
  argopt_add(ao, "-K", "%lf", &dermax,    "maximal temperature");
  argopt_add(ao, "-b", "%d",  &boundary,  "boundary condition, 0: smooth, 1: reflective");
  argopt_add(ao, "--a0", "%lf", &alf0,    "maximal amplitude");
  argopt_add(ao, "--ac", "%lf", &alfc,    "alpha_c");
  argopt_add(ao, "--km", "%lf", &derm,    "correction for x < xmin");
  argopt_add(ao, "--kp", "%lf", &derp,    "correction for x > xmax");
  argopt_add(ao, "-o",    NULL, &fnout,   "name of the output file");
  argopt_add(ao, "-H",    NULL, &fnhis,   "name of the histogram file");
  argopt_add(ao, "--every",   "%d", &nevery,  "interval of printing messages");
  argopt_add(ao, "--report",  "%d", &nreport, "interval of saving data");
  argopt_addhelp(ao, "-h");
  argopt_parse(ao, argc, argv);
  nsteps = nsweeps * N; /* convert to the number of steps */
  argopt_dump(ao);
  argopt_close(ao);
}

/* entropic sampling */
static int move(potts_t *pt, alge_t *al)
{
  int id, so, sn, de = 0, nb[PT2_Q], acc;

  PT2_PICK(pt, id, nb);
  PT2_NEWFACE(pt, id, so, sn); /* so --> sn */
  de = nb[so] - nb[sn];
  if (de != 0) {
    acc = alge_getacc(al, pt->E + de, pt->E, boundary,
      NULL, &de, NULL, NULL);
  } else acc = 1;

  if (acc) { PT2_FLIP(pt, id, so, sn, nb); }
  return de;
}

/* save all data */
static int saveall(alge_t *al, double *his, double *acc, double *inc, const char *fn)
{
  int i, n = ECNT, ie, ene;
  FILE *fp;
  double tot, fac, x;
  double *bet, *lng, *lngadj;

  for (tot = 0., i = 0; i < ECNT; i++)
    tot += his[i];
  if (tot < 0.5) {
    printf("histogram is empty\n");
    return -1;
  }
  fac = 1.0/(tot * EDEL);

  xnew(bet, n + 2);
  xnew(lng, n + 2);
  xnew(lngadj, n + 2);

  /* compute a detailed beta and density of states */
  for (lng[0] = 0, i = 0; i <= n; i++) {
    ene = EMIN + i * EDEL;
    if (ene < al->xmin) {
      bet[i] = al->f[0];
    } else if (ene >= al->xmax) {
      bet[i] = al->f[i]; /* use the last i */
    } else {
      ie = (ene - al->xmin)/al->dx;
      bet[i] = al->f[ie];
      lng[i + 1] = lng[i] + bet[i] * EDEL;
    }
  }
  /* shift the density of states */
  i = (al->xmin - EMIN)/EDEL;
  x = lng[i];
  for (i = 0; i <= n; i++) lng[i] -= x;

  /* construct the adjusted density of states */
  for (ene = al->xmin; ene <= al->xmax; ene += EDEL) {
    i = (ene - EMIN)/EDEL;
    lngadj[i] = lng[i] + log(his[i]);
  }
  /* shift the density of states */
  i = (al->xmin - EMIN)/EDEL;
  x = lngadj[i];
  for (i = 0; i <= n; i++) lngadj[i] -= x;

  xfopen(fp, fn, "w", return -1);
  fprintf(fp, "# %d %d %d 1 | %g\n",
    al->n, al->xmin, al->dx, tot);
  for (i = 0; i < ECNT; i++) {
    if (his[i] < 0.5)  continue;
    fprintf(fp, "%d %g %g %g %.6f %.6f %.6f\n",
      EMIN + i * EDEL, his[i]*fac, acc[i]*fac, inc[i]*fac,
      bet[i], lng[i], lngadj[i]);
  }
  fclose(fp);

  free(bet);
  free(lng);
  free(lngadj);
  return 0;
}


/* entropic sampling */
static void run(void)
{
  potts_t *pt = pt2_open(L, PT2_Q);
  alge_t *al;
  double *ehis, *eacc, *einc, t, duc;
  int ie, de, it = 0, u1, u0, du;

  al = alge_open(epmin, epmax, epdel, beta0);
  /* equilibrate the system till pt->E > epmin */
  for (; pt->E <= epmin + 4;) {
    int id, so, sn, nb[PT2_Q];
    PT2_PICK(pt, id, nb);
    PT2_NEWFACE(pt, id, so, sn); /* so --> sn */
    PT2_FLIP(pt, id, so, sn, nb);
  }
  printf("equilibration finished, E %d\n", pt->E);

  xnew(ehis, ECNT);
  xnew(eacc, ECNT);
  xnew(einc, ECNT);

  u0 = pt->E;

  for (t = 1; t <= nsteps; t++) {
    ie = (pt->E - EMIN)/EDEL;
    ehis[ie] += 1;
    de = move(pt, al);
    if (de != 0) {
      eacc[ie] += 1;
      einc[ie] += de*de;
    }

    if (++it % seglen == 0) {
      u1 = pt->E;
      du = u1 - u0;
      alge_update(al, u0, du, alf0, alfc, mindata, boundary,
          derm, derp, -dermax, NULL, &duc);
      u0 = u1; /* set the new start point */

      if (it % nevery == 0) {
        printf("t %g, ep %d, du %d, %g\n", t, pt->E, du, duc);
        if (it % nreport == 0) {
          saveall(al, ehis, eacc, einc, fnhis);
          alge_save(al, fnout);
          it = 0; /* reset the integer counter */
        }
      }
    }
  }
  alge_close(al);
  free(ehis); free(eacc); free(einc);
  pt2_close(pt);
}

int main(int argc, char **argv)
{
  doargs(argc, argv);
  run();
  return 0;
}

