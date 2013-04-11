/* Algrihtm E on Potts model */
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
//#define ZCOM_HIST
#include "zcom.h"
#include "alge.h"

int flathis = 0;
int epmin = -1920, epmax = -800, epdel = 16, order = 0;
double nsweeps = 100000, nsteps;
double amp0 = 5e-4, ampc = 5.0, beta0 = 1.4;
double mindata = 1000.0;
int nevery  = 1000000;
int nreport = 100000000;
char *fnhis = "epot.his";
char *fnout = "pt.e";
int seglen = 10;
double derm = 0.05f, derp = 0.1f;
double dermax = 10.f;

/* handle input arguments */
static void doargs(int argc, char **argv)
{
  argopt_t *ao = argopt_open(0);

  argopt_add(ao, "-1", "%lf", &nsweeps, "number of simulation SWEEPS");
  argopt_add(ao, "-f", "%b",  &flathis, "flat-distribution simulation");
  argopt_add(ao, "-d", "%d",  &order,   "order");
  argopt_add(ao, "-(", "%d",  &epmin,  "minimal energy");
  argopt_add(ao, "-)", "%d",  &epmax,  "maximal energy");
  argopt_add(ao, "-:", "%d",  &epdel,    "energy interval");
  argopt_add(ao, "-m", "%lf", &amp0,    "maximal amplitude");
  argopt_add(ao, "-a", "%lf", &ampc,    "alpha_c");
  argopt_add(ao, "-l", "%d",  &seglen,  "the number of steps to be treated as a perturbation");  
  argopt_add(ao, "-q", "%lf", &mindata, "minimal number of data points");
  argopt_add(ao, "-K", "%lf", &dermax,  "maximal temperature");
  argopt_add(ao, "--km", "%lf", &derm, "correction for x < xmin");
  argopt_add(ao, "--kp", "%lf", &derp, "correction for x > xmax");
  argopt_add(ao, "-o", NULL,  &fnout,   "name of the output file");
  argopt_add(ao, "-H", NULL,  &fnhis,   "name of the histogram file");
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
  int id, so, sn, eo, en = 0, de = 0, nb[PT2_Q], acc;
  double dh;

  PT2_PICK(pt, id, nb);
  PT2_NEWFACE(pt, id, so, sn); /* so --> sn */
  de = nb[so] - nb[sn];
  if (de != 0) {
    eo = pt->E;
    en = eo + de;
    dh = alge_dh0(al, en, eo);
    acc = (dh <= 0 || rnd0() < exp(-dh));
  } else acc = 1;

  if (acc) {  PT2_FLIP(pt, id, so, sn, nb); }
  return acc * de;
}

static int saveall(alge_t *al, double *his, double *acc, double *inc, const char *fn);

/* entropic sampling */
static int run(potts_t *pt, double trun)
{
  alge_t *al;
  double *ehis, *eacc, *einc, t, du, duc;
  int ie, de, it = 0, u1, u0, iu;

  al = alge_open(epmin, epmax, epdel, amp0, ampc,
    beta0, flathis, mindata, derm, derp);
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
  iu = alge_getidx(al, u0);
  
  for (t = 1; t <= trun; t++) {
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
      
      al->cc[iu] += 1;
      al->e2[iu] += du * du; /* using du instead of du here avoid the peaks at the boundaries */
      
      duc = alge_getcorr1(al, iu);
      du += duc;
      al->dh[iu] += du * alge_getalpha(al, iu);
      
      /* the confinement is no longer necessary */
      al->dh[iu] = dblconfine(al->dh[iu], 0, dermax);
      
      /* set the new start point */
      u0 = u1;
      iu = alge_getidx(al, u0);
      
      if (it % nevery == 0) {
        printf("t %g, ep %d, du %g, %g\n", t, pt->E, du, duc);
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
  return 0;
}

int main(int argc, char **argv)
{
  potts_t *pt;
  doargs(argc, argv);
  pt = pt2_open(L, PT2_Q);
  run(pt, nsteps);
  pt2_close(pt);
  return 0;
}

static int saveall(alge_t *al, double *his, double *acc, double *inc, const char *fn)
{
  int i, n = ECNT, ie, ene;
  FILE *fp;
  double tot, fac, x;
  double *bet, *lng, *lngadj;

  /* compute the normalization factor */
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
      bet[i] = al->dh[0];
    } else if (ene >= al->xmax) {
      bet[i] = al->dh[i]; /* use the last i */
    } else {
      ie = (ene - al->xmin)/al->dx;
      bet[i] = al->dh[ie];
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
  fprintf(fp, "# %g\n", tot);
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
