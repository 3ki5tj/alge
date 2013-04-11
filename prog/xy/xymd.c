#define ZCOM_PICK
#define ZCOM_ARGOPT
#define ZCOM_AV
#define ZCOM_MD
#define ZCOM_HIST
#include "zcom.h"
#include "alged2.h"

real tp = 1.f;
int nequil  = 10000;
int nsteps  = 1000000000;
int seglen  = 100;
int nevery  = 1000000;
int nreport = 100000000;
real mddt = 0.002f;
char *fnout = "cos.xy";

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
  argopt_add(ao, "--every",   "%d", &nevery,  "interval of printing messages");
  argopt_add(ao, "--report",  "%d", &nreport, "interval of saving data");
  argopt_addhelp(ao, "-h");
  argopt_parse(ao, argc, argv);

  argopt_dump(ao);
  argopt_close(ao);
}

#define DIM 2

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

/* compute the force */
double force(double r[], double f[])
{
  f[0] = -r[0]; f[1] = 0; return 0.5 * (r[0] * r[0]);
  //f[0] = -r[0]; f[1] = -r[1]; return 0.5 * (r[0] * r[0] + r[1] * r[1]);
}

/*
double force(double r[], double f[])
{
  double ep = 1.;
  int i, j;
  
  for (i = 0; i < DIM; i++) {
    f[i] = 1.;
    for (j = 0; j < DIM; j++) {
      if (i == j) f[i] *= sin(r[j]);
      else f[i] *= cos(r[j]);
    }
    ep *= cos(r[i]);
  }
  return ep;
}
*/
/* apply the biased force */
static void forceb(double f[], double fx, double fy)
{
  /* negate the mean force */
  f[0] -= fx;
  f[1] -= fy;
}

/* run md simulation */
static int run(void)
{
  int t, i, id;
  double r[DIM], f[DIM], v[DIM];
  double x0 = 0, y0 = 0, x1 = 0, y1 = 0, dx, dy, fx = 0, fy = 0, alf = 0;
  ad2_t *al;
  
  al = ad2_open(-M_PI, M_PI, 0.6, -M_PI, M_PI, 0.6,
     0.001, 1.0, 0.0, 0.0);

  for (i = 0; i < DIM; i++) {
    r[i] = (rnd0() * 2 - 1) * M_PI ;
    f[i] = 0;
    v[i] = grand0() * sqrt(tp);
  }
  force(r, f);
  
  x0 = r[0];
  y0 = r[1];
  id = ad2_getid(al, x0, y0);

  for (t = 1; t <= nsteps; t++) {
    /* velocity verlet */
    for (i = 0; i < DIM; i++) {
      v[i] += f[i] * mddt * .5f;
      r[i] += v[i] * mddt;

      /* wrap coordinates into (-pi, pi) */
      r[i] = WRAP(r[i]);
    }

    force(r, f);
    ad2_getf(al, r[0], r[1], &fx, &fy);
    forceb(f, fx, fy);
    for (i = 0; i < DIM; i++)
      v[i] += f[i] * mddt * .5f;

    /* andersen thermostat */
    if (t % 10 == 0)  v[(int)(rnd0() * DIM)] = sqrt(tp) * grand0();
    
    /* velocity rescaling thermostat */
    //md_vrescalex(v, DIM, DIM, tp, 0.1, NULL, NULL);
    
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
  ad2_close(al);
  return 0;
}

int main(int argc, char **argv)
{
  doargs(argc, argv);
  run();
  return 0;
}
