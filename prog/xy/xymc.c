#define ZCOM_PICK
#define ZCOM_ARGOPT
#define ZCOM_AV
#define ZCOM_MD
#define ZCOM_HIST
#include "zcom.h"
#include "alged2.h"

real tp = 1.f;
int nequil  = 10000;
int nsteps  = 10000000;
int seglen  = 5;
int nevery  = 1000000;
int nreport = 10000000;
real mddt = 0.002f;
char *fnout = "cos.xy";
char *fnhis = "xy.his";

/* handle input arguments */
static void doargs(int argc, char **argv)
{
  argopt_t *ao = argopt_open(0);
  argopt_add(ao, "-T", "%r", &tp,    "temperature");
  argopt_add(ao, "-0", "%d", &nequil, "number of equilibration steps");
  argopt_add(ao, "-1", "%d", &nsteps, "number of simulation steps");
  argopt_add(ao, "-l", "%d", &seglen, "the number of steps to be treated as a perturbation");
  argopt_add(ao, "-d", "%r", &mddt,   "molecular dynamics");
  argopt_add(ao, "-o", NULL, &fnout,  "output file");
  argopt_add(ao, "-H", NULL, &fnhis,  "histogram file");
  argopt_add(ao, "--every",   "%d", &nevery,  "interval of printing messages");
  argopt_add(ao, "--report",  "%d", &nreport, "interval of saving data");
  argopt_addhelp(ao, "-h");
  argopt_parse(ao, argc, argv);

  argopt_dump(ao);
  argopt_close(ao);
}

#define DIM 2

/* compute the force */
double force(double r[])
{
  return 0.5 * r[0] * r[0];
  //return 0.5 * (r[0] * r[0] + r[1] * r[1]);
  //return cos(r[0]) * cos(r[1]);
}

/* wrap coordinates to (-pi, pi) */
INLINE double WRAP(double x) {
  while (x < -M_PI) x += 2*M_PI;
  while (x >= M_PI) x -= 2*M_PI;
  return x;
}

/* return the difference */
INLINE double DIFF(double x, double y)
{
  double dx = x - y;

  if (dx > M_PI) return dx - 2 * M_PI;
  else if (dx < -M_PI) return dx + 2 * M_PI;
  else return dx;
}

/* run md simulation */
static int run(void)
{
  int t, i, id, etot = 0, eacc = 0;
  double r[DIM], r1[DIM], ep, ep1, dep;
  double x0 = 0, y0 = 0, x1 = 0, y1 = 0, dx, dy, alf = 0;
  ad2_t *al;
  hist2_t *hs;

  al = ad2_open(-M_PI, M_PI, M_PI/9.999, -M_PI, M_PI, M_PI/9.999,
     0.001, 1.0, 0.0, 0.0);
  hs = hs2_opensqr1(-M_PI, M_PI, M_PI/9.999);

  for (i = 0; i < DIM; i++) {
    r[i] = (rnd0() * 2 - 1) * M_PI;
  }
  ep = force(r);
  id = ad2_getid(al, r[0], r[1]);

  for (t = 1; t <= nsteps; t++) {
    for (i = 0; i < DIM; i++) {
      r1[i] = WRAP( r[i] + (rnd0() - .5) * 1.0 );
    }
    ep1 = force(r1);
    dep = ep1 - ep;
    etot++;
    if (dep <= 0 || rnd0() < exp(-dep)) {
      eacc++;
      for (i = 0; i < DIM; i++) {
        r[i] = r1[i];
      }
      ep = ep1;
    }

    hs2_add1ez(hs, r[0], r[1], 0);

    /* register */
    if (t % seglen == 0) {
      static const double fcmax = 1000000000.0;

      x1 = r[0];
      y1 = r[1];
      dx = DIFF(x1, x0);
      dy = DIFF(y1, y0);
      ad2_add(al, id, dx, dy);
/*
      ad2_getcorr(al, id, &delx, &dely);
      dx += delx;
      dy += dely;
*/
      alf = 0.1;
      al->fx[id] = dblconfine(al->fx[id] + dx * alf, -fcmax, fcmax);
      al->fy[id] = dblconfine(al->fy[id] + dy * alf, -fcmax, fcmax);

      /* set the new start point */
      x0 = x1;
      y0 = y1;
      id = ad2_getid(al, x0, y0);

      if (t % nevery == 0) {
        printf("t %d, x %g, y %g\n", t, r[0], r[1]);
      }
      if (t % nreport == 0) {
        ad2_save(al, fnout);
      }
    }
  }
  printf("acc %g\n", 1.0*eacc/etot);
  ad2_close(al);
  hs2_save(hs, "xy.his", 0);
  return 0;
}

int main(int argc, char **argv)
{
  doargs(argc, argv);
  run();
  return 0;
}
