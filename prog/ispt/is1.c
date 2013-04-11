/* Algrihtm E on Ising model, zeroth/first order dhde, without using TMH */
#define IS2_LB 5
#define L (1 << IS2_LB)
#define N (L*L)
#define EMIN (-2*N)
#define EMAX (2*N)
#define EDEL 4
#define ECNT ((EMAX - EMIN)/EDEL + 1)

#define ZCOM_PICK
#define ZCOM_ISING2
#define ZCOM_ARGOPT
//#define ZCOM_HIST
#include "zcom.h"
#include "alge.h"

int epmin = -1920, epmax = 0, epdel = 16;
double nsweeps = 1e5, nsteps;
/* alf0 must be small enough */
double alf0 = 5e-4, alfc = 0.5, beta0 = 0.4;
int nevery  = 1000000;
int nreport = 100000000;
double mindata = 1000.0;
char *fnhis = "ep.his";
char *fnout = "is.e";
int seglen = 10;
int boundary = 0; /* 0: smooth; 1: reflective */
double derm = 0.4f, derp = 0.1f;
double dermax = 100.f;

/* handle input arguments */
static void doargs(int argc, char **argv)
{
  argopt_t *ao = argopt_open(0);

  argopt_add(ao, "-1", "%lf", &nsweeps,   "number of simulation SWEEPS (input) or steps (display)");
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

/* configuration move under modified Hamiltonian, return de */
static int move(ising_t *is, const alge_t *al)
{
  int id, de, h, acc;

  IS2_PICK(is, id, h);
  de = 2 * h;  /* h = si * sj, which becomes -h in a flip, E = - si * sj */
  if (de != 0) {
    acc = alge_getacc(al, is->E + de, is->E, boundary,
      NULL, &de, NULL, NULL);
  } else acc = 1;

  if (acc) { IS2_FLIP(is, id, h); }
  return de;
}

/* compute the reference beta */
static void getrefbet(double *refbet, const double *logdos)
{
  int i, len = L*L+1, il, ir;
  double *arr;
  const double ninf = -10000;

  /* smoothed DOS to remove ruggedness */
  xnew(arr, len);
  for (i = 0; i < len; i++) {
    if (logdos[i] > ninf) {
      arr[i] = logdos[i];
      continue;
    }
    for (il = i - 1; il >= 0; il--)
      if (logdos[il] > ninf)
        break;
    if (il < 0) { /* cannot smooth it */
      arr[i] = logdos[i];
      continue;
    }
    for (ir = i + 1; ir < len; ir++)
      if (logdos[ir] > ninf)
        break;
    if (ir >= len) {
      arr[i] = logdos[i];
      continue;
    }
    /* interpolate */
    arr[i] = (logdos[il]*(ir-i) + logdos[ir]*(i-il))/(ir - il);
  }

  refbet[0] = (arr[1] - arr[0])/EDEL;
  refbet[len-1] = (arr[len-1] - arr[len-2])/EDEL;
  for (i = 1; i < len - 1; i++) {
    refbet[i] = (arr[i+1] - arr[i-1])/(2.*EDEL);
  }
  free(arr);
}

/* save histogram */
static int saveall(const alge_t *al, const double *logdos, double *verr,
  const double *his, const double *acc, const double *inc, const char *fn)
{
  int i, n = ECNT, ene, ie = 0;
  FILE *fp;
  double tot, fac, x;
  double *bet, *lng, *lngadj, *refbet;

  /* compute the normalization factor of the histogram */
  for (tot = 0., i = 0; i < n; i++)
    tot += his[i];
  if (tot < 0.5) {
    printf("histogram is empty\n");
    return -1;
  }
  fac = 1.0/(tot * EDEL);

  xnew(bet, n + 2);
  xnew(lng, n + 2);
  xnew(lngadj, n + 2);
  xnew(refbet, n + 2);

  /* compute bet from the reference dos */
  getrefbet(refbet, logdos);

  /* compute a detailed beta and density of states */
  for (lng[0] = 0, i = 0; i <= n; i++) {
    ene = EMIN + i * EDEL;
    if (ene < al->xmin) {
      bet[i] = al->f[0];
    } else if (ene >= al->xmax) {
      bet[i] = al->f[ie]; /* use the last ie */
    } else {
      ie = (ene - al->xmin)/al->dx;
      bet[i] = al->f[ie];
      lng[i + 1] = lng[i] + bet[i] * EDEL;
    }
  }
  /* shift the density of states */
  i = (al->xmin - EMIN)/EDEL;
  x = lng[i] - logdos[i];
  for (i = 0; i <= n; i++) lng[i] -= x;

  /* construct the adjusted density of states */
  for (ene = al->xmin; ene <= al->xmax; ene += EDEL) {
    i = (ene - EMIN)/EDEL;
    lngadj[i] = lng[i] + log(his[i]);
  }
  /* shift the density of states */
  i = (al->xmin - EMIN)/EDEL;
  x = lngadj[i] - logdos[i];
  for (i = 0; i <= n; i++) lngadj[i] -= x;

  /* compute the average and maximal absolute and relative error */
  for (i = 0; i < 8; i++) verr[i] = 0.;
  for (i = 0, ene = al->xmin; ene < al->xmax; ene += EDEL) {
    ie = (ene - EMIN)/EDEL;
    x = fabs(lng[ie] - logdos[ie]);
    verr[0] += x;
    if (x > verr[1]) verr[1] = x;
    x /= logdos[ie];
    verr[2] += x;
    if (x > verr[3]) verr[3] = x;

    x = fabs(lngadj[ie] - logdos[ie]);
    verr[4] += x;
    if (x > verr[5]) verr[5] = x;
    x /= logdos[ie];
    verr[6] += x;
    if (x > verr[7]) verr[7] = x;
    i++;
  }
  verr[0] /= i;
  verr[2] /= i;
  verr[4] /= i;
  verr[6] /= i;

  xfopen(fp, fn, "w", return -1);
  fprintf(fp, "# %d %d %d 1 | %g\n",
    al->n, al->xmin, al->dx, tot);
  for (i = 0; i < ECNT; i++) {
    if (his[i] < 0.5)  continue;
    fprintf(fp, "%d %g %g %g %.6f %.6f %.6f %.6f %.6f\n",
      EMIN + i * EDEL, his[i]*fac, acc[i]*fac, inc[i]*fac,
      bet[i], lng[i], lngadj[i], refbet[i], logdos[i]);
  }
  fclose(fp);

  free(refbet);
  free(bet);
  free(lng);
  free(lngadj);
  return 0;
}

/* entropic sampling */
static int run(ising_t *is, double trun)
{
  alge_t *al;
  double t, *ehis, *eacc, *einc, tote2 = 0., verr[8], duc;
  int it = 0, ie, de, u0 = 0, u1, du = 0;

  al = alge_open(epmin, epmax, epdel, beta0);
  /* equilibrate the system till is->E > epmin */
  for (t = 1; is->E <= epmin + 4; t++) {
    int id, h;
    IS2_PICK(is, id, h);
    IS2_FLIP(is, id, h);
  }
  printf("equilibration finished in %d steps\n", it);

  xnew(ehis, ECNT);
  xnew(eacc, ECNT);
  xnew(einc, ECNT);

  u0 = is->E;

  for (t = 1; t <= trun; t++) {
    ie = (is->E - EMIN)/EDEL;
    ehis[ie] += 1;
    de = move(is, al);
    if (de != 0) {
      eacc[ie] += 1;
      einc[ie] += de*de;
    }

    if (++it % seglen == 0) {
      u1 = is->E;
      du = u1 - u0;
      alge_update(al, u0, du, alf0, alfc, mindata, boundary,
          derm, derp, -dermax, NULL, &duc);
      u0 = u1; /* set the new start point */

      if (it % nevery == 0) {
        printf("t %g, ep %d, du %d, %g\n", t, is->E, du, duc);
        if (it % nreport == 0) {
          saveall(al, is->logdos, verr, ehis, eacc, einc, fnhis);
          alge_save(al, fnout);
          it = 0; /* reset the integer counter */
        }
      }
    }
  }
  saveall(al, is->logdos, verr, ehis, eacc, einc, fnhis);
  printf("trun %g, e2 %g, eabsave0 %g, eabsmax0 %g, erelave0 %g, erelmax0 %g, eabsave1 %g, eabsmax1 %g, erelave1 %g, erelmax1 %g\n",
    trun, tote2/trun, verr[0], verr[1], verr[2], verr[3],
    verr[4], verr[5], verr[6], verr[7]);
  alge_save(al, fnout);
  alge_close(al);
  free(ehis); free(eacc); free(einc);
  return 0;
}

int main(int argc, char **argv)
{
  ising_t *is;

  doargs(argc, argv);
  is = is2_open(L);

  /* read in the density of states */
  die_if (is2_loadlogdos(is, NULL) != 0,
      "no dos for the %dx%d model\n", L, L);

  run(is, nsteps);
  is2_close(is);
  //mtsave(NULL);
  return 0;
}
