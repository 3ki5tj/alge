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
double alf0 = 5e-4, alfc = 1.0, beta0 = 1.4;
int nevery  = 1000000;
int nreport = 100000000;
char *fnhis = "ep.his";
char *fnout = "pt.e";
int seglen = 10;
int boundary = 1; /* 0: smooth; 1: reflective */
double delmax = 10.f;
double betmax = 100.f;

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

/* entropic sampling */
static int move(potts_t *pt, alge_t *al, int stack[][2], int *nstack)
{
  int id, so, sn, de = 0, nb[PT2_Q], acc;

  PT2_PICK(pt, id, nb);
  PT2_NEWFACE(pt, id, so, sn); /* so --> sn */
  de = nb[so] - nb[sn];
  if (de != 0) {
    /* we always use smooth boundary condition within a segment */
    acc = alge_getacc(al, pt->E + de, pt->E, 0,
      NULL, &de, NULL, NULL);
  } else acc = 1;

  if (acc) { 
    PT2_FLIP(pt, id, so, sn, nb);
    stack[ *nstack ][0] = id;
    stack[ *nstack ][1] = so;
    (*nstack)++;
  }
  return de;
}


/* undo all moves in a segment */
static void undo(potts_t *pt, int stack[][2], int nstack)
{
  int i, id, so, sn, nb[PT2_Q];

  for (i = nstack - 1; i >= 0; i--) {
    id = stack[i][0];
    sn = pt->s[id];
    so = stack[i][1];
    PT2_GETH(pt, id, nb);
    PT2_FLIP(pt, id, sn, so, nb); /* sn --> so */
  }
}

/* save histogram and integrate a finer density of states */
static int saveall(alge_t *al, double *his, const char *fn)
{
  int i, n = ECNT, ie, ene;
  FILE *fp;
  double tot, fac, x;
  double *bet, *lng;

  for (tot = 0., i = 0; i < ECNT; i++)
    tot += his[i];
  if (tot < 0.5) {
    printf("histogram is empty\n");
    return -1;
  }
  fac = 1.0/(tot * EDEL);

  xnew(bet, n + 2);
  xnew(lng, n + 2);

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

  xfopen(fp, fn, "w", return -1);
  fprintf(fp, "# %d %d %d 1 | %g\n",
    al->n, al->xmin, al->dx, tot);
  for (i = 0; i < ECNT; i++) {
    if (his[i] < 0.5)  continue;
    fprintf(fp, "%d %g %.6f %.6f\n",
      EMIN + i * EDEL, his[i]*fac, 
      bet[i], lng[i]);
  }
  fclose(fp);

  free(bet);
  free(lng);
  return 0;
}
 
/* entropic sampling */
static void run(void)
{
  potts_t *pt = pt2_open(L, PT2_Q);
  alge_t *al;
  double *ehis, t, ave2 = 0, alf = 0;
  int it = 0, u1, u0, du;
  int (*stack)[2], nstack = 0;

  xnew(stack, seglen);

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
  
  u0 = pt->E;

  for (t = 1; t <= nsteps; t++) {
    ehis[ (pt->E - EMIN)/EDEL ] += 1;
    move(pt, al, stack, &nstack);

    if (++it % seglen == 0) {
      u1 = pt->E;
      du = u1 - u0;
      assert(u0 >= epmin && u0 < epmax);
      alge_fupdate(al, u0, du, alf0, alfc, &alf, 
            delmax, &ave2, 0, betmax);
      if (u1 < epmin || u1 >= epmax) { /* undo out-of-boudary segments */
        undo(pt, stack, nstack);
        u1 = pt->E;
      }
      u0 = u1; /* set the new start point */
      nstack = 0; /* clear the stack */

      if (it % nevery == 0) {
        printf("t %g, ep %d, du %d, e2 %g, alf %g\n", t, pt->E, du, ave2, alf);
      }

      if (it % nreport == 0 || t >= nsteps - .1) {
        saveall(al, ehis, fnhis);
        alge_save(al, fnout);
        it = 0; /* reset the integer counter */
      }
    }
  }
  alge_close(al);
  pt2_close(pt);
  free(ehis);
  free(stack);
}

int main(int argc, char **argv)
{
  doargs(argc, argv);
  run();
  return 0;
}

