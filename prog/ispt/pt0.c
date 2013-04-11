/* basic algrihtm E on Potts model
 * does not flatten the histogram
 * quick and dirty entropic sampling
 * stand-alone, does not use alge.h */
#define PT2_LB 5
#define PT2_Q  10
#define L (1 << PT2_LB)
#define N (L*L)
#define EMIN (-2*N)
#define EMAX 0
#define EDEL 1
#define ECNT ((EMAX - EMIN)/EDEL + 1)

#define ZCOM_PICK
#define ZCOM_POTTS2
#define ZCOM_HIST
#include "zcom.h"

int epmin = -1920, epmax = -800, epdel = 4;
double beta0 = 1.4, alpha = 1e-3;
double trun = 1000000*N;

typedef struct {
  int xmin, xmax, dx, n;
  double *f;
} alge_t;

static alge_t *alge_open(int xmin, int xmax, int dx)
{
  alge_t *al;
  int i;
  
  xnew(al, 1);
  al->xmin = xmin;
  al->xmax = xmax;
  al->dx = dx;
  al->n = (xmax - xmin)/dx;
  xnew(al->f, al->n + 1);
  for (i = 0; i <= al->n; i++) al->f[i] = beta0;
  return al;
}

static void alge_close(alge_t *al)
{
  free(al->f);
  free(al);
}

static int alge_savef(alge_t *al, const char *fn)
{
  FILE *fp;
  int i;
  
  xfopen(fp, fn, "w", return -1);
  for (i = 0; i <= al->n; i++)
    fprintf(fp, "%d %.6f\n", al->xmin + i * al->dx, al->f[i]);
  fclose(fp);
  return 0;
}

/* configuration move under modified Hamiltonian, return de */
static void move(potts_t *pt, alge_t *al)
{
  int id, so, sn, eo, en, de, nb[PT2_Q], acc, ie = -1, out = 0;
  double f;

  PT2_PICK(pt, id, nb);
  PT2_NEWFACE(pt, id, so, sn); /* so --> sn */
  de = nb[so] - nb[sn];
  if (de != 0) {
    eo = pt->E;
    en = eo + de;
    ie = (eo - al->xmin)/al->dx;
    f = de*al->f[ie]; /* approximate f, quick and dirty */
    out = (en >= al->xmax || en < al->xmin);
    acc = (f <= 0 || rnd0() < exp(-f));
  } else acc = 1;

  if (acc && de != 0) /* update with a fixed alpha */
    al->f[ie] += alpha * de;
  if (acc && !out) {
    PT2_FLIP(pt, id, so, sn, nb);
  }
}

/* change a random site */
static void randflip(potts_t *pt)
{
  int id, so, sn, nb[PT2_Q];
  PT2_PICK(pt, id, nb);
  PT2_NEWFACE(pt, id, so, sn); /* so --> sn */
  PT2_FLIP(pt, id, so, sn, nb);
}

/* entropic sampling */
static int run(potts_t *pt, double trun)
{
  alge_t *al;
  double *ehis;
  int it;
  
  al = alge_open(epmin, epmax, epdel);
  /* equilibrate the system till pt->E > epmin */
  for (it = 1; pt->E <= epmin + 4; it++) randflip(pt);
  printf("equilibration finished in %d steps\n", it);
  
  xnew(ehis, ECNT);
  for (it = 1; it <= trun; it++) {
    move(pt, al);
    ehis[pt->E - EMIN] += 1;
  }
  histsave(ehis, 1, ECNT, EMIN, EDEL, 0, "epot.his");
  alge_savef(al, "pt0.e");
  alge_close(al);
  free(ehis);
  return 0;
}

int main(void)
{
  potts_t *pt = pt2_open(L, PT2_Q);
  run(pt, trun);
  pt2_close(pt);
  return 0;
}
