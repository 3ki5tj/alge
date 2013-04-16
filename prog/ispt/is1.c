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
double nsweeps = 1e6, nsteps;
/* alf0 must be small enough */
double alf0 = 1e-3, alfc = 5.0, beta0 = 0.4;
int nevery  = 1000000;
int nreport = 100000000;
char *fnhis = "ep.his";
char *fnout = "is.e";
int seglen = 10;
int boundary = 0; /* 0: smooth; 1: reflective */
double delmax = 10.f;
double betmax = 100.f;

/* handle input arguments */
static void doargs(int argc, char **argv)
{
  argopt_t *ao = argopt_open(0);

  argopt_add(ao, "-1", "%lf", &nsweeps,   "number of simulation SWEEPS (input) or steps (display)");
  argopt_add(ao, "-(", "%d",  &epmin,     "minimal energy");
  argopt_add(ao, "-)", "%d",  &epmax,     "maximal energy");
  argopt_add(ao, "-:", "%d",  &epdel,     "energy interval");
  argopt_add(ao, "-l", "%d",  &seglen,    "the number of steps to be treated as a perturbation");
  argopt_add(ao, "-K", "%lf", &betmax,    "maximal temperature");
  argopt_add(ao, "-b", "%d",  &boundary,  "boundary condition, 0: smooth, 1: reflective");
  argopt_add(ao, "--a0", "%lf", &alf0,    "maximal amplitude");
  argopt_add(ao, "--ac", "%lf", &alfc,    "alpha_c");
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
static int move(ising_t *is, const alge_t *al, int stack[], int *nstack)
{
  int id, de, h, acc;

  IS2_PICK(is, id, h);
  de = 2 * h;  /* h = si * sj, which becomes -h in a flip, E = - si * sj */
  if (de != 0) {
    acc = alge_getacc(al, is->E + de, is->E, boundary,
      NULL, &de, NULL, NULL);
  } else acc = 1;

  if (acc) {
    IS2_FLIP(is, id, h);
    stack[ (*nstack)++ ] = id;
  }
  return de;
}


static void undo(ising_t *is, int stack[], int nstack)
{
  int i, id, h;

  for (i = nstack - 1; i >= 0; i--) {
    id = stack[i];
    IS2_GETH(is, id, h);
    IS2_FLIP(is, id, h);
  }
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

/* save histogram and integrate a finer density of states */
static int saveall(const alge_t *al, const double *logdos, double *verr,
  const double *his, const char *fn)
{
  int i, n = ECNT, ene, ie = 0;
  FILE *fp;
  double tot, fac, x;
  double *bet, *lng, *refbet;

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

  /* compute the average and maximal absolute and relative error */
  for (i = 0; i < 4; i++) verr[i] = 0.;
  for (i = 0, ene = al->xmin; ene < al->xmax; ene += EDEL) {
    ie = (ene - EMIN)/EDEL;
    x = fabs(lng[ie] - logdos[ie]);
    verr[0] += x;
    if (x > verr[1]) verr[1] = x;
    x /= logdos[ie];
    verr[2] += x;
    if (x > verr[3]) verr[3] = x;

    i++;
  }
  verr[0] /= i;
  verr[2] /= i;

  xfopen(fp, fn, "w", return -1);
  fprintf(fp, "# %d %d %d 1 | %g\n",
    al->n, al->xmin, al->dx, tot);
  for (i = 0; i < ECNT; i++) {
    if (his[i] < 0.5)  continue;
    fprintf(fp, "%d %g %.6f %.6f %.6f %.6f\n",
      EMIN + i * EDEL, his[i]*fac,
      bet[i], lng[i], refbet[i], logdos[i]);
  }
  fclose(fp);

  free(refbet);
  free(bet);
  free(lng);
  return 0;
}

/* entropic sampling */
static int run(ising_t *is, double trun)
{
  alge_t *al;
  double t, *ehis, verr[8], ave2 = 0, alf = 0;
  int it = 0, u0 = 0, u1, du = 0;
  int *stack, nstack = 0;

  xnew(stack, seglen);

  al = alge_open(epmin, epmax, epdel, beta0);
  /* equilibrate the system till is->E > epmin */
  for (t = 1; is->E <= epmin + 4; t++) {
    int id, h;
    IS2_PICK(is, id, h);
    IS2_FLIP(is, id, h);
  }
  printf("equilibration finished in %d steps\n", it);

  xnew(ehis, ECNT);

  u0 = is->E;

  for (t = 1; t <= trun; t++) {
    ehis[ (is->E - EMIN)/EDEL ] += 1;
    move(is, al, stack, &nstack);

    if (++it % seglen == 0) {
      u1 = is->E;
      du = u1 - u0;
      assert(u0 >= epmin && u0 < epmax);
      alge_fupdate(al, u0, du, alf0, alfc, &alf,
          delmax, &ave2, 0, betmax);
      if (u1 < epmin || u1 >= epmax) { /* undo out-of-boudary segments */
        undo(is, stack, nstack);
        u1 = is->E;
      }
      u0 = u1; /* set the new start point */
      nstack = 0; /* clear the stack */

      if (it % nevery == 0) {
        printf("t %g, ep %d, du %d, e2 %g, alf %g\n", t, is->E, du, ave2, alf);
      }

      if (it % nreport == 0 || t >= nsteps - .1) {
        saveall(al, is->logdos, verr, ehis, fnhis);
        printf("trun %g, eabsave %g, eabsmax %g, erelave %g, erelmax %g\n",
          trun, verr[0], verr[1], verr[2], verr[3]);        
        alge_save(al, fnout);
        it = 0; /* reset the integer counter */
      }
    }
  }
  alge_close(al);
  free(ehis);
  free(stack);
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
