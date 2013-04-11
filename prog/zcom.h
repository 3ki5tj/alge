/*
  common routines
  Copyright (c) 2006-2012 Cheng Zhang

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public License
  as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA

  Usage:

  1.  It is designed for quick programming.
      For simple use, include this file and all functions will be available.
      But there might be many compiler warnings for unused functions.

  2.  You can include this file multiple times in a single file.

  3.  Function are static by default. To export functions,
      e.g., to make it easier to debug, or to avoid warnings of unused functions,
      define ZCOM_XFUNCS before the first inclusion.

  4.  To hand-pick specific set of modules, e.g.,
        #define ZCOM_PICK
        #define ZCOM_RNG
        #define ZCOM_ARGOPT
      before including this file, so other modules are skipped.

  5.  If the compiler supports keywords inline and restrict, write
        #define INLINE inline
        #define RESRICT restrict
      before including this file. Otherwise the two keywords are guessed
      according to the compiler.

  6.  Define HAVEVAM if the compiler supports variable-argument macros.

  7.  The def module defines `real' as a double, to override it, write
        typedef float real;
        #define HAVEREAL 1
      before including this file (or equivalently define HAVE_REAL)
*/

/* ZCOM_PICK or ZCOM_NONE is used include only subset of modules
 * 1. to reduce the number of warnings for unused functions
 * 2. to reduce the compiling time
 * 3. to avoid potential name conflicts
 * By default, ZCOM_PICK is undefined, so everything is used. */
#ifdef ZCOM_NONE  /* equivalent to ZCOM_PICK */
#define ZCOM_PICK
#endif

#ifndef ZCOM_PICK
  #ifndef ZCOM_DEF
  #define ZCOM_DEF
  #endif
  #ifndef ZCOM_UTIL
  #define ZCOM_UTIL
  #endif
  #ifndef ZCOM_SS
  #define ZCOM_SS
  #endif
  #ifndef ZCOM_ENDN
  #define ZCOM_ENDN
  #endif
  #ifndef ZCOM_BIO
  #define ZCOM_BIO
  #endif
  #ifndef ZCOM_OSYS
  #define ZCOM_OSYS
  #endif
  #ifndef ZCOM_RNG
  #define ZCOM_RNG
  #endif
  #ifndef ZCOM_RC
  #define ZCOM_RC
  #endif
  #ifndef ZCOM_RV2
  #define ZCOM_RV2
  #endif
  #ifndef ZCOM_RV3
  #define ZCOM_RV3
  #endif
  #ifndef ZCOM_EIG
  #define ZCOM_EIG
  #endif
  #ifndef ZCOM_LU
  #define ZCOM_LU
  #endif
  #ifndef ZCOM_SVD
  #define ZCOM_SVD
  #endif
  #ifndef ZCOM_ROTFIT
  #define ZCOM_ROTFIT
  #endif
  #ifndef ZCOM_SAVGOL
  #define ZCOM_SAVGOL
  #endif
  #ifndef ZCOM_SPECFUNC
  #define ZCOM_SPECFUNC
  #endif
  #ifndef ZCOM_OPT
  #define ZCOM_OPT
  #endif
  #ifndef ZCOM_ARGOPT
  #define ZCOM_ARGOPT
  #endif
  #ifndef ZCOM_CFG
  #define ZCOM_CFG
  #endif
  #ifndef ZCOM_LOG
  #define ZCOM_LOG
  #endif
  #ifndef ZCOM_AV
  #define ZCOM_AV
  #endif
  #ifndef ZCOM_HIST
  #define ZCOM_HIST
  #endif
  #ifndef ZCOM_DISTR
  #define ZCOM_DISTR
  #endif
  #ifndef ZCOM_RPT
  #define ZCOM_RPT
  #endif
  #ifndef ZCOM_MDS
  #define ZCOM_MDS
  #endif
  #ifndef ZCOM_PDB
  #define ZCOM_PDB
  #endif
  #ifndef ZCOM_CLUS
  #define ZCOM_CLUS
  #endif
  #ifndef ZCOM_MD
  #define ZCOM_MD
  #endif
  #ifndef ZCOM_WLCVG
  #define ZCOM_WLCVG
  #endif
  #ifndef ZCOM_TMH
  #define ZCOM_TMH
  #endif
  #ifndef ZCOM_ISING2
  #define ZCOM_ISING2
  #endif
  #ifndef ZCOM_POTTS2
  #define ZCOM_POTTS2
  #endif
  #ifndef ZCOM_LJ
  #define ZCOM_LJ
  #endif
  #ifndef ZCOM_ABPRO
  #define ZCOM_ABPRO
  #endif
  #ifndef ZCOM_CAGO
  #define ZCOM_CAGO
  #endif
#endif

/* build dependencies */
#ifdef ZCOM_GLEZ
  #define ZCOM_RV3
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_CAGO
  #define ZCOM_MD
  #define ZCOM_PDB
  #define ZCOM_AV
  #define ZCOM_ROTFIT
#endif

#ifdef ZCOM_ABPRO
  #define ZCOM_MD
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_LJ
  #define ZCOM_MD
  #define ZCOM_HIST
#endif

#ifdef ZCOM_POTTS2
  #define ZCOM_RNG
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_ISING2
  #define ZCOM_RNG
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_TMH
  #define ZCOM_WLCVG
  #define ZCOM_AV
  #define ZCOM_RNG
#endif

#ifdef ZCOM_WLCVG
  #define ZCOM_HIST
#endif

#ifdef ZCOM_MD
  #define ZCOM_RV3
  #define ZCOM_RV2
#endif

#ifdef ZCOM_CLUS
  #define ZCOM_MDS
  #define ZCOM_RNG
#endif

#ifdef ZCOM_PDB
  #define ZCOM_RV3
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_MDS
  #define ZCOM_EIG
#endif

#ifdef ZCOM_RPT
  #define ZCOM_HIST
  #define ZCOM_AV
#endif

#ifdef ZCOM_DISTR
  #define ZCOM_SPECFUNC
  #define ZCOM_DEF
#endif

#ifdef ZCOM_HIST
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_AV
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_LOG
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_CFG
  #define ZCOM_OPT
#endif

#ifdef ZCOM_ARGOPT
  #define ZCOM_OPT
#endif

#ifdef ZCOM_OPT
  #define ZCOM_SS
  #define ZCOM_UTIL
  #define ZCOM_DEF
#endif

#ifdef ZCOM_SPECFUNC
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_SAVGOL
  #define ZCOM_LU
#endif

#ifdef ZCOM_ROTFIT
  #define ZCOM_RV3
#endif

#ifdef ZCOM_SVD
  #define ZCOM_UTIL
  #define ZCOM_DEF
#endif

#ifdef ZCOM_LU
  #define ZCOM_DEF
#endif

#ifdef ZCOM_EIG
  #define ZCOM_UTIL
  #define ZCOM_DEF
#endif

#ifdef ZCOM_RV3
  #define ZCOM_RNG
  #define ZCOM_DEF
#endif

#ifdef ZCOM_RV2
  #define ZCOM_RNG
  #define ZCOM_DEF
#endif

#ifdef ZCOM_RC
  #define ZCOM_DEF
#endif

#ifdef ZCOM_OSYS
  #define ZCOM_SS
  #define ZCOM_UTIL
#endif

#ifdef ZCOM_BIO
  #define ZCOM_ENDN
#endif


/* manage storage class: static is the safer choice
   to avoid naming conclict.  Example:
   both m.c and n.c include this file,
   m.c --> m.o, n.c --> n.o, m.o+n.o --> a.out
   static is the only way to avoid naming conflict in this case.

   In case that this file is included multiple times,
   ZCOM_XFUNCS should be defined before the first inclusion,
   otherwise it won't be effective in deciding storage class. */
#ifndef STRCLS
  #ifndef ZCOM_XFUNCS
    #define STRCLS static
  #else
    #define STRCLS
  #endif
#endif

/* inline keyword */
#ifndef INLINE
  #if defined(__GNUC__) || defined(__xlC__)
    #define INLINE STRCLS __inline__
  #elif defined(__INTEL_COMPILER)
    #define INLINE STRCLS __inline
  #elif defined(_MSC_VER) || defined(__BORLANDC__)
    #define INLINE __inline STRCLS
  #elif defined(__STDC_VERSION__) && (STDC_VERSION__ >= 199901L)
    #define INLINE STRCLS inline
  #else
    #define INLINE STRCLS
  #endif
#endif

/* restrict keyword */
#ifndef RESTRICT
  #if (defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__xlC__) \
      || (defined(_MSC_VER) && _MSC_VER >= 1400))
    #define RESTRICT __restrict
  #elif defined(__STDC_VERSION__) && (STDC_VERSION__ >= 199901L)
    #define RESTRICT restrict
  #else
    #define RESTRICT
  #endif
#endif

/* macros with variable-length arguments */
#ifndef HAVEVAM
  #if (  (defined(__GNUC__) && (__GNUC__ >= 3))   \
      || (defined(__xlC__)  && (__xlC__ >= 0x0700)) \
      || (defined(_MSC_VER) && (_MSC_VER >= 1400)) )
    #define HAVEVAM 1
  #endif
#endif

#ifdef __INTEL_COMPILER
  #pragma warning(disable:981) /* unspecified order warning */
  #pragma warning(disable:177) /* unreferenced function */
  #pragma warning(disable:161) /* unrecognized #pragma, for omp */
#elif defined(__GNUC__) && (__GNUC__ >= 4 && __GNUC_MINOR__ >= 2)
  #pragma GCC diagnostic ignored "-Wunknown-pragmas"
  #pragma GCC diagnostic ignored "-Wvariadic-macros"
#endif

#ifdef _MSC_VER
  #pragma warning(disable:4127) /* conditional expression constant */
  #pragma warning(disable:4505) /* unreferenced function */
  #pragma warning(disable:4514) /* unreferenced inline */
  #pragma warning(disable:4710) /* not inlined */
  #define _CRT_SECURE_NO_DEPRECATE /* suppress CRT safety warnings */
  #include <stdio.h>
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* In addition to ZCOM_ABC, we have to define another macro ZCOM_ABC__
 * in order to avoid multiple inclusions.
 * A single ZCOM_ABC__ won't do because different module-set may be selected */

#ifdef  ZCOM_DEF
#ifndef ZCOM_DEF__
#define ZCOM_DEF__
#include <float.h>

/* define a real type */
#ifdef HAVE_REAL
  #ifndef HAVEREAL
  #define HAVEREAL HAVE_REAL
  #endif
#endif

#ifndef HAVEREAL
  #define HAVEREAL 1
  typedef double real;
#endif

#endif /* ZCOM_DEF__ */
#endif /* ZCOM_DEF */

#ifdef  ZCOM_UTIL
#ifndef ZCOM_UTIL__
#define ZCOM_UTIL__
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <float.h>

#ifndef xnew
#define xnew(x, n) \
  if (#n[0] != '1' && (n) <= 0) { \
    fprintf(stderr, "cannot allocate %d objects for %s\n", (int) (n), #x); \
    exit(1); \
  } else if ((x = calloc(n, sizeof(*(x)))) == NULL) { \
    fprintf(stderr, "no memory for %s x %u\n", #x, (unsigned) (n)); \
    exit(1); }
#endif

#ifndef xrenew
#define xrenew(x, n) \
  if ((n) <= 0) { \
    fprintf(stderr, "cannot allocate %d objects for %s\n", (int) (n), #x); \
    exit(1); \
  } else if ((x = realloc(x, (n)*sizeof(*(x)))) == NULL) { \
    fprintf(stderr, "no memory for %s x %u\n", #x, (unsigned) (n)); \
    exit(1); }
#endif

/* print an error message */
INLINE void perrmsg__(const char *file, int line, const char *why,
    const char *fmt, va_list args)
{
  fprintf(stderr, "error: ");
  vfprintf(stderr, fmt, args);
  if (fmt[strlen(fmt) - 1] != '\n')
    fprintf(stderr, "\n"); /* add a new line if needed */
  if (file != NULL) fprintf(stderr, "file: %s\n", file);
  if (line >= 0) fprintf(stderr, "line: %d\n", line);
  if (why != NULL && strcmp(why, "1") != 0)
    fprintf(stderr, "cond: %s\n", why);
}

#ifdef HAVEVAM

INLINE void perrmsg_(const char *file, int line, const char *why,
    int cond, const char *fmt, ...)
{
  if (cond) {
    va_list args;
    va_start(args, fmt);
    perrmsg__(file, line, why, fmt, args);
    va_end(args);
    exit(1);
  }
}

#define die_if(cond, fmt, ...) \
  perrmsg_(__FILE__, __LINE__, #cond, cond, fmt, ## __VA_ARGS__)
#define fatal(fmt, ...)  die_if(1, fmt, ## __VA_ARGS__)

#else /* !HAVEVAM */

#define PERRMSG__(c) {                        \
  if ((#c[0] == '1' && #c[1] == '\0') || c) { \
    va_list args;                             \
    va_start(args, fmt);                      \
    perrmsg__(NULL, -1, NULL, fmt, args);     \
    va_end(args);                             \
    exit(1);                                  \
  } }
INLINE void die_if(int cond, const char *fmt, ...) PERRMSG__(cond)
INLINE void fatal(const char *fmt, ...) PERRMSG__(1)
#undef PERRMSG__

#endif /* HAVEVAM */

#define xfopen(fp, fn, fmt, err) \
  if ((fp = fopen(fn, fmt)) == NULL) { \
    fprintf(stderr, "cannot open file %s\n", fn); err; }

INLINE int fexists(const char *fn)
{
  FILE *fp;
  if ((fp = fopen(fn, "r")) == NULL) return 0;
  else { fclose(fp); return 1; }
}

/* swap two variables */
#ifndef xtpswap
#define xtpswap(tp, x, y) { tp dum_; dum_ = (x); (x) = (y); (y) = dum_; }
#endif

#ifndef intswap
#define intswap(x, y) xtpswap(int, x, y)
#endif

#ifndef dblswap
#define dblswap(x, y) xtpswap(double, x, y)
#endif

INLINE int intmax(int x, int y) { return x > y ? x : y; }
INLINE int intmin(int x, int y) { return x < y ? x : y; }
/* confine x within [xmin, xmax] */
INLINE int intconfine(int x, int xmin, int xmax)
  { return x < xmin ? xmin : x > xmax ? xmax : x; }

INLINE int intsqr(int x) { return x * x; }

/* get the pair index from 0 to n*(n - 1)/2 - 1 */
INLINE int getpairindex(int i, int j, int n)
{
  die_if (i < 0 || i >= n || j < 0 || j >= n || i == j,
      "bad index error i %d, j %d, n %d\n", i, j, n);
  if (i > j) { int i1 = i; i = j; j = i1; }
  return n*i - (i + 1)*(i + 2)/2 + j;
}

/* return individual indices for a given pair index */
INLINE int parsepairindex(int id, int n, int *i, int *j)
{
  int i1, n1;
  die_if (id < 0 || id >= n*(n - 1)/2, "index %d too large for n %d\n", id, n);
  for (i1 = n - 2; i1 >= 0; i1--) {
    if (id >= (n1 = i1*n - i1*(i1 + 1)/2)) {
      *i = i1;
      *j = id - n1 + i1 + 1;
      return 0;
    }
  }
  return 1;
}

INLINE double dblmax(double x, double y) { return x > y ? x : y; }
INLINE double dblmin(double x, double y) { return x < y ? x : y; }
/* confine x within [xmin, xmax] */
INLINE double dblconfine(double x, double xmin, double xmax)
  { return x < xmin ? xmin : x > xmax ? xmax : x; }

INLINE double dblsqr(double x) { return x * x; }

/* sqrt(x*x + y*y) */
INLINE double dblhypot(double x, double y)
{
  double t;
  x = fabs(x);
  y = fabs(y);
  if (x <= 0.) return y;
  else if (y <= 0.) return x;
  if (x < y) t = x, x = y, y = t;
  t = y/x;
  return x*sqrt(1+t*t);
}

/* round x to a multiple dx  */
INLINE double dblround(double x, double dx)
{
  if (x*dx > 0) return dx * (int)(x/dx + (.5 - DBL_EPSILON));
  else return -dx * (int)(-x/dx + (.5 - DBL_EPSILON));
}

INLINE void dblcleararr(double *x, int n)
  { int i; for (i = 0; i < n; i++) x[i] = 0.0; }

#ifndef LNADD_DEFINED
#define LNADD_DEFINED
#define LN_BIG 50.0

/* log(exp(a) + exp(b)) */
INLINE double lnadd(double a, double b)
{
  double c;
  if (a < b) { c = a; a = b; b = c; } /* ensure a >= b */
  return ((c = a-b) > LN_BIG) ? a : a + log(1 + exp(-c));
}

/* log(exp(a) - exp(b)), only works for a > b */
INLINE double lndif(double a, double b)
{
  double c;
  die_if (a < b, "lndif: %g < %g\n", a, b);
  return ((c = a-b) > LN_BIG) ? a : a + log(1 - exp(-c));
}

/* log(exp(a)+b) */
INLINE double lnaddn(double a, double b)
{
  return (a > LN_BIG) ? a : a + log(1 + b*exp(-a));
}

#undef LN_BIG
#endif  /* LNADD_DEFINED */

#define cisalnum(c)   isalnum((unsigned char)(c))
#define cisalpha(c)   isalpha((unsigned char)(c))
#define cisdigit(c)   isdigit((unsigned char)(c))
#define cisxdigit(c)  isxdigit((unsigned char)(c))
#define cisprint(c)   isprint((unsigned char)(c))
#define cisspace(c)   isspace((unsigned char)(c))
#define cislower(c)   islower((unsigned char)(c))
#define cisupper(c)   isupper((unsigned char)(c))
#define ctolower(c)   (char) tolower((unsigned char)(c))
#define ctoupper(c)   (char) toupper((unsigned char)(c))

/* string manipulation */
#define ZSTR_XSPACEL  0x0001
#define ZSTR_XSPACER  0x0002
#define ZSTR_XSPACE   (ZSTR_XSPACEL|ZSTR_XSPACER)
#define ZSTR_COPY     0x0004
#define ZSTR_CAT      0x0008
#define ZSTR_CASE     0x0100
#define ZSTR_UPPER_   0x0200
#define ZSTR_UPPER    (ZSTR_CASE|ZSTR_UPPER_)
#define ZSTR_LOWER    ZSTR_CASE

/* remove leading and trailing spaces */
#define strip(s)  stripx(s, ZSTR_XSPACE)
#define lstrip(s) stripx(s, ZSTR_XSPACEL)
#define rstrip(s) stripx(s, ZSTR_XSPACER)
INLINE char *stripx(char *s, unsigned flags)
{
  char *p;

  if (flags & ZSTR_XSPACEL) { /* remove leading spaces */
    for (p = s; cisspace(*p); p++) ;
    if (*p == '\0') *s = '\0';
    else memmove(s, p, strlen(p)+1);
  }
  if (flags & ZSTR_XSPACER) /* remove trailing spaces */
    for (p = s + strlen(s) - 1; p >= s && cisspace(*p); p--)
      *p = '\0';
  return s;
}

/* in the follows, size_s means the buffer size of s, i.e., sizeof(s) for static strings */
/* copy the string and convert it to upper/lower case */
#define strcpy2u(s, t, size_s) strcnv(s, t, size_s - 1, ZSTR_COPY|ZSTR_UPPER)
#define strcpy2l(s, t, size_s) strcnv(s, t, size_s - 1, ZSTR_COPY|ZSTR_LOWER)
#define strcpy_sf(s, t, size_s) strcnv(s, t, size_s - 1, ZSTR_COPY)
#define substr(s, t, start, len) strcnv(s, t+start, len, ZSTR_COPY)
/* concatenate strings, the last parameter is the buffer size of s,
 * unlike strncat(), in which it's the number of characters from *t* to be copied.  */
#define strcat_sf(s, t, size_s) strcnv(s, t, size_s - 1, ZSTR_CAT)
/* safely copy/cat strings with case conversion
 * unlike strncpy(), s is always null-terminated on return: it copies at most
 * len nonblank characters, i.e., s[len] = '\0' for the longest output */
INLINE char *strcnv(char *s, const char *t, size_t len, unsigned flags)
{
  size_t i = 0, j;
  unsigned docase = flags & ZSTR_CASE, up = flags & ZSTR_UPPER_;

  if (len == 0 || s == NULL || t == NULL) return s;
  if (flags & ZSTR_CAT) while(s[i]) i++;
  for (j = 0; i < len; i++, j++) {
    if (docase && t[j]) {
      if (up) s[i] = (char) (unsigned char) toupper((unsigned char) t[j]);
      else    s[i] = (char) (unsigned char) tolower((unsigned char) t[j]);
    } else s[i] = t[j];
    if (t[j] == 0) break;
  }
  if (i == len) s[i] = '\0';
  if (flags & ZSTR_XSPACE) stripx(s, flags); /* call strip */
  return s;
}

/* compare strings without case */
#define strcmpnc(s, t) strncmpnc(s, t, -1)
INLINE int strncmpnc(const char *s, const char *t, int n)
{
  int i, cs, ct;

  if (s == NULL || t == NULL) return 0;
  for (i = 0; ; i++) {
    if (i >= n) return 0;
    cs = s[i];
    ct = t[i];
    if (cs == 0 || ct == 0) break;
    cs = toupper( (unsigned char) cs );
    ct = toupper( (unsigned char) ct );
    if (cs != ct) break;
  }
  return cs-ct;
}

#endif /* ZCOM_UTIL__ */
#endif /* ZCOM_UTIL */

#ifdef  ZCOM_SS
#ifndef ZCOM_SS__
#define ZCOM_SS__

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

/* operation code */
enum { SSCAT = 1, SSDELETE = 2, SSSHRINK = 3, SSSINGLE = 0x1000 };

#define ssnew(n)       sscpycatx(NULL, NULL, (n),    0)
#define ssdup(t)       sscpycatx(NULL, (t),   0,     0)
#define sscpy(s, t)    sscpycatx(&(s), (t),   0,     0)
#define sscat(s, t)    sscpycatx(&(s), (t),   0, SSCAT)
#define ssdel(s)       ssmanage((s), SSDELETE|SSSINGLE)
#define ssdelete(s)    { ssdel(s); (s)=NULL; }
#define ssshrink(s)    ssmanage((s), SSSHRINK|SSSINGLE)
#define ssdelall()     ssmanage(NULL, SSDELETE)
#define ssshrinkall()  ssmanage(NULL, SSHRINK)
#define ssfgets(s, pn, fp)    ssfgetx(&(s), (pn), '\n', (fp))
#define ssfgetall(s, pn, fp)  ssfgetx(&(s), (pn), EOF, (fp))

INLINE int   ssmanage(char *, unsigned);
INLINE char *sscpycatx(char **, const char *, size_t, unsigned);
INLINE char *ssfgetx(char **, size_t *, int, FILE *fp);

INLINE char **ssparse(char *s, int *pn, const char *delim);


#ifndef SSMINSIZ /* to override the block size, define it before inclusion */
#define SSMINSIZ 256 /* at least sizeof(int), but change this value to 1 for debugging */
#endif
#ifndef SSHASHBITS
#define SSHASHBITS 8
#endif
#define SSHASHSIZ   (1 << SSHASHBITS)
#define SSOVERALLOC 1
#define sscalcsize_(n) (((n)/SSMINSIZ + 1) * SSMINSIZ) /* size for n nonblank characters */

struct ssheader {
  size_t size;
  size_t hashval;
  struct ssheader *next;
} ssbase_[SSHASHSIZ] = {{ 0u, 0u, NULL }};

/* we use the string address instead of that of the pointer
 * to struct ssheader to compute the Hash value,
 * because the former is more frequently used in e.g. looking-up
 * */
INLINE size_t sshashval_(const char *p)
{
  size_t val = (size_t) p * 1664525u + 1013904223u;
  return (val >> (sizeof(size_t)*8-SSHASHBITS)) & ((1<<SSHASHBITS)-1);
}

/*
 * return the *previous* header to the one that associates with s
 * first locate the list from the Hash value, then enumerate the linked list.
 * */
INLINE struct ssheader *sslistfind_(const char *s)
{
  struct ssheader *hp, *head;

  if (s == NULL) return NULL;
  head = ssbase_ + sshashval_(s);
  if (head->next == NULL) return NULL; /* uninitialized head node */
  for (hp = head; hp->next != head; hp = hp->next)
    if ((char *)(hp->next + 1) == s)
      return hp;
  return NULL;
}

/*
 * simply add the entry h at the begining of the list
 * we do not accept a precalculated hash value,
 * since realloc might have changed it
 * */
INLINE struct ssheader *sslistadd_(struct ssheader *h)
{
  struct ssheader *head;

  head = ssbase_ + sshashval_( (char *)(h+1) );
  if (head->next == NULL) /* initialize the base */
    head->next = head;
  h->next = head->next;
  head->next = h;
  return head;
}

/* remove hp->next */
INLINE void sslistremove_(struct ssheader *hp, int f)
{
  struct ssheader *h = hp->next;

  hp->next = h->next;
  if (f) free(h);
}

/* (re)allocate memory for (*php)->next, update list, return the new string
 * n is the number of nonempty characters, obtained e.g. from strlen().
 * create a new header if *php is NULL, in this case, the first character
 * of the string is '\0'
 * */
INLINE char *ssresize_(struct ssheader **php, size_t n, unsigned flags)
{
  struct ssheader *h = NULL, *hn, *hp;
  size_t size;

  if (php == NULL) {
    fprintf(stderr, "ssresize_: php is NULL, n = %u", (unsigned) n);
    return NULL;
  }

  /* we use the following if to assign hp and h, so the order is crucial */
  if ((hp = *php) == NULL || (h = hp->next)->size < n + 1 || !(flags & SSOVERALLOC)) {
    size = sscalcsize_(n);
    if (h == NULL || size != h->size) {
      /* remove h from the list  */
      if (hp != NULL) sslistremove_(hp, 0);
      if ((hn = calloc(sizeof(*h) + size, 1)) == NULL) {
        fprintf(stderr, "ssresize_: no memory for %u\n", (unsigned) size);
        return NULL;
      }
      if (h != NULL) {
        memcpy(hn, h, sizeof(*hn) + (size > h->size ? h->size : size));
        free(h);
      }
      h = hn;

      *php = hp = sslistadd_(h);
      hp->next->size = size;
    }
  }
  return (char *)(hp->next + 1);
}

INLINE void ssmanage_low_(struct ssheader *hp, unsigned opt)
{
  if (opt == SSDELETE)
    sslistremove_(hp, 1);
  else if (opt == SSSHRINK)
    ssresize_(&hp, strlen((char *)(hp->next+1)), 0);
}

/* delete a string, shrink memory, etc ... */
INLINE int ssmanage(char *s, unsigned flags)
{
  struct ssheader *hp, *head;
  unsigned opt = flags & 0xFF;
  size_t i;

  if (flags & SSSINGLE) {
    if (s == NULL || (hp = sslistfind_(s)) == NULL) {
      if (s) fprintf(stderr, "ssmanage: unknown address %p (%s)\n",  s, s);
      return -1;
    }
    ssmanage_low_(hp, opt);
  } else {
    for (i = 0; i < SSHASHSIZ; i++)
      for (hp = head = ssbase_+i; hp->next && hp->next != head; hp = hp->next)
        /* we must not operate on h itself, which renders the iterator h invalid */
        ssmanage_low_(hp, opt);
  }
  return 0;
}

/*
 * copy/cat t to *ps
 *
 * If (flags & SSCAT) == 0:
 * copy t to *ps, if ps is not NULL, and return the result
 * if ps or *ps is NULL, we return a string created from t
 *   *ps is set to the same value if ps is not NULL
 * otherwise, we update the record that corresponds to *ps
 *
 * minsize: to request a minimal size for the resulting buffer
 *
 * If flags & SSCAT:
 * append t after *ps. Equivalent to cpy if ps or *ps is NULL.
 * */
INLINE char *sscpycatx(char **ps, const char *t, size_t minsize, unsigned flags)
{
  struct ssheader *hp = NULL;
  size_t size = 0u, sizes = 0u;
  char *s = NULL, *p;

  /* both ps and *ps can be NULL, in which cases we leave hp as NULL */
  if (ps != NULL && (s = *ps) != NULL && (hp = sslistfind_(s)) == NULL) {
    fprintf(stderr, "sscpycatx: unknown address %p (%s)\n", s, s);
    return NULL;
  }
  if (t != NULL)
    while (t[size]) /* compute the length of t */
      size++;
  if (flags & SSCAT) {
    if (s != NULL)  /* s is also NULL, if ps itself is NULL */
      while (s[sizes]) /* compute the length of s */
        sizes++;
    size += sizes;
  }  /* sizes is always 0 in case of copying */
  if (size < minsize)
    size = minsize;
  if ((s = ssresize_(&hp, size, SSOVERALLOC)) == NULL) { /* change size */
    return NULL;
  }
  if (t != NULL)
    for (p = s + sizes; (*p++ = *t++) != '\0'; ) /* copy/cat the string */
      ;
  if (ps != NULL)
    *ps = s;
  return s;
}

/* get a string *ps from file fp
 * *ps can be NULL, in which case memory is allocated
 * *pn is number of characters read (including '\n', but not the terminal null)
 * delim is the '\n' for reading a singe line
 * */
INLINE char *ssfgetx(char **ps, size_t *pn, int delim, FILE *fp)
{
  size_t n, max;
  int c;
  char *s;
  struct ssheader *hp;

  if (ps == NULL || fp == NULL)
    return NULL;
  if ((s = *ps) == NULL) /* allocate an initial buffer if *ps is NULL */
    if ((s = sscpycatx(ps, NULL, 0, 0u)) == NULL)
      return NULL;
  if ((hp = sslistfind_(s)) == NULL) {
    fprintf(stderr, "ssfgetx: unknown address %p (%s)\n", s, s);
    return NULL;
  }
  max = hp->next->size-1;
  for (n = 0; (c = fgetc(fp)) != EOF; ) {
    if (n+1 > max) { /* request space for n+1 nonblank characters */
      if ((*ps = s = ssresize_(&hp, n+1, SSOVERALLOC)) == NULL)
        return NULL;
      max = hp->next->size - 1;
    }
    s[n++] = (char)(unsigned char) c;
    if (c == delim)
      break;
  }
  s[n] = '\0';
  if (pn != NULL)
    *pn = n;
  return (n > 0) ? s : NULL;
}


/* parse `s' into a string array
 * delimiters are removed */
INLINE char **ssparse(char *s, int *pn, const char *delim)
{
  const int capsz = 16;
  int cap, n;
  char **sarr, *p, *q;
  char delim0[8] = "\n\r"; /* default deliminators: new lines */

  if (pn) *pn = 0;
  if (delim == NULL) delim = delim0;

  cap = capsz;
  if ((sarr = calloc(cap, sizeof(sarr[0]))) == NULL) {
    fprintf(stderr, "no memory for sarr\n");
    return NULL;
  }
  for (n = 0, p = s; ; ) { /* n is # of lines */
    for (q = p; *q != '\0'; q++)
      if (strchr(delim, *q))
        break;
    if (q != p) { /* skip an empty line */
      sarr[n++] = p;
      if (n >= cap) { /* expand the array */
        cap += capsz;
        if ((sarr = realloc(sarr, cap * sizeof(sarr[0]))) == NULL) {
          fprintf(stderr, "no memory for sarr, %d\n", cap);
          return NULL;
        }
      }
    }
    if (*q == '\0') break; /* we are done */
    *q = '\0';
    /* search for the next starting point */
    for (p = q + 1; *p && strchr(delim, *p); p++)
      ;
    if (*p == '\0') break;
  }

  if (pn) *pn = n;
  return sarr;
}

/* free the string array, sarr[0] created by ssnew() and sarr created by malloc() */
#define ssarrfree(sarr) { ssdel(sarr[0]); free(sarr); }

#endif /* ZCOM_SS__ */
#endif /* ZCOM_SS */

#ifdef  ZCOM_ENDN
#ifndef ZCOM_ENDN__
#define ZCOM_ENDN__


#include <stdio.h>
#include <string.h>

STRCLS int endn_system(void);
STRCLS size_t endn_fwrite(void *ptr, size_t size, size_t n, FILE *fp, int endn);
STRCLS size_t endn_fread(void *ptr, size_t size, size_t n, FILE *fp, int flip);
STRCLS int endn_rmatch(void *src, const void *ref, size_t size, FILE *fp);
STRCLS int endn_rmatchi(int *src, int iref, FILE *fp);


/* return the system endian, 1: big endian, 0: little endian */
int endn_system(void)
{
  unsigned feff = 0xFEFF; /* assume unsigned is at least 16-bit */
  unsigned char *p;

  p  = (unsigned char *) &feff;
  return (*p == 0xFF) ? 0 : 1;
}

/* change endianness in-place for n items of size in ptr */
__inline void endn_flip(void *ptr, size_t size, size_t n)
{
  unsigned char *p = (unsigned char *) ptr, ch;
  size_t i, r, half = size/2;

  for (; n > 0; n--, p += size) {
    /* reverse bytes for each object */
    for (i = 0; i < half; i++) {
      r = size - i - 1;
      ch   = p[i];
      p[i] = p[r];
      p[r] = ch;
    }
  }
}

/* write data in ptr to file with a specific endian 'endn'
 * `ptr' is not const, because it needs to change its endian */
size_t endn_fwrite(void *ptr, size_t size, size_t n, FILE *fp, int endn)
{
  static int endsys = -1;

  /* initial determine the machine's endianess */
  if (endsys < 0) endsys = endn_system();
  if (endn == endsys) return fwrite(ptr, size, n, fp);

  endn_flip(ptr, size, n);
  n = fwrite(ptr, size, n, fp);
  endn_flip(ptr, size, n);
  return n;
}

/* read an object test object *src, compared with *ref
 * return 0 if they are identical without endian change
 * return 1 if changing the endianness of *src matches *ref
 * otherwise return -1 */
int endn_rmatch(void *src, const void *ref, size_t size, FILE *fp)
{
  if (1 != fread(src, size, 1, fp))
    return -1;
#ifdef ENDN_DBG
  if (size == sizeof(int))
    printf("A: 0x%X vs. 0x%X size = %u, cmp = %d\n",
      *(int *)src, *(int *)ref, (unsigned)size,
      memcmp(src, ref, size));
#endif
  if (memcmp(src, ref,  size) == 0)
    return 0;
  /* alter the endianness, and test again */
  endn_flip(src, size, 1);
#ifdef ENDN_DBG
  if (size == sizeof(int))
    printf("B: 0x%X vs. 0x%X size = %u, cmp = %d\n",
      *(int *)src, *(int *)ref, (unsigned)size,
      memcmp(src, ref, size));
#endif
  return (memcmp(src, ref, size) == 0) ? 1 : -1;
}

/* special case of endn_rmatchi for integer, convenient because
 * iref could be e.g. sizeof(int), which has no address */
int endn_rmatchi(int *src, int iref, FILE *fp)
{
  return endn_rmatch(src, &iref, sizeof(int), fp);
}

/* read data from file to ptr with endianness changed if 'flip' is 1
 * flip can be initialized by calling endn_rmatch() for a test object */
size_t endn_fread(void *ptr, size_t size, size_t n, FILE *fp, int flip)
{
  n = fread(ptr, size, n, fp);
  if (flip) endn_flip(ptr, size, n);
  return n;
}

#endif /* ZCOM_ENDN__ */
#endif /* ZCOM_ENDN */

#ifdef  ZCOM_BIO
#ifndef ZCOM_BIO__
#define ZCOM_BIO__


#include <stdio.h>

/*
 * Helper macros for reading binary files with endianness
 * support.  However, sizeof(int) must remain the same
 * between system and file.
 *
 * To use these macros in a function:
 * 1. define the following variables in your function
 *   FILE *fp;
 *   int endn, err;
 *   (no need for to define `endn' or `err' in writing a file)
 *
 * 2. define a label ERR for error exit
 *
 * 3. in reading a file, use BIO_INITENDIAN to determine
 *    the correct endianness
 * */

#ifndef BIO_ENDNDEF
#define BIO_ENDNDEF 1  /* big endian */
#endif

/* string for printing file name and line number */
#define BIO_FLFMT_ "file: %s, line: %d"

/* check type */
#define BIO_CHECKTP_(x, tp)                                           \
  if (sizeof(x) != sizeof(tp)) {                                      \
    fprintf(stderr, "%s is not %s\n", #x, #tp);                       \
    goto ERR;                                                         \
  }

/* initialize file endian state to variable 'endn'
 * endn = 1: a conversion is needed from file's endianess to system's
 * endn = 0: otherwise
 * read an int variable x,
 * determine endian by comparing the value of x with ref
 * quit if neither endians makes x == ref */
#define BIO_INIT_ENDIAN(x, ref) {                                     \
  BIO_CHECKTP_(x, int)                                                \
  if ((endn = endn_rmatchi(&(x), ref, fp)) < 0) {                     \
    fprintf(stderr, "%s 0x%X cannot match %s 0x%X\n",                 \
      #x, (unsigned) x, #ref, (unsigned) ref);                        \
    goto ERR;                                                         \
  } }

/* read an array of size n, set err, fix endian */
#define BIO_RATOM_(arr, n)                                                      \
  if ((n) > 0 && endn_fread(arr, sizeof(*(arr)), n, fp, endn) != (size_t) n) {  \
    fprintf(stderr, "error while reading %s, size %u, "                         \
        BIO_FLFMT_ "\n", #arr, (unsigned) n, __FILE__, __LINE__);               \
    err = 1;                                                                    \
  } else { err = 0; }

/* read an array, set error */
#define BIO_RNA_(arr, n, tp) BIO_CHECKTP_(*(arr), tp) BIO_RATOM_(arr, n)
/* read a single variable x of type tp, set err if error occurs */
#define BIO_R1A_(x, tp) BIO_RNA_(&(x), 1, tp)

/* goto ERR if error occurs during reading */
#define BIO_RNB_(arr, n, tp) { BIO_RNA_(arr, n, tp); if (err) goto ERR; }
#define BIO_R1B_(x, tp) { BIO_R1A_(x, tp); if (err) goto ERR; }

/* most common: int and double cases */
#define BIO_RI_ERR(x)     BIO_R1A_(x, int)
#define BIO_RI(x)         BIO_R1B_(x, int)
#define BIO_RIARR(x, n)   BIO_RNB_(x, n, int)

#define BIO_RD_ERR(x)     BIO_R1A_(x, double)
#define BIO_RD(x)         BIO_R1B_(x, double)
#define BIO_RDARR(x, n)   BIO_RNB_(x, n, double)

/* match a temperory int x with the reference var */
#define BIO_MI(x, var)                                                \
  if ((x) != (var)) {                                                 \
    fprintf(stderr, "%s mismatch, expect: %d, read: %d "              \
        BIO_FLFMT_ "\n", #var, (int) var, x, __FILE__, __LINE__);     \
    goto ERR; }

/* match a temperory double x with the reference var */
#define BIO_MD(x, var, eps)                                           \
  if (fabs((x) - (var)) > eps) {                                      \
    fprintf(stderr, "%s mismatch, expect: %g, read: %g "              \
        BIO_FLFMT_ "\n", #var, var, x, __FILE__, __LINE__);           \
    goto ERR; }

/* read an int to x, match it with xref */
#define BIO_RMI(x, xref)       BIO_RI(x); BIO_MI(x, xref)
/* read a double to x, match it with xref */
#define BIO_RMD(x, xref, eps)  BIO_RD(x); BIO_MD(x, xref, eps)

/* write an array of size n with endian being BIO_ENDNDEF
 * we do not set err, directly goto ERR */
#define BIO_WATOM_(arr, n)                                            \
  if ((n) > 0 &&  (size_t) (n) !=                                     \
      endn_fwrite(arr, sizeof(*(arr)), n, fp, BIO_ENDNDEF) ) {        \
    fprintf(stderr, "error while reading %s, size %u, "               \
        BIO_FLFMT_ "\n", #arr, (unsigned) n, __FILE__, __LINE__);     \
    goto ERR;                                                         \
  }

/* write an array, go to ERR if error occurs */
#define BIO_WNB_(arr, n, tp) BIO_CHECKTP_(*(arr), tp) BIO_WATOM_(arr, n)
/* write a single variable, go to ERR if error occurs */
#define BIO_W1B_(x, tp) BIO_WNB_(&(x), 1, tp)

#define BIO_WI(x)           BIO_W1B_(x, int)
#define BIO_WIARR(x, n)     BIO_WNB_(x, n, int)
#define BIO_WD(x)           BIO_W1B_(x, double)
#define BIO_WDARR(x, n)     BIO_WNB_(x, n, double)


#endif /* ZCOM_BIO__ */
#endif /* ZCOM_BIO */

#ifdef  ZCOM_OSYS
#ifndef ZCOM_OSYS__
#define ZCOM_OSYS__

#define OSYS_VERBOSE 0x1

/* run command and capture the output
 * `cmd' is the command to run
 * `*nc' returns the number of characters read */
INLINE char *sysrun(const char *cmd, size_t *nc, unsigned flags)
{
  FILE *fp;
  char fntmp[] = "h1Qi7G0c.TmP"; /* output file */
  char *ncmd, *output = NULL;
  int i;

  if (nc) *nc = 0;

  /* construct the command */
  ncmd = ssdup(cmd);
  sscat(ncmd, " > ");
  sscat(ncmd, fntmp);

  /* run it */
  if ((i = system(ncmd)) != 0)
    if (flags & OSYS_VERBOSE)
      fprintf(stderr, "command \"%s\" failed\n", ncmd);
  ssdel(ncmd);
  if (i != 0) goto EXIT; /* output should be NULL in this case */

  xfopen(fp, fntmp, "r", goto EXIT);
  ssfgetall(output, nc, fp);
  fclose(fp);
EXIT:
  remove(fntmp);
  return output;
}

/* Get a list of file names satisfying a pattern
 * `pat' is the file name pattern, such as '*.c'
 * `*n' returns the number of matches
 * `lscmd' is the list command
 * the output is a file list (string array), to free it:
 *    ssdel(fnls[0]); free(fnls); */
INLINE char **fnglob(const char *pat, int *pn, const char *lscmd, unsigned flags)
{
  size_t nc = 0;
  char *cmd, *output;

  if (pn) *pn = 0;

  /* construct a command first */
  cmd = ssnew(256);
  if (lscmd == NULL) /* assuming linux */
    lscmd = "ls --color=never ";
  sscpy(cmd, lscmd);
  sscat(cmd, pat);

  /* run the command and get the output */
  output = sysrun(cmd, &nc, flags);
  ssdel(cmd);
  if (output == NULL || nc == 0) return NULL;

  /* parse the output into file names
   * don't ssdel(output), for it's used in the output */
  return ssparse(output, pn, NULL);
}
#endif /* ZCOM_OSYS__ */
#endif /* ZCOM_OSYS */

#ifdef  ZCOM_RNG
#ifndef ZCOM_RNG__
#define ZCOM_RNG__

#include <stdio.h>
#include <string.h>
#include <math.h>

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
  #include <inttypes.h>
#elif defined(_MSC_VER) || defined(__BORLANDC__)
  typedef unsigned uint32_t;
  typedef unsigned __int64 uint64_t;
#else
  #include <inttypes.h>
#endif

#ifndef PRIu32
  #if (defined(_MSC_VER) && (_MSC_VER >= 1300)) || defined(__BORLANDC__)
    #define PRIu32 "I32u"
  #else
    #define PRIu32 "u"
  #endif
#endif

#ifndef PRIu64
  #if defined(_MSC_VER) || defined(__BORLANDC__)
    #define PRIu64 "I64u"
  #else
    #define PRIu64 "llu"
  #endif
#endif

#define rand32()  mtrand()
#define rnd0()    ((1.0/4294967296.0) * rand32()) /* double, [0, 1) */

#define MTFILE    "MTSEED"  /* default file */
#define MTSEED    5489UL    /* default seed */
INLINE int mtsave(const char *fname);
INLINE int mtload(const char *fname, uint32_t seed);
INLINE uint32_t mtrand(void);
INLINE double grand0(void);

/* metropolis acceptance probability rnd0() < exp(r), assuming r > 0 */
INLINE int metroacc0(double r) { r = exp(r); return rnd0() < r; }

/* metropolis acceptance probability rnd0() < exp(- bet * de), assuming bet > 0
 * defined as a macro, in case r is an integer */
#define metroacc1(de, bet) ((de <= 0) ? 1 : metroacc0(- bet * de))


/* Mersenne Twister was developped by Makoto Matsumoto and Takuji Nishimura */
#define MT_N 624
#define MT_M 397
#define MT_UMASK 0x80000000UL /* most significant w-r bits */
#define MT_LMASK 0x7fffffffUL /* least significant r bits */

int mtidx_ = -1; /* index in mt_, -1: uninitialized */
uint32_t mt_[MT_N]; /* array for the mt state vector */

/* save the current mt state to file */
INLINE int mtsave(const char *fname)
{
  FILE *fp;
  int k;

  if (mtidx_ < 0) return 1; /* RNG was never used, so it cannot be saved */
  if (fname == NULL) fname = MTFILE;
  if ((fp = fopen(fname, "w")) == NULL) {
    fprintf(stderr, "cannot save to %s.\n", fname);
    return 1;
  }
  fprintf(fp, "MTSEED\n%d\n", mtidx_);
  for (k = 0; k < MT_N; k++) fprintf(fp, "%"PRIu32"\n", mt_[k]);
  fclose(fp);
  return 0;
}

/* load mt state from `fname', or if it fails, use `seed' to initialize mt  */
INLINE int mtload(const char *fname, uint32_t seed)
{
  static char s[64];
  int k, z, err = 1;
  FILE *fp;

  if (fname == NULL) fname = MTFILE;
  if ((fp = fopen(fname, "r")) != NULL) { /* try to load from file */
    if (fgets(s, sizeof s, fp) == NULL) {
      fprintf(stderr, "%s is empty\n", fname);
    } else if (strncmp(s, "MTSEED", 6) != 0) { /* to check the first line */
      fprintf(stderr, "mtrand: corrupted file.\n");
    } else if (fscanf(fp, "%d", &mtidx_) != 1) {
      fprintf(stderr, "no index in %s\n", fname);
    } else {
      if (mtidx_ < 0) mtidx_ = MT_N; /* request updating */
      for (z = 1, k = 0; k < MT_N; k++) {
        if (fscanf(fp, "%"PRIu32, &mt_[k]) != 1) break;
        if (mt_[k] != 0) z = 0; /* a non-zero number */
      }
      if (k != MT_N) fprintf(stderr, "%s incomplete %d/%d\n", fname, k, MT_N);
      else err = z; /* clear error, if array is nonzero */
    }
    fclose(fp);
  }

  if (err) { /* initialize from seed */
    if (seed == 0) seed = MTSEED;
    mt_[0] = seed & 0xffffffffUL;
    for (k = 1; k < MT_N; k++) /* the final mask is for 64-bit machines */
      mt_[k] = (1812433253UL * (mt_[k-1] ^ (mt_[k-1]>>30)) + k) & 0xffffffffUL;
    mtidx_ = MT_N; /* request updating */
  }
  return (mtidx_ < 0);
}

/* return an unsigned random number */
INLINE uint32_t mtrand(void)
{
  uint32_t x;
  static const uint32_t mag01[2] = {0, 0x9908b0dfUL}; /* MATRIX_A */
  int k;

  if (mtidx_ < 0) mtload(NULL, 0);
  if (mtidx_ >= MT_N) { /* generate MT_N words at one time */
    for (k = 0; k < MT_N - MT_M; k++) {
      x = (mt_[k] & MT_UMASK) | (mt_[k+1] & MT_LMASK);
      mt_[k] = mt_[k+MT_M] ^ (x>>1) ^ mag01[x&1UL];
    }
    for (; k < MT_N-1; k++) {
      x = (mt_[k] & MT_UMASK) | (mt_[k+1] & MT_LMASK);
      mt_[k] = mt_[k+(MT_M-MT_N)] ^ (x>>1) ^ mag01[x&1UL];
    }
    x = (mt_[MT_N-1] & MT_UMASK) | (mt_[0] & MT_LMASK);
    mt_[MT_N-1] = mt_[MT_M-1] ^ (x>>1) ^ mag01[x&1UL];
    mtidx_ = 0;
  }
  x = mt_[ mtidx_++ ];
  /* tempering */
  x ^= (x >> 11);
  x ^= (x <<  7) & 0x9d2c5680UL;
  x ^= (x << 15) & 0xefc60000UL;
  x ^= (x >> 18);
  return x;
}

#undef MT_N
#undef MT_M
#undef MT_UMASK
#undef MT_LMASK

/* Gaussian distribution with zero mean and unit variance
 * using ratio method */
INLINE double grand0(void)
{
  double x, y, u, v, q;
  do {
    u = 1 - rnd0();
    v = 1.7156*(rnd0() - .5);  /* >= 2*sqrt(2/e) */
    x = u - 0.449871;
    y = fabs(v) + 0.386595;
    q = x*x  + y*(0.196*y - 0.25472*x);
    if (q < 0.27597) break;
  } while (q > 0.27846 || v*v > -4*u*u*log(u));
  return v/u;
}


/* return a random number that satisfies a gamma distribution
   p(x) = x^(k - 1) e^(-x) / (k - 1)!. */
INLINE double randgam(int k)
{
  int i;
  double x, k1 = k - 1, r, y, v1, v2, s;

  if (k < 0) { printf("randgam: k %d must be positive\n", k); return 0.; }
  if (k == 0) return 0.; /* nothing */
  if (k <= 7) { /* adding numbers of exponential distribution */
    /* exp(- x1 - x2 - x3 - x4) dx1 dx2 dx3 dx4 */
    for (x = 1.0, i = 0; i < k; i++)
      x *= rnd0();
    return -log(x);
  }

  /* generate gamma distribution by the rejection method */
  for(;;) {
    /* generate lorentz distribution, centered at k1, width is sqrt(2.0*k - 1)
     p(y) = 1/pi/(1 + y^2), x = y*w + k1, w = sqrt(2.0*k - 1) */
    for (;;) { /* get a unit circle */
      v1 = 2.0*rnd0() - 1.0;
      v2 = 2.0*rnd0() - 1.0;
      if (v1*v1 + v2*v2 <= 1.0) {
        y = v2/v1; /* tan */
        s = sqrt(2.0*k - 1);
        x = s*y + k1;
        if (x > 0.0) break; /* drop the negative value */
      }
    }
    /* compare with the gamma distribution
       r peaks at x = k1, where, y = 0 and r = 1 */
    r = (1.0 + y*y)*exp(k1*log(x/k1) - x + k1);
    if (rnd0() <= r) break;
  }

  return x;
}

/* return the sum of the square of Gaussian random numbers  */
INLINE double randgausssum(int n)
{
  double x, r;
  if (n <= 0) return 0.0;
  x = 2.0*randgam(n/2);
  if (n % 2) { r = grand0(); x += r*r; }
  return x;
}

/* return randomly oriented vector on a uniform sphere */
INLINE double *randor3d(double *v)
{
  double a, b, sq, s;

  do { /* projection on the x-y plane */
    a = 2 * rnd0() - 1;
    b = 2 * rnd0() - 1;
    sq = a * a + b * b;
  } while (sq > 1);

  s = 2.0 * sqrt(1 - sq);

  /* x^2 + y^2 = 4 [1 - (a^2 + b^2)] (a^2 + b^2)
   * z^2 = 1 - 2 (a^2 + b^2), so x^2 + y^2 + z^2 = 1 */
  v[0] = a * s;
  v[1] = b * s;
  v[2] = 1 - 2*sq;

  return v;
}

#endif /* ZCOM_RNG__ */
#endif /* ZCOM_RNG */

#ifdef  ZCOM_RC
#ifndef ZCOM_RC__
#define ZCOM_RC__

typedef struct { real re, im; } rcomplex_t;


/* make complex */
INLINE rcomplex_t rc_make(real re, real im)
{
  rcomplex_t x;
  x.re = re; x.im = im;
  return x;
}

/* complex conjugate */
INLINE rcomplex_t rc_star(rcomplex_t x)
{
  x.im = - x.im;
  return x;
}

/* complex times real */
INLINE rcomplex_t rc_smul(rcomplex_t x, real s)
{
  x.re *= s; x.im *= s;
  return x;
}

/* complex divided by real  */
INLINE rcomplex_t rc_sdiv(rcomplex_t x, real s)
{
  x.re /= s; x.im /= s;
  return x;
}

/* complex addition */
INLINE rcomplex_t rc_add(rcomplex_t x, rcomplex_t y)
{
  x.re += y.re; x.im += y.im;
  return x;
}

/* complex multiplication */
INLINE rcomplex_t rc_mul(rcomplex_t x, rcomplex_t y)
{
  rcomplex_t z;
  z.re = x.re * y.re - x.im * y.im;
  z.im = x.re * y.im + x.im * y.re;
  return z;
}

#endif /* ZCOM_RC__ */
#endif /* ZCOM_RC */

#ifdef  ZCOM_RV2
#ifndef ZCOM_RV2__
#define ZCOM_RV2__

#ifndef RV2_T
#define RV2_T rv2_t
  typedef real rv2_t[2];
  typedef const real crv2_t[2];
  typedef real rm2_t[2][2];
#endif

#include <stdio.h>
#include <string.h>
#include <math.h>

/* due to that pointer may overlap with each other,
 * be careful when using the const modifier */
INLINE real *rv2_make(real *x, real a, real b) { x[0] = a; x[1] = b; return x; }
INLINE real *rv2_zero(real *x) { return rv2_make(x, 0, 0); }
INLINE real *rv2_copy(real *x, const real *src) { x[0] = src[0]; x[1] = src[1]; return x; }
/* use macro to avoid const qualifier of src */
#define rv2_ncopy(x, src, n) memcpy(x, src, 2*n*sizeof(real))

INLINE real rv2_sqr(const real *x) { return x[0]*x[0]+x[1]*x[1]; }
INLINE real rv2_norm(const real *x) { return (real)sqrt(x[0]*x[0]+x[1]*x[1]); }

INLINE real rv2_dot(const real *x, const real *y) { return x[0]*y[0]+x[1]*y[1]; }

INLINE real rv2_cross(const real *x, const real *y)
{
  return x[0]*y[1]-x[1]*y[0];
}

INLINE real *rv2_neg(real *x)
{
  x[0] = -x[0];
  x[1] = -x[1];
  return x;
}

INLINE real *rv2_neg2(real *nx, const real *x)
{
  nx[0] = -x[0];
  nx[1] = -x[1];
  return nx;
}

INLINE real *rv2_inc(real *x, const real *dx)
{
  x[0] += dx[0];
  x[1] += dx[1];
  return x;
}

INLINE real *rv2_dec(real *x, const real *dx)
{
  x[0] -= dx[0];
  x[1] -= dx[1];
  return x;
}

INLINE real *rv2_sinc(real *x, const real *dx, real s)
{
  x[0] += s*dx[0];
  x[1] += s*dx[1];
  return x;
}

INLINE real *rv2_smul(real *x, real s)
{
  x[0] *= s;
  x[1] *= s;
  return x;
}

INLINE real *rv2_smul2(real *y, const real *x, real s)
{
  y[0] = x[0]*s;
  y[1] = x[1]*s;
  return y;
}

INLINE real *rv2_normalize(real *x)
{
  real r = rv2_norm(x);
  if (r > 0.f) rv2_smul(x, 1.f/r);
  return x;
}

/* for in-place difference use rv2_dec */
INLINE real *rv2_diff(real *diff, const real *a, const real *b)
{
  diff[0] = a[0]-b[0];
  diff[1] = a[1]-b[1];
  return diff;
}

/* distance^2 between a and b */
INLINE real rv2_dist2(const real *a, const real *b)
{
  real d[2];
  return rv2_sqr(rv2_diff(d, a, b));
}

/* distance between a and b */
INLINE real rv2_dist(const real *a, const real *b)
{
  return (real) sqrt(rv2_dist2(a, b));
}

/* sum = a+b, for in-place addition use rv2_inc */
INLINE real *rv2_add(real *sum, const real *a, const real *b)
{
  sum[0] = a[0]+b[0];
  sum[1] = a[1]+b[1];
  return sum;
}

/* sum = -a-b */
INLINE real *rv2_nadd(real *sum, const real *a, const real *b)
{
  sum[0] = -a[0]-b[0];
  sum[1] = -a[1]-b[1];
  return sum;
}

INLINE real *rv2_lincomb2(real *sum, const real *a, const real *b, real s1, real s2)
{
  sum[0] = a[0]*s1+b[0]*s2;
  sum[1] = a[1]*s1+b[1]*s2;
  return sum;
}

/* consine of the angle of x1-x2-x3 */
INLINE real rv2_cosang(const real *x1, const real *x2, const real *x3,
    real *g1, real *g2, real *g3)
{
  real a[2], b[2], ra, rb, dot;

  ra = rv2_norm(rv2_diff(a, x1, x2));
  rv2_smul(a, 1.f/ra);
  rb = rv2_norm(rv2_diff(b, x3, x2));
  rv2_smul(b, 1.f/rb);
  dot = rv2_dot(a, b);
  if (dot > 1) dot = 1; else if (dot < -1) dot = -1;
  if (g1) {
    rv2_lincomb2(g1, b, a, 1.f/ra, -dot/ra);
    rv2_lincomb2(g3, a, b, 1.f/rb, -dot/rb);
    rv2_nadd(g2, g1, g3);
  }
  return dot;
}

/* angle and gradients of x1-x2-x3 */
INLINE real rv2_ang(const real *x1, const real *x2, const real *x3,
    real *g1, real *g2, real *g3)
{
  real dot, sn;
  dot = rv2_cosang(x1, x2, x3, g1, g2, g3);
  sn = (real) sqrt(1 - dot*dot);
  if (sn > 1e-7) sn = -1/sn; else sn = 0.;
  if (g1) {
    rv2_smul(g1, sn);
    rv2_smul(g2, sn);
    rv2_smul(g3, sn);
  }
  return (real) acos(dot);
}

/* vertical distance from x to line a-b */
INLINE real rv2_vdist(const real *x, const real *a, const real *b)
{
  real nm[2], d[2], dot;

  rv2_diff(d, x, a);
  rv2_normalize(rv2_diff(nm, a, b));
  dot = rv2_dot(d, nm);
  return rv2_norm(rv2_sinc(d, nm, -dot));
}

/* determinant of a 2x2 matrix */
INLINE real rm2_det(real a[2][2])
{
  return a[0][0]*a[1][1] - a[0][1]*a[1][0];
}

/* inverse matrix b = a^(-1) */
INLINE void rm2_inv(real b[2][2], real a[2][2])
{
  real det = rm2_det(a);
  if (fabs(det) < 1e-30) det = (det < 0) ? -1e-30f: 1e-30f;
  b[0][0] =  a[1][1]/det;
  b[0][1] = -a[0][1]/det;
  b[1][0] = -a[1][0]/det;
  b[1][1] =  a[0][0]/det;
}

#define rv2_print(r, nm, fmt, nl) rv2_fprint(stdout, r, nm, fmt, nl)
INLINE void rv2_fprint(FILE *fp, const real *r, const char *nm,
    const char *fmt, int nl)
{
  int i;
  if (nm) fprintf(fp, "%s: ", nm);
  for (i = 0; i < 2; i++)
    fprintf(fp, fmt, r[i], nl);
  fprintf(fp, "%c", (nl ? '\n' : ';'));
}

#define rm2_print(r, nm, fmt, nl) rm2_fprint(stdout, r, nm, fmt, nl)
INLINE void rm2_fprint(FILE *fp, real r[2][2], const char *nm,
    const char *fmt, int nl)
{
  int i, j;
  if (nm) fprintf(fp, "%s:%c", nm, (nl ? '\n' : ' '));
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      fprintf(fp, fmt, r[i][j], nl);
    }
    fprintf(fp, "%s", (nl ? "\n" : "; "));
  }
}

/* uniformly distributed random vector [a, a + b) */
#define rv2_rnd0() rv2_rnd(v, 0, 1)
INLINE real *rv2_rnd(rv2_t v, real a, real b)
{
  v[0] = (real) (a + b * rnd0());
  v[1] = (real) (a + b * rnd0());
  return v;
}


/* normally distributed random vector */
#define rv2_grand0(v) rv2_grand(v, 0, 1)
INLINE real *rv2_grand(rv2_t v, real c, real r)
{
  v[0] = (real) (c + r * grand0());
  v[1] = (real) (c + r * grand0());
  return v;
}

/* generate a random orthonormal (unitary) 2x2 matrix */
INLINE rv2_t *rm2_rnduni(real a[2][2])
{
  rv2_rnd(a[0], -.5f, 1.f);
  rv2_normalize(a[0]);

  a[1][0] = a[0][1];
  a[1][1] = -a[0][0];
  if (rnd0() > 0.5) rv2_neg(a[1]);
  return a;
}

#endif /* ZCOM_RV2__ */
#endif /* ZCOM_RV2 */

#ifdef  ZCOM_RV3
#ifndef ZCOM_RV3__
#define ZCOM_RV3__

#ifndef DV3_T
#define DV3_T dv3_t
  typedef double dv3_t[3];
  typedef const double cdv3_t[3];
  typedef double dm3_t[3][3];
#endif

#ifndef RV3_T
#define RV3_T rv3_t
  typedef real rv3_t[3];
  typedef const real crv3_t[3];
  typedef real rm3_t[3][3];
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

#define rv3_fprint_(fp, r, nm, fmt, nl) { int i_; \
  if (nm) fprintf(fp, "%s: ", nm); \
  for (i_ = 0; i_ < 3; i_++) fprintf(fp, fmt, r[i_]); \
  fprintf(fp, "%c", (nl ? '\n' : ';')); }

#define rm3_fprint_(fp, m, nm, fmt, nl) { int i_, j_; \
  if (nm) fprintf(fp, "%s:%c", nm, (nl ? '\n' : ' ')); \
  for (i_ = 0; i_ < 3; i_++) { \
    for (j_ = 0; j_ < 3; j_++) \
      fprintf(fp, fmt, m[i_][j_]); \
    fprintf(fp, "%s", (nl ? "\n" : "; ")); } }

#define dv3_print(r, nm, fmt, nl) dv3_fprint(stdout, r, nm, fmt, nl)
INLINE void dv3_fprint(FILE *fp, double *r, const char *nm, const char *fmt, int nl)
  rv3_fprint_(fp, r, nm, fmt, nl)

#define dm3_print(m, nm, fmt, nl) dm3_fprint(stdout, m, nm, fmt, nl)
INLINE void dm3_fprint(FILE *fp, double (*m)[3], const char *nm, const char *fmt, int nl)
  rm3_fprint_(fp, m, nm, fmt, nl)

#define rv3_print(r, nm, fmt, nl) rv3_fprint(stdout, r, nm, fmt, nl)
INLINE void rv3_fprint(FILE *fp, real *r, const char *nm, const char *fmt, int nl)
  rv3_fprint_(fp, r, nm, fmt, nl)

#define rm3_print(m, nm, fmt, nl) rm3_fprint(stdout, m, nm, fmt, nl)
INLINE void rm3_fprint(FILE *fp, real (*m)[3], const char *nm, const char *fmt, int nl)
  rm3_fprint_(fp, m, nm, fmt, nl)

/* due to possible pointer overlap, be careful when to use 'const' */

INLINE double *dv3_make(double *x, double a, double b, double c)
  { x[0] = a; x[1] = b; x[2] = c; return x; }
INLINE double *dv3_fromrv3(double *x, const real *rx)
  { return dv3_make(x, rx[0], rx[1], rx[2]); }
INLINE double *dv3_zero(double *x) { return dv3_make(x, 0, 0, 0); }
INLINE double *dv3_copy(double *x, const double *src)
  { x[0] = src[0]; x[1] = src[1]; x[2] = src[2]; return x; }
#define dv3_ncopy(x, src, n) memcpy(x, src, 3*n*sizeof(double))
INLINE void dv3_swap(double *x, double *y)
  { double z[3]; dv3_copy(z, x); dv3_copy(x, y); dv3_copy(y, z); }

INLINE double dv3_sqr (const double *x) { return x[0]*x[0]+x[1]*x[1]+x[2]*x[2]; }
INLINE double dv3_norm(const double *x) { return (double)sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]); }

INLINE double dv3_dot(const double *x, const double *y)
{
  return x[0]*y[0] + x[1]*y[1] + x[2]*y[2];
}

INLINE double *dv3_cross(double *RESTRICT z, const double *x, const double *y)
{
  z[0] = x[1]*y[2]-x[2]*y[1];
  z[1] = x[2]*y[0]-x[0]*y[2];
  z[2] = x[0]*y[1]-x[1]*y[0];
  return z;
}

INLINE double *dv3_neg(double *x)
{
  x[0] = -x[0];
  x[1] = -x[1];
  x[2] = -x[2];
  return x;
}

INLINE double *dv3_neg2(double *nx, const double *x)
{
  nx[0] = -x[0];
  nx[1] = -x[1];
  nx[2] = -x[2];
  return nx;
}

INLINE double *dv3_inc(double * RESTRICT x, const double *dx)
{
  x[0] += dx[0];
  x[1] += dx[1];
  x[2] += dx[2];
  return x;
}

INLINE double *dv3_dec(double *x, const double *dx)
{
  x[0] -= dx[0];
  x[1] -= dx[1];
  x[2] -= dx[2];
  return x;
}

INLINE double *dv3_sinc(double * RESTRICT x, const double *dx, double s)
{
  x[0] += dx[0]*s;
  x[1] += dx[1]*s;
  x[2] += dx[2]*s;
  return x;
}

INLINE double *dv3_smul(double *x, double s)
{
  x[0] *= s;
  x[1] *= s;
  x[2] *= s;
  return x;
}

INLINE double *dv3_smul2(double * RESTRICT y, const double *x, double s)
{
  y[0] = x[0]*s;
  y[1] = x[1]*s;
  y[2] = x[2]*s;
  return y;
}

INLINE double *dv3_normalize(double *x)
{
  double r = dv3_norm(x);
  if (r > 0.0) dv3_smul(x, 1.0/r);
  return x;
}

INLINE double *dv3_makenorm(double *v, double x, double y, double z)
  { return dv3_normalize( dv3_make(v, x, y, z) ); }

INLINE double *dv3_diff(double * RESTRICT diff, const double *a, const double *b)
{
  diff[0] = a[0] - b[0];
  diff[1] = a[1] - b[1];
  diff[2] = a[2] - b[2];
  return diff;
}

INLINE double dv3_dist2(const double *a, const double *b)
{
  double d[3];
  return dv3_sqr(dv3_diff(d, a, b));
}

INLINE double dv3_dist(const double *a, const double *b)
{
  return (double) sqrt(dv3_dist2(a, b));
}

INLINE double *dv3_add(double * RESTRICT sum, const double *a, const double *b)
{
  sum[0] = a[0]+b[0];
  sum[1] = a[1]+b[1];
  sum[2] = a[2]+b[2];
  return sum;
}

INLINE double *dv3_nadd(double *sum, const double *a, const double *b)
{
  sum[0] = -a[0]-b[0];
  sum[1] = -a[1]-b[1];
  sum[2] = -a[2]-b[2];
  return sum;
}

INLINE double *dv3_lincomb2(double * RESTRICT sum, const double *a, const double *b, double s1, double s2)
{
  sum[0] = a[0]*s1+b[0]*s2;
  sum[1] = a[1]*s1+b[1]*s2;
  sum[2] = a[2]*s1+b[2]*s2;
  return sum;
}

INLINE real *rv3_make(real *x, real a, real b, real c)
  { x[0] = a; x[1] = b; x[2] = c; return x; }
INLINE real *rv3_fromdv3(real *x, const double *dx)
  { return rv3_make(x, (real) dx[0], (real) dx[1], (real) dx[2]); }
INLINE real *rv3_zero(real *x) { return rv3_make(x, 0, 0, 0); }
INLINE real *rv3_copy(real *x, const real *src)
  { x[0] = src[0]; x[1] = src[1]; x[2] = src[2]; return x; }
/* use macro to avoid const qualifier of src */
#define rv3_ncopy(x, src, n) memcpy(x, src, 3*n*sizeof(real))
INLINE void rv3_swap(real *x, real *y)
  { real z[3]; rv3_copy(z, x); rv3_copy(x, y); rv3_copy(y, z); }

INLINE real rv3_sqr (const real *x) { return x[0]*x[0]+x[1]*x[1]+x[2]*x[2]; }
INLINE real rv3_norm(const real *x) { return (real)sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]); }

/* if x == y, try to use sqr */
INLINE real rv3_dot(const real *x, const real *y)
{
  return x[0]*y[0] + x[1]*y[1] + x[2]*y[2];
}

INLINE real *rv3_cross(real *RESTRICT z, const real *x, const real *y)
{
  z[0] = x[1]*y[2] - x[2]*y[1];
  z[1] = x[2]*y[0] - x[0]*y[2];
  z[2] = x[0]*y[1] - x[1]*y[0];
  return z;
}

INLINE real *rv3_neg(real *x)
{
  x[0] = -x[0];
  x[1] = -x[1];
  x[2] = -x[2];
  return x;
}

INLINE real *rv3_neg2(real *nx, const real *x)
{
  nx[0] = -x[0];
  nx[1] = -x[1];
  nx[2] = -x[2];
  return nx;
}

INLINE real *rv3_inc(real * RESTRICT x, const real *dx)
{
  x[0] += dx[0];
  x[1] += dx[1];
  x[2] += dx[2];
  return x;
}

INLINE real *rv3_dec(real *x, const real *dx)
{
  x[0] -= dx[0];
  x[1] -= dx[1];
  x[2] -= dx[2];
  return x;
}

INLINE real *rv3_sinc(real * RESTRICT x, const real *dx, real s)
{
  x[0] += dx[0]*s;
  x[1] += dx[1]*s;
  x[2] += dx[2]*s;
  return x;
}

INLINE real *rv3_smul(real *x, real s)
{
  x[0] *= s;
  x[1] *= s;
  x[2] *= s;
  return x;
}

/* if y == x, just use smul */
INLINE real *rv3_smul2(real * RESTRICT y, const real *x, real s)
{
  y[0] = x[0]*s;
  y[1] = x[1]*s;
  y[2] = x[2]*s;
  return y;
}

INLINE real *rv3_normalize(real *x)
{
  real r = rv3_norm(x);
  if (r > 0.f) rv3_smul(x, 1.f/r);
  return x;
}

INLINE real *rv3_makenorm(real *v, real x, real y, real z)
  { return rv3_normalize( rv3_make(v, x, y, z) ); }

/* for in-place difference use rv3_dec */
INLINE real *rv3_diff(real * RESTRICT diff, const real *a, const real *b)
{
  diff[0] = a[0]-b[0];
  diff[1] = a[1]-b[1];
  diff[2] = a[2]-b[2];
  return diff;
}

/* distance^2 between a and b */
INLINE real rv3_dist2(const real *a, const real *b)
{
  real d[3];
  return rv3_sqr(rv3_diff(d, a, b));
}

/* distance between a and b */
INLINE real rv3_dist(const real *a, const real *b)
{
  return (real) sqrt(rv3_dist2(a, b));
}

/* sum = a+b, for in-place addition use rv3_inc */
INLINE real *rv3_add(real * RESTRICT sum, const real *a, const real *b)
{
  sum[0] = a[0]+b[0];
  sum[1] = a[1]+b[1];
  sum[2] = a[2]+b[2];
  return sum;
}

/* sum = -a-b */
INLINE real *rv3_nadd(real *sum, const real *a, const real *b)
{
  sum[0] = -a[0]-b[0];
  sum[1] = -a[1]-b[1];
  sum[2] = -a[2]-b[2];
  return sum;
}

INLINE real *rv3_lincomb2(real * RESTRICT sum, const real *a, const real *b, real s1, real s2)
{
  sum[0] = a[0]*s1+b[0]*s2;
  sum[1] = a[1]*s1+b[1]*s2;
  sum[2] = a[2]*s1+b[2]*s2;
  return sum;
}

/* angle and gradients of cos(x1-x2-x3) */
INLINE real rv3_cosang(const real *x1, const real *x2, const real *x3,
    real *g1, real *g2, real *g3)
{
  real a[3], b[3], ra, rb, dot;

  ra = rv3_norm(rv3_diff(a, x1, x2));
  rv3_smul(a, 1.f/ra);
  rb = rv3_norm(rv3_diff(b, x3, x2));
  rv3_smul(b, 1.f/rb);
  dot = rv3_dot(a, b);
  if (dot > 1) dot = 1; else if (dot < -1) dot = -1;
  if (g1) {
    rv3_lincomb2(g1, b, a, 1.f/ra, -dot/ra);
    rv3_lincomb2(g3, a, b, 1.f/rb, -dot/rb);
    rv3_nadd(g2, g1, g3);
  }
  return dot;
}

/* angle and gradients of x1-x2-x3 */
INLINE real rv3_ang(const real *x1, const real *x2, const real *x3,
    real *g1, real *g2, real *g3)
{
  real dot, sn;

  dot = rv3_cosang(x1, x2, x3, g1, g2, g3);
  sn = (real) sqrt(1 - dot*dot);
  if (sn < 1e-7) sn = 1; else sn = -1.f/sn;
  if (g1) {
    rv3_smul(g1, sn);
    rv3_smul(g2, sn);
    rv3_smul(g3, sn);
  }
  return (real) acos(dot);
}

/* vertical distance from x to line a-b */
INLINE real rv3_vdist(const real *x, const real *a, const real *b)
{
  real nm[3], d[3], dot;

  rv3_diff(d, x, a);
  rv3_normalize(rv3_diff(nm, a, b));
  dot = rv3_dot(d, nm);
  return rv3_norm(rv3_sinc(d, nm, -dot));
}

/* signed distance from x to the plane extended by a, b, c */
INLINE real rv3_vpdist(const real *x, const real *a, const real *b, const real *c)
{
  real u[3], v[3], m[3];

  rv3_diff(u, b, a);
  rv3_diff(v, c, b);
  rv3_normalize(rv3_cross(m, u, v));
  rv3_diff(u, x, a);
  return rv3_dot(u, m);
}

/* light weight dihedral */
INLINE real rv3_dih(const real xi[], const real xj[], const real xk[], const real xl[],
    real gi[], real gj[], real gk[], real gl[])
{
  real tol, phi, cosphi = 1.f;
  real nxkj, nxkj2, m2, n2;
  real xij[3], xkj[3], xkl[3], uvec[3], vvec[3], svec[3];
  real m[3], n[3]; /* the planar vector of xij x xkj,  and xkj x xkj */

  rv3_diff(xij, xi, xj);
  rv3_diff(xkj, xk, xj);
  rv3_diff(xkl, xk, xl);
  nxkj2 = rv3_sqr(xkj);
  nxkj = (real) sqrt(nxkj2);
  tol = (sizeof(real) == sizeof(float)) ? nxkj2 * 6e-8f : nxkj2 * 1e-16f;

  rv3_cross(m, xij, xkj);
  m2 = rv3_sqr(m);
  rv3_cross(n, xkj, xkl);
  n2 = rv3_sqr(n);
  if (m2 > tol && n2 > tol) {
    cosphi = rv3_dot(m, n);
    cosphi /= (real) sqrt(m2 * n2);
    if (cosphi >= 1.f) cosphi = 1.f;
    else if (cosphi < -1.f) cosphi = -1.f;
  }
  phi = (real) acos(cosphi);
  if (rv3_dot(n, xij) < 0.0) phi = -phi;

  /* optionally calculate the gradient */
  if (gi != NULL) {
    if (m2 > tol && n2 > tol) {
      rv3_smul2(gi, m, nxkj/m2);
      rv3_smul2(gl, n, -nxkj/n2);
      rv3_smul2(uvec, gi, rv3_dot(xij, xkj)/nxkj2);
      rv3_smul2(vvec, gl, rv3_dot(xkl, xkj)/nxkj2);
      rv3_diff(svec, uvec, vvec);
      rv3_diff(gj, svec, gi);
      rv3_nadd(gk, svec, gl);
    } else { /* clear the gradients */
      rv3_zero(gi);
      rv3_zero(gj);
      rv3_zero(gk);
      rv3_zero(gl);
    }
  }
  return phi;
}


/* structure for dihedral calculation */
typedef struct {
  int  szreal; /* sizeof real */
  int  pad0;   /* padding */
  real phi; /* cis is zero, clockwise positive */
  real cos; /* cos(m, n) */
  real sgn; /* (0, pi) is 1.0, otherwise -1.0 */

  real g2;
  real g[4][3]; /* gradient for each particle */

  real div; /* the divengence */
  real d4ij, d4ik, d4jj, d4jk, d4jl, d4kk, d4kl;

  unsigned int flags; /* a copy of flags used */
  int t1, t2, t3; /* gromacs shift indices */
  const void *pbcdata; /* periodic boundary condition descriptor */
  int (*pbcdiff)(real *xij, const real *xi, const real *xj, const void *);
    /* function to handle pbc, use GROMACS convention: the last is the difference */
} dihcalc_t;

#define DIH_GRAD  0x0001
#define DIH_DIV   0x0002
/*#define DIH_CONJ  0x0004 */
/*#define DIH_PROJ  0x0008 */
#define DIH_I     0x0010
#define DIH_J     0x0020
#define DIH_K     0x0040
#define DIH_L     0x0080
#define DIH_FOUR  (DIH_I|DIH_J|DIH_K|DIH_L)
/* the four atoms involved */
#define DIH_ALL   (DIH_FOUR|DIH_GRAD|DIH_DIV)
/* only I and L, so no divergence */
#define DIH_ENDS  (DIH_GRAD|DIH_I|DIH_L)
/* polymer convention, 0 == trans */
#define DIH_POLYMER 0x1000

/* compute the dihedral angle, gradient g and divegence
 * of the field v conjugate to gradient (v.g = 1)
 *
 * if dih is NULL and flags is 0, only the dihedral angle is computed
 * optionally, the gradient and divergent are computed with flags
 * DIH_GRAD and DIH_DIV respectively (the latter requires the former)
 * routine for treating periodic boundary condition can specified by
 * assigning a function pointer to dih->pbcdiff with additional information
 * to dih->pbcdata entry, otherwise, dih->pbcdiff *must* be set to NULL
 * the procedure of computing similar to that in GROMACS
 *
 * the conjugate field v = g / [g.g], such that v.g = 1, where g = grad(phi)
 * it is not explicitly computed (since it lies along the gradient)
 * however, the denominator is saved to dih->g2
 * the calculation of the divergence of v is simplified by the fact that
 * the divergence of the gradient is always zero, i.e., div.g = 0, thus
 *     div.v = -2 [ g.(gg).g ] /[g.g]^2,
 * where gg = grad grad(phi) involves: d4ij, d4ik, ..., d4kl.
 *
 * both g and div can be computed for a subset of the four involving atoms
 * by passing `flags' a combination of DIH_I, DIH_J, DIH_K and DIH_L
 * however, *all* moments d4ij, d4ik, ... , d4kl are always calculated
 * though only the involved ones are used to produce the divergence. */
#define rv3_calcdihv(dih, x, idx, flags) \
  rv3_calcdih(dih, x[*(idx)], x[*(idx+1)], x[*(idx+2)], x[*(idx+3)], flags)

INLINE real rv3_calcdih(dihcalc_t *dih,
    const real *xi, const real *xj, const real *xk, const real *xl,
    unsigned int flags)
{
  real dot, scl, tol, vol, phi, sgn, cosphi;
  real nxkj, nxkj2, m2, n2;
  real xij[3], xkj[3], xkl[3];
  real m[3], n[3]; /* the planar vector of xij x xkj,  and xkj x xkj */

  if (dih != NULL && sizeof(real) != dih->szreal) {
    fprintf(stderr, "size real should be %d instead of %d\n",
        (int) sizeof(real), (int) dih->szreal);
    exit(1);
  }
  if (dih != NULL && dih->pbcdiff != NULL) { /* handle pbc */
    dih->t1 = (*dih->pbcdiff)(xij, xi, xj, dih->pbcdata);
    dih->t2 = (*dih->pbcdiff)(xkj, xk, xj, dih->pbcdata);
    dih->t3 = (*dih->pbcdiff)(xkl, xk, xl, dih->pbcdata);
  } else {
    rv3_diff(xij, xi, xj);
    rv3_diff(xkj, xk, xj);
    rv3_diff(xkl, xk, xl);
  }
  nxkj2 = rv3_sqr(xkj);
  nxkj = (real) sqrt(nxkj2);
  if (sizeof(real) <= 4)
    tol = nxkj2 * 6e-8f;
  else
    tol = nxkj2 * 1e-16f;

  rv3_cross(m, xij, xkj);
  m2 = rv3_sqr(m);
  rv3_cross(n, xkj, xkl);
  n2 = rv3_sqr(n);
  if (m2 > tol && n2 > tol) {
    scl = (real) sqrt(m2*n2);
    dot = rv3_dot(m, n);
    cosphi = dot/scl;
    if (cosphi >= (real) 1.) cosphi = 1.f;
    else if (cosphi < (real)(-1.)) cosphi = -1.f;
  } else {
    cosphi = 1.f;
  }
  phi = (real) acos(cosphi);
  vol = rv3_dot(n, xij);
  sgn = (vol > 0.0f) ? 1.0f : -1.0f;
  phi *= sgn;
  if (flags & DIH_POLYMER) { /* switch to polymer convention, 0 == trans */
    if (phi > 0) phi -= M_PI;
    else phi += M_PI;
  }
  if (dih != NULL) {
    dih->phi = phi;
    dih->sgn = sgn;
    dih->cos = cosphi;
    dih->flags = flags;
  }

  /* optionally calculate the gradient */
  if (dih != NULL && (flags & (DIH_GRAD|DIH_DIV))) { /* divergence implies gradient */
    /* clear divergence */
    dih->div = dih->d4ij = dih->d4ik = dih->d4jj = dih->d4jk = dih->d4jl = dih->d4kk = dih->d4kl = 0.0f;

    /* calculate the gradient of the dihedral */
    if (m2 > tol && n2 > tol) {
      real uvec[3], vvec[3], svec[3], g2all, invg2;
      unsigned doi, doj, dok, dol;

      doi = (flags & DIH_I);
      doj = (flags & DIH_J);
      dok = (flags & DIH_K);
      dol = (flags & DIH_L);

      rv3_smul2(dih->g[0], m,  nxkj/m2);
      rv3_smul2(dih->g[3], n, -nxkj/n2);

      rv3_smul2(uvec, dih->g[0], rv3_dot(xij, xkj)/nxkj2);
      rv3_smul2(vvec, dih->g[3], rv3_dot(xkl, xkj)/nxkj2);
      rv3_diff(svec, uvec, vvec);

      rv3_diff(dih->g[1], svec, dih->g[0]);
      rv3_nadd(dih->g[2], svec, dih->g[3]);

      g2all = 0.0f;
      if (doi) g2all += rv3_sqr(dih->g[0]);
      if (doj) g2all += rv3_sqr(dih->g[1]);
      if (dok) g2all += rv3_sqr(dih->g[2]);
      if (dol) g2all += rv3_sqr(dih->g[3]);
      dih->g2 = g2all;
      invg2 = 1.0f/g2all;

      if (flags & DIH_DIV) {
        real xkjv[3], nvv[3], mvv[3];
        real gjxij, gjmvv, gjxkl, gjnvv;
        real gkmvv, gknvv, gkxkl, gkxij;
        real kivkj, klvkj, ljvkj, ijvkj;
        real kikl, ijlj;
        real tmp1, tmp2;
        real sinmn;

        rv3_smul2(mvv, m, 1.0f/m2);
        rv3_smul2(nvv, n, 1.0f/n2);
        rv3_smul2(xkjv, xkj, 1.0f/nxkj);

        sinmn = vol*nxkj/(m2*n2);

        ijvkj = rv3_dot(xij, xkjv);
        kivkj = nxkj-ijvkj;
        klvkj = rv3_dot(xkl, xkjv);
        ljvkj = nxkj-klvkj;

        ijlj = ijvkj*ljvkj;
        kikl = kivkj*klvkj;

        gjxij = rv3_dot(dih->g[1], xij);
        gjxkl = rv3_dot(dih->g[1], xkl);
        gjmvv = rv3_dot(dih->g[1], mvv);
        gjnvv = rv3_dot(dih->g[1], nvv);
        gkxij = rv3_dot(dih->g[2], xij);
        gkxkl = rv3_dot(dih->g[2], xkl);
        gkmvv = rv3_dot(dih->g[2], mvv);
        gknvv = rv3_dot(dih->g[2], nvv);

        tmp1 = nxkj2*sinmn;
        tmp2 = tmp1/m2;
        dih->d4ij = kikl*tmp2;
        dih->d4ik = ijlj*tmp2;
        tmp2 = tmp1/n2;
        dih->d4jl = kikl*tmp2;
        dih->d4kl = ijlj*tmp2;

        dih->d4jj = -(gjxij*gjmvv+gjxkl*gjnvv)/nxkj
                +2.0f*(kivkj*gjmvv-klvkj*gjnvv)*(-kikl*sinmn);

        dih->d4jk = (gjxij*gkmvv+gjxkl*gknvv)/nxkj
              +(-(gjmvv*ljvkj+gkmvv*klvkj)*(ijvkj*kivkj)
                +(gjnvv*ijvkj+gknvv*kivkj)*(ljvkj*klvkj) )*sinmn;

        dih->d4kk = -(gkxkl*gknvv+gkxij*gkmvv)/nxkj
                +2.0f*(ljvkj*gknvv-ijvkj*gkmvv)*(ijlj*sinmn);

        /* summarize */
        if ((flags & DIH_FOUR) == DIH_FOUR) {
          tmp1 = dih->d4jj + dih->d4kk;
          tmp2 = dih->d4ij + dih->d4ik+dih->d4jk+dih->d4jl+dih->d4kl;
        } else {
          tmp1 = tmp2 = 0.0f;
          if (doj) { tmp1 += dih->d4jj; }
          if (dok) { tmp1 += dih->d4kk; }
          if (doi && doj) tmp2 += dih->d4ij;
          if (doi && dok) tmp2 += dih->d4ik;
          if (doj && dok) tmp2 += dih->d4jk;
          if (doj && dol) tmp2 += dih->d4jl;
          if (dok && dol) tmp2 += dih->d4kl;
        }
        dih->div = -2.0f*(tmp1+2.0f*tmp2)*(invg2*invg2);
      } /* do divengence */

    } else { /* clear the gradients */
      int j;
      for (j = 0; j < 4; j++)
        rv3_zero(dih->g[j]);
    }
  }
  return phi;
}

/* compute the trihedral angle
 * http://planetmath.org/encyclopedia/TrihedralAngle.html
 * tan(omega/2) = vol/den,
 * where
 * den = r1 (r2.r3) + r2 (r1.r3) + r3 (r1.r2) + r1 r2 r3
 */
INLINE real rv3_solidang(const real v1[], const real v2[], const real v3[],
  real g1[], real g2[], real g3[])
{
  real vc[3];
  real r1, r2, r3;
  real ang, vol, den, v2d2, scnum, scden;
  const real eps = 1e-10;

  r1 = rv3_norm(v1);
  r2 = rv3_norm(v2);
  r3 = rv3_norm(v3);
  if (g1 != NULL) rv3_zero(g1);
  if (g2 != NULL) rv3_zero(g2);
  if (g3 != NULL) rv3_zero(g3);

  /* at least two points coincide */
  if (r1 < eps || r2 < eps || r3 < eps) return 0;

  /* the numerator */
  vol = rv3_dot(v3, rv3_cross(vc, v1, v2));

  /* the denominator */
  den = r1*rv3_dot(v3, v2) + r2*rv3_dot(v3, v1)
      + r3*(r1*r2 + rv3_dot(v1, v2));

  v2d2 = vol*vol + den*den;

  /* this happens if two vector are opposite
     the solid angle could be evolved from  +/-pi or 0
     but unfortunately, we don't know which one */
  if (v2d2 < eps) return 0;

  if (g1 != NULL && g2 != NULL && g3 != NULL) { /* compute the gradients */
    scnum =  2.f*den/v2d2;
    scden = -2.f*vol/v2d2;

    /* cross products */
    rv3_smul(rv3_cross(g3, v1, v2), scnum);
    rv3_smul(rv3_cross(g1, v2, v3), scnum);
    rv3_smul(rv3_cross(g2, v3, v1), scnum);

    /* compute the contributions to the denominator */
    rv3_lincomb2(vc, v2, v3, r3, r2);
    rv3_sinc(vc, v1, (rv3_dot(v2, v3) + r2*r3)/r1);
    rv3_sinc(g1, vc, scden);

    rv3_lincomb2(vc, v1, v3, r3, r1);
    rv3_sinc(vc, v2, (rv3_dot(v1, v3) + r1*r3)/r2);
    rv3_sinc(g2, vc, scden);

    rv3_lincomb2(vc, v1, v2, r2, r1);
    rv3_sinc(vc, v3, (rv3_dot(v1, v2) + r1*r2)/r3);
    rv3_sinc(g3, vc, scden);
  }

  /* calculate tan(omega/2) */
  ang = atan2(vol, den); /* 0 to pi */
  return 2*ang;
}


/* compute the Gauss integral for the two line segments, with gradients
 *    int_i \int_j (dri X drj).rij/ rij^3,
 * over two line segments rip - ri, rjp - rj, and rij = ri - rj
 * (-2 pi, 2 pi)
 * Note the sign is opposite to that of the dihedral */
INLINE real rv3_solidang2g(const real ri[], const real rip[], const real rj[],
  const real rjp[], real gi[], real gip[], real gj[], real gjp[])
{
  rv3_t v0, v1, v2, v3, g0, g1, g2, g3, g4, g5;
  real ang1, ang2;

  rv3_diff(v0, ri, rj);
  rv3_diff(v1, ri, rjp);
  rv3_diff(v2, rip, rj);
  rv3_diff(v3, rip, rjp);

  ang1 = rv3_solidang(v0, v1, v2, g0, g1, g2);
  ang2 = rv3_solidang(v2, v1, v3, g3, g4, g5);

  rv3_inc(rv3_inc(rv3_copy(gi,  g0), g1), g4);
  rv3_inc(rv3_inc(rv3_copy(gip, g2), g3), g5);
  rv3_neg(rv3_inc(rv3_inc(rv3_copy(gj,  g0), g2), g3));
  rv3_neg(rv3_inc(rv3_inc(rv3_copy(gjp, g1), g4), g5));

  return ang1 + ang2;
}


/* compute the double integral, old code
 *    \int_i \int_j (dri X drj).rij/ rij^3,
 * over two line segments rip - ri, rjp - rj, and rij = ri - rj
 * (-2 pi, 2 pi)
 * Note the sign is opposite to that of the dihedral */
INLINE real rv3_solidang2(const real *ri, const real *rip,
    const real *rj, const real *rjp)
{
  real v0[3], v1[3], v2[3], v3[3], vc[3];
  double r0, r1, r2, r3;
  double ang, vol, dn1, dn2, dn, tmp;

  r0 = rv3_norm(rv3_diff(v0, ri, rj));
  r1 = rv3_norm(rv3_diff(v1, ri, rjp));
  r2 = rv3_norm(rv3_diff(v2, rip, rj));
  r3 = rv3_norm(rv3_diff(v3, rip, rjp));

  /* avoid coplanar vectors */
  vol = rv3_dot(v0, rv3_cross(vc, v1, v2));
  if(fabs(vol) < 1e-28) return 0;

  /* calculate the denominator */
  tmp = r1*r2 + rv3_dot(v1, v2);
  /* http://planetmath.org/encyclopedia/TrihedralAngle.html
   * tan(omega/2) = vol/den,
   * where
   * den = r1 (r2.r3) + r2 (r1.r3) + r3 (r1.r2) + r1 r2 r3
   * */
  dn1 = r1*rv3_dot(v0, v2) + r2*rv3_dot(v0, v1) + r0*tmp;
  dn2 = r1*rv3_dot(v3, v2) + r2*rv3_dot(v3, v1) + r3*tmp;

  /* calculate tan(omega1/2 + omega2/2) */
  dn = (dn1 + dn2)/(dn1*dn2 - vol*vol);
  ang = atan(fabs(vol) * dn) + (dn < 0 ? M_PI : 0); /* 0 to pi */

  return (real) (vol > 0 ? 2*ang : -2*ang);
}


INLINE dv3_t *dm3_fromrm3(double a[3][3], real ra[3][3])
{
  a[0][0] = ra[0][0];
  a[0][1] = ra[0][1];
  a[0][2] = ra[0][2];
  a[1][0] = ra[1][0];
  a[1][1] = ra[1][1];
  a[1][2] = ra[1][2];
  a[2][0] = ra[2][0];
  a[2][1] = ra[2][1];
  a[2][2] = ra[2][2];
  return a;
}


/* a = b */
INLINE dv3_t *dm3_copy(double a[3][3], double b[3][3])
{
  dv3_copy(a[0], b[0]);
  dv3_copy(a[1], b[1]);
  dv3_copy(a[2], b[2]);
  return a;
}

/* transpose */
INLINE dv3_t *dm3_trans(double a[3][3])
{
  double x;
  x = a[0][1], a[0][1] = a[1][0], a[1][0] = x;
  x = a[0][2], a[0][2] = a[2][0], a[2][0] = x;
  x = a[2][1], a[2][1] = a[1][2], a[1][2] = x;
  return a;
}

/* a = u^T v */
INLINE dv3_t *dm3_vtv(double a[3][3], const double *u, const double *v)
{
  a[0][0] = u[0]*v[0];
  a[0][1] = u[0]*v[1];
  a[0][2] = u[0]*v[2];
  a[1][0] = u[1]*v[0];
  a[1][1] = u[1]*v[1];
  a[1][2] = u[1]*v[2];
  a[2][0] = u[2]*v[0];
  a[2][1] = u[2]*v[1];
  a[2][2] = u[2]*v[2];
  return a;
}

/* a += b */
INLINE dv3_t *dm3_inc(double a[3][3], double b[3][3])
{
  a[0][0] += b[0][0];
  a[0][1] += b[0][1];
  a[0][2] += b[0][2];
  a[1][0] += b[1][0];
  a[1][1] += b[1][1];
  a[1][2] += b[1][2];
  a[2][0] += b[2][0];
  a[2][1] += b[2][1];
  a[2][2] += b[2][2];
  return a;
}

/* a += b*s */
INLINE dv3_t *dm3_sinc(double a[3][3], double b[3][3], double s)
{
  a[0][0] += b[0][0]*s;
  a[0][1] += b[0][1]*s;
  a[0][2] += b[0][2]*s;
  a[1][0] += b[1][0]*s;
  a[1][1] += b[1][1]*s;
  a[1][2] += b[1][2]*s;
  a[2][0] += b[2][0]*s;
  a[2][1] += b[2][1]*s;
  a[2][2] += b[2][2]*s;
  return a;
}

/* c = a b */
INLINE dv3_t *dm3_mul(double c[3][3], double a[3][3], double b[3][3])
{
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      c[i][j] = a[i][0]*b[0][j]+a[i][1]*b[1][j]+a[i][2]*b[2][j];
  return c;
}

/* c = a b^T */
INLINE dv3_t *dm3_mult(double c[3][3], double a[3][3], double b[3][3])
{
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      c[i][j] = dv3_dot(a[i], b[j]);
  return c;
}

/* c = a^T b */
INLINE dv3_t *dm3_tmul(double c[3][3], double a[3][3], double b[3][3])
{
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      c[i][j] = a[0][i]*b[0][j] + a[1][i]*b[1][j] + a[2][i]*b[2][j];
  return c;
}

/* c = a v */
INLINE double *dm3_mulvec(double *c, double a[3][3], const double *v)
{
  c[0] = a[0][0]*v[0] + a[0][1]*v[1] + a[0][2]*v[2];
  c[1] = a[1][0]*v[0] + a[1][1]*v[1] + a[1][2]*v[2];
  c[2] = a[2][0]*v[0] + a[2][1]*v[1] + a[2][2]*v[2];
  return c;
}

/* c = a^T v */
INLINE double *dm3_tmulvec(double *c, double a[3][3], const double *v)
{
  c[0] = a[0][0]*v[0] + a[1][0]*v[1] + a[2][0]*v[2];
  c[1] = a[0][1]*v[0] + a[1][1]*v[1] + a[2][1]*v[2];
  c[2] = a[0][2]*v[0] + a[1][2]*v[1] + a[2][2]*v[2];
  return c;
}

/* determinant of a 3x3 matrix */
INLINE double dm3_det(double a[3][3])
{
  return a[0][0] * (a[1][1]*a[2][2] - a[1][2]*a[2][1])
      +  a[0][1] * (a[1][2]*a[2][0] - a[1][0]*a[2][2])
      +  a[0][2] * (a[1][0]*a[2][1] - a[1][1]*a[2][0]);
}

/* inverse matrix b = a^(-1) */
INLINE dv3_t *dm3_inv(double b[3][3], double a[3][3])
{
  double d00, d01, d02, detm;
  d00 = a[1][1]*a[2][2] - a[1][2]*a[2][1];
  d01 = a[1][2]*a[2][0] - a[1][0]*a[2][2];
  d02 = a[1][0]*a[2][1] - a[1][1]*a[2][0];
  detm = a[0][0]*d00 + a[0][1]*d01 + a[0][2]*d02;
  if (fabs(detm) < DBL_EPSILON) detm = (detm < 0) ? -DBL_EPSILON: DBL_EPSILON;
  b[0][0] = d00/detm;
  b[0][1] = (a[2][1]*a[0][2] - a[0][1]*a[2][2])/detm;
  b[0][2] = (a[0][1]*a[1][2] - a[0][2]*a[1][1])/detm;
  b[1][0] = d01/detm;
  b[1][1] = (a[2][2]*a[0][0] - a[2][0]*a[0][2])/detm;
  b[1][2] = (a[0][2]*a[1][0] - a[1][2]*a[0][0])/detm;
  b[2][0] = d02/detm;
  b[2][1] = (a[2][0]*a[0][1] - a[2][1]*a[0][0])/detm;
  b[2][2] = (a[0][0]*a[1][1] - a[0][1]*a[1][0])/detm;
  return b;
}

INLINE rv3_t *rm3_fromdm3(real a[3][3], double da[3][3])
{
  a[0][0] = (real) da[0][0];
  a[0][1] = (real) da[0][1];
  a[0][2] = (real) da[0][2];
  a[1][0] = (real) da[1][0];
  a[1][1] = (real) da[1][1];
  a[1][2] = (real) da[1][2];
  a[2][0] = (real) da[2][0];
  a[2][1] = (real) da[2][1];
  a[2][2] = (real) da[2][2];
  return a;
}

/* a = b */
INLINE rv3_t *rm3_copy(real a[3][3], real b[3][3])
{
  rv3_copy(a[0], b[0]);
  rv3_copy(a[1], b[1]);
  rv3_copy(a[2], b[2]);
  return a;
}

/* transpose */
INLINE rv3_t *rm3_trans(real a[3][3])
{
  real x;
  x = a[0][1], a[0][1] = a[1][0], a[1][0] = x;
  x = a[0][2], a[0][2] = a[2][0], a[2][0] = x;
  x = a[2][1], a[2][1] = a[1][2], a[1][2] = x;
  return a;
}

/* a = u^T v */
INLINE rv3_t *rm3_vtv(real a[3][3], const real *u, const real *v)
{
  a[0][0] = u[0]*v[0];
  a[0][1] = u[0]*v[1];
  a[0][2] = u[0]*v[2];
  a[1][0] = u[1]*v[0];
  a[1][1] = u[1]*v[1];
  a[1][2] = u[1]*v[2];
  a[2][0] = u[2]*v[0];
  a[2][1] = u[2]*v[1];
  a[2][2] = u[2]*v[2];
  return a;
}

/* a += b */
INLINE rv3_t *rm3_inc(real a[3][3], real b[3][3])
{
  a[0][0] += b[0][0];
  a[0][1] += b[0][1];
  a[0][2] += b[0][2];
  a[1][0] += b[1][0];
  a[1][1] += b[1][1];
  a[1][2] += b[1][2];
  a[2][0] += b[2][0];
  a[2][1] += b[2][1];
  a[2][2] += b[2][2];
  return a;
}

/* a += b*s */
INLINE rv3_t *rm3_sinc(real a[3][3], real b[3][3], real s)
{
  a[0][0] += b[0][0]*s;
  a[0][1] += b[0][1]*s;
  a[0][2] += b[0][2]*s;
  a[1][0] += b[1][0]*s;
  a[1][1] += b[1][1]*s;
  a[1][2] += b[1][2]*s;
  a[2][0] += b[2][0]*s;
  a[2][1] += b[2][1]*s;
  a[2][2] += b[2][2]*s;
  return a;
}

/* c = a b */
INLINE rv3_t *rm3_mul(real c[3][3], real a[3][3], real b[3][3])
{
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      c[i][j] = a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j];
  return c;
}

/* c = a b^T */
INLINE rv3_t *rm3_mult(real c[3][3], real a[3][3], real b[3][3])
{
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      c[i][j] = rv3_dot(a[i], b[j]);
  return c;
}

/* c = a^T b */
INLINE rv3_t *rm3_tmul(real c[3][3], real a[3][3], real b[3][3])
{
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      c[i][j] = a[0][i]*b[0][j] + a[1][i]*b[1][j] + a[2][i]*b[2][j];
  return c;
}

/* c = a v */
INLINE real *rm3_mulvec(real *c, real a[3][3], const real *v)
{
  c[0] = a[0][0]*v[0] + a[0][1]*v[1] + a[0][2]*v[2];
  c[1] = a[1][0]*v[0] + a[1][1]*v[1] + a[1][2]*v[2];
  c[2] = a[2][0]*v[0] + a[2][1]*v[1] + a[2][2]*v[2];
  return c;
}

/* c = a^T v */
INLINE real *rm3_tmulvec(real *c, real a[3][3], const real *v)
{
  c[0] = a[0][0]*v[0] + a[1][0]*v[1] + a[2][0]*v[2];
  c[1] = a[0][1]*v[0] + a[1][1]*v[1] + a[2][1]*v[2];
  c[2] = a[0][2]*v[0] + a[1][2]*v[1] + a[2][2]*v[2];
  return c;
}

/* determinant of a 3x3 matrix */
INLINE real rm3_det(real a[3][3])
{
  return a[0][0] * (a[1][1]*a[2][2] - a[1][2]*a[2][1])
      +  a[0][1] * (a[1][2]*a[2][0] - a[1][0]*a[2][2])
      +  a[0][2] * (a[1][0]*a[2][1] - a[1][1]*a[2][0]);
}

/* inverse matrix b = a^(-1) */
INLINE rv3_t *rm3_inv(real b[3][3], real a[3][3])
{
  real d00, d01, d02, detm;
  d00 = a[1][1]*a[2][2] - a[1][2]*a[2][1];
  d01 = a[1][2]*a[2][0] - a[1][0]*a[2][2];
  d02 = a[1][0]*a[2][1] - a[1][1]*a[2][0];
  detm = a[0][0]*d00 + a[0][1]*d01 + a[0][2]*d02;
  if (fabs(detm) < 1e-30) detm = (detm < 0) ? -1e-30f: 1e-30f;
  b[0][0] = d00/detm;
  b[0][1] = (a[2][1]*a[0][2] - a[0][1]*a[2][2])/detm;
  b[0][2] = (a[0][1]*a[1][2] - a[0][2]*a[1][1])/detm;
  b[1][0] = d01/detm;
  b[1][1] = (a[2][2]*a[0][0] - a[2][0]*a[0][2])/detm;
  b[1][2] = (a[0][2]*a[1][0] - a[1][2]*a[0][0])/detm;
  b[2][0] = d02/detm;
  b[2][1] = (a[2][0]*a[0][1] - a[2][1]*a[0][0])/detm;
  b[2][2] = (a[0][0]*a[1][1] - a[0][1]*a[1][0])/detm;
  return b;
}

/* compute eigenvalues of a 3x3 matrix
 * solving a cubic equation */
INLINE double *dm3_eigval(double v[3], double a[3][3])
{
  double m, p, q, pr, pr3, a00, a11, a22;

  m = (a[0][0] + a[1][1] + a[2][2])/3;
  a00 = a[0][0] - m;
  a11 = a[1][1] - m;
  a22 = a[2][2] - m;
  q = ( a00 * (a11*a22 - a[1][2]*a[2][1])
      + a[0][1] * (a[1][2]*a[2][0] - a[1][0]*a22)
      + a[0][2] * (a[1][0]*a[2][1] - a11*a[2][0]) ) / 2.0;
  p = (a00*a00 + a11*a11 + a22*a22) / 6.0
    + (a[0][1]*a[1][0] + a[1][2]*a[2][1] + a[2][0]*a[0][2]) / 3.0;
  /* solve x^3 - 3 p x  - 2 q = 0 */
  pr = sqrt(p);
  pr3 = p*pr;
  if (pr3 <= fabs(q)) {
    if (q < 0.) { /* choose phi = pi/3 */
      v[1] = v[0] = m + pr;
      v[2] = m - 2.0 * pr;
    } else { /* phi = 0 */
      v[0] = m + 2.0 * pr;
      v[2] = v[1] = m - pr;
    }
  } else {
    double phi = acos(q/pr3)/3.0; /* 0 < phi < pi/3 */
    v[0] = m + 2.0 * pr * cos(phi);  /* largest */
    v[1] = m + 2.0 * pr * cos(phi - 2*M_PI/3); /* second largest */
    v[2] = m + 2.0 * pr * cos(phi + 2*M_PI/3); /* smallest */
#ifdef RV3_DEBUG
    { int i; double vi, y[3], dy[3];
      for (i = 0; i < 3; i++) { vi = v[i] - m; y[i] = vi*(vi*vi - 3*p) - 2 * q; dy[i] = 3*(vi*vi - p); }
      dv3_print(v,  "roots   ", "%26.14e", 1);
      dv3_print(y,  "residues", "%26.14e", 1);
      dv3_print(dy, "slope   ", "%26.14e", 1);
      printf("m %20.14f, q/pr3 %22.14e, pr %20.14f, phi %20.14f, %20.14f deg\n", m, q/pr3, pr, phi/M_PI*180, 120 - phi/M_PI*180);
    }
#endif
  }
  return v;
}

/* sort s to descending order, order u and v correspondingly */
INLINE void dv3_sort3(double s[3], double (*u)[3], double (*v)[3])
{
  double tmp;

  if (s[2] > s[1]) {
    tmp = s[1]; s[1] = s[2]; s[2] = tmp;
    if (u) dv3_swap(u[1], u[2]);
    if (v) dv3_swap(v[1], v[2]);
  }
  if (s[1] > s[0]) {
    tmp = s[0]; s[0] = s[1]; s[1] = tmp;
    if (u) dv3_swap(u[0], u[1]);
    if (v) dv3_swap(v[0], v[1]);
  }
  if (s[2] > s[1]) {
    tmp = s[1]; s[1] = s[2]; s[2] = tmp;
    if (u) dv3_swap(u[1], u[2]);
    if (v) dv3_swap(v[1], v[2]);
  }
}

/* return the pivot row for column c, row index starts from r0 */
INLINE int dm3_pivot_(double m[3][3], int r0, int c, double *max)
{
  int i, r = r0;
  double tmp;

  for (*max = fabs(m[r = r0][c]), i = r0 + 1; i < 3; i++)
    if ((tmp = fabs(m[i][c])) > *max) r = i, *max = tmp;
  return r;
}

/* solve matrix equation a x = 0, matrix 'a' is destroyed
 * solutions are saved as *row* vectors in 'x'
 * return the number of solutions */
INLINE int dm3_solvezero(double a[3][3], double (*x)[3], double tol)
{
  double max;
  int i, j, k, ns = 0;

  k = dm3_pivot_(a, 0, 0, &max); /* pivot for column 0 */
  if (max <= tol) { /* found the first eigenvector */
    dv3_make(x[ns++], 1, 0, 0);
    k = dm3_pivot_(a, 0, 1, &max); /* pivot for column 1 */
    if (max <= tol) {
      dv3_make(x[ns++], 0, 1, 0);
      k = dm3_pivot_(a, 0, 2, &max);
      if (max <= tol) dv3_make(x[ns++], 0, 0, 1);
    } else {
      if (k != 0) dv3_swap(a[0], a[k]);
      a[0][2] /= a[0][1]; /* normalize row 0, a[0][1] = 1; */
      for (i = 1; i < 3; i++) a[i][2] -= a[i][1]*a[0][2];
      dm3_pivot_(a, 1, 2, &max);
      if (max <= tol) dv3_makenorm(x[ns++], 0, a[0][2], -1);
    }
  } else {
    if (k != 0) dv3_swap(a[0], a[k]);
    a[0][1] /= a[0][0]; a[0][2] /= a[0][0]; /* normalize row 0, a[0][0] = 1 */
    for (i = 1; i < 3; i++)
      for (j = 1; j < 3; j++) /* a[i][0] = 0 now */
        a[i][j] -= a[i][0]*a[0][j];
    k = dm3_pivot_(a, 1, 1, &max); /* pivot for column 1 */
    if (max <= tol) { /* column 1 is empty */
      dv3_makenorm(x[ns++], -a[0][1], 1, 0);
      k = dm3_pivot_(a, 1, 2, &max);
      if (max <= tol) /* column 2 is empty too */
        dv3_makenorm(x[ns++], -a[0][2], 0, 1);
    } else {
      if (k != 1) dv3_swap(a[1], a[k]);
      a[1][2] /= a[1][1]; /* normalize row 1, a[1][1] = 1 */
      a[2][2] -= a[2][1]*a[1][2];
      if (fabs(a[2][2]) > tol) {
#ifdef RV3_DEBUG
        printf("a22 %g vs tol %g\n", a[2][2], tol);
#endif
        return 0; /* no solutions */
      }
      a[0][2] -= a[0][1]*a[1][2];
      dv3_makenorm(x[ns++], -a[0][2], -a[1][2], 1);
    }
  }
  return ns;
}

/* given an eigenvalue, return the corresponding eigenvectors */
INLINE int dm3_eigvecs(double (*vecs)[3], double mat[3][3], double val, double tol)
{
  double m[3][3];

  dm3_copy(m, mat); /* make a matrix */
  m[0][0] -= val; m[1][1] -= val; m[2][2] -= val;
  return dm3_solvezero(m, vecs, tol);
}

/* given the matrix 'mat' and its eigenvalues 'v' return eigenvalues 'vecs' */
INLINE dv3_t *dm3_eigsys(double v[3], double vecs[3][3], double mat[3][3], int nt)
{
  double vs[5][3], sq, tol, nv; /* for safty, vs needs 5 rows */
  int n = 0, nn, i;

  dm3_eigval(v, mat);
  for (sq = 0, i = 0; i < 3; i++) sq += dv3_sqr(mat[i]);
  /* errors of the eigenvalues from the cubic equation can reach sqrt(eps)
   * use a large tolerance */
  tol = 10.0 * sqrt(sq * DBL_EPSILON);

  for (nn = i = 0; i < 3; i++) {
    n = dm3_eigvecs(vs+nn, mat, v[nn], tol);
    if (n == 0) goto ERR;
    if ((nn += n) >= 3) break;
  }

  /* NOTE: make sure eigenvectors are orthogonal */
  dv3_normalize( dv3_cross(vs[2], vs[0], vs[1]) );
  dv3_normalize( dv3_cross(vs[1], vs[2], vs[0]) );

  dm3_copy(vecs, vs);
  for (i = 0; i < 3; i++) {
    nv = dv3_dot(dm3_mulvec(vs[i], mat, vecs[i]), vecs[i]);
    if (fabs(nv - v[i]) > tol) {
      fprintf(stderr, "corrupted eigenvalue i %d, %g vs. %g\n", i, nv, v[i]);
      goto ERR;
    }
#ifdef RV3_DEBUG
    printf("Eigenvalue: %22.14f vs %22.14f (corrected)\n", v[i], nv);
    dv3_print(vecs[i], "eigenvector i", "%20.12e", 1);
#endif
    v[i] = nv;
  }
#ifdef RV3_DEBUG
  printf("det(V) = %g\n", dm3_det(vecs));
#endif
  dv3_sort3(v, vecs, NULL);

  if (nt) return vecs; else return dm3_trans(vecs);
ERR:
  printf("fatal: bad eigenvalues, n %d, nn %d\n", n, nn);
  dm3_print(mat, "matrix", "%24.16e", 1);
  dv3_print(v, "eigenvalues", "%24.16e", 1);
  exit(1);
  return NULL;
}

/* SVD decomposition of a 3x3 matrix A = U S V^T */
INLINE void dm3_svd(double a[3][3], double u[3][3], double s[3], double v[3][3])
{
  int i, rank;
  double ata[3][3], us[3][3];

  /* 1. compute A^T A and its eigenvectors, which is V */
  dm3_tmul(ata, a, a);
  dm3_eigsys(s, v, ata, 1);
#ifdef RV3_DEBUG
  dv3_print(s, "S^2 ", "%22.14e", 1);
  dm3_print(ata, "A^T A ",  "%20.14f", 1);
  dm3_print(v, "V^T ",  "%20.14f", 1);
#endif

  /* 2. U^T = S^{-1} V^T A^T, and each row of U^T is an eigenvector
   * since eigenvectors are to be normalized, S^{-1} is unnecessary */
  if (s[0] <= 0.0) {
    rank = 0;
    dm3_copy(u, v);
  } else {
    double tol = 10. * sqrt(DBL_EPSILON);
    /* the test i = 1 + (s[1] > s[0]*tol) + (s[2] > s[0]*tol); */
    dm3_mult(u, v, a);
    for (i = 0; i < 3; i++) {
      dv3_copy(us[i], u[i]); /* save a copy of V^T A^T before normalizing it */
      s[i] = dv3_norm(u[i]);
      if (s[i] > 0.0) dv3_smul(u[i], 1.0/s[i]);
    }
    rank = 1;
    rank += (fabs(dv3_dot(u[0], u[1])) < tol && s[1] > tol);
    rank += (fabs(dv3_dot(u[0], u[2])) < tol && fabs(dv3_dot(u[1], u[2])) < tol && s[2] > tol);
#ifdef RV3_DEBUG
    dm3_print(u, "U^T ", "%22.14e", 1);
    dm3_print(us, "Us^T ", "%22.14e", 1);
    dv3_print(s, "S ", "%22.14e", 1);
    dm3_print(a, "A ",  "%20.14f", 1);
    printf("rank = %d, tol %g, det %g, u0.u0 %g, u0.u1 %g, u0.u2 %g, u1.u1 %g, u1.u2 %g, u2.u2 %g\n\n\n", rank, tol, dm3_det(u),
        dv3_sqr(u[0]), dv3_dot(u[0], u[1]), dv3_dot(u[0], u[2]), dv3_sqr(u[1]), dv3_dot(u[1], u[2]), dv3_sqr(u[2]));
#endif
    if (rank <= 2) {
      if (rank == 1) {
        double z[3] = {0, 0, 0}, w, tmp;
        w = fabs(u[0][i = 0]);
        if ((tmp = fabs(u[0][1])) < w) w = tmp, i = 1;
        if ((tmp = fabs(u[0][2])) < w) i = 2;
        z[i] = 1.0f; /* select the smallest element in u[0] as z */
        dv3_normalize( dv3_cross(u[1], z, u[0]) );
        s[1] = dv3_dot(u[1], us[1]); /* S = U^T (V^T A^T)^T is more accurate than sqrt(A^T A) */
        if (s[1] < 0) { s[1] = -s[1]; dv3_neg(u[1]); } /* make sure s[1] > 0 */
      }
      dv3_normalize( dv3_cross(u[2], u[0], u[1]) );
      s[2] = dv3_dot(u[2], us[2]);
      if (s[2] < 0) { s[2] = -s[2]; dv3_neg(u[2]); }
    }
    dv3_sort3(s, u, v);
#ifdef RV3_DEBUG
    printf("det(U) %g, det(V) %g\n", dm3_det(u), dm3_det(v));
#endif
  }
  dm3_trans(v);
  dm3_trans(u);
}

/* eigenvalues of a 3x3 matrix
 * internal calculation are carried out in double precision */
INLINE real *rm3_eigval(real v[3], real a[3][3])
{
  if (sizeof(real) == sizeof(double)) {
    return (real *) dm3_eigval((double *) v, (dv3_t *) a);
  } else { /* the routine require high precision, double is safer */
    double da[3][3], dv[3];

    dm3_fromrm3(da, a);
    dm3_eigval(dv, da);
    return rv3_fromdv3(v, dv);
  }
}

/* solve A x = 0 */
INLINE int rm3_solvezero(real a[3][3], real (*x)[3], real tol)
{
  if (sizeof(real) == sizeof(double)) {
    return dm3_solvezero((dv3_t *) a, (dv3_t *) x, tol);
  } else {
    double da[3][3], dx[3][3];
    int n, i;
    dm3_fromrm3(da, a);
    n = dm3_solvezero(da, dx, tol);
    for (i = 0; i < n; i++)
      rv3_fromdv3(x[i], dx[i]);
    return n;
  }
}

/* given an eigenvalue, return the corresponding eigenvectors */
INLINE int rm3_eigvecs(real (*vecs)[3], real mat[3][3], real val, real tol)
{
  real m[3][3];

  rm3_copy(m, mat); /* make a matrix */
  m[0][0] -= val; m[1][1] -= val; m[2][2] -= val;
  return rm3_solvezero(m, vecs, tol);
}

/* compute eigenvectors for the eigenvalues
 * ideally, eigenvalues should be sorted in magnitude-descending order
 * by default, vecs are transposed as a set of column vectors
 * set 'nt' != 0 to disable it: so vecs[0] is the first eigenvector  */
INLINE rv3_t *rm3_eigsys(real v[3], real vecs[3][3], real mat[3][3], int nt)
{
  if (sizeof(real) == sizeof(double)) {
    return (rv3_t *) dm3_eigsys((double *) v, (dv3_t *) vecs, (dv3_t *) mat, nt);
  } else {
    double dvecs[3][3], dmat[3][3], dv[3];

    dm3_fromrm3(dmat, mat);
    dm3_eigsys(dv, dvecs, dmat, nt);
    rv3_fromdv3(v, dv);
    return rm3_fromdm3(vecs, dvecs);
  }
}

/* SVD decomposition of a 3x3 matrix a = u s v^T */
INLINE void rm3_svd(real a[3][3], real u[3][3], real s[3], real v[3][3])
{
  if (sizeof(real) == sizeof(double)) {
    dm3_svd((dv3_t *) a, (dv3_t *) u, (double *) s, (dv3_t *) v);
  } else {
    double da[3][3], du[3][3], ds[3], dv[3][3];

    dm3_fromrm3(da, a);
    dm3_svd(da, du, ds, dv);
    rm3_fromdm3(u, du);
    rm3_fromdm3(v, dv);
    rv3_fromdv3(s, ds);
  }
}

/* return 0 rotation matrix around v for ang */
INLINE rv3_t *rm3_mkrot(real m[3][3], const real *v, real ang)
{
  real c = (real) cos(ang), s = (real) sin(ang), nc, n[3];

  rv3_copy(n, v);
  rv3_normalize(n);
  nc = 1 - c;
  m[0][0] = n[0]*n[0]*nc + c;
  m[0][1] = n[0]*n[1]*nc - n[2]*s;
  m[0][2] = n[0]*n[2]*nc + n[1]*s;
  m[1][0] = n[1]*n[0]*nc + n[2]*s;
  m[1][1] = n[1]*n[1]*nc + c;
  m[1][2] = n[1]*n[2]*nc - n[0]*s;
  m[2][0] = n[2]*n[0]*nc - n[1]*s;
  m[2][1] = n[2]*n[1]*nc + n[0]*s;
  m[2][2] = n[2]*n[2]*nc + c;
  return m;
}

/* rotate v0 around u by ang, save result to v1 */
INLINE real *rv3_rot(real *v1, const real *v0, const real *u, real ang)
{
  real m[3][3];

  rm3_mkrot(m, u, ang);
  rm3_mulvec(v1, m, v0);
  return v1;
}

/* uniformly distributed random vector [a, a + b) */
#define rv3_rnd0() rv3_rnd(v, 0, 1)
INLINE real *rv3_rnd(rv3_t v, real a, real b)
{
  v[0] = (real) (a + b * rnd0());
  v[1] = (real) (a + b * rnd0());
  v[2] = (real) (a + b * rnd0());
  return v;
}

/* normally distributed random vector */
#define rv3_grand0(v) rv3_grand(v, 0, 1)
INLINE real *rv3_grand(rv3_t v, real c, real r)
{
  v[0] = (real) (c + r * grand0());
  v[1] = (real) (c + r * grand0());
  v[2] = (real) (c + r * grand0());
  return v;
}

/* generate a random orthonormal (unitary) 3x3 matrix */
INLINE rv3_t *rm3_rnduni(real a[3][3])
{
  real dot;

  rv3_rnd(a[0], -.5f, 1.f);
  rv3_normalize(a[0]);

  rv3_rnd(a[1], -.5f, 1.f);
  /* normalize a[1] against a[0] */
  dot = rv3_dot(a[0], a[1]);
  rv3_sinc(a[1], a[0], -dot);
  rv3_normalize(a[1]);

  rv3_cross(a[2], a[0], a[1]);
  return a;
}

#endif /* ZCOM_RV3__ */
#endif /* ZCOM_RV3 */

#ifdef  ZCOM_EIG
#ifndef ZCOM_EIG__
#define ZCOM_EIG__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

STRCLS int eigsym(real *mat, real *eigval, real *eigvec, int n);

/* To reduce a real symmetric matrix 'm' to tridiagonal by Householder transformations.
 * The diagonal elements are saved in vector 'd' and off-diagonal elements 'e'.  */
static void tridiag(real *m, real d[], real e[], int n)
{
  int i, j, k;
  real H, sigma, p, K, *x;

  /* use d[i] to indicate if the i'th Householder transformation is performed */
  for (i = 0; i < n; i++) d[i] = 0;

  /* n-2 Householder transformations */
  for (i = 0; i < n-2; i++) {
    x = m+i*n; /* alias x[k] == m[i*n+k] */

    for (H = 0, k = i+1; k < n; k++) H += x[k]*x[k];
    sigma = (real)(x[i+1] > 0 ? sqrt(H) : -sqrt(H)); /* sigma = sgn(x1) |x| */
    e[i] = -sigma; /* P x = - sigma e1 */
    H += sigma*x[i+1]; /* H= (1/2) |u|^2 = |x|^2 + sigma x1 */

    /* To avoid singularity due to (partially) diagonal matrix as input */
    if (sigma + m[i*n+i] == m[i*n+i]) {
      e[i] = m[i*n+i+1];
      continue;
    }

    x[i+1] += sigma;  /* u = x + sigma e1, we now switch to 'u' */
    for (j = i+1; j < n; j++) m[j*n+i] = x[j]/H; /* save u/H in column i */

    /*  CALCULATE P A P */
    K = 0;
    for (j = i+1; j < n; j++) {
      /* calculate p=A u /H, we only use the up triangle */
      for (p = 0, k = i+1; k <= j; k++) p += m[k*n+j]*x[k];
      for (k = j+1; k < n; k++) p += m[j*n+k]*x[k];
      e[j] = (p /= H); /* save p temporarily to e[j], notice e[i+1..n-1] are not used yet.*/
      K += x[j]*p; /* K = u' p / (2H) */
    }
    K /= (2*H); /* K = u' p / (2H) */
    for (j = i+1; j < n; j++) e[j] -= K*x[j];  /* form  q = p - K u */
    for (j = i+1; j < n; j++) /* calculate A' = A - q u' - u q' (only right-top triangle) */
      for (k = j; k < n; k++)
        m[j*n+k] -= e[j]*x[k]+x[j]*e[k];

    d[i] = 1; /* indicate that the transformation is performed */
  }
  e[n-2] = m[(n-2)*n + n-1]; /* for i == n-2 */
  e[n-1] = 0;

  /* if only eigenvalues are required, enable the above line and ignore the rest */

  /* To form Q = P1 ... Pn-2 */
  d[n-2] = m[(n-2)*n + n-2]; d[n-1] = m[(n-1)*n + n-1]; /* copy last two eigenvalues */
  m[(n-2)*n + n-2] = 1; m[(n-2)*n + n-1] = 0; /* initialize the right-bottom corner */
  m[(n-1)*n + n-2] = 0; m[(n-1)*n + n-1] = 1;

  /* P Q = (1 - u u'/H) Q = Q - (u/H) (u' Q) */
  for (i = n-3; i >= 0; i--) { /* for each P */
    x = m + i*n; /* alias x[k] == m[i*n+k] */

    /* Form eigenvector, ONLY if i'th transformation is performed */
    if (d[i] != 0) {
      for (j = i+1; j < n; j++) {
        /* form K = u'Q */
        for (K = 0, k = i+1; k < n; k++) K += x[k]*m[k*n + j];
        /* Q = Q - K (u/H)  */
        for (k = i+1; k < n; k++) m[k*n + j] -= K*m[k*n + i];
      }
    }
    /* copy the diagonal element and proceed */
    d[i] = m[i*n + i];
    m[i*n + i] = 1;
    for (j = i+1; j < n; j++) m[i*n + j] = m[j*n + i] = 0.;
  }
}


/* diagonize the tridiagonal matrix by QR algorithm,
   whose diagonal is d[0..n-1], off-diagonal is e[0..n-2];
 * reduce from the left-top to right-left */
static void eigtriqr(real d[], real e[], int n, real *mat)
{
  const int itermax = 1000;
  int i, j, k, m, iter, sgn;
  real ks = 0, r, c, s, delta, f, t1, t2, tol;

  e[n-1] = 0;
  tol = (sizeof(real) == sizeof(float)) ? 1e-6f : 1e-12f;
  for (i = 0; i < n; i++) {
    /* for each eigenvalue */
    for (iter = 0; iter < itermax; iter++) {
      /* Look for a single small subdiagonal element to split the matrix */
      for (m = i; m < n-1; m++) {
        if (fabs(e[m]) < (fabs(d[m+1])+fabs(d[m]))*tol)
          break;
      }

      /* I have isolated d[i] from other matrix elements
       * so that d[i] is the eigenvalue.
       * stop iteration and look for next(i+1) eigenvalue  */
      if (m == i) break;

      /* form shift ks */
      delta = d[m]-d[m-1];
      sgn = ((delta > 0) ? 1: -1);
      delta /= e[m-1];
      r = (real) dblhypot(delta, 1);
      ks = d[m] + sgn*e[m-1]/(r + (real) fabs(delta));

      /* Rotations */
      for (j = i; j <= m-1; j++) {
       /* calculate c and s */
       if (j == i) {
         /* First rotation */
         r = (real) dblhypot(d[i]-ks, e[i]);
         c = (d[i]-ks)/r;
         s = e[i]/r;
       } else {
         /* Givens rotations */
         r = (real) dblhypot(e[j-1], f);
         c = e[j-1]/r;
         s = f/r;
         e[j-1] = r;
       }

       /* update the diagonal and off-diagonal elements */
       r = s*(d[j+1]-d[j]) + 2*c*e[j];
       d[j]   += s*r;
       d[j+1] -= s*r;
       e[j]    = c*r - e[j];
       f       = s*e[j+1];
       e[j+1] *= c;

       /* update eigenvectors */
       for (k = 0; k < n; k++) {
         t1 = mat[k*n + j];
         t2 = mat[k*n + j+1];
         mat[k*n + j]   = c*t1+s*t2;
         mat[k*n + j+1] = -s*t1+c*t2;
       }
      } /* end of rotations */
    } /* end for iteration */
    /*printf("Iterate %d times for %d'th eigenvalue.\n", iter, i);*/
  }/* end for each eigenvalue */
}

/* sort eigen values and vectors into ascending order */
static void eigsort(real *d, real *v, int n)
{
  int i, j, im;
  real max, tmp;

  for (i = 0; i < n - 1; i++) {
    /* search the maximal eigenvalue */
    for (max = d[i], im = i, j = i+1; j < n; j++) {
      if (d[j] > max) max = d[im = j];
    }
    if (im != i) { /* change column im and i */
      tmp = d[i], d[i] = d[im], d[im] = tmp;
      for (j = 0; j < n; j++)
        tmp = v[j*n+i], v[j*n+i] = v[j*n+im], v[j*n+im] = tmp;
    }
  }
}

/* solve eigensystem of a real symmetric matrix `mat',
 * eigenvalues saved to `d', eigenvectors to v */
int eigsym(real *mat, real *d, real *v, int n)
{
  real *e;
  int i;

  xnew(e, n);
  for (i = 0; i < n*n; i++) v[i] = mat[i];
  tridiag(v, d, e, n);
  eigtriqr(d, e, n, v);
  eigsort(d, v, n);
  free(e);
  return 0;
}

#endif /* ZCOM_EIG__ */
#endif /* ZCOM_EIG */

#ifdef  ZCOM_LU
#ifndef ZCOM_LU__
#define ZCOM_LU__

/* LU decomposition part  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

STRCLS int lusolve(real *a, real *b, int n);


/* solve A x = b by L U decomposition
 * the matrix `a' will be destroyed
 * the vector `b' will be `x' on return */
int lusolve(real *a, real *b, int n)
{
  int i, j, k, imax = 0;
  real x, max;
  const real mintol = 1e-16; /* absolute minimal value for a pivot */

  for (i = 0; i < n; i++) {  /* normalize each equation */
    for (max = 0.0, j = 0; j < n; j++)
      if ((x = fabs(a[i*n+j])) > max)
        max = x;
    if (max < mintol) {
      return 1;
    }
    for (x = 1.0/max, j = 0; j < n; j++)
      a[i*n+j] *= x;
    b[i] *= x;
  }

  /* step 1: A = L U, column by column */
  for (j = 0; j < n; j++) {
    /* matrix U */
    for (i = 0; i < j; i++) {
      for (x = a[i*n+j], k = 0; k < i; k++)
        x -= a[i*n+k]*a[k*n+j];
      a[i*n+j] = x;
    }

    /* matrix L, diagonal of L are 1 */
    max = 0.0;
    for (i = j; i < n; i++) {
      for (x = a[i*n+j], k = 0; k < j; k++)
        x -= a[i*n+k]*a[k*n+j];
      a[i*n+j] = x;
      if (fabs(x) >= max) {
        max = fabs(x);
        imax = i;
      }
    }

    if (j != imax) { /* swap the pivot row with the jth row */
      for (k = 0; k < n; k++)
        x = a[imax*n+k], a[imax*n+k] = a[j*n+k], a[j*n+k] = x;
      x = b[imax]; b[imax] = b[j]; b[j] = x;
    }
    if (fabs(a[j*n+j]) < mintol)
      return 2;
    /* divide by the pivot element, for the L matrix */
    if (j != n-1)
      for (x = 1.0/a[j*n+j], i = j+1; i < n; i++)
        a[i*n+j] *= x;
  }

  /* step2: solve the equation L U x = b */
  for (i = 0; i < n; i++) { /* L y = b */
    x = b[i];
    for (j = 0; j < i; j++) x -= a[i*n+j]*b[j];
    b[i] = x;
  }
  for (i = n-1; i >= 0; i--) { /* U x = y. */
    x = b[i];
    for (j = i+1; j < n; j++) x -= a[i*n+j]*b[j];
    b[i] = x/a[i*n+i];
  }
  return 0;
}

#endif /* ZCOM_LU__ */
#endif /* ZCOM_LU */

#ifdef  ZCOM_SVD
#ifndef ZCOM_SVD__
#define ZCOM_SVD__


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

STRCLS int svd(real *a, real *s, real *v, int m, int n);
STRCLS int svdback(real *u, real *w, real *v, int m, int n, real *x, real *b);
STRCLS int svdsolve(real *a, real *x, real *b, int n, real tol);


/* singular value decomposition of mxn matrix `a'
 * a[m*n] (or u[m*n] on return), w[n], v[n*n] */
int svd(real *a, real *w, real *v, int m, int n)
{
  int flag, i, it, j, jj, k, l, nm;
  real c, f, h, s, x, y, z;
  real anorm = 0.0, g, scl;
  real *rv1;

  die_if (m < n, "ERROR: m %d < n %d\n", m, n);
  xnew(rv1, n);

  /* Householder reduction to bidiagonal form */
  for (g = s = scl = 0., i = 0; i < n; i++) {
    /* left-hand reduction */
    l = i + 1;
    rv1[i] = scl * g;
    g = s = scl = 0.0;
    if (i < m) {
      for (k = i; k < m; k++)
        scl += fabs(a[k*n+i]);
      if (scl > 0.) {
        for (k = i; k < m; k++) {
          a[k*n+i] = x = a[k*n+i]/scl;
          s += x*x;
        }
        f = a[i*n+i];
        g = (f > 0.) ? -sqrt(s) : sqrt(s);
        h = f * g - s;
        a[i*n+i] = f - g;
        if (i != n - 1) {
          for (j = l; j < n; j++) {
            for (s = 0.0, k = i; k < m; k++)
              s += a[k*n+i] * a[k*n+j];
            f = s / h;
            for (k = i; k < m; k++)
              a[k*n+j] += f * a[k*n+i];
          }
        }
        for (k = i; k < m; k++)
          a[k*n+i] = a[k*n+i]*scl;
      }
    }
    w[i] = scl*g;

    /* right-hand reduction */
    g = s = scl = 0.0;
    if (i < m && i != n - 1) {
      for (k = l; k < n; k++)
        scl += fabs(a[i*n+k]);
      if (scl > 0.) {
        for (k = l; k < n; k++) {
          a[i*n+k] = x = a[i*n+k]/scl;
          s += x*x;
        }
        f = a[i*n+l];
        g = (f > 0.) ? -sqrt(s) : sqrt(s);
        h = f * g - s;
        a[i*n+l] = f - g;
        for (k = l; k < n; k++)
          rv1[k] = a[i*n+k] / h;
        if (i != m - 1) {
          for (j = l; j < m; j++) {
            for (s = 0.0, k = l; k < n; k++)
              s += a[j*n+k] * a[i*n+k];
            for (k = l; k < n; k++)
              a[j*n+k] += s * rv1[k];
          }
        }
        for (k = l; k < n; k++)
          a[i*n+k] *= scl;
      }
    }
    x = fabs(w[i]) + fabs(rv1[i]);
    if (x > anorm) anorm = x;
  }

  /* accumulate the right-hand transformation */
  for (i = n - 1; i >= 0; i--) {
    if (i < n - 1) {
        if (g != 0.) {
            for (j = l; j < n; j++)
                v[j*n+i] = ((a[i*n+j] / a[i*n+l]) / g);
                /* real division to avoid underflow */
            for (j = l; j < n; j++) {
                for (s = 0.0, k = l; k < n; k++)
                    s += (a[i*n+k] * v[k*n+j]);
                for (k = l; k < n; k++)
                    v[k*n+j] += (s * v[k*n+i]);
            }
        }
        for (j = l; j < n; j++)
            v[i*n+j] = v[j*n+i] = 0.0;
    }
    v[i*n+i] = 1.0;
    g = rv1[i];
    l = i;
  }

  /* accumulate the left-hand transformation */
  for (i = n - 1; i >= 0; i--) {
    l = i + 1;
    g = w[i];
    if (i < n - 1)
      for (j = l; j < n; j++) a[i*n+j] = 0.0;
    if (g != 0.) {
      g = 1.0 / g;
      if (i != n - 1) {
        for (j = l; j < n; j++) {
          for (s = 0.0, k = l; k < m; k++)
            s += (a[k*n+i] * a[k*n+j]);
          f = s/a[i*n+i]*g;
          for (k = i; k < m; k++)
            a[k*n+j] += f*a[k*n+i];
        }
      }
      for (j = i; j < m; j++)
        a[j*n+i] = a[j*n+i]*g;
    } else {
      for (j = i; j < m; j++) a[j*n+i] = 0.0;
    }
    a[i*n+i] += 1.;
  }

  /* diagonalize the bidiagonal form */
  for (k = n - 1; k >= 0; k--) { /* loop over singular values */
    for (it = 0; it < 200; it++) { /* loop over allowed iterations */
      flag = 1;
      for (l = k; l >= 0; l--) { /* test for splitting */
        nm = l - 1;
        if (fabs(rv1[l]) + anorm == anorm) {
          flag = 0;
          break;
        }
        if (fabs(w[nm]) + anorm == anorm)
          break;
      }
      if (flag) {
        c = 0.0;
        s = 1.0;
        for (i = l; i <= k; i++) {
          f = s * rv1[i];
          if (fabs(f) + anorm == anorm) continue;
          g = w[i];
          h = dblhypot(f, g);
          w[i] = h;
          h = 1.0 / h;
          c = g * h;
          s = (- f * h);
          for (j = 0; j < m; j++) {
            y = a[j*n+nm];
            z = a[j*n+i];
            a[j*n+nm] = y * c + z * s;
            a[j*n+i] = z * c - y * s;
          }
        }
      }
      z = w[k];
      if (l == k) { /* convergence */
        if (z < 0.0) { /* flip sign of w */
          w[k] = -z;
          for (j = 0; j < n; j++)
            v[j*n+k] = -v[j*n+k];
        }
        break;
      }
      if (it >= 200) {
        free(rv1);
        fprintf(stderr, "svd: failed to converge\n");
        return -1;
      }

      /* shift from bottom 2 x 2 minor */
      x = w[l];
      nm = k - 1;
      y = w[nm];
      g = rv1[nm];
      h = rv1[k];
      f = ((y - z) * (y + z) + (g - h) * (g + h)) / (2.0 * h * y);
      g = dblhypot(f, 1.0);
      if (f < 0.) g = -g;
      f = ((x - z) * (x + z) + h * (y/(f + g) - h)) / x;

      /* next QR transformation */
      c = s = 1.0;
      for (j = l; j <= nm; j++) {
        i = j + 1;
        g = rv1[i];
        y = w[i];
        h = s * g;
        g = c * g;
        z = dblhypot(f, h);
        rv1[j] = z;
        c = f / z;
        s = h / z;
        f = x * c + g * s;
        g = g * c - x * s;
        h = y * s;
        y = y * c;
        for (jj = 0; jj < n; jj++) {
          x = v[jj*n+j];
          z = v[jj*n+i];
          v[jj*n+j] = x * c + z * s;
          v[jj*n+i] = z * c - x * s;
        }
        w[j] = z = dblhypot(f, h);
        if (z > 0.) { c = f/z; s = h/z; }
        f = c * g + s * y;
        x = c * y - s * g;
        for (jj = 0; jj < m; jj++) {
          y = a[jj*n+j];
          z = a[jj*n+i];
          a[jj*n+j] = y * c + z * s;
          a[jj*n+i] = z * c - y * s;
        }
      }
      rv1[l] = 0.0;
      rv1[k] = f;
      w[k] = x;
    }
  }
  free(rv1);
  return 0;
}

int svdback(real *u, real *w, real *v, int m, int n, real *x, real *b)
{
  int i, j;
  real *b1, y;

  xnew(b1, n);
  for (i = 0; i < n; i++) {
    if (w[i] <= 0.) { b1[i] = 0.; continue; }
    for (y = 0, j = 0; j < m; j++)
      y += u[j*n+i]*b[j];
    b1[i] = y/w[i];
  }
  for (i = 0; i < n; i++) {
    for (y = 0., j = 0; j < n; j++)
      y += v[i*n+j]*b1[j];
    x[i] = y;
  }
  free(b1);
  return 0;
}

int svdsolve(real *a, real *x, real *b, int n, real rerr)
{
  int i;
  real *u, *v, *w, wmax, wmin;

  xnew(w, n); xnew(u, n*n); xnew(v, n*n);
  for (i = 0; i < n*n; i++) u[i] = a[i];
  svd(u, w, v, n, n);
  for (wmax = 0., i = 0; i < n; i++)
    if (w[i] > wmax) wmax = w[i];
  for (wmin = wmax*rerr, i = 0; i < n; i++)
    if (w[i] < wmin) w[i] = wmin;
  for (i = 0; i < n; i++) printf("%g  ", w[i]);
  printf("\n");
  svdback(u, w, v, n, n, x, b);
  free(u); free(v); free(w);
  return 0;
}

#endif /* ZCOM_SVD__ */
#endif /* ZCOM_SVD */

#ifdef  ZCOM_ROTFIT
#ifndef ZCOM_ROTFIT__
#define ZCOM_ROTFIT__

STRCLS real rotfit3(rv3_t *x, rv3_t *xf, rv3_t *y, const real *w, int n,
    real (*r)[3], real *t);


/* least square fit from x to y after rotation/translation of the former
 * the best fit structure is saved to xf, if not NULL */
real rotfit3(rv3_t *x, rv3_t *xf, rv3_t *y, const real *w, int n,
    real (*r)[3], real *t)
{
  int i;
  real wtot = 0, sq, dev = 0, dev0, detm;
  rv3_t xc, yc, xs, ys, sig, t_;
  real u[3][3], v[3][3], s[3][3] = {{0,0,0},{0,0,0},{0,0,0}}, xy[3][3], r_[3][3];

  if (r == NULL) r = r_;
  if (t == NULL) t = t_;

  /* 1. compute the centers */
  rv3_zero(xc);
  rv3_zero(yc);
  if (w == NULL) {
    for (i = 0; i < n; i++) {
      rv3_inc(xc, x[i]);
      rv3_inc(yc, y[i]);
    }
    wtot = (real) n;
  } else {
    for (wtot = 0., i = 0; i < n; i++) {
      rv3_sinc(xc, x[i], w[i]);
      rv3_sinc(yc, y[i], w[i]);
      wtot += w[i];
    }
  }
  rv3_smul(xc, 1.f/wtot);
  rv3_smul(yc, 1.f/wtot);

  /* 2. compute 3x3 asymmetric covarience matrix S = (x-xc) (y-yc)^T */
  for (i = 0; i < n; i++) {
    rv3_diff(xs, x[i], xc); /* shift to the center avoid the translation */
    rv3_diff(ys, y[i], yc);
    rm3_vtv(xy, xs, ys);
    sq  = rv3_sqr(xs);
    sq += rv3_sqr(ys);
    if (w) {
      rm3_sinc(s, xy, w[i]);
      dev += w[i]*sq;
    } else {
      rm3_inc(s, xy);
      dev += sq; /* Tr(x^T x + y^T y) */
    }
  }
  dev0 = dev;

  /* 3. SVD decompose S = u sig v^T */
  rm3_svd(s, u, sig, v);

  /* 4. compute R = v u^T */
  rm3_mult(r, v, u);
  detm = rm3_det(r);

#define rotfit3_dump_(title) { const char *rfmt = "%22.14e"; \
    printf("rotfit " title " fatal error: detm = %g, n = %d\n", detm, n); \
    rm3_print(r, "r", rfmt, 1); \
    printf("det(r) = %g\n", rm3_det(r)); \
    rm3_mult(r, u, v); rm3_print(r, "rx", rfmt, 1); \
    printf("det(rx) = %g\n", rm3_det(r)); \
    rm3_print(u, "u", rfmt, 1); \
    printf("det(u) = %g\n", rm3_det(u)); \
    rm3_print(v, "v", rfmt, 1); \
    printf("det(v) = %g\n", rm3_det(v)); \
    rm3_print(s, "s", rfmt, 1); \
    printf("det(s) = %g\n", rm3_det(s)); \
    rv3_print(sig, "sig", rfmt, 1); \
    exit(1); }
  if (fabs(fabs(detm) - 1) > 0.01) rotfit3_dump_("bad svd");
  if (detm < 0) { /* to avoid a reflection */
    rm3_trans(u);
    rv3_neg(u[2]); /* flip the last eigenvector */
    rm3_mul(r, v, u);
    dev -= 2*(sig[0]+sig[1]-sig[2]);
    detm = rm3_det(r);
    if (fabs(fabs(detm) - 1) > 0.01) rotfit3_dump_("bad inv.");
#undef rotfit3_dump_
  } else {
    dev -= 2*(sig[0]+sig[1]+sig[2]); /* -2 Tr(R x y^T) */
  }
  if (dev < 0) dev = 0;
  rv3_diff(t, yc, rm3_mulvec(xs, r, xc)); /* t = yc - R xc */

  /* 5. compute the rotated structure */
  if (xf || dev < dev0*0.01) { /* if there's a large cancellation recompute the deviation */
    real xfit[3];
    for (dev = 0, i = 0; i < n; i++) {
      rv3_add(xfit, rm3_mulvec(xs, r, x[i]), t); /* xf = R x + t */
      sq = rv3_dist2(y[i], xfit);
      if (xf) rv3_copy(xf[i], xfit);
      dev +=  (w ? w[i]*sq : sq); /* recompute the deviation */
    }
  }
  return (real) sqrt(dev/wtot);
}

#endif /* ZCOM_ROTFIT__ */
#endif /* ZCOM_ROTFIT */

#ifdef  ZCOM_SAVGOL
#ifndef ZCOM_SAVGOL__
#define ZCOM_SAVGOL__


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

INLINE double *savgol(int w, int ord, int der, int h, int verbose);
INLINE double *savgol2d(int iw, int jw, int ord, int h, int verbose);


/* compute 1d Savitzky-Golay coefficients
 * der == 0 for function itself, 1 for first-order derivative */
INLINE double *savgol(int w, int ord, int der, int h, int verbose)
{
  int i, i0, i1, ox, oy, nop, orm, npt;
  double x, xk, y;
  double *mmt, *b, *mat, *x2m, *c;

  nop = ord+1;
  orm = 2*ord+1;
  npt = h ? (2*w) : (2*w+1);
  i0 = -w;
  i1 = h ? w : (w+1);
  if ((c = calloc(npt, sizeof(double))) == NULL)
    return NULL;
  if ((b = calloc(nop, sizeof(double))) == NULL) {
    free(c);
    return NULL;
  }
  if ((mat = calloc(nop*nop, sizeof(double))) == NULL) {
    free(b); free(c);
    return NULL;
  }
  if ((mmt = calloc(orm, sizeof(double))) == NULL) {
    free(mat); free(b); free(c);
    return NULL;
  }
  if ((x2m = calloc(nop*npt, sizeof(double))) == NULL) {
    free(mmt); free(mat); free(b); free(c);
    return NULL;
  }
  if (der > ord) {
    fprintf(stderr, "no %dth order of derivative, order = %d\n", der, ord);
    return NULL;
  }

  for (i = 0; i < orm; i++) mmt[i] = 0.;
  for (i = i0; i < i1; i++) {
    x = h ? (i + .5) : i;
    /* mmt[k] = < x^k > */
    for (xk = 1., ox = 0; ox < orm; ox++, xk *= x)
      mmt[ox] += xk;
    /* x2m[k*npt + x] = x^k */
    for (xk = 1., ox = 0; ox <= ord; ox++, xk *= x)
      x2m[ox*npt + (i - i0)] = xk;
  }

  /* install matrix from moments */
  for (ox = 0; ox < nop; ox++)
    for (oy = 0; oy < nop; oy++)
      mat[ox*nop + oy] = mmt[ox+oy];

  /* we approximate y(x) = a0 + a1 x + a2 x^2 + ...
   * mat.a = b = x2m.y, or a = mat^(-1).b
   * since mat is symmetrical, rows == columns,
   * we thus extract the first row by solving b = {1, 0, 0, ...} */
  for (i = 0; i < nop; i++) b[i] = 0;
  b[der] = 1.;
  i = lusolve(mat, b, nop);
  if (i != 0) {
    fprintf(stderr, "unable to inverse matrix!\n");
    return NULL;
  }
  /* c = mat^(-1).x2m */
  for (i = 0; i < npt; i++) {
    for (y = 0, ox = 0; ox < nop; ox++)
      y += b[ox]*x2m[ox*npt + i];
    c[i] = y;
  }
  free(x2m);
  free(mmt);
  free(mat);
  free(b);
  if (verbose) {
    for (i = 0; i < npt; i++)
      printf("%g\t", c[i]);
    printf("\n");
  }
  return c;
}

/* compute 2d Savitzky-Golay coefficients
 * h means if it is a histogram */
INLINE double *savgol2d(int iw, int jw, int ord, int h, int verbose)
{
  int i, j, i0, i1, j0, j1, id, nop, orm, npt;
  int io, iq, ox, oy, o1, o2, o3, o4;
  double w, x, y, xk, xyk;
  double *mmt, *b, *mat, *x2m, *c;

  nop = (ord+1)*(ord+2)/2;
  orm = 2*ord+1;
  i0 = -iw;
  j0 = -jw;
  if (h) { /* for histogram */
    npt = (2*iw)*(2*jw);
    i1 = iw;
    j1 = jw;
  } else {
    npt = (2*iw+1)*(2*jw+1);
    i1 = iw + 1;
    j1 = jw + 1;
  }
  if ((c = calloc(npt, sizeof(double))) == NULL)
    return NULL;
  if ((b = calloc(nop, sizeof(double))) == NULL) {
    free(c);
    return NULL;
  }
  if ((mat = calloc(nop*nop, sizeof(double))) == NULL) {
    free(b); free(c);
    return NULL;
  }
  if ((mmt = calloc(orm*orm, sizeof(double))) == NULL) {
    free(mat); free(b); free(c);
    return NULL;
  }
  if ((x2m = calloc(nop*npt, sizeof(double))) == NULL) {
    free(mmt); free(mat); free(b); free(c);
    return NULL;
  }

  for (i = 0; i < orm*orm; i++) mmt[i] = 0.;
  for (i = i0; i < i1; i++) {
    x = h ? (i + .5) : i;
    for (j = j0; j < j1; j++) {
      y = h ? (j + .5) : j;
      w = 1.;
      /* moment matrix */
      xk = w;
      for (ox = 0; ox < orm; ox++) {
        xyk = xk;
        for (oy = 0; oy < orm-ox; oy++) {
          mmt[ox*orm + oy] += xyk;
          xyk *= y;
        }
        xk *= x;
      }
      /* position to z-moment matrix */
      id = (i - i0)*(j1 - j0) + (j - j0);
      for (io = 0, o1 = 0; o1 <= ord; o1++) {
        for (o2 = 0; o2 <= o1; o2++, io++) {
          xyk = w;
          for (ox = 0; ox < o1 - o2; ox++) xyk *= x;
          for (oy = 0; oy < o2; oy++) xyk *= y;
          x2m[io*npt + id] = xyk;
        }
      }
    }
  }

  /* install matrix from moments */
  for (io = 0, o1 = 0; o1 <= ord; o1++)
  for (o2 = 0; o2 <= o1; o2++, io++) {
    /* x^(o1-o2) y^o2 */
    for (iq = 0, o3 = 0; o3 <= ord; o3++)
    for (o4 = 0; o4 <= o3; o4++, iq++) {
      /* x^(o3-o4) y^o4 */
      ox = o3 - o4 + o1 - o2;
      oy = o4 + o2;
      mat[io*nop + iq] = mmt[ox*orm + oy];
    }
  }

  for (i = 0; i < nop; i++) b[i] = 0.;
  b[0] = 1.;
  i = lusolve(mat, b, nop);
  if (i != 0) {
    fprintf(stderr, "unable to inverse matrix!\n");
    return NULL;
  }
  for (i = 0; i < npt; i++) {
    for (y = 0, io = 0; io < nop; io++)
      y += b[io]*x2m[io*npt + i];
    c[i] = y;
  }
  free(x2m);
  free(mmt);
  free(mat);
  free(b);
  if (verbose) {
    for (i = i0; i < i1; i++) {
      for (j = j0; j < j1; j++) {
        printf("%7.4f ", c[(i-i0)*(j1 - j0)+(j-j0)]);
      }
      printf("\n");
    }
  }
  return c;
}

#endif /* ZCOM_SAVGOL__ */
#endif /* ZCOM_SAVGOL */

#ifdef  ZCOM_SPECFUNC
#ifndef ZCOM_SPECFUNC__
#define ZCOM_SPECFUNC__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

INLINE double lngam(double a);
INLINE double lnincgam(double a, double x);
INLINE double lnincgamup(double a, double x);

INLINE double ksq(double x);
INLINE double plegendre(double x, int l, int m);


/* returns log(Gamma(a)),
 * where Gamma(a) = \int_0^\infty e^(-t) t^(a-1) dt */
INLINE double lngam(double a)
{
  int i;
  double xp, ahg;
  static const double gh = 671./128, sqrt2pi = 2.506628274631000242,
    c[15] = {0.999999999999997092, 57.1562356658629235,-59.5979603554754912,
    14.1360979747417471,-0.491913816097620199,.339946499848118887e-4,
    .465236289270485756e-4,-.983744753048795646e-4,.158088703224912494e-3,
    -.210264441724104883e-3,.217439618115212643e-3,-.164318106536763890e-3,
    .844182239838527433e-4,-.261908384015814087e-4,.368991826595316234e-5};

  die_if (a <= 0., "neg. arg. for lngam(%g)\n", a);
  for (xp = c[0], i = 1; i < 15; i++)
    xp += c[i]/(a + i);
  ahg = a + gh;
  return (a+.5)*log(ahg) - ahg + log(sqrt2pi*xp/a); /* gamma(a) = gamma(a+1)/a */
}

/* returns incomplete gamma function log(gamma(a, x)),
 * where gamma(a, x) = \int_0^x e^(-t) t^(a-1) dt
 * = e^(-x) x^a \sum_{i = 0} Gamma(a)/Gamma(a + 1 + i) x^i
 * for small x, cf. gser() in Numerical-Recipes */
INLINE double lnincgam0(double a, double x)
{
  int i;
  double del, sum;

  die_if (x < 0., "neg. arg. for lnincgam0(%g)\n", x);
  if (x <= 0) return -1e30; /* log(0+) */
  sum = del = 1.0/a;
  for (i = 1; i <= 1000; i++) {
    del *= x/(a + i);
    sum += del;
    if (fabs(del) < fabs(sum)*5e-16) break;
  }
  return -x + a * log(x) + log(sum);
}

/* returns incomplete gamma function log(Gamma(a, x)),
 * where Gamma(a, x) = \int_x^\infty e^(-t) t^(a-1) dt
 * = e^(-x) x^a [1/(x+1-a-) [1*(1-a)/(x+3-a-) [2*(2-a)/(x+5-a) ...]
 * for large x, cf. gcf() in Numerical-Recipes */
INLINE double lnincgam1(double a, double x)
{
  int i;
  double an, b, c, d, h, del;
  const double fpmin = 1e-300;

  b = x + 1 - a;
  d = 1/b;
  c = 1/fpmin;
  h = d;
  /* modified Lentz's method for the continued fraction */
  for (i = 1; i <= 1000; i++) {
    an = -1.*i*(i - a); /* numerator */
    b += 2;
    d = d*an + b;
    if (fabs(d) < fpmin) d = fpmin;
    c = b + an/c;
    if (fabs(c) < fpmin) c = fpmin;
    d = 1.0/d;
    del = d*c;
    h *= del;
    if (fabs(del - 1) < 5e-16) break;
  }
  return -x + a * log(x) + log(h);
}

/* returns incomplete gamma function log(gamma(a, x)),
 * where gamma(a, x) = \int_0^x e^(-t) t^(a-1) dt */
INLINE double lnincgam(double a, double x)
{
  return (x < a + 1) ? lnincgam0(a, x) : lndif(lngam(a), lnincgam1(a, x));
}

/* returns incomplete gamma function log(Gamma(a, x)),
 * where Gamma(a, x) = \int_x^\infty e^(-t) t^(a-1) dt */
INLINE double lnincgamup(double a, double x)
{
  return (x < a + 1) ? lndif(lngam(a), lnincgam0(a, x)) : lnincgam1(a, x);
}

/* return the p-value, or 1 - cdf(x), for KS distribution */
INLINE double ksq(double x)
{
  double y;
  die_if (x < 0, "neg. arg. for ksq(x = %g)\n", x);
  if (x < 1e-15) {
    return 1.;
  } else if (x < 1.18) {
    x = 1.110720734539591525/x;
    y = exp(-x*x);
    return 1. - 2.25675833419102515*x*(y+pow(y,9)+pow(y,25)+pow(y,49));
  } else {
    y = exp(-x*x*2.);
    return 2.*(y - pow(y, 4) + pow(y, 9));
  }
}

/* normalized associated legendre polynomial
 * nplm(x) = sqrt( (2l+1)/(4 pi) (l-m)!/(l+m)!) P_l^m(x)
 * real solution of m <= l, l, m >= 0
 * (1 - x^2) y'' - 2 x y' + [l(l+1) - m^2/(1-x^2)] y = 0 */
INLINE double plegendre(double x, int l, int m)
{
  int i;
  double y, yp, ypp, f, fp, s = 1 - x*x;

  if (m < 0 || m > l || s < 0) return 0;
  for (yp = 1, i = 1; i <= m; i++) yp *= (1 + .5/i)*s;
  yp = sqrt(yp/(4*M_PI)) * (m % 2 ? -1: 1); /* P(m, m) */
  /* (l-m) P_l^m = x (2l-1) P_{l-1}^m - (l+m-1)*P_{l-2}^m */
  for (fp = 1, ypp = 0, i = m + 1; i <= l; i++, fp = f, ypp = yp, yp = y) {
    f = sqrt((4.*i*i-1)/((i-m)*(i+m)));
    y = f*(x*yp - ypp/fp);
  }
  return yp;
}

#endif /* ZCOM_SPECFUNC__ */
#endif /* ZCOM_SPECFUNC */

#ifdef  ZCOM_OPT
#ifndef ZCOM_OPT__
#define ZCOM_OPT__
#include <stdio.h>

/* option either from arguments or configuration */
typedef struct {
  int isopt; /* is option or argument */
  char ch; /* single letter option flag */
  const char *sflag; /* long string flag */
  const char *key; /* key */

  const char *val; /* raw string from command line */
  const char *desc; /* description */
  const char *fmt; /* sscanf format */
  const char *pfmt; /* printf format, NULL: to guess */
  void *ptr; /* address to the target variable */
  unsigned flags;
} opt_t;

#define OPT_MUST     0x0001  /* a mandatory argument or option */
#define OPT_SWITCH   0x0002  /* an option is a switch */
#define OPT_SET      0x0004  /* an argument/option is set */

/* translate string values to actual ones through sscanf() */
INLINE int opt_getval(opt_t *o)
{
  const char *fmt = o->fmt;

  if (fmt == NULL || fmt[0] == '\0') { /* raw string assignment */
    *(const char **)o->ptr = o->val;
  } else if (strcmp(fmt, "%s") == 0) {
    sscpy( *(char **)o->ptr, o->val);
  } else { /* call sscanf */
    if (strcmp(fmt, "%r") == 0) /* real */
      fmt = (sizeof(real) == sizeof(float)) ? "%f" : "%lf";
    if (1 != sscanf(o->val, fmt, o->ptr)) {
      fprintf(stderr, "Error: unable to convert a value for [%s] as fmt [%s], raw string: [%s]\n",
          o->desc, fmt, o->val);
      return 1;
    }
  }
  return 0;
}

/* set properties of an option: fmt = "%b" for a switch */
INLINE void opt_set(opt_t *o, const char *sflag, const char *key,
    const char *fmt, void *ptr, const char *desc)
{
  o->ch = '\0';
  if (key) {
    o->isopt = 2;
  } else if (sflag) { /* option */
    o->isopt = 1;
    o->ch = (char) ( sflag[2] ? '\0' : sflag[1] ); /* no ch for a long flag */
  } else { /* argument */
    o->isopt = 0;
  }
  o->sflag = sflag;
  o->key = key;
  o->flags = 0;
  die_if (ptr == NULL, "null pass to opt with %s: %s\n", sflag, desc);
  o->ptr = ptr;
  if (fmt == NULL) fmt = "";
  if (fmt[0] == '!') {
    fmt++;
    o->flags |= OPT_MUST;
  }
  if (strcmp(fmt, "%b") == 0) {
    fmt = "%d";
    o->flags |= OPT_SWITCH;
  }
  o->fmt = fmt;
  o->pfmt = NULL;
  o->desc = desc;
}

/* print the value of o->ptr */
#define opt_printptr(o) opt_fprintptr(stderr, o)
INLINE void opt_fprintptr(FILE *fp, opt_t *o)
{
  const char *fmt;

  for (fmt = o->fmt; *fmt && *fmt != '%'; fmt++) ;
#define ELIF_PF_(fm, fmp, type) \
  else if (strcmp(fmt, fm) == 0) \
    fprintf(fp, (o->pfmt ? o->pfmt : fmp), *(type *)o->ptr)

  if (fmt == NULL || *fmt == '\0' || strcmp(fmt, "%s") == 0)
    fprintf(fp, "%s", (*(char **)o->ptr) ? (*(char **)o->ptr) : "NULL");
  ELIF_PF_("%b", "%d", int); /* switch */
  ELIF_PF_("%d", "%d", int);
  ELIF_PF_("%u", "%u", unsigned);
  ELIF_PF_("%x", "0x%x", unsigned);
  ELIF_PF_("%ld", "%ld", long);
  ELIF_PF_("%lu", "%lu", unsigned long);
  ELIF_PF_("%lx", "0x%lx", unsigned long);
#if 0  /* C99 only */
  ELIF_PF_("%lld", "%lld", long long);
  ELIF_PF_("%llu", "%llu", unsigned long long);
  ELIF_PF_("%llx", "0x%llx", unsigned long long);
#endif
  ELIF_PF_("%f", "%g", float);
  ELIF_PF_("%lf", "%g", double);
  ELIF_PF_("%r", "%g", real);
  else fprintf(fp, "unknown %s-->%%d: %d", fmt, *(int *)o->ptr);
#undef ELIF_PF_
}

/* search an option list, return an option whose variable address is p */
INLINE opt_t *opt_find(opt_t *ls, int n, const void *p)
{
   int i;
   for (i = 0; i < n; i++) if (ls[i].ptr == p) return ls + i;
   return NULL;
}

/* search an option list to see if an option is explicitly set */
INLINE int opt_isset(opt_t *ls, int n, const void *p, const char *var)
{
  opt_t *o = opt_find(ls, n, p);
  die_if (!o, "cannot find var %s, ptr %p\n", var, p);
  return o->flags & OPT_SET ? 1 : 0;
}
#endif /* ZCOM_OPT__ */
#endif /* ZCOM_OPT */

#ifdef  ZCOM_ARGOPT
#ifndef ZCOM_ARGOPT__
#define ZCOM_ARGOPT__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  int nopt;
  opt_t *opts;
  const char *prog;
  const char *desc;
  const char *author;
  const struct tm *tm; /* compilation time */
  int version;
  unsigned flags;
  int dum_[4]; /* space holder */
} argopt_t;

#define ARGOPT_MUST     OPT_MUST    /* mandatory argument or option, format starts with ! */
#define ARGOPT_SWITCH   OPT_SWITCH  /* format "%b" */
#define ARGOPT_SET      OPT_SET
#define ARGOPT_LONGOPT  0x0010  /* always assume long format, e.g., -maxh */

STRCLS argopt_t *argopt_open(unsigned flags);
STRCLS void argopt_close(argopt_t *ao);
#define argopt_regarg(ao, fmt, ptr, desc) argopt_add(ao, NULL, fmt, ptr, desc)
#define argopt_regopt argopt_add
#define argopt_reghelp argopt_addhelp
#define argopt_regversion argopt_addversion
STRCLS int argopt_add(argopt_t *ao, const char *sflag,
    const char *fmt, void *ptr, const char *desc);
STRCLS void argopt_parse(argopt_t *ao, int argc, char **argv);
INLINE void argopt_dump(const argopt_t *ao);

#define argopt_addhelp(ao, sflag) argopt_add(ao, sflag, "%b", ao->dum_, "$HELP")
#define argopt_addversion(ao, sflag) argopt_add(ao, sflag, "%b", ao->dum_, "$VERSION")

#define argopt_getopt(ao, p) opt_find(ao->opts, ao->nopt, p)
#define argopt_getarg argopt_getopt

/* test if argument/option is explicitly set */
#define argopt_set(ao, var) opt_isset(ao->opts, ao->nopt, &var, #var)


/* initialize the argument structure */
argopt_t *argopt_open(unsigned flags)
{
  argopt_t *ao;
  time_t tmcmpl;

  xnew(ao, 1);
  ao->flags = flags;
  ao->nopt = 0;
  ao->opts = NULL;
  tmcmpl = time(NULL);
  ao->tm = localtime( &tmcmpl );
  memset(ao->dum_, '\0', sizeof(ao->dum_));
  return ao;
}

void argopt_close(argopt_t *ao)
{
  if (ao->opts) { free(ao->opts); ao->opts = NULL; }
  free(ao);
}

/* print version and die */
static void argopt_version(argopt_t *ao)
{
  fprintf(stderr, "%s: %s, version %d\n",
      ao->prog, ao->desc ? ao->desc : "", ao->version);
  if (ao->author && ao->tm)
    fprintf(stderr, "Copyright (c) %s %d\n", ao->author, ao->tm->tm_year + 1900);
  argopt_close(ao);
  exit(1);
}

/* print help message and die */
static void argopt_help(argopt_t *ao)
{
  int i, len, maxlen;
  opt_t *o;
  const char *sysopt[2] = {"print help message", "print version"}, *desc;

  fprintf(stderr, "%s, version %d",
      ao->desc ? ao->desc : ao->prog, ao->version);
  if (ao->author && ao->tm)
    fprintf(stderr, ", Copyright (c) %s %d", ao->author, ao->tm->tm_year + 1900);
  fprintf(stderr, "\nUSAGE\n  %s {OPTIONS}", ao->prog);
  for (i = 0; i < ao->nopt; i++) {
    const char *bra = "", *ket = "";
    o = ao->opts + i;
    if (o->isopt) continue;
    if (o->flags & OPT_MUST) {
      if (strchr(o->desc, ' '))
        bra = "[", ket = "]";
    } else
      bra = "{", ket = "}";
    fprintf(stderr, " %s%s%s", bra, o->desc, ket);
  }
  fprintf(stderr, "\n");

  fprintf(stderr, "OPTIONS:\n") ;
  for (maxlen = 0, i = 0; i < ao->nopt; i++) { /* compute the longest option */
    if (!ao->opts[i].isopt) continue;
    len = strlen(ao->opts[i].sflag);
    if (len > maxlen) maxlen = len;
  }
  for (i = 0; i < ao->nopt; i++) {
    o = ao->opts + i;
    if (!o->isopt) continue;
    desc = o->desc;
    if (strcmp(desc, "$HELP") == 0)
      desc = sysopt[0];
    else if (strcmp(desc, "$VERSION") == 0)
      desc = sysopt[1];
    fprintf(stderr, "  %-*s : %s%s%s", maxlen, o->sflag,
        ((o->flags & OPT_MUST) ? "[MUST] " : ""),
        (!(o->flags & OPT_SWITCH) ? "followed by " : ""), desc);
    if (o->ptr && o->ptr != ao->dum_) { /* print default values */
      fprintf(stderr, ", default: ");
      opt_fprintptr(stderr, o);
    }
    fprintf(stderr, "\n");
  }
  argopt_close(ao);
  exit(1);
}

/* register an argument or option
 * sflag: string flag, or NULL for an argument
 * fmt: sscanf() format string, "%b" for a switch, "%r" for real
 * return the index */
int argopt_add(argopt_t *ao, const char *sflag,
    const char *fmt, void *ptr, const char *desc)
{
  opt_t *o;
  int n;

  n = ao->nopt++;
  xrenew(ao->opts, ao->nopt);
  o = ao->opts + n;
  opt_set(o, sflag, NULL, fmt, ptr, desc);
  return n;
}

/* main parser of arguments */
void argopt_parse(argopt_t *ao, int argc, char **argv)
{
  int i, j, k, ch, acnt = 0;
  opt_t *ol = ao->opts;

  ao->prog = argv[0];
  for (i = 1; i < argc; i++) {
    if (argv[i][0] != '-') { /* it's an argument */
      while (ol[acnt].isopt && acnt < ao->nopt) acnt++;
      if (acnt >= ao->nopt) argopt_help(ao);
      ol[acnt].val = argv[i];
      ol[acnt].flags |= OPT_SET;
      if (0 != opt_getval(ol + acnt))
        argopt_help(ao);
      ++acnt;
      continue;
    }

    /* it's an option, loop for abbreviated form "-abc" == "-a -b -c" */
    for (j = 1; (ch = argv[i][j]) != '\0'; j++) {
      int islong = (j == 1 && argv[i][1] == '-') | (ao->flags & ARGOPT_LONGOPT);

      if (islong) { /* compare against long options */
        for (k = 0; k < ao->nopt; k++)
          if (ol[k].isopt &&
              strncmp(argv[i], ol[k].sflag, strlen(ol[k].sflag)) == 0)
            break;
      } else { /* compare against short options */
        for (k = 0; k < ao->nopt; k++)
          if (ol[k].isopt && ch == ol[k].ch)
            break;
      }
      if (k >= ao->nopt) {
        fprintf(stderr, "cannot handle option [%s]\n", argv[i]);
        argopt_help(ao);
      }

      if (ol[k].desc[0] == '$') { /* system commands */
        if (strcmp(ol[k].desc, "$HELP") == 0)
          argopt_help(ao);
        else if (strcmp(ol[k].desc, "$VERSION") == 0)
          argopt_version(ao);
      }

      if (ol[k].flags & OPT_SWITCH) {
        ol[k].flags |= OPT_SET;
        *(int *)ol[k].ptr = 1;
        if (islong) break; /* go to the next argument argv[i+1] */
      } else { /* look for the additional argument for this */
        int hasv = 0;
        if (islong) { /* e.g., --version=11 */
          j = strlen(ol[k].sflag);
          if (argv[i][ j ] == '=') {
            ol[k].val = argv[i] + j + 1;
            hasv = 1;
          }
        } else { /* e.g., -n8 */
          if (argv[i][++j]) {
            ol[k].val = argv[i] + j;
            hasv = 1;
          }
        }

        if (!hasv) { /* --version 11 or -n 8 */
          if (++i >= argc) {
            fprintf(stderr, "%s(%s) requires an argument!\n", ol[k].sflag, argv[i-1]);
            argopt_help(ao);
          }
          ol[k].val = argv[i];
        }
        ol[k].flags |= OPT_SET;
        if (0 != opt_getval(ol+k)) argopt_help(ao);
        break; /* go to the next argument argv[i+1] */
      }
    } /* end of short option loop */
  }
  /* check if we have all mandatory arguments and options */
  for (i = 0; i < ao->nopt; i++) {
    if ((ol[i].flags & OPT_MUST) && !(ol[i].flags & OPT_SET)) {
      fprintf(stderr, "Error: missing %s %s: %s\n\n",
          ol[i].isopt ? "option" : "argument", ol[i].sflag, ol[i].desc);
      argopt_help(ao);
    }
  }
}

/* dump the current values */
INLINE void argopt_dump(const argopt_t *ao)
{
  int i, len = 2;
  opt_t *ol = ao->opts;

  /* get the width of the widest option */
  for (i = 0; i < ao->nopt; i++)
    if (ol[i].sflag)
      len = intmax(len, strlen(ol[i].sflag));

  /* print values of all options */
  for (i = 0; i < ao->nopt; i++) {
    const char *sflag = ol[i].sflag;
    if (sflag == NULL) sflag = "arg";
    fprintf(stderr, "%*s: ", len+1, sflag);
    opt_fprintptr(stderr, ol + i);
    fprintf(stderr, ",  %s\n", ol[i].desc);
  }
}


#endif /* ZCOM_ARGOPT__ */
#endif /* ZCOM_ARGOPT */

#ifdef  ZCOM_CFG
#ifndef ZCOM_CFG__
#define ZCOM_CFG__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
  char *key, *val;
  int used;
} cfgent_t; /* line from cfg file */

typedef struct {
  char *buf;      /* the entire configuration file */
  int nent;       /* number of entries */
  cfgent_t *ents; /* entries */
  int nopt;       /* number of user-requested options */
  opt_t *opts;    /* user-requested options */
} cfg_t;
typedef cfg_t cfgdata_t;

#define CFG_CHECKUSE 0x0100
#define CFG_VERBOSE  0x1000


STRCLS cfg_t *cfg_open(const char *fn);
STRCLS void cfg_close(cfg_t *cfg);
STRCLS int cfg_add(cfg_t *cfg, const char *key, const char *fmt, void *ptr, const char *desc);

#define CFG_UNUSED   0x0001
#define CFG_NOTSET   0x0002
#define cfg_parse(cfg, flags) cfg_match(cfg, flags)
STRCLS int cfg_match(cfg_t *cfg, unsigned flags);

#define cfg_set(cfg, var) opt_isset(cfg->opts, cfg->nopt, &var, #var)

/* old style functions */
#define cfgopen(fn) cfg_open(fn)
#define cfgclose(cfg) cfg_close(cfg)
/* Read the value of a given variable from the current configuration file,
 * the name of variable is given by `key',
 * If the key is matched, its value is saved to `*var' through sscanf,
 *   otherwise, the content in *var is not modified.
 * If the function succeeds, it returns 0.
 * In case fmt is "%s", (*var) is a string, or a pointer to char.
 *   The space for (*var) will be managed through sscpy. */
INLINE int cfgget(cfg_t *cfg, void *var, const char *key, const char *fmt)
{
  int i;

  for (i = 0; i < cfg->nent; i++) {
    cfgent_t *ent = cfg->ents + i;
    if (ent->key != NULL && strcmp(ent->key, key) == 0) {
      if (strcmp(fmt, "%s") == 0) { /* string */
        sscpy( *(char **)var, ent->val); /* make a copy and return */
        return 0;
      } else /* use sscanf for other cases, like int, float,... */
        return EOF == sscanf(ent->val, fmt, var) ? 2 : 0;
    }
  }
  return 1; /* no match */
}

/* load the whole configuration file into memory, parse it to entries */
cfg_t *cfg_open(const char *fn)
{
  cfg_t *cfg;
  cfgent_t *ent;
  FILE *fp;
  size_t i, j, n, size = 0;
  char *p, *q;

  xnew(cfg, 1);

  xfopen(fp, fn, "r", return NULL);
  if (ssfgetall(cfg->buf, &size, fp) == NULL) {
    fprintf(stderr, "error reading file %s\n", fn);
    return NULL;
  }
  sscat(cfg->buf, "\n"); /* in case the file is not ended by a new line, we add one */
  fclose(fp);

  /* count the number of lines (before allocating the key-table) */
  for (p = cfg->buf, i = 0, n = 0; i < size; i++) {
    if (p[i] == '\n' || p[i] == '\r') {
      if (i > 0 && p[i-1] == '\\') {
        /* multiple-line splicing by replacing cr, lf with spaces
           parse should be aware of these additional spaces */
        p[i-1] = p[i] = ' ';
      } else {
        p[i] = '\0';
        n++;
      }

      /* replace following CR LF by spaces for efficiency
         as the size of the key table == the number of blank lines */
      for (j = i+1; j < size && cisspace(p[j]); j++) p[j] = ' ';
    }
  }

  xnew(cfg->ents, n);

  /* load lines into the keytable */
  for (p = cfg->buf, j = 0, i = 0; i < size; i++) {
    if (cfg->buf[i] == '\0') {
      cfg->ents[j++].key = p;
      if (j >= n) break;
      p = cfg->buf + i + 1;
    }
  }
  n = j;

  /* parse each line to a key-value pair */
  for (j = 0; j < n; j++) {
    ent = cfg->ents + j;
    p = ent->key;
    strip(p);

    /* skip a blank or comment line */
    if (p[0] == '\0' || strchr("#%!;", p[0]) != NULL) {
      ent->key = NULL;
      continue;
    }

    /* remove trailing space and ';' */
    for (q = p + strlen(p) - 1; q >= p && (cisspace(*q) || *q == ';'); q--)
      *q = '\0';

    if ((q = strchr(p, '=')) == NULL) { /* skip a line without '=' */
      ent->key = NULL;
      continue;
    }
    *q = '\0';
    ent->val = q + 1;
    strip(ent->key);
    strip(ent->val);
  }
  cfg->nent = (int) n;
  cfg->nopt = 0;
  xnew(cfg->opts, 1);
  return cfg;
}

void cfg_close(cfg_t *cfg)
{
  ssdelete(cfg->buf);
  free(cfg->ents);
  free(cfg->opts);
  memset(cfg, 0, sizeof(*cfg));
  free(cfg);
}

/* register an option request, return the index */
int cfg_add(cfg_t *cfg, const char *key, const char *fmt, void *ptr, const char *desc)
{
  int n = cfg->nopt++;
  opt_t *o;
  xrenew(cfg->opts, cfg->nopt);
  o = cfg->opts + n;
  opt_set(o, NULL, key, fmt, ptr, desc);
  return n;
}

/* match requested options with entries in cfg file
 * returns 0 if successful
 * if mandetory variables are not set
 * if `flags' has OPT_CHECKUSE, then unused setting cause an error code CFG_UNUSED */
int cfg_match(cfg_t *cfg, unsigned flags)
{
  int i, j, ret = 0, verbose = flags & CFG_VERBOSE, must;
  opt_t *o;
  cfgent_t *ent;

  for (i = 0; i < cfg->nopt; i++) {
    o = cfg->opts + i;
    for (j = 0; j < cfg->nent; j++) {
      ent = cfg->ents + j;
      if (ent->key != NULL && strcmp(ent->key, o->key) == 0) {
        ent->used = 1;
        o->flags |= OPT_SET;
        o->val = ent->val;
        opt_getval(o);
        break;
      }
    }
    must = (o->flags & OPT_MUST);
    if (!(o->flags & OPT_SET) && (must || verbose)) {
      fprintf(stderr, "cfg: %s not set, default: ", o->key);
      opt_fprintptr(stderr, o);
      fprintf(stderr, "\n");
      if (must) ret |= CFG_NOTSET;
    }
  }

  if (flags & CFG_CHECKUSE) {
    for (j = 0; j < cfg->nent; j++) {
      ent = cfg->ents + j;
      if (ent->key != NULL && !ent->used && verbose) {
        fprintf(stderr, "cfg: unused entry: %s = %s\n", ent->key, ent->val);
        ret |= CFG_UNUSED;
      }
    }
  }
  return ret;
}

/* dump the current values */
INLINE void cfg_dump(const cfg_t *cfg)
{
  int i, len = 2;
  opt_t *ol = cfg->opts;

  /* get the width of the widest entry */
  for (i = 0; i < cfg->nopt; i++)
    len = intmax(len, strlen(ol[i].key));

  /* print values of all options */
  for (i = 0; i < cfg->nopt; i++) {
    fprintf(stderr, "%*s: ", len+1, ol[i].key);
    opt_fprintptr(stderr, ol + i);
    fprintf(stderr, ",  %s\n", ol[i].desc);
  }
}

#endif /* ZCOM_CFG__ */
#endif /* ZCOM_CFG */

#ifdef  ZCOM_LOG
#ifndef ZCOM_LOG__
#define ZCOM_LOG__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct {
  FILE *fp;
  const char *fname;
  unsigned flags;
} logfile_t;

#define LOG_WRITESCREEN  0x01
#define LOG_FLUSHAFTER   0x02
#define LOG_NOWRITEFILE  0x10
#define LOG_APPEND       0x80

INLINE logfile_t *log_open(const char *fn)
{
  logfile_t *log;

  xnew(log, 1);
  if (fn == NULL) fn = "LOG";
  log->fname = fn;
  log->flags = 0;
  return log;
}

INLINE int log_printf(logfile_t *log, char *fmt, ...)
{
  va_list args;

  if (log == NULL) return 1;
  if (log->fp == NULL) {
    const char *aw = (log->flags & LOG_APPEND) ? "a" : "w";
    xfopen(log->fp, log->fname, aw, return 1);
  }
  if ((log->flags & LOG_NOWRITEFILE) == 0) {
    va_start(args, fmt);
    vfprintf(log->fp, fmt, args);
    va_end(args);
  }
  if (log->flags & LOG_WRITESCREEN) {
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
  }
  if (log->flags & LOG_FLUSHAFTER)
    fflush(log->fp);
  return 0;
}

INLINE void log_close(logfile_t *log)
{
  if (log == NULL) return;
  if (log->fp != NULL) { fclose(log->fp); log->fp = NULL; }
  free(log);
}


/* close & reopen log file to make sure that stuff is written to disk */
INLINE int log_hardflush(logfile_t *log)
{
  if (log->fp == NULL || log->fname == NULL) return 1;
  fclose(log->fp);
  xfopen(log->fp, log->fname, "a", return 1);
  return 0;
}

#if defined(HAVEVAM) && defined(NEED_WTRACE)
STRCLS logfile_t log_stock_[1] = {{ NULL, "TRACE", 0 }};
#define wtrace(fmt, ...) { \
  if (fmt) log_printf(log_stock_, fmt, ##__VA_ARGS__); \
  else if (log_stock_->fp) { fclose(log_stock_->fp); log_stock_->fname = NULL; } }
#endif

#endif /* ZCOM_LOG__ */
#endif /* ZCOM_LOG */

#ifdef  ZCOM_AV
#ifndef ZCOM_AV__
#define ZCOM_AV__
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

typedef struct {
  double s, sx, sx2; /* sum, sum x, variance */
} av_t;

INLINE void av_clear(av_t *av) { av->s = av->sx = av->sx2 = 0; }
INLINE double av_getave(const av_t *av) { return (av && av->s > 0) ? av->sx/av->s : 0; }
INLINE double av_getvar(const av_t *av) { return (av && av->s > 0) ? av->sx2/av->s : 0; }
INLINE double av_getdev(const av_t *av) { return (av && av->s > 0) ? sqrt(av_getvar(av)) : 0; }

/* add a new value to av_t with a weight `w' */
INLINE void av_addw(av_t *av, double x, double w)
{
  double s, sx;

  av->s = (s = av->s) + w;
  av->sx = (sx = av->sx) + x*w;
  if (s <= 0.0) return;
  av->sx2 += (x - sx/s)*(x - av->sx/av->s)*w;
}
#define av_add(av, x) av_addw(av, x, 1)

/* update: sX = sX*gam + X */
INLINE void av_gaddw(av_t *av, double x, double w, double ngam)
{
  double s, sx, del, gam = 1.0 - ngam;

  av->s = (s = av->s)*gam + w;
  av->sx = (sx = av->sx)*gam + w*x;
  if (s <= 0.0) return;
  del = x*s - sx;
  av->sx2 = (av->sx2 + w*del*del/(s*av->s))*gam;
}

#define av_gadd(av, x, ngam) av_gaddw(av, x, 1, ngam)


/* average of n quantities */
typedef struct {
  int n;
  double s;
  double *x; /* buffer, current x value */
  double *sx, *sxb; /* sum */
  double *sx2; /* variance */
} avn_t;

/* open average for n quantities */
INLINE avn_t *avn_open(int n)
{
  avn_t *a;
  int i;

  xnew(a, 1);
  die_if (n <= 0, "avn needs at least n %d >= 1\n", n);
  a->n = n;
  xnew(a->x, n);
  xnew(a->sx, n);
  xnew(a->sxb, n);
  xnew(a->sx2, n*n);
  a->s = 0;
  for (i = 0; i < n; i++) a->x[i] = a->sx[i] = a->sxb[i] = 0;
  for (i = 0; i < n * n; i++) a->sx2[i] = 0;
  return a;
}

INLINE void avn_close(avn_t *a)
{
  free(a->x);
  free(a->sx);
  free(a->sxb);
  free(a->sx2);
  free(a);
}

/* add values to avn_t with a weight `w'
 * must add all values simultaneously, otherwise a->s is messed up */
INLINE void avn_addwv(avn_t *a, const double *x, double w)
{
  int k, l, n = a->n;
  double s;

  a->s = (s = a->s) + w;
  for (k = 0; k < n; k++) {
    a->sx[k] = (a->sxb[k] = a->sx[k]) + x[k] * w;
  }
  if (s > 0) { /* update variance */
    for (k = 0; k < n; k++)
      for (l = k; l < n; l++)
        a->sx2[k*n + l] += (x[k] - a->sxb[k]/s) * (x[l] - a->sx[l]/a->s) * w;
  }
}

#define avn_addv(a, x) avn_addwv(a, x, 1)

/* add values to avn_t with a weight `w'
 * use argument list */
INLINE void avn_addw(avn_t *a, double w, ...)
{
  int k;
  va_list va;

  va_start(va, w);
  for (k = 0; k < a->n; k++) {
    a->x[k] = va_arg(va, double);
  }
  va_end(va);
  avn_addwv(a, a->x, w);
}


/* weighted update: sX = sX*gam + X */
INLINE void avn_gaddwv(avn_t *a, const double *x, double w, double ngam)
{
  int k, l, n = a->n;
  double s, gam = 1.0 - ngam;

  a->s = (s = a->s)*gam + w;
  for (k = 0; k < n; k++) {
    a->sx[k] = (a->sxb[k] = a->sx[k]) * gam + w * x[k];
  }
  if (s > 0) { /* update variance */
    for (k = 0; k < n; k++)
      for (l = k; l < n; l++)
        a->sx2[k*n + l] = gam * (a->sx2[k*n + l] +
            w*(x[k]*s - a->sxb[k]) * (x[l]*s - a->sxb[l])/(s*a->s));
  }
}

#define avn_gaddv(a, x, ngam) avn_gaddwv(a, x, 1, ngam)

/* weighted update
 * use argument list */
INLINE void avn_gaddw(avn_t *a, double w, double ngam, ...)
{
  int k;
  va_list va;

  va_start(va, ngam);
  for (k = 0; k < a->n; k++)
    a->x[k] = va_arg(va, double);
  va_end(va);
  avn_gaddwv(a, a->x, w, ngam);
}

/* these macros are only available if we have variable arguments macros */
#ifdef HAVEVAM
#define anv_add(a, ...) avn_addw(a, 1.0, ## __VARARGS__)
#define anv_gadd(a, ngam, ...) avn_gaddw(a, 1.0, ngam, ## __VARARGS__)
#endif

INLINE void avn_clear(avn_t *a)
{
  int i;

  a->s = 0;
  for (i = 0; i < a->n; i++)
    a->x[i] = a->sx[i] = a->sxb[i] = 0;
  for (i = 0; i < a->n * a->n; i++)
    a->sx2[i] = 0;
}

/* get average of quantity k */
INLINE double avn_getave(const avn_t *a, int k)
{
  die_if (k < 0 || k >= a->n, "avn index %d out of range %d\n", k, a->n);
  return (a->s > 0) ? a->sx[k]/a->s : 0;
}

/* get averages of all quantities */
INLINE double *avn_getaven(const avn_t *a, double *val)
{
  int k;

  if (a->s <= 0.) {
    for (k = 0; k < a->n; k++) val[k] = 0;
  } else {
    for (k = 0; k < a->n; k++)
      val[k] = a->sx[k] / a->s;
  }
  return val;
}

/* get cross variance of quantities k and l */
INLINE double avn_getvar(const avn_t *a, int k, int l)
{
  die_if (k < 0 || k >= a->n || l < 0 || l >= a->n,
      "avn index %d, %d out of range %d\n", k, l, a->n);
  if (k > l) intswap(k, l);
  return (a->s > 0) ? a->sx2[k * a->n + l]/a->s : 0;
}

/* get variances of all quantities */
INLINE double *avn_getvarn(const avn_t *a, double *val)
{
  int k, l, n = a->n;

  if (a->s <= 0.) {
    for (k = 0; k < n * n; k++) val[k] = 0;
  } else {
    for (k = 0; k < n; k++) {
      for (l = k; l < n; l++) {
        val[k*n + l] = a->sx2[k*n + l] / a->s;
        if (l > k) val[l*n + k] = val[k*n + l];
      }
    }
  }
  return val;
}

/* get standard deviation of quantity k */
INLINE double avn_getdev(const avn_t *a, int k)
{
  die_if (k < 0 || k >= a->n, "avn index %d out of range %d\n", k, a->n);
  return (a->s > 0) ? sqrt(a->sx2[k * a->n + k]/a->s) : 0;
}

/* get standard deviations of all quantities */
INLINE double *avn_getdevn(const avn_t *a, double *val)
{
  int k, n = a->n;

  if (a->s <= 0.) {
    for (k = 0; k < n; k++) val[k] = 0;
  } else {
    for (k = 0; k < n; k++)
      val[k] = sqrt(a->sx2[k*n + k] / a->s);
  }
  return val;
}

/* get correlation coefficient between quantities k and l */
INLINE double avn_getcor(const avn_t *a, int k, int l)
{
  int n = a->n;
  die_if (k < 0 || k >= n || l < 0 || l >= n,
      "avn index %d, %d out of range %d\n", k, l, n);
  if (k > l) intswap(k, l);
  return (a->s > 0) ? a->sx2[k*n+l] / sqrt(a->sx2[k*n+k] * a->sx2[l*n+l]) : 0;
}

/* get correlation coefficents among all quantities */
INLINE double *avn_getcorn(const avn_t *a, double *val)
{
  int k, l, n = a->n;

  if (a->s <= 0.) {
    for (k = 0; k < n * n; k++) val[k] = 0;
  } else {
    for (k = 0; k < n; k++) {
      for (l = k; l < n; l++) {
        val[k*n + l] = a->sx2[k*n + l] / sqrt(a->sx2[k*n + k] * a->sx2[l*n + l]);
        if (l > k) val[l*n + k] = val[k*n + l];
      }
    }
  }
  return val;
}

#endif /* ZCOM_AV__ */
#endif /* ZCOM_AV */

#ifdef  ZCOM_HIST
#ifndef ZCOM_HIST__
#define ZCOM_HIST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define HIST_VERBOSE    0x0001

#define HIST_ADDAHALF   0x0010
#define HIST_NOZEROES   0x0020
#define HIST_KEEPLEFT   0x0040
#define HIST_KEEPRIGHT  0x0080
#define HIST_KEEPLEFT2  0x0040
#define HIST_KEEPRIGHT2 0x0080
#define HIST_KEEPEDGE   (HIST_KEEPLEFT|HIST_KEEPRIGHT|HIST_KEEPLEFT2|HIST_KEEPRIGHT2)
#define HIST_KEEPHIST   0x0100
#define HIST_OVERALL    0x0200

#define HIST_ADDITION   0x1000

/* old names */
#define wdist(h,m,n,x0,dx,fn) wdistex(h,m,n,x0,dx,HIST_ADDAHALF|HIST_VERBOSE,fn)
#define wdistex histsave

#define histsave(h,rows,n,xmin,dx,flags,fname) \
  histsavex((const double *)h,rows,n,xmin,dx,flags,NULL,NULL,NULL,fname)

INLINE int histsavex(const double *h, int rows, int n, double xmin, double dx,
    unsigned flags, int (*fwheader)(FILE *, void *),
    double (*fnorm)(int, int, double, double, void *),
    void *pdata, const char *fname);

#define histload(h,rows,n,xmin,dx,flags,fname) \
  histloadx((double *)h,rows,n,xmin,dx,flags,NULL,NULL,NULL,fname)

INLINE int histloadx(double *hist, int rows, int n, double xmin, double dx,
    unsigned flags, int (*frheader)(const char *, void *),
    double (*fnorm)(int, int, double, double, void *),
    void *pdata, const char *fn);

INLINE int histadd(const double *x, double w, double *h, int rows,
    int n, double xmin, double dx, unsigned flags);

/* object oriented wrapper functions */
typedef struct {
  int rows;
  int n;
  double xmin;
  double dx;
  double *arr;
  int (*fwheader)(FILE *, void *);
  int (*frheader)(const char *, void *);
  double (*fnorm)(int, int, double, double, void *);
} hist_t;

typedef hist_t hs_t;

#define hs_open(m, x0, x1, dx) hs_openx(m, x0, x1, dx, NULL, NULL, NULL)
#define hs_open1(x0, x1, dx) hs_open(1, x0, x1, dx)
#define hs_save(hs,fn,flags) hs_savex(hs, fn, NULL, flags)
#define hs_load(hs,fn,flags) hs_loadx(hs, fn, NULL, flags)
#define hs_clear(hs) dblcleararr(hs->arr, hs->rows * hs->n)

INLINE hist_t *hs_openx(int rows, double xmin, double xmax, double dx,
    int (*fwh)(FILE *, void *), int (*frh)(const char*, void *),
    double (*fnorm)(int, int, double, double, void *))
{
  hist_t *hs;

  xnew(hs, 1);
  hs->rows = rows;
  hs->xmin = xmin;
  hs->dx   = dx;
  hs->n = (int)((xmax - xmin)/dx + 0.99999999);
  xnew(hs->arr, hs->n*hs->rows);
  hs->fwheader = fwh;
  hs->frheader = frh;
  hs->fnorm = fnorm;
  return hs;
}

INLINE void hs_close(hist_t *hs)
{
  if (!hs) return;
  if (hs->arr) free(hs->arr);
  memset(hs, 0, sizeof(*hs));
  free(hs);
}

INLINE void hs_check(const hist_t *hs)
{
  die_if (hs == NULL, "hs is %p", (const void *) hs);
  die_if (hs->arr == NULL || hs->rows == 0 || hs->n == 0,
    "hist: arr %p rows %d n %d\n", (const void *)(hs->arr), hs->rows, hs->n);
}

INLINE int hs_savex(const hist_t *hs, const char *fn, void *pdata, unsigned flags)
{
  hs_check(hs);
  return histsavex(hs->arr, hs->rows, hs->n, hs->xmin, hs->dx, flags,
      hs->fwheader, hs->fnorm, pdata, fn);
}

INLINE int hs_loadx(hist_t *hs, const char *fn, void *pdata, unsigned flags)
{
  hs_check(hs);
  return histloadx(hs->arr, hs->rows, hs->n, hs->xmin, hs->dx, flags,
      hs->frheader, hs->fnorm, pdata, fn);
}

INLINE int hs_add(hist_t *hs, const double *x, double w, unsigned flags)
{
  hs_check(hs);
  return histadd(x, w, hs->arr, hs->rows, hs->n, hs->xmin, hs->dx, flags);
}

#define hs_add1ez(hs, x, flags) hs_add1(hs, 0, x, 1, flags)

INLINE int hs_add1(hist_t *hs, int r, double x, double w, unsigned flags)
{
  hs_check(hs);
  die_if (r >= hs->rows || r < 0, "bad row index %d\n", r);
  return histadd(&x, w, hs->arr + r*hs->n, 1, hs->n, hs->xmin, hs->dx, flags);
}

/* two dimensional version */
INLINE int hist2save(const double *h, int rows, int n, double xmin, double dx,
    int m, double ymin, double dy, unsigned flags, const char *fname);
INLINE int hist2load(double *hist, int rows, int n, double xmin, double dx,
    int m, double ymin, double dy, unsigned flags, const char *fname);
INLINE int hist2add(const double *xarr, const double *yarr, int skip,
    double w, double *h, int rows,
    int n, double xmin, double dx,
    int m, double ymin, double dy, unsigned flags);

typedef struct {
  int rows;
  int n, m;
  double xmin, ymin;
  double dx, dy;
  double *arr, *dumptr;
} hist2_t;

typedef hist2_t hs2_t;

#define hs2_clear(hs2) dblcleararr(hs2->arr, hs2->rows * hs2->n * hs2->m)

#define hs2_open1(xmin, xmax, dx, ymin, ymax, dy) \
  hs2_open(1, xmin, xmax, dx, ymin, ymax, dy)
#define hs2_opensqr(rows, xmin, xmax, dx) \
  hs2_open(rows, xmin, xmax, dx, xmin, xmax, dx)
#define hs2_opensqr1(xmin, xmax, dx) \
  hs2_opensqr(1, xmin, xmax, dx)

INLINE hist2_t *hs2_open(int rows, double xmin, double xmax, double dx,
    double ymin, double ymax, double dy)
{
  hist2_t *hs2;

  xnew(hs2, 1);
  hs2->rows = rows;
  hs2->xmin = xmin;
  hs2->dx   = dx;
  hs2->n    = (int)((xmax - xmin)/dx + 0.99999999);
  hs2->ymin = ymin;
  hs2->dy   = dy;
  hs2->m    = (int)((ymax - ymin)/dy + 0.99999999);
  xnew(hs2->arr, hs2->n * hs2->m * hs2->rows);
  return hs2;
}

INLINE void hs2_close(hist2_t *hs2)
{
  if (hs2) {
    if (hs2->arr) free(hs2->arr);
    memset(hs2, 0, sizeof(*hs2));
    free(hs2);
  }
}

INLINE void hs2_check(const hist2_t *hs)
{
  die_if (hs == NULL, "hist2 is %p", (const void *) hs);
  die_if (hs->arr == NULL || hs->rows == 0 || hs->n == 0 || hs->m == 0,
    "hist2: arr %p rows %d n %d m %d\n",
    (const void *)(hs->arr), hs->rows, hs->n, hs->m);
}

INLINE int hs2_save(const hist2_t *hs, const char *fn, unsigned flags)
{
  hs2_check(hs);
  return hist2save(hs->arr, hs->rows, hs->n, hs->xmin, hs->dx,
      hs->m, hs->ymin, hs->dy, flags, fn);
}

INLINE int hs2_load(hist2_t *hs, const char *fn, unsigned flags)
{
  hs2_check(hs);
  return hist2load(hs->arr, hs->rows, hs->n, hs->xmin, hs->dx,
      hs->m, hs->ymin, hs->dy, flags, fn);
}

INLINE int hs2_add(hist2_t *hs, const double *x, const double *y, int skip,
    double w, unsigned flags)
{
  hs2_check(hs);
  return hist2add(x, y, skip, w, hs->arr, hs->rows, hs->n, hs->xmin, hs->dx,
      hs->m, hs->ymin, hs->dy, flags);
}

#define hs2_add1ez(hs, x, y, flags) hs2_add1(hs, 0, x, y, 1.0, flags)

INLINE int hs2_add1(hist2_t *hs, int r, double x, double y,
    double w, unsigned flags)
{
  hs2_check(hs);
  return hist2add(&x, &y, 1, w, hs->arr+r*hs->n*hs->m, 1,
     hs->n, hs->xmin, hs->dx, hs->m, hs->ymin, hs->dy, flags);
}


/* compute sum, average and variance */
INLINE double *histgetsums_(const double *h, int rows, int n,
    double xmin, double dx, double *sums)
{
  double *xav, *xxc, x, w;
  int i, r;

  xav = sums + rows;
  xxc = xav  + rows;
  for (r = 0; r < rows; r++) {
    sums[r] = xav[r] = xxc[r] = 0.;
    for (i = 0; i < n; i++) {
      x = xmin + (i+.5)*dx;
      w = h[r*n + i];
      sums[r] += w;
      xav[r]  += w*x;
      xxc[r]  += w*x*x;
    }
    if (sums[r] > 1e-5) {
      xav[r] /= sums[r];
      xxc[r] = xxc[r]/sums[r] - xav[r]*xav[r];
    }
  }
  return sums;
}


/* get average of a certain `row' */
INLINE double hs_getave(const hist_t *hs, int row, double *sum, double *var)
{
  double arr[3];

  histgetsums_(hs->arr + row * hs->n, 1, hs->n, hs->xmin, hs->dx, arr);
  if (sum) *sum = arr[0];
  if (var) *var = arr[2];
  return arr[1];
}


/* write histograms to file
 * histogram 'h' contains 'rows' histograms,
 * each contains 'n' entries, from 'xmin' to 'xmin+dx*n'
 * (*fwheader) is function to print additional information
 * (*fnorm) is advanced normalization function */
INLINE int histsavex(const double *h, int rows, int n, double xmin, double dx,
    unsigned flags,
    int (*fwheader)(FILE *fp, void *data),
    double (*fnorm)(int r, int ix, double xmin, double dx, void *data),
    void *pdata,
    const char *fn)
{
  const int version = 0;
  FILE *fp;
  int i, r, rp, rowp, imax, imin;
  const double *p;
  double sm, *sums, fac, delta;
  double smtot[3], *htot = NULL;

  if (fn == NULL) fn = "HIST";
  xfopen(fp, fn, "w", return -1);

  /* get statistics */
  xnew(sums, rows * 3);
  histgetsums_(h, rows, n, xmin, dx, sums);

  /* compute the overall histogram */
  if (flags & HIST_OVERALL) {
    xnew(htot, n); /* the overall histogram */
    for (i = 0; i < n; i++) htot[i] = 0.;

    for (r = 0; r < rows; r++)
      for (i = 0; i < n; i++)
        htot[i] += h[r*n + i];
    histgetsums_(htot, 1, n, xmin, dx, smtot);
    rowp = rows + 1;
  } else {
    rowp = rows;
  }

  /* print basic information */
  fprintf(fp, "# %d 0x%X | %d %d %g %g | ",
      version, flags, rows, n, xmin, dx);
  for (r = 0; r < rows; r++) /* number of visits */
    fprintf(fp, "%g ", sums[r]);
  fprintf(fp, "| ");
  for (r = 0; r < rows; r++) /* average, standard deviation */
    fprintf(fp, "%g %g ", sums[r+rows], sqrt(sums[r+rows*2]));
  fprintf(fp, "| ");
  if (fwheader != NULL) (*fwheader)(fp, pdata);
  fprintf(fp, "\n");

  delta = (flags & HIST_ADDAHALF) ? 0.5 : 0;

  for (r = 0; r < rowp; r++) {
    p = (r == rows) ? htot : (h+r*n);

    if (flags & HIST_KEEPRIGHT) {
      imax = n;
    } else { /* trim the right edge */
      for (i = n-1; i >= 0; i--)
        if (p[i] > 0)
          break;
      imax = i+1;
      if (imax == 0)
        continue;
    }

    if (flags & HIST_KEEPLEFT) {
      imin = 0;
    } else { /* trim the left edge */
      for (i = 0; i < imax; i++)
        if (p[i] > 0)
          break;
      imin = i;
    }

    sm = (r == rows) ? smtot[0] : sums[r];
    if (fabs(sm) < 1e-6) fac = 1.;
    else fac = 1.0/(sm*dx);

    for (i = imin; i < imax; i++) {
      if ((flags & HIST_NOZEROES) && p[i] < 1e-6)
        continue;
      fprintf(fp,"%g ", xmin+(i+delta)*dx);
      if (flags & HIST_KEEPHIST)
        fprintf(fp, "%20.14E ", p[i]);
      rp = (r == rows) ? (-1) : r;
      if (fnorm != NULL) /* advanced normalization, note the r = -1 case */
        fac = (*fnorm)(rp, i, xmin, dx, pdata);
      fprintf(fp,"%20.14E %d\n", p[i]*fac, rp);
    }
    fprintf(fp,"\n");
  }
  fclose(fp);
  if (flags & HIST_VERBOSE) {
    fprintf(stderr, "successfully wrote %s\n", fn);
    for (r = 0; r < rows; r++)
      fprintf(stderr, "%2d cnt: %20.4f av: %10.4f(%10.4f)\n",
          r, sums[r], sums[r+rows], sums[r+rows*2]);
  }
  free(sums);
  if (flags & HIST_OVERALL) {
    free(htot);
  }
  return 0;
}

/* fetch histogram size */
INLINE int histgetinfo(const char *fn, int *row, double *xmin, double *xmax, double *xdel,
    int *version, unsigned *fflags)
{
  FILE *fp;
  char s[1024];
  int n;

  xfopen(fp, fn, "r", return -1);
  if (fgets(s, sizeof s, fp) == NULL) {
    fprintf(stderr, "%s: missing the first line\n", fn);
    fclose(fp);
    return -1;
  }
  if (6 != sscanf(s, "# %d 0x %X | %d %d %lf %lf ",
        version, fflags, row, &n, xmin, xdel)) {
    fprintf(stderr, "%s: bad first line\n%s", fn, s);
    fclose(fp);
    return -1;
  }
  *xmax = *xmin + *xdel * n;
  fclose(fp);
  return 0;
}

/* skip a | */
INLINE char *skipabar_(char *p)
{
  int next = -1;
  sscanf(p, " | %n", &next);
  return (next < 0) ? NULL : (p + next);
}

/* load a previous histogram
 * (*frheader) function to read additional header info.
 * (*fnorm) normalization factor
 * flags can have HIST_ADDITION and/or HIST_VERBOSE */
INLINE int histloadx(double *hist, int rows, int n, double xmin, double dx,
    unsigned flags,
    int (*frheader)(const char *s, void *data),
    double (*fnorm)(int r, int ix, double xmin, double dx, void *data),
    void *pdata,
    const char *fn)
{
  FILE *fp;
  static char s[40960] = "", *p;
  int verbose = (flags & HIST_VERBOSE);
  int add = (flags & HIST_ADDITION);
  int ver, next, hashist;
  int i, i1, r, r1, nlin = 0;
  unsigned fflags;
  double x, y, y2, fac, delta, *arr, *sums = NULL;

  xfopen(fp, fn, "r", return -1);

  /* check the first line */
  if (fgets(s, sizeof s, fp) == NULL || s[0] != '#') {
    fprintf(stderr, "%s: missing the first line\n", fn);
    fclose(fp);
    return -1;
  }
  nlin++;
  if (6 != sscanf(s, " # %d 0x %X | %d%d%lf%lf | %n", &ver, &fflags, &r, &i, &y, &x, &next)
      || i < n || r != rows || fabs(x - dx) > 1e-5) {
    fprintf(stderr, "Error: bins = %d, %d, ng = %d, %d; dx = %g, %g\n",
        i, n, r, rows, x, dx);
    fclose(fp);
    return -1;
  }
  delta   = ((fflags & HIST_ADDAHALF) ? .5 : 0.);
  hashist =  (fflags & HIST_KEEPHIST);
  /* scan sums */
  xnew(sums, rows);
  for (p = s+next, r = 0; r < rows; r++) {
    if (1 != sscanf(p, "%lf%n", sums + r, &next)) {
      fprintf(stderr, "cannot read sums from at %d/%d, s:\n%s\np:\n%s\n", r, rows, s, p);
      goto EXIT;
    }
    p += next;
  }
  if ((p = skipabar_(p)) == NULL) goto EXIT;
  for (r = 0; r < rows; r++) {
    if (2 != sscanf(p, "%lf%lf%n", &y, &y2, &next)) {
      fprintf(stderr, "cannot read average/stddev from at %d/%d, s:\n%s\np:\n%s\n", r, rows, s, p);
      goto EXIT;
    }
    p += next;
  }
  if ((p = skipabar_(p)) == NULL) goto EXIT;
  if (frheader != NULL) {
    if (0 != frheader(p, pdata))
      goto EXIT;
  }


  if (!add) { /* clear histogram */
    for (i = 0; i < rows*n; i++) hist[i] = 0.;
  }

  /* loop over r = 0..rows-1 */
  for (r = 0; r < rows; r++) {
    arr = hist + r*n;
    fac = sums[r]*dx;
    while (fgets(s, sizeof s, fp)) {
      nlin++;
      for (p = s+strlen(s)-1; isspace((unsigned char)(*p)) && p >= s; p--)
        *p = '\0'; /* trim ending */
      if (s[0] == '#' || s[0] == '\0') break;
      if (hashist) {
        if (4 != sscanf(s, "%lf%lf%lf%d", &x, &y, &y2, &r1)) {
          fprintf(stderr, "error on line %d\n", nlin);
          goto EXIT;
        }
      } else { /* simple */
        if (3 != sscanf(s, "%lf%lf%d", &x, &y2, &r1)) {
          fprintf(stderr, "error on line %d\n", nlin);
          goto EXIT;
        }
      }
      if (r1 < 0) break; /* overall histogram */

      if (r1 < r) {
        fprintf(stderr, "wrong column index %d vs. %d on line %d, s=[%s]\n",
            r1, r, nlin, s);
        goto EXIT;
      } else if (r1 > r) {
        r = r1;
        arr = hist + r*n;
        fac = sums[r]*dx;
      }
      i1 = (int)((x - xmin)/dx - delta + .5);
      if (i1 < 0 || i1 >= n) {
        fprintf(stderr, "cannot find index for x = %g, delta = %g, i = %d/%d, on line %d\n",
            x, delta, i1, n, nlin);
        goto EXIT;
      }
      if (!hashist) {
        if (fnorm != NULL) {
          fac = (*fnorm)(r, i1, xmin, dx, pdata);
          fac = ((fabs(fac) < 1e-8) ? 1. : 1./fac);
        }
        y = y2*fac;
      }
      if (add) arr[i1] += y;
      else arr[i1] = y;
    }
  }
  if (verbose)
    fprintf(stderr, "histogram loaded successfully from %s\n", fn);

  if (sums) free(sums);
  fclose(fp);
  return 0;
EXIT:
  fprintf(stderr, "error occurs at file %s, line %d, s:%s\n", fn, nlin, s);
  if (sums) free(sums);
  /* we always clear histogram on error */
  for (i = 0; i < rows*n; i++) hist[i] = 0.;
  return -1;
}

/* add x of weight w, into histogram h
 * return number of success */
INLINE int histadd(const double *xarr, double w, double *h, int rows,
    int n, double xmin, double dx, unsigned flags)
{
  int r, ix, good = 0, verbose = flags & HIST_VERBOSE;
  double x;

  for (r = 0; r < rows; r++) {
    x = xarr[r];
    if (x < xmin) {
      if (verbose)
       fprintf(stderr, "histadd underflows %d: %g < %g\n", r, x, xmin);
      continue;
    }
    ix = (int)((x - xmin)/dx);
    if (ix >= n) {
      if (verbose)
        fprintf(stderr, "histadd overflows %d: %g > %g\n", r, x, xmin+dx*n);
      continue;
    }
    h[r*n + ix] += w;
    good++;
  }
  return good;
}


INLINE double *hist2getsums_(const double *h, int rows, int n,
    double xmin, double dx, int m, double ymin, double dy, double *sums)
{
  double *xav, *yav, *xxc, *yyc, *xyc, x, y, w;
  int i, j, r;

  xav = sums + rows;
  xxc = sums + rows*2;
  yav = sums + rows*3;
  yyc = sums + rows*4;
  xyc = sums + rows*5;
  for (r = 0; r < rows; r++) {
    sums[r] = xav[r] = xxc[r] = yav[r] = yyc[r] = 0.;
    for (i = 0; i < n; i++) {
      x = xmin + (i+.5)*dx;
      for (j = 0; j < m; j++) {
        y = ymin + (j+.5)*dy;
        w = h[r*n*m + i*m + j];
        sums[r] += w;
        xav[r]  += w*x;
        xxc[r]  += w*x*x;
        yav[r]  += w*y;
        yyc[r]  += w*y*y;
        xyc[r]  += w*x*y;
      }
    }
    if (sums[r] > 1e-5) {
      xav[r] /= sums[r];
      xxc[r] = sqrt(xxc[r]/sums[r] - xav[r]*xav[r]);
      yav[r] /= sums[r];
      yyc[r] = sqrt(yyc[r]/sums[r] - yav[r]*yav[r]);
      xyc[r] = xyc[r]/sums[r] - xav[r]*yav[r];
    }
  }
  return sums;
}


/* write 'rows' 2d n^2 histograms to file */
INLINE int hist2save(const double *h, int rows, int n, double xmin, double dx,
    int m, double ymin, double dy, unsigned flags, const char *fn)
{
  const int version = 1; /* v1 allows different dimension in x and y */
  FILE *fp;
  int i, j, r, imax, imin, jmax, jmin, nm;
  const double *p;
  double *sums, fac, delta;

  if (fn == NULL) fn = "HIST2";
  xfopen(fp, fn, "w", return 1);

  nm = n*m;
  xnew(sums, rows * 6);
  hist2getsums_(h, rows, n, xmin, dx, m, ymin, dy, sums);
  /* print basic information */
  fprintf(fp, "# %d 0x%X | %d %d %g %g %d %g %g | ",
      version, flags, rows, n, xmin, dx, m, ymin, dy);
  for (r = 0; r < rows; r++) /* number of visits */
    fprintf(fp, "%g ", sums[r]);
  fprintf(fp, " | ");
  for (r = 0; r < rows; r++) /* averages and standard deviations */
    fprintf(fp, "%g %g %g %g %g ", sums[r+rows], sums[r+rows*2],
        sums[r+rows*3], sums[r+rows*4], sums[r+rows*5]);
  fprintf(fp, "| \n");

  delta = (flags & HIST_ADDAHALF) ? 0.5 : 0;

  for (r = 0; r < rows; r++) { /* the rth data set */
    p = h + r*nm;

    if (flags & HIST_KEEPRIGHT) {
      imax = n;
    } else { /* trim the right edge of i */
      for (i = n-1; i >= 0; i--) {
        for (j = 0; j < m; j++)
          if (p[i*m + j] > 0) break;
        if (j < m) break; /* found a nonzero entry */
      }
      imax = i+1;
      if (imax == 0)
        continue;
    }

    if (flags & HIST_KEEPLEFT) {
      imin = 0;
    } else { /* trim the left edge of i */
      for (i = 0; i < imax; i++) {
        for (j = 0; j < m; j++)
          if (p[i*m + j] > 0) break;
        if (j < m) break; /* found a nonzero entry */
      }
      imin = i;
    }

    if (flags & HIST_KEEPRIGHT2) {
      jmax = m;
    } else { /* trim the right edge of j */
      for (j = m-1; j >= 0; j--) {
        for (i = imin; i < imax; i++)
          if (p[i*m + j] > 0) break;
        if (i < imax) break;
      }
      jmax = j+1;
    }

    if (flags & HIST_KEEPLEFT2) {
      jmin = 0;
    } else { /* trim the left edge of j */
      for (j = 0; j < jmax; j++) {
        for (i = imin; i < imax; i++)
          if (p[i*m + j] > 0) break;
        if (i < imax) break;
      }
      jmin = j;
    }

    if (fabs(sums[r]) < 1e-6) fac = 1.;
    else fac = 1.0/(sums[r]*dx*dy);

    for (i = imin; i < imax; i++) {
      for (j = jmin; j < jmax; j++) {
        double x, y;
        if ((flags & HIST_NOZEROES) && p[i*m + j] < 1e-16)
          continue;
        x = xmin + (i+delta)*dx;
        y = ymin + (j+delta)*dy;
        fprintf(fp,"%g %g ", x, y);
        if (flags & HIST_KEEPHIST)
          fprintf(fp, "%20.14E ", p[i*m+j]);
        fprintf(fp,"%20.14E %d\n", p[i*m+j]*fac, r);
      }
      fprintf(fp,"\n");
    }
    fprintf(fp, "\n#\n");
  }
  fclose(fp);
  if (flags & HIST_VERBOSE) {
    fprintf(stderr, "successfully wrote %s\n", fn);
    for (r = 0; r < rows; r++)
      fprintf(stderr, "%2d cnt: %20.4f xav: %10.4f(%10.4f) yav: %10.4f(%10.4f)\n",
          r, sums[r], sums[r+rows], sums[r+rows*2], sums[r+rows*3], sums[r+rows*4]);
  }
  free(sums);
  return 0;
}

INLINE int hist2load(double *hist, int rows, int n, double xmin, double dx,
    int m, double ymin, double dy, unsigned flags, const char *fn)
{
  FILE *fp;
  static char s[40960] = "", *p;
  int verbose = (flags & HIST_VERBOSE);
  int add = (flags & HIST_ADDITION);
  int ver, next, hashist;
  int i, j, r, r1, nm, nlin = 0;
  unsigned fflags;
  double x, y, g, g2, fac, delta, *arr, *sums = NULL;
  double xmin1, dx1, ymin1, dy1;

  xfopen(fp, fn, "r", return -1);

  nm = n*m;
  /* check the first line */
  if (fgets(s, sizeof s, fp) == NULL || s[0] != '#') {
    fprintf(stderr, "%s: missing the first line\n", fn);
    fclose(fp);
    return -1;
  }
  nlin++;
  if (9 != sscanf(s, " # %d 0x %X | %d%d%lf%lf%d%lf%lf | %n", &ver, &fflags, &r,
        &i, &xmin1, &dx1, &j, &ymin1, &dy1, &next)
      || i < n || j < m || r != rows
      || fabs(dx1 - dx) > 1e-5 || fabs(dy1 - dy) > 1e-5 ) {
    fprintf(stderr, "Error: bins %d, %d; %d, %d; ng %d, %d; dx %g, %g; dy %g, %g\n",
        i, n, j, m, r, rows, dx1, dx, dy1, dy);
    fclose(fp);
    return -1;
  }
  delta   = ((fflags & HIST_ADDAHALF) ? .5 : 0.);
  hashist =  (fflags & HIST_KEEPHIST);
  /* scan sums */
  xnew(sums, rows);
  for (p = s+next, r = 0; r < rows; r++) {
    if (1 != sscanf(p, "%lf%n", sums + r, &next)) {
      fprintf(stderr, "cannot read sums from at %d/%d, s:\n%s\np:\n%s\n", r, rows, s, p);
      goto EXIT;
    }
    p += next;
  }
  if ((p = skipabar_(p)) == NULL) goto EXIT;
  for (r = 0; r < rows; r++) {
    if (4 != sscanf(p, "%lf%lf%lf%lf%n", &x, &y, &g, &g2, &next)) {
      fprintf(stderr, "cannot read average/stddev from at %d/%d, s:\n%s\np:\n%s\n", r, rows, s, p);
      goto EXIT;
    }
    p += next;
  }
  if ((p = skipabar_(p)) == NULL) goto EXIT;

  if (!add) { /* clear histogram */
    for (i = 0; i < rows*nm; i++) hist[i] = 0.;
  }

  /* loop over r = 0..rows-1 */
  for (r = 0; r < rows; r++) {
    arr = hist + r*nm;
    fac = sums[r]*(dx*dx);
    while (fgets(s, sizeof s, fp)) {
      nlin++;
      for (p = s+strlen(s)-1; isspace((unsigned char)(*p)) && p >= s; p--)
        *p = '\0'; /* trim ending */
      if (s[0] == '#') break;
      if (s[0] == '\0') continue;

      if (hashist) {
        if (5 != sscanf(s, "%lf%lf%lf%lf%d", &x, &y, &g, &g2, &r1)) {
          fprintf(stderr, "error on line %d\n", nlin);
          goto EXIT;
        }
      } else {
        if (4 != sscanf(s, "%lf%lf%lf%d", &x, &y, &g2, &r1)) {
          fprintf(stderr, "error on line %d\n", nlin);
          goto EXIT;
        }
      }
      if (r1 != r) {
        fprintf(stderr, "wrong column index %d vs. %d on line %d\n",
          r1, r, nlin);
        goto EXIT;
      }
      i = (int)((x - xmin)/dx - delta + .5);
      if (i < 0 || i >= n) {
        fprintf(stderr, "cannot find index for x = %g\n", x);
        goto EXIT;
      }
      j = (int)((y - ymin)/dy - delta + .5);
      if (j < 0 || j >= m) {
        fprintf(stderr, "cannot find index for y = %g\n", y);
        return -1;
      }
      if (!hashist) {
        g = g2*fac;
      }
      if (add) arr[i*m+j] += g;
      else arr[i*m+j] = g;
    }
  }
  if (verbose) fprintf(stderr, "%s loaded successfully\n", fn);
  return 0;
EXIT:
  fprintf(stderr, "error occurs at file %s, line %d, s:%s\n", fn, nlin, s);
  if (sums) free(sums);
  for (i = 0; i < rows*nm; i++) hist[i] = 0.;
  return -1;
}

/* add (xarr[skip*r], yarr[skip*r]) of weight w, into histogram h
 * return number of success */
INLINE int hist2add(const double *xarr, const double *yarr, int skip,
    double w, double *h, int rows,
    int n, double xmin, double dx,
    int m, double ymin, double dy, unsigned flags)
{
  int r, ix, iy, good = 0, verbose = flags & HIST_VERBOSE;
  double x, y;

  for (r = 0; r < rows; r++) {
    x = xarr[skip*r];
    y = yarr[skip*r];
    if (x < xmin || y < ymin) {
      if (verbose)
       fprintf(stderr, "histadd underflows %d: %g < %g or %g < %g\n",
          r, x, xmin, y, ymin);
      continue;
    }
    ix = (int)((x - xmin)/dx);
    iy = (int)((y - ymin)/dy);
    if (ix >= n || iy >= m) {
      if (verbose)
        fprintf(stderr, "histadd overflows %d: %g > %g or %g > %g\n",
            r, x, xmin + dx*n, y, ymin + dy*m);
      continue;
    }
    h[r*n*m + ix*m + iy] += w;
    good++;
  }
  return good;
}


#endif /* ZCOM_HIST__ */
#endif /* ZCOM_HIST */

#ifdef  ZCOM_DISTR
#ifndef ZCOM_DISTR__
#define ZCOM_DISTR__

#define DSDIF_HIS1 0x01 /* the first distribution is histogram */
#define DSDIF_HIS2 0x02 /* the second (reference) is histogram */

/* return KS difference between f and ref, with p-value
 * f and ref are distribution densities
 * if ishis & DSDIF_HIS1, f[0..n-1] is histogram, otherwise f[0..n] is the distribution
 * is ishis & DSDIF_HIS2, ref[0..n-1] is histogram, otherwise ref[0..n] is the distribution
 * smpsize is the sample size */
INLINE double ksdif1d(const double f[], const double ref[], int n, int ishis,
    double smpsiz, double *p, double err[])
{
  int i, alloc = 0, his1 = ishis & DSDIF_HIS1, his2 = ishis & DSDIF_HIS2;
  double tot1, tot2, sum1, sum2, e, emax;

  if (err == NULL) { alloc = 1; xnew(err, n + 1); }
  err[0] = 0.;

  /* compute the normalization factor for both distributions */
  for (tot1 = tot2 = 0., i = 0; i < n; i++) {
    tot1 += his1 ? f[i]   : .5*(f[i] + f[i+1]);
    tot2 += his2 ? ref[i] : .5*(ref[i] + ref[i+1]);
  }
  if (tot1 <= 0. || tot2 <= 0.) {
    fprintf(stderr, "ksdif: bad distribution, tot 1: %g, 2: %g\n", tot1, tot2);
    return 0;
  }

  for (sum1 = sum2 = 0., emax = 0., i = 0; i < n; i++) {
    sum1 += (his1 ? f[i]   : .5*(f[i] + f[i+1])) / tot1;
    sum2 += (his2 ? ref[i] : .5*(ref[i] + ref[i+1])) / tot2;
    err[i + 1] = e = sum1 - sum2;
    if ((e = fabs(e)) > emax) emax = e;
  }
  e = sqrt(smpsiz);
  emax *= e + .12 + .11/e; /* a formula from numerical recipes */
  if (p != NULL) *p = ksq(emax);
  if (alloc) free(err);
  return emax;
}


/* entropic difference = integral log(ref/r) ref(x) dx */
INLINE double entdif1d(const double f[], const double ref[], int n,
    int ishis, double err[])
{
  int i, alloc = 0, his1 = ishis & DSDIF_HIS1, his2 = ishis & DSDIF_HIS2;
  double tot1, tot2, y1, y2, e;

  if (err == NULL) { alloc = 1; xnew(err, n + 1); }
  err[0] = 0.;

  /* compute the normalization factor for both distributions */
  for (tot1 = tot2 = 0., i = 0; i < n; i++) {
    tot1 += his1 ? f[i]   : .5*(f[i] + f[i+1]);
    tot2 += his2 ? ref[i] : .5*(ref[i] + ref[i+1]);
  }
  if (tot1 <= 0. || tot2 <= 0.) {
    fprintf(stderr, "entdif: bad distribution, tot 1: %g, 2: %g\n", tot1, tot2);
    return 0;
  }

  for (e = 0., i = 0; i < n; i++) {
    y1 = (his1 ? f[i]   : .5*(f[i] + f[i+1])) / tot1;
    y2 = (his2 ? ref[i] : .5*(ref[i] + ref[i+1])) / tot2;
    if (y1 <= 0 || y2 <= 0) {
      if (err) err[i] = 0;
      continue;
    }
    y2 = log(y1/y2);
    if (err) err[i] = y2;
    e += y2 * y1;
  }
  if (alloc) free(err);
  return e;
}


/* data collected in each bin */
typedef struct {
  double s;
  double sf;  /* mean force */
  double sf2; /* mean force^2 */
  double sdv; /* average value for the 2nd derivative */
} distrsum_t;

INLINE void distrsum_clear(distrsum_t *x) { x->s = x->sf = x->sf2 = x->sdv = 0.0; }


/* 1D window boundaries */
typedef struct { int il, ir; } distrwin_t;


/* distribution object */
typedef struct {
  int n;
  double xmin, xmax, dx;
  distrsum_t *arr; /* [0..n), bin data */
  double *rho; /* [0..n], output distribution */
  double *lnrho;  /* [0..n], from mean force integration */
  double *his; /* [0..n], histogram average */
  double *mf, *mdv; /* estimated mean force and deterministic part of mdv
                     * in the simplest case, mf[i] = arr[i].sf/arr[i].s */
  distrwin_t *win; /* window size */
  double *err;
  double *hsum; /* histogram sum for comparison */
  double *mfsig; /* std. dev. of mf, for adaptive window */
  double *norm; /* normalization vector */
} distr_t;

/* compute mean force from a single bin or a narrowest symmetric window
 * that contains at least one data point */
INLINE void distr_mf0(distr_t *d)
{
  int i, m = 0, n = d->n;
  double s, sf, sdv;

  for (i = 0; i < n; i++) {
    distrsum_t *ds = d->arr + i;
    s = ds->s;
    sf = ds->sf;
    sdv = ds->sdv;
    /* extend to both sides, stop as soon as we have one data point */
    for (m = 1; m < n && s <= 0.; m++) {
      if (i - m >= 0) { /* extend to the left */
        ds = d->arr + i - m;
        s += ds->s;
        sf += ds->sf;
        sdv += ds->sdv;
      }
      if (i + m < n) { /* extend to the right */
        ds = d->arr + i + m;
        s += ds->s;
        sf += ds->sf;
        sdv += ds->sdv;
      }
    }
    d->mf[i] = (s > 0.) ? (sf / s) : 0.;
    d->mdv[i] = (s > 0.) ? (sdv / s) : 0.;
  }
}

#define distr_mfav(d, m) distr_mfwin(d, m, 0)
#define distr_mfii(d, m) distr_mfwin(d, m, 1)

/* compute mean force from a symmetric window
 * if ii, we use the integral identity, otherwise, a plain average
 * linear phi(x) is used for the integral identity
 * improves mean force, slightly smoothness of distribution itself */
INLINE void distr_mfwin(distr_t *d, int m, int ii)
{
  int i, j, j0, j1, n = d->n;
  double s0, s1, s, phi, dx = d->dx;

  distr_mf0(d);
  for (i = 0; i < n; i++) {
    j0 = intmax(0, i - m);
    j1 = intmin(n, i + m + 1);
    for (s0 = s1 = s = 0., j = j0; j < j1; j++) {
      phi = (j == i) ? 0 : (j + .5 - (j < i ? j0 : j1)) * dx;
      s0 += d->mf[j];
      s1 += d->mdv[j] * phi;
      s += 1;
    }
    if (ii) s0 += s1; /* add correction from the second-order derivative */
    d->mf[i] = (s > 0) ? s0/s : 0.0;
  }
}

/* Adib-Jazynski identity from [i - m, i + m)
 * where `i' and `m' are integer bin index
 * linear function phi(x) is assumed
 * asymmetric windows are used at the boundaries
 * uses d->arr[j].s and .sf (but not the second derivatives .sf2)
 * sets d->his, d->rho, d->win */
INLINE void distr_aj(distr_t *d, int m)
{
  int i, j, j0, j1, n = d->n;
  double s0, s1, phi, den, tot, s, sf, dx = d->dx;
  distrsum_t *ds;

  /* compute the total number of visits */
  for (tot = 0., i = 0; i < n; i++) tot += d->arr[i].s;

  /* estimate using integral identity */
  for (i = 0; i <= n; i++) {
    /* compute # of visits in a window around i
     * the window is asymmetric at the boundaries */
    j0 = intmax(i - m, 0);
    j1 = intmin(i + m, n);
    for (s0 = s1 = 0., j = j0; j < j1; j++) {
      /* compute the linear phi(x) = (x - x0)/(x1 - x0) - Step(x);
       * here variable `phi' is phi(x) * (x1 - x0)
       * which yields a unit derivative */
      phi = (j + .5 - (j < i ? j0 : j1)) * dx;
      ds = d->arr + j;
      s = ds->s;
      sf = ds->sf;
      /* apply the normalization factor, for the radial distribution function */
      if (d->norm) {
        double nm = .5 * (d->norm[j] + d->norm[j + 1]);
        s /= nm;
        sf /= nm;
      }
      s0 += s; /* the histogram part, phi' = 1 */
      s1 += sf * phi;  /* the additive correction */
    }
    den = 1.0 * (j1 - j0) * tot * dx;
    d->his[i] = s0/den;
    d->rho[i] = (s0 + s1 > 0) ? (s0 + s1)/den : 0.;
    d->win[i].il = i - j0;
    d->win[i].ir = j1 - i;
  }
}

/* make fixed windows
 * if m == 0, guess width from 2 m dx = 1/sig(mf) */
INLINE void distr_winfixed(distr_t *d, distrwin_t *win, double gam, int m)
{
  int i, n = d->n;
  double his, sig;

  if (m == 0) { /* guess window size */
    /* error of mean force as variance divided by the number of samples */
    for (sig = his = 0, i = 0; i < n; i++) {
      distrsum_t *ds = d->arr + i;
      if (ds->s > 0.) {
        sig += ds->sf2 - ds->sf * ds->sf / ds->s;
        his += ds->s;
      }
    }
    sig = sqrt(sig/his);

    m = intmax(1, (int) (0.5 * gam/(sig * d->dx) + .5));
    printf("mean force standard deviation is %g, m %d\n", sig, m);
  }

  for (i = 0; i <= n; i++) {
    win[i].il = intmax(i - m, 0);
    win[i].ir = intmin(i + m, n);
  }
}

/* estimate local standard deviation of the mean force
 * average over local window of 2 m */
INLINE void distr_mfsig0(distr_t *d, double sampmin)
{
  int i, m, n = d->n;
  double x, sig, his, *asig, *hsum;

  xnew(asig, n + 1);
  xnew(hsum, n + 1);
  for (asig[0] = hsum[0] = 0, i = 0; i < n; i++) {
    distrsum_t *ds = d->arr + i;
    hsum[i+1] = hsum[i] + ds->s;
    x = (ds->s > 0) ? (ds->sf2 - ds->sf * ds->sf / ds->s) : 0.;
    asig[i+1] = asig[i] + x;
  }
  for (i = 0; i < n; i++) {
    /* start from the minimal window size, expand until included sampmin data points */
    for (m = 1; m < n; m++) {
      int j0 = intmax(0, i - m), j1 = intmin(i + m + 1, n);
      his = hsum[j1] - hsum[j0];
      sig = asig[j1] - asig[j0];
      d->mfsig[i] = his > 0. ? sqrt(sig/his) : 0.;
      if (his > sampmin || (j0 == 0 && j1 == n)) break;
    }
  }
  d->mfsig[n] = d->mfsig[n-1];
  free(asig);
  free(hsum);
}

/* make symmetrical but x-dependent window
 * for the volume distribution
 * requires d->mfsig */
INLINE void distr_winadp0(distr_t *d, distrwin_t *win, double gam, int mlimit)
{
  int i, m, n = d->n;
  double dx = d->dx;

  if (mlimit < 0) mlimit = 100000000; /* set a very large number */

  for (i = 0; i <= n; i++) {
    m = (int) intmax(1, (int) (0.5 * gam/(d->mfsig[i] * dx) + .5));
    win[i].il = intmax(0, i - m);
    win[i].ir = intmin(n, i + m);
  }
}

/* make adaptive window
 * for the volume distribution
 * requires d->rho and d->mfsig */
INLINE void distr_winadp(distr_t *d, int mlimit)
{
  int i, n = d->n;
  double dx = d->dx, *hsum, *hhis;

  xnew(hsum, n + 1);
  xnew(hhis, n + 1);
  for (i = 0; i < n; i++) {
    hhis[i] = .5 * (d->rho[i] + d->rho[i + 1]);
    if (d->norm) hhis[i] *= .5 * (d->norm[i] + d->norm[i + 1]);
  }
  for (hsum[0] = 0., i = 0; i < n; i++)
    hsum[i + 1] = hsum[i] + hhis[i];

  if (mlimit < 0) mlimit = 100000000; /* set a very large number */

  for (i = 0; i <= n; i++) {
    int k = 0, jl = i, jr = i+1, el = 0, er = 0, jlm, jrm;

    jlm = intmax(0, i - mlimit);
    jrm = intmin(n, i + mlimit);
    for (k = 0; el == 0 || er == 0; k++) {
      if (k % 2 == 0) { /* do the left */
        if (el || jl <= jlm) {
          el = 1;
          continue;
        }
        if (hhis[jl - 1] / (hsum[jr] - hsum[jl] + 1e-10) < d->mfsig[jl - 1] * dx) {
          el = 1;
        } else {
          jl--;
        }
      } else { /* do the right */
        if (er || jr >= jrm) {
          er = 1;
          continue;
        }
        if (hhis[jr] / (hsum[jr] - hsum[jl] + 1e-10) < d->mfsig[jr] * dx) {
          er = 1;
        } else {
          jr++;
        }
      }
    }
    d->win[i].il = jl;
    d->win[i].ir = jr;
  }
  free(hhis);
  free(hsum);
}

/* obtain distribution from integrating the mean force
 *  d->lnrho[i] = \sum_{j < i} d->mf[i] * dx
 * limiting case of distr_ii0 with infinite window size
 * it uses d->mf[i] (which should have been computed already)
 * it outputs d->rho[i] and d->lnrho[i] */
INLINE void distr_iimf(distr_t *d)
{
  int i, n = d->n;
  double max, tot, x, lntot, dx = d->dx;

  /* integrate mf to get ln(rho) */
  for (max = d->lnrho[0] = 0, i = 0; i < n; i++) {
    d->lnrho[i + 1] = d->lnrho[i] + d->mf[i] * dx;
    if (d->lnrho[i + 1] > max) max = d->lnrho[i + 1];
  }

  for (tot = 0, i = 0; i <= n; i++) {
    x = exp(d->lnrho[i] -= max);
    if (d->norm) x *= d->norm[i];
    tot += d->rho[i] = x;
  }
  tot *= dx;
  lntot = log(tot);

  for (i = 0; i <= n; i++) {
    d->lnrho[i] -= lntot;
    d->rho[i] /= tot;
  }
}

/* fractional integral identity (low level)
 * set rho[], lnrho[], his[]
 * before calling this function
 * first call mfX() to compute the mean force,
 * and call winX() to compute the window */
INLINE void distr_ii0(distr_t *d, distrwin_t *win)
{
  int i, j, jl, jr, n = d->n;
  double x, delx, den, tot, dx = d->dx;

  /* construct ln(rho) from the mean force */
  distr_iimf(d);

  for (d->hsum[0] = 0., i = 0; i < n; i++)
    d->hsum[i + 1] = d->hsum[i] + d->arr[i].s;
  tot = d->hsum[n]; /* total number of visits */

  /* estimate using integral identity */
  for (i = 0; i <= n; i++) {
    /* compute # of visits in a window around i */
    jl = win[i].il;
    jr = win[i].ir;
    d->his[i] = d->hsum[jr] - d->hsum[jl];

    /* integrate over exp(lnrho[j] - lnrho[i])
     * Note: we can loop from j0 to j1, with little difference */
    for (den = 0., delx = 0., j = jl; j <= jr; j++) {
      x = exp(d->lnrho[j] - d->lnrho[i]);
      if (d->norm) x *= d->norm[j]; /* apply the normalization factor */
      den += (j == jl || j == jr) ? x * .5 : x;
      if (d->norm)
        delx += d->norm[j] * ((j == jl || j == jr) ? .5 : 1.);
    }
    den *= tot * dx;
    d->rho[i] = (den > 0.) ? d->his[i] / den : 0.;
    if (d->norm == NULL) delx = jr - jl;
    if (tot > 0.) d->his[i] /= tot * dx * delx;
  }
}

/* perform integral identity
 * iitype: 0: Adib-Jazynski, 1: fraction identity, 2: integrate the mean force
 * halfwin: half window size
 *          > 0:  fixed size,
 *            0:  fixed size (determined automatically)
 *           -1:  adaptive window size
 * mfhalfwin: half window size for mean force integration
 *            use zero for simple bin average
 *            positive for unbiased window average
 *            negative for simple average
 * gam: window size amplification factor
 * mlimit: maximal half window size (-1 to disable)
 * sampmin: minimal number of samples in estimating mean force std. */
INLINE void distr_iiez(distr_t *d, int iitype, int halfwin, int mfhalfwin,
    double gam, int mlimit, double sampmin)
{
  if (iitype == 0) { /* Jarzynski method */
    distr_aj(d, halfwin);
    return;
  } else if (iitype < 0 || iitype > 2) {
    fprintf(stderr, "unsupported method %d\n", iitype);
    return;
  }

  /* 1. compute the mean force */
  if (mfhalfwin == 0) {
    distr_mf0(d);
  } else {
    /* positive `mfhalfwin' means an unbiased estimate
     * negative means the */
    distr_mfwin(d, abs(mfhalfwin), mfhalfwin > 0 ? 1 : 0);
  }

  /* 2. compute the distribution */
  if (iitype == 1) {
    if (halfwin < -1) {
      fprintf(stderr, "iiadp no longer supported!\n");
      /* distr_iiadp(d, mlimit, sampmin); */
      return;
    }

    /* computing the window size */
    if (halfwin >= 0) {
      /* uniform windows i.e.
       * if halfwin == 0, estimate from the global mean force fluctuation */
      distr_winfixed(d, d->win, gam, halfwin);
    } else { /* halfwin == -1 */
      /* compute the nonuniform window size */
      distr_mfsig0(d, sampmin);
      distr_winadp0(d, d->win, gam, mlimit);
    }
    /* using the integral identity */
    distr_ii0(d, d->win);
    return;
  }

  if (iitype == 0) { /* do simple mean force integration */
    distr_iimf(d);
    return;
  }
}

INLINE distr_t *distr_open(double xmin, double xmax, double dx)
{
  distr_t *d;
  xnew(d, 1);
  d->xmin = xmin;
  d->dx = dx;
  d->n = (int)((xmax - xmin)/dx + 0.999999f);
  d->xmax = xmin + d->n * dx;
  xnew(d->arr, d->n + 1);
  xnew(d->rho, d->n + 1);
  xnew(d->lnrho, d->n + 1);
  xnew(d->his, d->n + 1);
  xnew(d->mf, d->n + 1);
  xnew(d->mdv, d->n + 1);
  xnew(d->win, d->n + 1);
  xnew(d->err, d->n + 1);
  xnew(d->hsum, d->n + 1);
  xnew(d->mfsig, d->n + 1);
  d->norm = NULL;
  return d;
}

INLINE void distr_close(distr_t *d)
{
  if (!d) return;
  free(d->arr);
  free(d->rho);
  free(d->lnrho);
  free(d->his);
  free(d->mf);
  free(d->mdv);
  free(d->win);
  free(d->err);
  free(d->hsum);
  free(d->mfsig);
  free(d);
}

INLINE void distr_add(distr_t *d, double x, double f, double dv, double w)
{
  if (x >= d->xmin && x <= d->xmax) {
    distrsum_t *ds = d->arr + (int)((x - d->xmin)/d->dx);
    ds->s += w;
    ds->sf += w * f;
    ds->sf2 += w * f * f;
    ds->sdv += w * dv;
  }
}


#define DISTR_KEEPLEFT   0x0040
#define DISTR_KEEPRIGHT  0x0080
#define DISTR_KEEPEDGE   (DISTR_KEEPLEFT | DISTR_KEEPRIGHT)
#define distr_save(d, fn) distr_savex(d, fn, 0)

INLINE int distr_savex(distr_t *d, const char *fn, unsigned flags)
{
  FILE *fp;
  int i, i0 = 0, i1 = d->n, n = d->n;
  distrsum_t *ds = d->arr;

  if (!(flags & DISTR_KEEPEDGE)) {
    /* determine the range */
    for (i0 = 0; i0 <= n; i0++)
      if (d->his[i0] > 0. || d->arr[i0].s > 0.)
        break;
    for (; i1 >= i0; i1--)
      if (d->his[i1] > 0. || d->arr[i1].s > 0.)
        break;
    if (i0 > i1) {
      printf("histogram is empty\n");
      return 1;
    }
  }

  xfopen(fp, fn, "w", return -1);
  fprintf(fp, "# 1 %d %.14e %.14e\n", d->n, d->xmin, d->dx);

  for (i = i0; i <= i1; i++) {
    double f = 0.0, f2 = 0.0, dv = 0.0;
    ds = d->arr + i;
    if (i < n && ds->s > 0.) {
      f = ds->sf / ds->s;
      f2 = ds->sf2 / ds->s - f * f; /* convert to variance */
      dv = ds->sdv / ds->s;
    }
    fprintf(fp, "%g %.14e %.14e %.14e %.14e "
        "%.14e %.14e %.14e %.14e %.14e %g %g "
        "%g %g\n",
      d->xmin + i * d->dx, ds->s, f, f2, dv,
      d->rho[i], d->lnrho[i], d->his[i], d->mf[i], d->mdv[i],
      d->xmin + d->dx * d->win[i].il, d->xmin + d->dx * d->win[i].ir,
      d->err[i], d->mfsig[i]);
  }
  fclose(fp);
  return 0;
}

/* load a previous histogram */
INLINE int distr_load(distr_t *d, const char *fn)
{
  FILE *fp;
  char s[1024];
  int ver, i, n = d->n, nlin;
  double x, sm, f, f2, dv, rho, xmin = d->xmin, dx = d->dx;
  distrsum_t *ds;

  xfopen(fp, fn, "r", return -1);

  /* check the first line */
  if (fgets(s, sizeof s, fp) == NULL || s[0] != '#') {
    fprintf(stderr, "%s: missing the first line\n", fn);
    fclose(fp);
    return -1;
  }
  if (4 != sscanf(s, " # %d%d%lf%lf", &ver, &i, &x, &sm)
      || i != n || fabs(x - xmin) > 1e-3 || fabs(sm - dx) > 1e-5) {
    fprintf(stderr, "error: bins = %d, %d, xmin = %g, %g; dx = %g, %g\n",
        i, n, x, xmin, sm, dx);
    fclose(fp);
    return -1;
  }

  /* only read in raw data */
  for (nlin = 2; fgets(s, sizeof s, fp); nlin++) {
    if (6 != sscanf(s, "%lf%lf%lf%lf%lf%lf", &x, &sm, &f, &f2, &dv, &rho)) {
      fprintf(stderr, "sscanf error\n");
      goto ERR;
    }
    /* locate the bin */
    i = (int)( (x - xmin)/dx + .1);
    if (i < 0 || i >= n) {
      fprintf(stderr, "bad x %g, xmin %g, i %d, n %d\n", x, xmin, i, n);
      goto ERR;
    }
    ds = d->arr + i;
    ds->s = sm;
    ds->sf = f * sm;
    ds->sf2 = (f2 + f*f)*sm;
    ds->sdv = dv * sm;
    d->rho[i] = rho;
    if (i >= n - 1) break;
  }
  return 0;
ERR:
  fprintf(stderr, "error occurs at file %s, line %d, s:%s\n", fn, nlin, s);
  /* clear everything on error */
  for (i = 0; i <= n; i++) distrsum_clear(d->arr + i);
  return -1;
}

#endif /* ZCOM_DISTR__ */
#endif /* ZCOM_DISTR */

#ifdef  ZCOM_RPT
#ifndef ZCOM_RPT__
#define ZCOM_RPT__
#ifndef RPT_INF
#define RPT_INF 1e30 /* infinity temperature */
#endif

/* random perturbation temperature, continuous case */
typedef struct  {
  av_t av; /* simple average data */
  hist_t *hs; /* histogram data */
  double cnt; /* total number of data points */
} rpt_t;

INLINE rpt_t *rpt_open(double emin, double emax, double edel)
{
  rpt_t *t;

  xnew(t, 1);
  av_clear(&t->av);
  t->hs = hs_open(1, emin, emax, edel);
  t->cnt = 0;
  die_if (t->hs == NULL, "failed to initialize rpt, (%g: %g: %g)\n", emin, edel, emax);
  return t;
}

INLINE void rpt_close(rpt_t *t)
{
  hs_close(t->hs);
  free(t);
}

/* add the change */
INLINE void rpt_addw(rpt_t *t, double e, double w)
{
  av_addw(&(t->av), e, w);
  hs_add1(t->hs, 0, e, w, HIST_VERBOSE);
  t->cnt += 1;
}
#define rpt_add(t, e) rpt_addw(t, e, 1.0)

#define rpt_bet0(t) rpt_bet0x(t, 0)
#define rpt_bet1(t) rpt_bet0x(t, 0)

/* return beta = 2 < e > / < e^2 > or 2 < e > / < de^2 > */
INLINE double rpt_bet0x(const rpt_t *t, int order)
{
  double ave, var, w, we;

  if (t->cnt <= 0) return 0.0; /* no data */
  w = t->av.s / t->cnt;
  if (fabs(w - 1) < 1e-6) { /* unweighted case */
    ave = av_getave(&(t->av));
    var = av_getvar(&(t->av));
    if (order == 0)
      var += ave * ave;
    return (var > 0.) ? (2.0 * ave / var) : 0.0;
  } else { /* weighted case, e.g., for pressure */
    we = t->av.sx / t->cnt;
    if (fabs(we) < 1e-30) return 0.0;
    return (w - 1) / we;
  }
}

/* obtain a rough estimate of bet, return 1 if it's a special case */
INLINE int rpt_prepbet(const rpt_t *t, double *bet)
{
  int i, l = 0, r = 0, verbose = 0;
  const hist_t *hs = t->hs;
  double cc, cnt, sm1, sm2, e, eps = 1e-10, *h = t->hs->arr;
  double w;

  *bet = 0.;
  /* count the total number and get a rough estimate */
  if (verbose >= 2) printf("  e   #\n");
  for (cnt = sm1 = sm2 = 0, i = 0; i < hs->n; i++) {
    e = hs->xmin + (i + .5) * hs->dx;
    if ((cc = h[i]) <= 0.) continue;
    if (e < -eps) l = 1; else if (e > eps) r = 1;
    cnt += cc;
    sm1 += cc * e;
    sm2 += cc * e * e;
    if (verbose >= 2) printf("%4g %g\n", e, cc);
  }
  if (verbose >= 2) printf("\n");
  if (cnt <= 0.) return 1; /* no data */

  w = cnt / t->cnt;
  if (fabs(w - 1) < 1e-6) {
    /* one-sided, beta = +/- inf. */
    if (!l) { *bet =  RPT_INF; return 1; }
    if (!r) { *bet = -RPT_INF; return 1; }
    if (fabs(sm1) < eps * cnt) return 1; /* even distribution, beta = 0 */

    *bet = 2.0 * sm1 / sm2; /* should be an underestimate */
  } else {
    if (fabs(sm1) > 1e-30)
      *bet = log(w) * cnt / sm1;
    if (verbose) {
      printf("w %g, sm1/cnt %g, bet %g\n", w, sm1/cnt, *bet);
    }
  }

  if (verbose)
    printf("Compare: %g, %g;  %g, %g;  %g, %g\n",
        t->av.s, cnt, t->av.sx, sm1, t->av.sx2, sm2);
  return 0;
}

INLINE double rpt_refinebet(const rpt_t *t, double bet0,
  double (*func)(const rpt_t*, double, int, double*), int ord)
{
  int it, verbose = 0;
  double bet, dbet, dbmax, f, df;

  /* increase bet, such that <exp(-bet*de)>  > 1 */
  for (bet = bet0; ; bet *= 1.4)
    if ((f = (*func)(t, bet, ord, &df)) > 0) break;
  if (verbose) printf("expanded bet from %g to %g, f %g, df %g\n", bet0, bet, f, df);

  dbmax = fabs(bet*0.1); /* limit the maximal amount of updating */

  /* iteratively refine the temperature */
  for (it = 0; it <= 1000; it++) {
    f = (*func)(t, bet, ord, &df);
    if (fabs(f) < 1e-14) break;
    dbet = dblconfine(f/df, -dbmax, dbmax);
    if (verbose) printf("f %g, df %g, bet %g, dbet %g\n", f, df, bet, dbet);
    bet += dbet;  /* f should be one, derivative is -df */
  }
  if (verbose >= 2) printf("\n\n");
  return bet;
}

/* evaluate f = < (-e)^ord exp(-bet*e) - e^ord > and -df/dbet */
INLINE double rpt_getf(const rpt_t *t, double bet, int ord, double *pdf)
{
  int i, k;
  const hist_t *hs = t->hs;
  double f, cnt, e, xp, df, *h = t->hs->arr;

  for (f = df = cnt = 0., i = 0; i < hs->n; i++) {
    if (h[i] <= 0.) continue;
    e = hs->xmin + (i + .5) * hs->dx;
    xp = exp(-bet*e);
    if (ord % 2) xp = -xp;
    xp -= 1;
    for (k = 0; k < ord; k++) xp *= e;
    cnt += h[i];
    f   += h[i] * xp;
    df  += h[i] * xp * e;
  }
  f /= cnt;
  df /= cnt;
  if (pdf) *pdf = df;
  return f;
}

/* obtain the nontrivial solution of < (-e)^ord exp(-bet * e) - e^ord > = 0 */
INLINE double rpt_bet(const rpt_t *t, int ord)
{
  double bet;

  if (rpt_prepbet(t, &bet)) return bet;
  return rpt_refinebet(t, bet, rpt_getf, ord);
}

/* evaluate f = < w exp(-bet*e) > - 1 and -df/dbet */
INLINE double rpt_getfw(const rpt_t *t, double bet, int ord, double *pdf)
{
  int i;
  const hist_t *hs = t->hs;
  double f, e, xp, df, *h = t->hs->arr;

  (void) ord;
  for (f = df = 0., i = 0; i < hs->n; i++) {
    if (h[i] <= 0.) continue;
    e = hs->xmin + (i + .5) * hs->dx;
    xp = exp(-bet*e);
    f   += h[i] * xp;
    df  += h[i] * xp * e;
  }
  f = f / t->cnt - 1;
  df /= t->cnt;
  if (pdf) *pdf = df;
  return f;
}

/* obtain the nontrivial solution of < w exp(-bet * e) > = 1 */
INLINE double rpt_betw(const rpt_t *t)
{
  double bet;

  if (rpt_prepbet(t, &bet)) return bet;
  return rpt_refinebet(t, bet, rpt_getfw, 0);
}

/* evaluate f = (-bet) < min{1, exp(-bet * e)} sgn(e) |e|^ord > and -df/dbet */
INLINE double rpt_getfs(const rpt_t *t, double bet, int ord, double *pdf)
{
  int i, sgn;
  const hist_t *hs = t->hs;
  double f, cnt, e, ep, xp, df, *h = t->hs->arr;

  for (f = df = cnt = 0., i = 0; i < hs->n; i++) {
    if (h[i] <= 0.) continue;
    cnt += h[i];
    e = hs->xmin + (i + .5) * hs->dx;
    sgn = (e > 0.) ? 1 : (e < 0.) ? -1 : 0;
    ep = pow(fabs(e), ord) * sgn;
    xp = -bet*e;
    if (xp >= 0.) {
      xp   = ep;
      f   += h[i] * xp;
    } else {
      xp   = exp(xp) * ep;
      f   += h[i] * xp;
      df  += h[i] * xp * e;
    }
  }
  f *= -bet/cnt;
  df *= -bet/cnt;
  if (pdf) *pdf = df;
  return f;
}

/* obtain the nontrivial solution of < min{1, exp(-bet * e)} sgn(e) |e|^ord > = 0 */
INLINE double rpt_bets(const rpt_t *t, int ord)
{
  double bet;

  if (rpt_prepbet(t, &bet)) return bet;
  return rpt_refinebet(t, bet, rpt_getfs, ord);
}

/* evaluate f = (-bet) < exp(-bet/2 * e) sgn(e) |e|^ord > */
INLINE double rpt_getfh(const rpt_t *t, double bet, int ord, double *pdf)
{
  int i, sgn;
  const hist_t *hs = t->hs;
  double f, cnt, e, ep, xp, df, *h = t->hs->arr;

  for (f = df = cnt = 0., i = 0; i < hs->n; i++) {
    if (h[i] <= 0.) continue;
    cnt += h[i];
    e = hs->xmin + (i + .5) * hs->dx;
    sgn = (e > 0.) ? 1 : (e < 0.) ? -1 : 0;
    ep = pow(fabs(e), ord) * sgn;
    xp   = exp(-.5*bet*e) * ep;
    f   += h[i] * xp;
    df  += .5* h[i] * xp * e;
  }
  f *= -bet/cnt;
  df *= -bet/cnt;
  if (pdf) *pdf = df;
  return f;
}

/* obtain the nontrivial solution of < exp(-bet/2 * e) sgn(e) |e|^ord > = 0 */
INLINE double rpt_beth(const rpt_t *t, int ord)
{
  double bet;

  if (rpt_prepbet(t, &bet)) return bet;
  return rpt_refinebet(t, bet, rpt_getfh, ord);
}

/* write distribution to file */
INLINE int rpt_wdist(rpt_t *t, const char *fn)
{
  return hs_save(t->hs, fn, HIST_ADDAHALF);
}

#define RPTI_HASINF 0x1000

typedef struct {
  int emin, emax, edel, m;
  int *h; /* histogram */
  unsigned flags;
} rpti_t; /* perturbation temperature, integer */

INLINE rpti_t *rpti_open(int emin, int emax, int edel, unsigned flags)
{
  rpti_t *t;

  xnew(t, 1);
  die_if (emin >= emax, "emin %d >= emax %d\n", emin, emax);
  t->emin = emin;
  t->emax = emax;
  t->edel = edel;
  t->m = (emax - emin)/edel + 1;
  t->flags = flags;
  xnew(t->h, t->m + 1); /* add one for infinity */
  return t;
}

INLINE void rpti_close(rpti_t *t)
{
  free(t->h);
  free(t);
}

/* add an energy increment */
INLINE void rpti_add(rpti_t *t, int e)
{
  int ie;

  die_if (e < t->emin, "e %d smaller than emin %d\n", e, t->emin);
  ie = (e - t->emin) / t->edel;
  if (e > t->emax) {
    if (t->flags & RPTI_HASINF)
      t->h[t->m]++;
    else
      die_if (e > t->emax, "e %d larger than emax %d\n", e, t->emax);
  } else {
    t->h[ie]++;
  }
}


/* count data points */
INLINE double rpti_cnt(rpti_t *t)
{
  int i;
  double cnt = 0;
  for (i = 0; i < t->m + 1;  i++)
    cnt += t->h[i];
  return cnt;
}


/* estimate the temperature from 2 <e> / <e^2>, and 2 <e> / <De^2> */
INLINE double rpti_bet1(const rpti_t *t, double *bet0)
{
  int i;
  double e, cnt = 0, sm = 0., sm2 = 0.;

  for (i = 0; i < t->m;  i++) { /* do not count infinity at i == t->m */
    e = t->emin + i * t->edel; /* the energy change */
    cnt += t->h[i];
    sm  += t->h[i] * e;
    sm2 += t->h[i] * e * e;
  }
  if (bet0) *bet0 = 0.;
  if (cnt <= 0.) return 0.;
  sm /= cnt;
  sm2 = sm2/cnt;
  if (t->h[t->m] > 0 && sm < 0.) sm = 0.; /* has infinity */
  if (bet0) *bet0 = 2.0*sm/sm2;
  sm2 -= sm*sm;
  if (sm2 <= 0.) return (sm > 0.) ? RPT_INF : -RPT_INF;
  return 2.0*sm/sm2;
}

/* a rough estimate for bet, return 1 if it's a special case  */
INLINE int rpti_prepbet(const rpti_t *t, double *bet)
{
  int i, e;
  int hl, hr;

  /* I. get a rough estimate */
  rpti_bet1(t, bet);
  if (fabs(*bet) < 1e-14 || fabs(*bet) > .99*RPT_INF) return 1;

  /* II. check if the distribution is single-sided, which means infinite beta */
  for (hl = hr = 0, i = 0; i <= t->m; i++) {
    e = t->emin + i * t->edel;
    if (e < 0) hl += t->h[i];
    else if (e > 0) hr += t->h[i];
  }
  if (hl <= 0.) { *bet = RPT_INF; return 1; }
  if (hr <= 0.) { *bet =-RPT_INF; return 1; }
  return 0;
}

/* adjust beta until (*func) becomes 0 */
INLINE double rpti_refinebet(const rpti_t *t, double bet0,
  double (*func)(const rpti_t*, double, int, double*), int ord)
{
  double bet, dbmax, dbet, f, df;
  int it, verbose = 0;

  /* I. increase |bet|, such that <func> > 0 */
  for (bet = bet0; ; bet *= 1.4)
    if ((f = (*func)(t, bet, ord, &df)) > 0) break;
  if (verbose) printf("expanded bet from %g to %g, f %g, df %g\n", bet0, bet, f, df);

  dbmax = fabs(bet*0.1); /* limit the maximal amount of updating */

  /* II. iteratively refine the temperature */
  for (it = 0; it <= 1000; it++) {
    f = (*func)(t, bet, ord, &df);
    /* f should be one, derivative is -df */
    if (fabs(f) < 1e-14) break;
    dbet = dblconfine(f/df, -dbmax, dbmax);
    if (verbose) printf("f %g, df %g, bet %g, dbet %g\n", f, df, bet, dbet);
    bet += dbet;
  }
  if (verbose) printf("\n\n");
  return bet;
}

/* evaluate f = < (-e)^ord exp(-bet*e) - e^ord> and -df/dbet */
INLINE double rpti_getf(const rpti_t *t, double bet, int ord, double *pdf)
{
  int i, k, e;
  double f, cnt, xp, df;

  for (f = df = cnt = 0., i = 0; i < t->m; i++) {
    e = t->emin + i * t->edel;
    if (t->h[i] <= 0) continue;
    xp = exp(-bet*e);
    if (ord % 2) xp = -xp;
    xp -= 1;
    for (k = 0; k < ord; k++) xp *= e;
    cnt += t->h[i];
    f += t->h[i] * xp;
    df += t->h[i] * xp * e;
  }
  /* we should not include the infinity here */
  f /= cnt;
  df /= cnt;
  if (pdf) *pdf = df;
  return f;
}

/* estimated the temperature using the identity approach */
INLINE double rpti_bet(rpti_t *t, int ord)
{
  double bet;

  if (rpti_prepbet(t, &bet)) return bet;
  return rpti_refinebet(t, bet, rpti_getf, ord);
}

/* evaluate f = (-bet) < min{1, exp(-bet*e)} sgn(e) * |e|^ord > and -d f/d bet */
INLINE double rpti_getfs(const rpti_t *t, double bet, int ord, double *pdf)
{
  int i, e, sgn, k, ep;
  double f, cnt, xp, df;

  die_if (bet < 0. && t->h[t->m] > 0, "bet %g must be positive with inf. (%d)\n", bet, t->h[t->m]);
  for (f = df = cnt = 0., i = 0; i < t->m; i++) {
    if (t->h[i] <= 0.) continue;
    cnt += t->h[i];
    e = t->emin + i * t->edel;
    sgn = (e > 0) ? 1 : (e < 0) ? -1 : 0;
    /*  double ep = pow(fabs(e), ord) * sgn; */
    for (ep = 1, k = 0; k < ord; k++) ep *= e;
    ep = abs(ep) * sgn;
    xp = -bet*e;
    if (xp >= 0.) {
      xp     = ep;
      f     += t->h[i] * ep;
    } else {
      xp     = exp(xp) * ep;
      f     += t->h[i] * xp;
      df    += t->h[i] * xp * e;
    }
  }
  f *= -bet/cnt;
  df *= -bet/cnt;
  if (pdf) *pdf = df;
  return f;
}

/* estimated the temperature using area integrals */
INLINE double rpti_bets(rpti_t *t, int ord)
{
  double bet;

  if (rpti_prepbet(t, &bet)) return bet;
  return rpti_refinebet(t, bet, rpti_getfs, ord);
}


/* evaluate f = (-bet) < exp(-bet/2*e) sgn(e) * |e|^ord > and -d f/d bet */
INLINE double rpti_getfh(const rpti_t *t, double bet, int ord, double *pdf)
{
  int i, e, sgn, k, ep;
  double f, cnt, xp, df;

  die_if (bet < 0. && t->h[t->m] > 0, "bet %g must be positive with inf. (%d)\n", bet, t->h[t->m]);
  for (f = df = cnt = 0., i = 0; i < t->m; i++) {
    if (t->h[i] <= 0.) continue;
    cnt += t->h[i];
    e = t->emin + i * t->edel;
    sgn = (e > 0) ? 1 : (e < 0) ? -1 : 0;
    /*  double ep = pow(fabs(e), ord) * sgn; */
    for (ep = 1, k = 0; k < ord; k++) ep *= e;
    ep = abs(ep) * sgn;
    xp     = exp(-.5*bet*e) * ep;
    f     += t->h[i] * xp;
    df   += .5 * t->h[i] * xp * e;
  }
  f *= -bet/cnt;
  df *= -bet/cnt;
  if (pdf) *pdf = df;
  return f;
}

/* estimated the temperature using area integrals */
INLINE double rpti_beth(rpti_t *t, int ord)
{
  double bet;

  if (rpti_prepbet(t, &bet)) return bet;
  return rpti_refinebet(t, bet, rpti_getfh, ord);
}


/* write distribution to file */
INLINE int rpti_wdist(rpti_t *t, const char *fn)
{
  int i, i0 = -1, i1 = -1, cnt = 0;
  FILE *fp;

  for (i = 0; i < t->m; i++) {
    if (t->h[i] > 0) {
      if (i0 < 0) i0 = i;
      if (i > i1) i1 = i;
      cnt += t->h[i];
    }
  }
  /* cnt += t->h[t->m]; */

  xfopen(fp, fn, "w", return -1);
  fprintf(fp, "# 0 0 | 1 %d %d %d |\n", t->m, t->emin, t->edel);
  for (i = i0; i <= i1; i++)
    fprintf(fp, "%d %d %.8f 0\n",
      t->emin + i * t->edel, t->h[i], 1.0*t->h[i]/t->edel/cnt);
  if (t->h[i = t->m] > 0)
    fprintf(fp, "inf %d %.8f 0\n", t->h[i], 1.0*t->h[i]/t->edel/cnt);
  fclose(fp);
  return 0;
}

#endif /* ZCOM_RPT__ */
#endif /* ZCOM_RPT */

#ifdef  ZCOM_MDS
#ifndef ZCOM_MDS__
#define ZCOM_MDS__

/* multidimensional scaling */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

STRCLS real mds_min0(real *x, real *dm, int n, int dim, double tol);


/* compute force and energy */
static real mds_force(real *x, real *f, real *dm, int n, int dim)
{
  const real dmin = 1e-6f;
  int i, j, k;
  real ene = 0., dij, dref, dsc;
  real *dx, *xi, *xj, *fi, *fj;

  xnew(dx, dim);
  for (i = 0; i < n*dim; i++) f[i] = 0.;
  for (i = 0; i < n; i++) {
    xi = x + i*dim;
    fi = f + i*dim;
    for (j = i+1; j < n; j++) {
      xj = x + j*dim;
      fj = f + j*dim;
      for (dij = 0, k = 0; k < dim; k++) {
        dx[k] = xi[k] - xj[k];
        dij += dx[k]*dx[k];
      }
      dij = (real) sqrt(dij);
      dref = dm[i*n+j];
      if (dref < dmin) dref = dmin;
      dsc = dij/dref - 1;
      ene += dsc*dsc;
      /* dij is to be used in denominator in the loop, ensure its > 0 */
      if (dij < dmin) dij = dmin;
      for (k = 0; k < dim; k++) {
        dx[k] *= -(dij - dref)/(dref*dref*dij);
        fi[k] += dx[k];
        fj[k] -= dx[k];
      }
    }
  }
  free(dx);
  return ene;
}

/* make coordinates neat
 * center coordinates
 * rotate to principle coordinates */
static void mds_trim(real *x, int n, int dim)
{
  real *av, *mmt, *eig, *vec, *xi, *b;
  int i, d, d2;

  /* center the graph */
  xnew(av, dim);
  for (i = 0; i < n; i++)
    for (d = 0; d < dim; d++)
      av[d] += x[i*dim + d];
  for (d = 0; d < dim; d++) av[d] /= n;
  for (i = 0; i < n; i++)
    for (d = 0; d < dim; d++)
      x[i*dim + d] -= av[d];
  free(av);

  /* compute moments */
  xnew(mmt, dim*dim);
  xnew(eig, dim);
  xnew(vec, dim*dim);
  xnew(b, dim);
  for (i = 0; i < n; i++) {
    for (d = 0; d < dim; d++)
      for (d2 = 0; d2 < dim; d2++)
        mmt[d*dim+d2] += x[i*dim+d]*x[i*dim+d2];
  }
  eigsym(mmt, eig, vec, dim);
  for (i = 0; i < n; i++) {
    /* rotate x[i*dim .. i*dim+d-1] --> b[0 .. d-1] */
    xi = x + i*dim;
    for (d = 0; d < dim; d++) /* b = xi.vec */
      for (b[d] = 0., d2 = 0; d2 < dim; d2++)
        b[d] += xi[d2]*vec[d2*dim+d];
    for (d = 0; d < dim; d++) xi[d] = b[d];
  }
  free(b);
  free(eig);
  free(vec);
  free(mmt);
}

/* multidimensional scaling - steepest descend
 * given a distance matrix dm[n x n],
 * return best mds position x[n x dim];
 * dim is the target dimensional, e.g. 2
 * return the total discrepancy */
real mds_min0(real *x, real *dm, int n, int dim, double tol)
{
  int i, j, it, itermax = 100000, npr;
  real *f, *fp, *xp, ene, enep;
  real dt = 1e-1f;

  if (n == 1) {
    for (j = 0; j < dim; j++) x[j] = 0.;
    return 0.0;
  }
  npr = n*(n-1)/2;
  xnew(f, n*dim);
  xnew(xp, n*dim);
  xnew(fp, n*dim);
  for (i = 0; i < n*dim; i++)
    x[i] = 1.f*rand()/RAND_MAX;
  ene = mds_force(x, f, dm, n, dim);
  for (it = 0; it < itermax; it++) {
    enep = ene;
    for (i = 0; i < n*dim; i++) { /* backup */
      xp[i] = x[i];
      fp[i] = f[i];
    }
    for (i = 0; i < n*dim; i++) x[i] += f[i]*dt;
    ene = mds_force(x, f, dm, n, dim);
    if (ene > enep) {
      dt *= 0.7f;
      for (i = 0; i < n*dim; i++) { /* recover */
        x[i] = xp[i];
        f[i] = fp[i];
      }
    } else {
      if (fabs(ene-enep) < tol*npr*dt) break;
      dt *= 1.03f; /* attempt to increase time step */
    }
  }
  if (it >= itermax) {
    fprintf(stderr, "mds: failed to converge after %d iterations, %g\n",
        it, fabs(ene-enep));
  }
  mds_trim(x, n, dim);
  free(xp);
  free(f);
  free(fp);
  return ene;
}

#endif /* ZCOM_MDS__ */
#endif /* ZCOM_MDS */

#ifdef  ZCOM_PDB
#ifndef ZCOM_PDB__
#define ZCOM_PDB__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct {
  int aid; /* atom index */
  int rid; /* residue index */
  int insert; /* PDB insertion code, column 27 */
  char atnm[8];
  char resnm[8];
  char elem[4];
  real *x; /* pointer to pdbmodel_t.x */
} pdbatom_t; /* a single atom entry */

typedef struct {
  int natm; /* # of lines == # of atoms */
  int nalloc;
  int nres;
  pdbatom_t *atm; /* array of n or nalloc */
  real (*x)[3];  /* coordinate array of n or nalloc */
  const char *file;
} pdbmodel_t; /* raw data in a pdb model */


typedef struct {
  int aa;  /* index of amino acid [0, 20) */
  int nat; /* number of atoms */
  int id[32]; /* indices to the coordinate array */
  unsigned long flags;
  real *xca, *xn, *xc, *xo;
} pdbaar_t; /* amino-acid residues */

typedef struct {
  int nres;
  int natm;
  pdbaar_t *res; /* array of nres */
  real (*x)[3]; /* array of natom */
  const char *file; /* input file */
} pdbaac_t; /* amino-acid chain */

/* generic pdb model */
STRCLS pdbmodel_t *pdbm_read(const char *fname, int verbose);
INLINE int pdbm_write(pdbmodel_t *m, const char *fn);
#define pdbm_free(m) { free(m->atm); free(m->x); free(m); }

enum { PDB_CONTACT_CA, PDB_CONTACT_HEAVY, PDB_CONTACT_ALL }; /* ways of searching contacts */
STRCLS int *pdbm_contact(pdbmodel_t *pm, double rc, int level, int nearby, int dbg);

/* protein pdb */
STRCLS pdbaac_t *pdbaac_parse(pdbmodel_t *m, int verbose);
#define pdbaac_free(c) { free(c->res); free(c->x); free(c); }
#define pdbaac_x(c, i, nm) pdbaac_getx(c, i, #nm)

#define AA_CA         0x1
#define AA_N          0x2
#define AA_C          0x4
#define AA_BACKBONE   (AA_CA | AA_N | AA_C)
#define AA_MAINCHAIN  (AA_BACKBONE | AA_O)
#define AA_H2   29
#define AA_H3   30
#define AA_OXT  31

/* don't edit data in the structure, written by mkdb.py */
struct tag_pdb_aadb {
  const char *resnm;      /* residue name */
  const char *atom[25];   /* atoms */
  const char *sub[11];    /* substitutions */
  unsigned long hvflags;  /* backbone and heavy atom flags */
} pdb_aadb[20] = {
{"GLY", {"CA", "N", "C", "O", "HA1", "HA2", "H", NULL}, {"HA3", "HA1", NULL}, 0xful},
{"ALA", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "HB3", "HA", "H", NULL}, {NULL}, 0x1ful},
{"VAL", {"CA", "N", "C", "O", "CB", "HB", "CG1", "HG11", "HG12", "HG13", "CG2", "HG21", "HG22", "HG23", "HA", "H", NULL}, {NULL}, 0x45ful},
{"LEU", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "HG", "CD1", "HD11", "HD12", "HD13", "CD2", "HD21", "HD22", "HD23", "HA", "H", NULL}, {"HB3", "HB1", NULL}, 0x229ful},
{"ILE", {"CA", "N", "C", "O", "CB", "HB", "CG2", "HG21", "HG22", "HG23", "CG1", "HG11", "HG12", "CD", "HD1", "HD2", "HD3", "HA", "H", NULL}, {"HG13", "HG11", "CD1", "CD", "HD11", "HD1", "HD12", "HD2", "HD13", "HD3", NULL}, 0x245ful},
{"PRO", {"CA", "N", "C", "O", "CD", "HD1", "HD2", "CG", "HG1", "HG2", "CB", "HB1", "HB2", "HA", NULL}, {"HB3", "HB1", "HG3", "HG1", "HD3", "HD1", NULL}, 0x49ful},
{"SER", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "OG", "HG", "HA", "H", NULL}, {"HB3", "HB1", NULL}, 0x9ful},
{"THR", {"CA", "N", "C", "O", "CB", "HB", "CG2", "HG21", "HG22", "HG23", "OG1", "HG1", "HA", "H", NULL}, {NULL}, 0x45ful},
{"CYS", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "SG", "HG", "HA", "H", NULL}, {"HB3", "HB1", NULL}, 0x9ful},
{"MET", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "HG1", "HG2", "SD", "CE", "HE1", "HE2", "HE3", "HA", "H", NULL}, {"HB3", "HB1", "HG3", "HG1", NULL}, 0xc9ful},
{"ASN", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "OD1", "ND2", "HD21", "HD22", "HA", "H", NULL}, {"HB3", "HB1", NULL}, 0x39ful},
{"GLN", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "HG1", "HG2", "CD", "OE1", "NE2", "HE21", "HE22", "HA", "H", NULL}, {"HB3", "HB1", "HG3", "HG1", NULL}, 0x1c9ful},
{"ASP", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "OD1", "OD2", "HA", "H", NULL}, {"HB3", "HB1", NULL}, 0x39ful},
{"GLU", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "HG1", "HG2", "CD", "OE1", "OE2", "HA", "H", NULL}, {"HB3", "HB1", "HG3", "HG1", NULL}, 0x1c9ful},
{"LYS", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "HG1", "HG2", "CD", "HD1", "HD2", "CE", "HE1", "HE2", "NZ", "HZ1", "HZ2", "HZ3", "HA", "H", NULL}, {"HB3", "HB1", "HG3", "HG1", "HD3", "HD1", "HE3", "HE1", NULL}, 0x1249ful},
{"ARG", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "HG1", "HG2", "CD", "HD1", "HD2", "NE", "HE", "CZ", "NH1", "HH11", "HH12", "NH2", "HH21", "HH22", "HA", "H", NULL}, {"HB3", "HB1", "HG3", "HG1", "HD3", "HD1", NULL}, 0x9a49ful},
{"HIS", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "ND1", "HD1", "CE1", "HE1", "NE2", "HE2", "CD2", "HD2", "HA", "H", NULL}, {"HB3", "HB1", NULL}, 0x559ful},
{"PHE", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "CD1", "HD1", "CE1", "HE1", "CZ", "HZ", "CE2", "HE2", "CD2", "HD2", "HA", "H", NULL}, {"HB3", "HB1", NULL}, 0x1559ful},
{"TYR", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "CD1", "HD1", "CE1", "HE1", "CZ", "OH", "HH", "CE2", "HE2", "CD2", "HD2", "HA", "H", NULL}, {"HB3", "HB1", NULL}, 0x2b59ful},
{"TRP", {"CA", "N", "C", "O", "CB", "HB1", "HB2", "CG", "CD1", "HD1", "NE1", "HE1", "CE2", "CZ2", "HZ2", "CH2", "HH2", "CZ3", "HZ3", "CE3", "HE3", "CD2", "HA", "H", NULL}, {"HB3", "HB1", NULL}, 0x2ab59ful}};


INLINE int pdbaaidx(const char *res)
{
  int i;
  if (strcmp(res, "HID") == 0 || strcmp(res, "HIE") == 0 || strcmp(res, "HIP") == 0)
    res = "HIS"; /* quick fix for HIS */
  for (i = 0; i < 20; i++)
    if (strcmp(res, pdb_aadb[i].resnm) == 0)
      return i;
  return -1;
}

INLINE const char *pdbaaname(int i)
{
  die_if (i < 0 || i >= 20, "invalid amino acid id %d\n", i);
  return pdb_aadb[i].resnm;
}

/* return the index of an atom from */
INLINE int pdbaagetaid(int aa, const char *atnm)
{
  int k;
  for (k = 0; pdb_aadb[aa].atom[k]; k++)
    if (strcmp(pdb_aadb[aa].atom[k], atnm) == 0) return k;
  return -1;
}

/* return the global atom index */
INLINE int pdbaar_getaid(pdbaar_t *r, const char *atnm)
  { int topid = pdbaagetaid(r->aa, atnm); return (topid < 0) ? -1 : r->id[topid]; }
INLINE int pdbaac_getaid(pdbaac_t *c, int i, const char *atnm)
  { return pdbaar_getaid(c->res + i, atnm); }
/* return coordinates */
INLINE real *pdbaac_getx(pdbaac_t *c, int i, const char *atnm)
  { int id = pdbaac_getaid(c, i, atnm); return (id < 0) ? NULL : c->x[id]; }

/* format atom name, out could be equal to atnm
 * style 0: atom name first, e.g., "HE21", "CB", or style 1: "1HE2" or " CB " */
INLINE char *pdbm_fmtatom(char *out, const char *inp, int style)
{
  size_t n, i;
  char c, cn, atnm[5];
  const char *p;

  die_if (style > 2 || style < 0, "bad format style %d\n", style);

  /* copy inp to a buffer without space */
  for (p = inp; *p == ' '; p++) ;
  for (n = 0; n < 4 && p[n] && p[n] != ' '; n++) atnm[n] = p[n];
  atnm[n] = '\0';
  die_if (n == 4 && p[n] && p[n] != ' ', "bad input atom name [%s]\n", atnm);

  if (style <= 1) { /* style 0: "H", "CA", "HE21", style 1: " H", " CA", "HE21" */
    if (n == 4) {
      c = atnm[0];
      if (isdigit(c)) { /* rotate the string, such that 1HE2 --> HE21; */
        for (i = 1; i < n; i++) out[i-1] = atnm[i];
        out[n-1] = c;
        out[n] = '\0';
      } else strcpy(out, atnm);
    } else { /* n <= 3 */
      if (style == 0) strcpy(out, atnm);
      else { out[0] = ' '; strcpy(out+1, atnm); }
    }
  } else if (style == 2) { /* style 2: " H", " CA", "1HE2" */
    if (n == 4) {
      c = atnm[0];
      cn = atnm[n - 1];
      if (isalpha(c) && isdigit(cn)) { /* HE21 --> 1HE2 */
        for (i = n-1; i > 0; i--) out[i] = atnm[i-1];
        out[0] = cn;
        out[n] = '\0';
      } else strcpy(out, atnm);
    } else { /* n <= 3 */
      out[0] = ' '; strcpy(out+1, atnm);
    }
  }
  return out;
}


/* read raw atom data from pdb */
static pdbmodel_t *pdbm_readpdb(const char *fname)
{
  const int BSIZ = 256;
  FILE *fp;
  pdbmodel_t *m;
  pdbatom_t *atm;
  int i, ir;
  char s[256], resnm[8] = "";
  float x[3];

  xfopen(fp, fname, "r", return NULL);
  xnew(m, 1);
  m->natm = 0;
  m->nalloc = BSIZ;
  m->file = fname;
  xnew(m->atm, m->nalloc);
  xnew(m->x,   m->nalloc);
  /* read through pdb */
  ir = -1;
  while (fgets(s, sizeof s, fp)) {
    if (strncmp(s, "TER", 3) == 0 ||
        strncmp(s, "ENDMDL", 6) == 0 ||
        strncmp(s, "END", 3) == 0)
      break;
    if (strncmp(s, "ATOM ", 5) != 0)
      continue;
    if (s[16] != ' ' && s[16] != 'A') /* discard alternative position */
      continue;
    i = m->natm;
    if (i >= m->nalloc) {
      m->nalloc += BSIZ;
      xrenew(m->atm, m->nalloc);
      xrenew(m->x,   m->nalloc);
    }
    atm = m->atm + i;
    atm->aid = i;
    atm->insert = s[26];

    /* atom name */
    strip( substr(atm->atnm, s, 12, 4) );
    pdbm_fmtatom(atm->atnm, atm->atnm, 0);
    /* residue name */
    strip( substr(atm->resnm, s, 17, 3) );
    /* residue number */
    sscanf(s+22, "%d", &(atm->rid));
    if (ir == atm->rid && resnm[0] && strcmp(atm->resnm, resnm) != 0) {
      fprintf(stderr, "atom %d, %s, residue %d conflicts %s --> %s, file %s\n",
          i, atm->atnm, ir, resnm, atm->resnm, fname);
    }
    strcpy(resnm, atm->resnm);
    ir = atm->rid;
    /* coordinates */
    sscanf(s+30, "%f%f%f", x, x+1, x+2);
    rv3_make(m->x[i], x[0], x[1], x[2]);
    /* element name */
    atm->elem[0] = '\0';
    if (strlen(s) >= 78)
      strip( substr(atm->elem, s, 76, 2) );
    if (atm->elem[0] == '\0') { /* guess */
      atm->elem[0] = atm->atnm[0];
      atm->elem[1] = '\0';
    }
    m->natm++;
  }
  for (i = 0; i < m->natm; i++) /* set atom x */
    m->atm[i].x = m->x[i];
  fclose(fp);
  return m;
}

/* read from GROMACS .gro format */
static pdbmodel_t *pdbm_readgro(const char *fname)
{
  FILE *fp;
  pdbmodel_t *m;
  pdbatom_t *atm;
  int i, ir;
  char s[256], resnm[8] = "";
  float x[3];

  xfopen(fp, fname, "r", return NULL);
  xnew(m, 1);
  if (fgets(s, sizeof s, fp) == NULL) { /* title line */
    fprintf(stderr, "cannot read the first line of %s\n", fname);
    goto ERR;
  }
  if (fgets(s, sizeof s, fp) == NULL) { /* number of particles */
    fprintf(stderr, "cannot read the second line of %s\n", fname);
    goto ERR;
  }
  if (1 != sscanf(s, "%d", &m->natm)) {
    fprintf(stderr, "no # of atoms, %s\n", fname);
    goto ERR;
  }
  m->nalloc = m->natm;
  m->file = fname;
  xnew(m->atm, m->nalloc);
  xnew(m->x,   m->nalloc);
  ir = -1;
  for (i = 0; i < m->natm; i++) {
    if (fgets(s, sizeof s, fp) == NULL) {
      fprintf(stderr, "unable to read atom %d\n", i+1);
      goto ERR;
    }
    atm = m->atm + i;
    atm->aid = i;

    /* atom name */
    strip( substr(atm->atnm, s, 10, 5) );
    pdbm_fmtatom(atm->atnm, atm->atnm, 0);
    /* residue name */
    strip( substr(atm->resnm, s, 5, 5) );
    /* residue number */
    sscanf(s, "%d", &atm->rid);
    if (ir == atm->rid && resnm[0] && strcmp(atm->resnm, resnm) != 0) {
      fprintf(stderr, "atom %d, %s, residue %d conflicts %s --> %s, file %s\n",
          i, atm->atnm, ir, resnm, atm->resnm, fname);
    }
    strcpy(resnm, atm->resnm);
    ir = atm->rid;
    /* coordinates */
    sscanf(s+20, "%f%f%f", x, x+1, x+2);
    rv3_smul( rv3_make(m->x[i], x[0], x[1], x[2]), 10.0f); /* nm --> A */
    atm->x = m->x[i];
    /* guess element name */
    atm->elem[0] = atm->atnm[0];
    atm->elem[1] = '\0';
  }
  fclose(fp);
  return m;
ERR:
  free(m);
  fclose(fp);
  return NULL;
}

/* read pdb */
pdbmodel_t *pdbm_read(const char *fname, int verbose)
{
  int i, j, ir, iro;
  pdbmodel_t *m;
  const char *p;

  p = strrchr(fname, '.');
  if (p != NULL && strcmp(p + 1, "gro") == 0) {
    m = pdbm_readgro(fname);
  } else {
    m = pdbm_readpdb(fname);
  }
  if (m == NULL) return NULL;

  if (verbose)
    printf("%s has %d residues\n", fname, m->atm[m->natm-1].rid);

  /* sort residue indices */
  for (ir = 0, i = 0; i < m->natm; ir++) {
    iro = m->atm[i].rid;
    for (j = i; j < m->natm && m->atm[j].rid == iro &&
        strcmp(m->atm[j].resnm, m->atm[i].resnm) == 0; j++) {
      m->atm[j].rid = ir;
    }
    if (verbose >= 2)
      printf("atoms %d to %d --> residue %s, %d (%d)\n",
        i+1, j, m->atm[i].resnm, iro, ir+1);
    i = j;
  }
  m->nres = ir;

  if (verbose >= 3)
    for (i = 0; i < m->natm; i++) {
      pdbatom_t *atm = m->atm + i;
      printf("%4d %4s %4d %4s %8.3f %8.3f %8.3f\n",
          atm->aid+1, atm->atnm, atm->rid+1, atm->resnm,
          atm->x[0], atm->x[1], atm->x[2]);
    }
  return m;
}

/* write data to file fn */
INLINE int pdbm_write(pdbmodel_t *m, const char *fn)
{
  int i, aid, ATMFMT = 1;
  char atnm[8] = "";
  FILE *fp;
  pdbatom_t *atm;
  real *x;

  if (m->natm <= 0) return 1;
  xfopen(fp, fn, "w", return 1);
  for (aid = 1, i = 0; i < m->natm; i++) {
    atm = m->atm + i;
    pdbm_fmtatom(atnm, atm->atnm, ATMFMT);
    x = m->x[i];
    fprintf(fp, "ATOM  %5d %-4s %-4sA%4d    %8.3f%8.3f%8.3f  1.00  0.00          %2s  \n",
        aid++, atnm, atm->resnm, atm->rid+1, x[0], x[1], x[2], atm->elem);
  }
  fprintf(fp, "TER   %5d      %-4sA%4d%54s\n", m->natm+1, atm->resnm, atm->rid+1, "");
  fprintf(fp, "END%77s\n", " ");
  fclose(fp);
  return 0;
}

INLINE int iscontactatom(int level, const char *atnm)
{
  if (level == PDB_CONTACT_ALL) return 1;
  else if (level == PDB_CONTACT_HEAVY) return atnm[0] != 'H';
  else return strcmp(atnm, "CA") == 0; /* PDB_CONTACT_CA */
}

/* return a nres x nres matrix that defines if two residues are contacts
 * a pair is considered as a contact only if the distance of two
 * specific-type atoms from the two residues is less than rc
 * 'level' : types of atoms to be used in defining atoms
 *           PDB_CONTACT_CA:      only alpha carbon atoms
 *           PDB_CONTACT_HEAVY:   non-hydrogen atoms
 *           PDB_CONTACT_ALL:     include hydrogen atoms
 * 'nearby': # of adjacent resdiues to be excluded from the list
 * */
int *pdbm_contact(pdbmodel_t *pm, double rc, int level, int nearby, int dbg)
{
  int ir, jr, i, j, im, jm, ica, jca, n = pm->natm, nres = pm->nres, ct, cnt = 0;
  pdbatom_t *atm = pm->atm;
  real d, dmin, dca;
  int *iscont;

  xnew(iscont, nres*nres);
  for (ir = 0; ir < nres; ir++) {
    for (jr = ir + nearby + 1; jr < nres; jr++) {
      /* compute the minimal distance between atoms
       * in residues `ir' and `jr' of certain types */
      dmin = 1e9; dca = 0; im = jm = -1;
      /* loop through atoms to collect those of residue id `ir'
       * the loop is inefficient, but this function is rarely called */
      for (i = 0; i < n; i++) {
        if (atm[i].rid != ir) continue;
        if (!iscontactatom(level, atm[i].atnm)) continue;
        ica = iscontactatom(PDB_CONTACT_CA, atm[i].atnm);
        /* loop through atoms to collect those of residue id `jr' */
        for (j = 0; j < n; j++) {
          if (atm[j].rid != jr) continue;
          if (!iscontactatom(level, atm[j].atnm)) continue;
          jca = iscontactatom(PDB_CONTACT_CA, atm[j].atnm);
          d = rv3_dist(atm[i].x, atm[j].x);
          if (d < dmin) { dmin = d; im = i; jm = j; }
          if (ica && jca) dca = d; /* CA distance */
        }
      }
      iscont[ir*nres+jr] = iscont[jr*nres+ir] = ct = (dmin < rc) ? 1 : 0;
      if (ct) cnt++;
      if (dbg && ct) /* print decision */
        printf("[%3d] %s%-3d and %s%-3d: dca %6.3fA dmin %6.3fA (%s:%d, %s:%d)\n",
          cnt, atm[im].resnm, ir+1, atm[jm].resnm, jr+1, dca, dmin,
          atm[im].atnm, im+1, atm[jm].atnm, jm+1);
    }
  }
  return iscont;
}

/* get amino acid chain by parsing pdbmodel_t m */
pdbaac_t *pdbaac_parse(pdbmodel_t *m, int verbose)
{
  pdbatom_t *atm;
  pdbaac_t *c;
  pdbaar_t *r;
  int i, k, match;
  unsigned long hvflags;

  xnew(c, 1);
  c->nres = m->nres;
  c->natm = m->natm;
  xnew(c->res, c->nres);
  xnew(c->x, m->natm);
  memcpy(c->x, m->x, sizeof(*(c->x))*m->natm); /* copy coordinates */
  c->file = m->file;

  for (i = 0; i < m->natm; i++) {
    atm = m->atm + i;
    r = c->res + atm->rid;
    r->aa = pdbaaidx(atm->resnm);
    if (r->aa < 0) {
      fprintf(stderr, "unknown amino acid residue %d/%d[%s]\n",
          atm->rid, m->nres, atm->resnm);
      goto ERR;
    }

    /* match index */
    match = 0;
    for (k = 0; pdb_aadb[r->aa].atom[k] != NULL; k++)
      if (strcmp(atm->atnm, pdb_aadb[r->aa].atom[k]) == 0) {
        r->id[k] = i;
        r->flags |= 1ul << k;
        match = 1;
        break;
      }
    if (!match) { /* check terminals */
#define AAMAPIT_(lead, str, nm) lead (strcmp(atm->atnm, str) == 0) \
    { int aid = pdbaagetaid(r->aa, #nm); r->id[aid] = i; r->flags |= 1ul << (unsigned long) aid; match = 1; }
#define AAMATCH_(lead, str, nm) lead (strcmp(atm->atnm, str) == 0) \
    { r->id[AA_ ## nm] = i; r->flags |= 1ul << AA_##nm; match = 1; }
      AAMAPIT_(if, "H1", H)
      AAMATCH_(else if, "H2",   H2)
      AAMATCH_(else if, "H3",   H3)
      AAMATCH_(else if, "OXT",  OXT)
      AAMAPIT_(else if, "OC1",  O)
      AAMATCH_(else if, "OC2",  OXT)
      AAMAPIT_(else if, "O1",   O)
      AAMATCH_(else if, "O2",   OXT)
      else { /* check substitutions */
        for (k = 0; pdb_aadb[r->aa].sub[k] != NULL; k += 2)
          if (strcmp(atm->atnm, pdb_aadb[r->aa].sub[k]) == 0) {
            int aid = pdbaagetaid(r->aa, pdb_aadb[r->aa].sub[k+1]);
            r->id[aid] = i;
            r->flags |= 1ul << (unsigned) aid;
            match = 1;
            break;
          }
      }
    }
    if (!match)
      printf("unknown atom %s:%d res %s%d\n", atm->atnm, i+1, atm->resnm, atm->rid+1);
  }

#define pdbaac_pmiss_(xflags) { \
  unsigned long miss = (r->flags ^ xflags) & xflags; \
  fprintf(stderr, "file %s, residue %s%d misses atom(s): ", c->file, pdbaaname(r->aa), i+1); \
  for (k = 0; pdb_aadb[r->aa].atom[k] != NULL; k++) { \
    if (miss & (1ul << k)) fprintf(stderr, "%s ", pdb_aadb[r->aa].atom[k]); } \
  fprintf(stderr, "\n"); }

  /* checking integrity */
  for (i = 0; i < c->nres; i++) {
    r = c->res + i;
    hvflags = pdb_aadb[r->aa].hvflags;
    if ((r->flags & AA_BACKBONE) != AA_BACKBONE) {
      pdbaac_pmiss_(AA_BACKBONE);
      goto ERR;
    } else if ((r->flags & hvflags) != hvflags) {
      pdbaac_pmiss_(hvflags);
    }
    r->xn  = pdbaac_x(c, i, N);
    r->xca = pdbaac_x(c, i, CA);
    r->xc  = pdbaac_x(c, i, C);
    r->xo  = pdbaac_x(c, i, O);
  }
  /* check bond-length, assume backbone are present */
  for (i = 0; i < c->nres; i++) {
    real x;
    r = c->res + i;
    if (i > 0) {
      x = rv3_dist(pdbaac_x(c, i-1, C), r->xn);
      if (x < .3 || x > 2.3) {
        if (verbose) {
          const char *aap = pdbaaname(c->res[i-1].aa), *aa = pdbaaname(r->aa);
          fprintf(stderr, "%s: C-N bond between %d (%s) and %d (%s) is broken %g, insert break\n",
            c->file, i, aap, i+1, aa, x);
          goto ERR;
        }
      }
    }
    x = rv3_dist(r->xn, r->xca);
    if (x < .4 || x > 3.0) {
      if (verbose) {
        fprintf(stderr, "%s: N-CA bond of residue %d (%s) is broken %g\n",
          c->file, i+1, pdbaaname(r->aa), x);
        fprintf(stderr, "N : %8.3f %8.3f %8.3f\n", r->xn[0], r->xn[1], r->xn[2]);
        fprintf(stderr, "CA: %8.3f %8.3f %8.3f\n", r->xca[0], r->xca[1], r->xca[2]);
      }
      goto ERR;
    }
    x = rv3_dist(r->xca, r->xc);
    if (x < .4 || x > 3.0) {
      if (verbose) {
        fprintf(stderr, "%s: CA-C bond of residue %d (%s) is broken %g\n",
          c->file, i+1, pdbaaname(r->aa), x);
        fprintf(stderr, "CA: %8.3f %8.3f %8.3f\n", r->xca[0], r->xca[1], r->xca[2]);
        fprintf(stderr, "C : %8.3f %8.3f %8.3f\n", r->xc[0], r->xc[1], r->xc[2]);
      }
      goto ERR;
    }
  }
  if (verbose >= 3) {
    for (i = 0; i < c->nres; i++)
      printf("%4d: %s\n", i+1, pdbaaname(c->res[i].aa));
  }
  return c;
ERR:
  if (c->res) free(c->res);
  if (c->x) free(c->x);
  free(c);
  return NULL;
}

/* parse helices, return the number of helices `nse'
 * (*pse)[0..nse*2 - 1] are start and finishing indices of helices */
INLINE int pdbaac_parsehelices(pdbaac_t *c, int **pse)
{
  int i, nse = 0, is, it, nres = c->nres;
  int aa, aagly, aapro;
  int *se, *ishx, quin[5];
  double phi, psi;

  /* A. make an array of nres, identify if each residue is helix */
  xnew(ishx, nres);
  ishx[0] = ishx[nres-1] = 0;
  for (i = 1; i < nres-1; i++) {
    /* make local quintuple */
    quin[0] = pdbaac_getaid(c, i-1, "C");  die_if(quin[0] < 0, "no C  of %d\n", i-1);
    quin[1] = pdbaac_getaid(c, i,   "N");  die_if(quin[1] < 0, "no N  of %d\n", i);
    quin[2] = pdbaac_getaid(c, i,   "CA"); die_if(quin[2] < 0, "no CA of %d\n", i);
    quin[3] = pdbaac_getaid(c, i,   "C");  die_if(quin[3] < 0, "no C  of %d\n", i);
    quin[4] = pdbaac_getaid(c, i+1, "N");  die_if(quin[4] < 0, "no N  of %d\n", i+1);
    phi = rv3_calcdihv(NULL, c->x, quin, 0);
    psi = rv3_calcdihv(NULL, c->x, quin+1, 0);
    ishx[i] = (phi < 0 && psi > -100*M_PI/180 && psi < 80*M_PI/180);
  }

  /* B. searching for segments
   * make 2*pro->ngrp for start/end of each segment
   * range of segment k is se[2*k] <= id < se[2*k+1] */
  xnew(se, 2);
  aagly = pdbaaidx("GLY");
  aapro = pdbaaidx("PRO");
  for (i = 0, is = 0; i < nres; ) { /* try to find the helices */
    while (i < nres && !ishx[i]) i++;
    if (i >= nres) break; /* no more helices */
    is = i;
    while (ishx[i] && i < nres) i++;
    it = i;
    for (; is < it; is++) { /* skip terminal GLY and PRO */
      aa = c->res[is].aa;
      if (aa != aagly && aa != aapro)  break;
    }
    for (; it > is; it--) {
      aa = c->res[it - 1].aa;
      if (aa != aagly && aa != aapro) break;
    }
    if (it - is >= 4) { /* successfully find a helical segment */
      xrenew(se, 2*(nse+1));
      se[2*nse] = is;
      se[2*nse+1] = it;
      nse++;
    } else { } /* just let go, don't increment nse */
  }
  free(ishx);
  *pse = se;
  return nse;
}

#endif /* ZCOM_PDB__ */
#endif /* ZCOM_PDB */

#ifdef  ZCOM_CLUS
#ifndef ZCOM_CLUS__
#define ZCOM_CLUS__
/* abstract function for cluster analysis using Monte Carlo sampling
 * given the distance matrix, we give out a cluster*/
#include <stdio.h>
#include <stdlib.h>

typedef struct { /* structure of a single cluster */
  int *idx;
  int cnt; /* number of points in this cluster, size of idx */
  int cap; /* capacity for holding */
  int centroid; /* centroid */
  double smdis; /* sum of pair distances, wi*wj*dij */
  double smwt;  /* sum of weights, wi */
  double x, y;  /* multidimensional scaling */
} clus_t;

typedef struct { /* clsys: array of all clusters */
  int np;       /* # of points */
  int nc;       /* # of clusters */
  float **mat;  /* distance matrix i < j */
  double *wt;   /* weight */
  double wtot;  /* total weight */
  clus_t *c;    /* cluster array */
  double ene;   /* energy of all clusters */
  /* auxiliary variables */
  double mu0;   /* input mu */
  double muw;   /* penalty of adding a cluster the actual one
                   the weighted version, 0.5 * mu0  */
  double bet;   /* inverse temperature */
  int acc; /* accepted metropolis moves */
  int iter;  /* iteration index */
} clsys_t;


#define CLUS_METROPOLIS 0x00
#define CLUS_VERBOSE    0x01
#define CLUS_VVERBOSE   0x02
#define CLUS_HEATBATH   0x10
#define CLUS_CHECK      0x20
#define CLUS_NOGIANT    0x100 /* ignore a single-cluster configuration during sampling */

STRCLS clsys_t *cls_init(float **mat, double *wt, int n, double mu);
STRCLS void cls_free(clsys_t *cls, int matwt);
STRCLS void cls_changemu(clsys_t *cls, double mu);
STRCLS clsys_t *cls_read(const char *fn, void (*rhead)(FILE *, clsys_t *, void *data), void *data);
STRCLS int cls_write(clsys_t *cls, const char *fn,
    void (*whead)(FILE *, const clsys_t *cls, const void *data), const void *data, int ver);
STRCLS clsys_t *cls_anneal(clsys_t *cls, int itmax, int method, double bet0, double bet1);
STRCLS clsys_t *cls_zalgo(clsys_t *cls, int itmax, int method,
    double bet0, double bet1, int nbet, int nstmin, int verbose);


/* allocate space for the distance matrix */
static float **dismat_alloc(int n)
{
  float **mat, *larr;
  int npr, offset, i;

  xnew(mat, n);
  npr = (n+1)*n/2;
  xnew(larr, npr);
  for (offset = 0, i = 0; i < n; i++) {
    mat[i] = larr + offset - i;
    mat[i][i] = 0.;
    offset += n - i;
  }
  return mat;
}

/* free the distance matrix */
static void dismat_free(float **mat)
{
  free(mat[0]);
  free(mat);
}

int CLIDBLOCKSIZ = 16; /* block size for allocating clus.idx */

/* initialize a cluster of a single point i */
static void cl_init(clus_t *cl, int i, double wt)
{
  cl->cnt = 1;
  cl->cap = CLIDBLOCKSIZ;
  xnew(cl->idx, cl->cap);
  cl->idx[0] = i;
  cl->smdis = 0.;
  cl->smwt  = wt;
}

static void cl_free(clus_t *cl)
{
  if (cl->cnt > 0) {
    free(cl->idx);
    memset(cl, 0, sizeof(*cl));
  }
}

/* duplicate information in cluster b to cluster a */
static void cl_copy(clus_t *a, const clus_t *b)
{
  int k;

  a->cnt = b->cnt;
  a->cap = a->cnt;
  xrenew(a->idx, a->cap);
  for (k = 0; k < a->cnt; k++)
    a->idx[k] = b->idx[k];
  a->smdis = b->smdis;
  a->smwt  = b->smwt;
  a->centroid = b->centroid;
}

/* add a new point `i' into the cluster `cl'
 * update deldis and delwt */
static void cl_padd(clus_t *cl, int i, double deldis, double delwt)
{
  cl->cnt++;
  if (cl->cnt > cl->cap) {
    cl->cap += CLIDBLOCKSIZ;
    xrenew(cl->idx, cl->cap);
  }
  cl->idx[cl->cnt - 1] = i;
  cl->smdis += deldis;
  cl->smwt  += delwt;
}

/* remove the kth item in cluster 'cl', the energy change de  */
static void cl_premove(clus_t *cl, int k, double deldis, double delwt)
{
  die_if (k >= cl->cnt, "index error %d >= %d\n", k, cl->cnt);
  cl->cnt--;
  if (k < cl->cnt)
    cl->idx[k] = cl->idx[cl->cnt];
  cl->smdis += deldis;
  cl->smwt  += delwt;
}

#define cls_getwt(cls, i)  (cls->wt ? cls->wt[i] : 1.)

/* init. an cluster configuration from an nxn distance matrix */
clsys_t *cls_init(float **mat, double *wt, int n, double mu)
{
  clsys_t *cls;
  int ic;
  double wi;

  xnew(cls, 1);
  cls->np = n;
  cls->nc = n;
  cls->mat = mat;
  cls->wt  = wt;
  xnew(cls->c, cls->nc);
  cls->bet = 0.0;
  cls->wtot = 0.;
  for (ic = 0; ic < cls->nc; ic++) {
    wi = cls_getwt(cls, ic);
    cl_init(cls->c + ic, ic, wi);
    cls->wtot += wi;
  }
  cls->mu0 = mu;
  cls->muw = .5*mu*cls->wtot;
  cls->ene = cls->nc*cls->muw;
  return cls;
}

/* copy b to a, assume a is made by cls_init */
static void cls_copy(clsys_t *a, const clsys_t *b)
{
  int ic;
  a->np = b->np;
  a->nc = b->nc;
  a->mat = b->mat;
  a->wt = b->wt;
  a->bet = b->bet;
  a->wtot = b->wtot;
  a->mu0 = b->mu0;
  a->muw = b->muw;
  a->ene = b->ene;
  for (ic = 0; ic < a->nc; ic++) {
    cl_copy(a->c + ic, b->c + ic);
  }
}

/* find point ip in clusters,
 * return cluster id, *pk is ip's index in the cluster */
static int cls_find(clsys_t *cls, int ip, int *k)
{
  clus_t *ci;
  int ic;

  for (ic = 0; ic < cls->nc; ic++) {
    ci = cls->c + ic;
    for (*k = 0; *k < ci->cnt; (*k)++) {
      if (ip == ci->idx[*k])
        return ic;
    }
  }
  die_if (1, "cannot find point ip %d, np %d, nc %d\n", ip, cls->np, cls->nc);
  return -1;
}

/* add a new cluster with a single point */
static void cls_cadd(clsys_t *cls, int i)
{
  double wt;
  ++cls->nc;
  die_if (cls->nc > cls->np, "too many clusters %d > %d\n", cls->nc, cls->np);
  wt = cls_getwt(cls, i);
  cl_init(cls->c + cls->nc - 1, i, wt);
}

/* remove cluster ic */
static void cls_cremove(clsys_t *cls, int ic)
{
  die_if (ic >= cls->nc, "invalid cluster %d >= %d\n", ic, cls->nc);
  cls->nc--;
  if (ic < cls->nc)
    cl_copy(cls->c + ic, cls->c + cls->nc);
  cl_free(cls->c + cls->nc);
}

void cls_free(clsys_t *cls, int matwt)
{
  int ic;
  for (ic = 0; ic < cls->np; ic++)
    cl_free(cls->c + ic);
  free(cls->c);
  if (matwt) {
    if (cls->wt != NULL) free(cls->wt);
    dismat_free(cls->mat);
  }
  memset(cls, 0, sizeof(*cls));
  free(cls);
}

/* compute distance between two points i and j */
INLINE double cls_pdis(clsys_t *cls, int i, int j)
{
  die_if (i == j || i < 0 || i >= cls->np || j < 0 || j >= cls->np,
      "bad index  i: %d, j: %d, np: %g", i, j, cls->np);
  if (i < j) return cls->mat[i][j]; else return cls->mat[j][i];
}

/* check cluster configuration */
static void cls_check(clsys_t *cls, int acctype)
{
  clus_t *cl;
  int *in, ic, k, ip;

  xnew(in, cls->np);
  for (ic = 0; ic < cls->nc; ic++) {
    cl = cls->c + ic;
    die_if (cl->cnt <= 0, "invalid size %d, %d\n", ic, cl->cnt);
    for (k = 0; k < cl->cnt; k++) {
      ip = cl->idx[k];
      die_if (ip >= cls->np || in[ip], "type %d/%d: invalid ip %d/%d", acctype, cls->iter, ip, cls->np);
      in[ip] = 1;
    }
  }
  free(in);
}

/* comparison of two integers */
static int cls_cmpint_(const void *a, const void *b)
{
  return (*(const int *)a) - (*(const int *)b);
}

/* sort 1) indices in a cluster, 2) clusters by size */
static void cls_sort(clsys_t *cls)
{
  int ic, jc, im;
  clus_t *cl, cbuf;
  double wm;

  /* sort indices */
  for (ic = 0; ic < cls->nc; ic++) {
    cl = cls->c + ic;
    qsort(cl->idx, cl->cnt, sizeof(int), &cls_cmpint_);
  }
  /* sort clusters by size */
  for (ic = 0; ic < cls->nc - 1; ic++) {
    wm = cls->c[ic].smwt;
    for (im = ic, jc = ic + 1; jc  < cls->nc; jc++) {
      if (cls->c[jc].smwt > wm) {
        im = jc;
        wm = cls->c[jc].smwt;
      }
    }
    if (im != ic) {
      memcpy(&cbuf, cls->c + ic, sizeof(clus_t));
      memcpy(cls->c + ic, cls->c + im, sizeof(clus_t));
      memcpy(cls->c + im, &cbuf, sizeof(clus_t));
    }
  }
}

/* compute centroid */
static void cls_centroid(clsys_t *cls)
{
  int ic, i, ip, j, jp, imin;
  double dsm, wj, dmin;
  clus_t *cl;

  for (ic = 0; ic < cls->nc; ic++) {
    /* compute the centroid of cluster cl
     * closest to all other points */
    cl = cls->c + ic;
    if (cl->cnt <= 1) {
      cl->centroid = 0;
      continue;
    }
    for (dmin = 1e9, imin = -1, i = 0; i < cl->cnt; i++) {
      ip = cl->idx[i];
      /* compute distance from others */
      dsm = 0.;
      for (j = 0; j < cl->cnt; j++) {
        if (i == j) continue;
        jp = cl->idx[j];
        wj = cls_getwt(cls, jp);
        dsm += wj * cls_pdis(cls, ip, jp);
      }
      if (dsm < dmin) {
        imin = i;
        dmin = dsm;
      }
    }
    cl->centroid = imin;
  }
}

/* energy of a single cluster, i.e., its average distance */
static double cls_ene1(clsys_t *cls, int ic, unsigned flags)
{
  clus_t *cl = cls->c + ic;
  int k1, k2, ip, jp;
  double dis, ene, wi, wj, wtot;

  die_if(cl->cnt <= 0, "invalid cluster, n(%d) = %d\n", ic, cl->cnt);
  if (cl->cnt == 1) {
    cl->smdis = 0;
    cl->smwt = cls_getwt(cls, cl->idx[0]);
    return 0.;
  }
  for (dis = 0., wtot = 0., k1 = 0; k1 < cl->cnt; k1++) {
    ip = cl->idx[k1];
    wi = cls_getwt(cls, ip);
    wtot += wi;
    for (k2 = k1+1; k2 < cl->cnt; k2++) {
      jp = cl->idx[k2];
      wj = cls_getwt(cls, jp);
      die_if (ip == jp, "same ip jp %d\n", ip);
      dis += wi*wj*cls_pdis(cls, ip, jp);
      if (flags & CLUS_VVERBOSE)
        printf("clus %d: ip %d %g jp %d %g dis %g\n", ic, ip, wi, jp, wj, dis);
    }
  }
  if (flags & CLUS_CHECK) {
    die_if (fabs(cl->smdis - dis) > 1e-2,
      "corruption distance sum %d, %g, vs. %g\n", ic, cl->smdis, dis);
  }
  cl->smdis = dis;
  cl->smwt  = wtot;
  ene = dis/wtot;
  if (flags & CLUS_VERBOSE)
    printf("ENE: clus %d: %d points, E %g = %g/%g\n", ic, cl->cnt, ene, dis, wtot);
  return ene;
}

/* energy of all clusters */
static double cls_ene(clsys_t *cls, unsigned flags)
{
  int ic;
  double ene;

  ene = cls->nc * cls->muw;
  for (ic = 0; ic < cls->nc; ic++) {
    ene += cls_ene1(cls, ic, flags);
  }
  if (flags & CLUS_VERBOSE)
    printf("ENE: %d clusters, ene = %g\n", cls->nc, ene);
  return ene;
}

/* change mu of the cluster  */
void cls_changemu(clsys_t *cls, double mu)
{
  cls->mu0 = mu;
  cls->muw = .5 * mu * cls->wtot;
  cls->ene = cls_ene(cls, 0); /* NOTE: to improve */
}

/* merge a single-point cluster i to cluster j */
static void cls_merge(clsys_t *cls, int i, int j, double disj, double dene)
{
  clus_t *ci = cls->c + i;
  int ip;
  double wi;

/*
  printf("cls_merge, consistency check, ene %g vs %g\n", cls->ene, cls_ene(cls, 0));
*/
  die_if (ci->cnt != 1, "cluster %d is not alone %d\n", i, ci->cnt);
  ip = ci->idx[0];
  wi = cls_getwt(cls, ip);
  cl_padd(cls->c + j, ip, disj, wi); /* add ip to cluster j */
/*
  printf("cls_merge, before removal of cluster i %d, wi %g, ene %g vs. %g\n", i, wi, cls->ene, cls_ene(cls, 0));
*/
  cls_cremove(cls, i); /* remove cluster i, done after cl_padd() to avoid messing up with cluster index */
/*
  printf("cls_merge, before ene %g, dene %g, after should be %g, actually %g\n", cls->ene, dene, cls->ene + dene, cls_ene(cls, 0));
*/
  cls->ene += dene;
}

/* remove the kth point in cluster i, and add it to cluster j */
static void cls_transfer(clsys_t *cls, int i, int k, int j,
    double disi, double disj, double dene)
{
  clus_t *ci = cls->c + i;
  int ip;
  double wi;

  die_if (ci->cnt <= 1, "cluster %d is alone %d\n", i, ci->cnt);
  die_if (k < 0 || k >= ci->cnt, "point %d out of range %d\n", k, ci->cnt);
  ip = ci->idx[k];
  wi = cls_getwt(cls, ip);
  cl_premove(ci, k, -disi, -wi);
  if (j == cls->nc) {
    cls_cadd(cls, ip);
  } else {
    cl_padd(cls->c + j, ip, disj, wi);
  }
  cls->ene += dene;
}

/* remove the kth point in the cluster i,
 * and add it to the cluster j
 * combines cls_merge() and cls_transfer()
 * removes cluster i, if there is only one point there, i.e., cls_merge() */
static int cls_pmove(clsys_t *cls, int i, int ik, int j,
    double disi, double disj, double dene)
{
  const int freq = 1000;
  clus_t *ci = cls->c + i;
  int mvtype = 0, ip = ci->idx[ik];

  if (i == j) {
    return 0;
  } else if (ci->cnt == 1) {
    cls_merge(cls, i, j, disj, dene);
    mvtype = 1;
  } else {
    cls_transfer(cls, i, ik, j, disi, disj, dene);
    mvtype = 2;
  }

  cls_check(cls, mvtype);
  if (++cls->acc % freq == 0) {
    double ene1 = cls_ene(cls, CLUS_CHECK);
    die_if (fabs(ene1 - cls->ene) > 1e-1,
        "iter %d, type %d: ene diff %g, %g; de %g, clus i: %d (%d:%d), clus j: %d\n",
        cls->iter, mvtype, ene1, cls->ene, dene, i, ik, ip, j);
    cls->ene = ene1;
  }
  return mvtype;
}

/* compute the energy change of adding from point k of cluster i to cluster j */
static double cls_deadd(clsys_t *cls, int i, int k, int j, double *dis)
{
  clus_t *ci = cls->c + i, *cj = cls->c + j;
  double wi, wj;
  int ip, k1, jp;

  *dis = 0.;
  if (j == cls->nc) return cls->muw;
  ip = ci->idx[k];
  wi = cls_getwt(cls, ip);
  for (k1 = 0; k1 < cj->cnt; k1++) {
    jp = cj->idx[k1];
    wj = cls_getwt(cls, jp);
    *dis += wj*cls_pdis(cls, ip, jp);
  }
  *dis *= wi;
/*
  printf("add %d from cluster %d to %d (cnt %d, first %d): smdis %g, ddis %g, wt %g, wi %g\n", ip, i, j, cj->cnt, cj->idx[0], cj->smdis, *dis, cj->smwt, wi);
*/
  return (cj->smdis + *dis)/(cj->smwt + wi) - cj->smdis/cj->smwt;
}

/* compute the energy change of removing kth point from cluster i */
static double cls_deremove(clsys_t *cls, int i, int k, double *dis)
{
  clus_t *ci = cls->c + i;
  double wi, wj;
  int ip, k1, jp;

  die_if (i >= cls->nc, "i: %d, nc %d\n", i, cls->nc);
  if (ci->cnt == 1) {
    *dis = 0;
    return -cls->muw;
  }
  die_if (k < 0 || k >= ci->cnt, "bad index k = %d, cnt = %d\n", k, ci->cnt);
  ip = ci->idx[k];
  wi = cls_getwt(cls, ip);
  for (*dis = 0., k1 = 0; k1 < ci->cnt; k1++) {
    if (k == k1) continue;
    jp = ci->idx[k1];
    wj = cls_getwt(cls, jp);
    *dis += wj * cls_pdis(cls, ip, jp);
  }
  *dis *= wi;
  return (ci->smdis - *dis)/(ci->smwt - wi) - ci->smdis/ci->smwt;
}

/* one step, metropolis move of a cluster
 * iter is the index of iteration */
static int cls_metropolis(clsys_t *cls, unsigned flags)
{
  clus_t *ci;
  int i, j, k, acc;
  double dene, disi, disj;

  if (cls->nc < 1) return 0;
  i = (int)(cls->nc * rnd0());
  ci = cls->c + i;
  k = (int)(ci->cnt * rnd0());
  die_if(ci->cnt <= 0, "empty cluster %d\n", i);
  if (ci->cnt == 1) { /* a cluster of a single point */
    /* try to merge to another cluster */
    if ((flags & CLUS_NOGIANT) && cls->nc == 2) return 0; /* forbid giant formation */
    j = (int)((cls->nc - 1) * rnd0());
    j = (i + 1 + j) % cls->nc; /* choose any other cluster */
  } else {
    j = (int)(cls->nc * rnd0());
    j = (i + 1 + j) % (cls->nc + 1); /* m for a new cluster */
  }
  dene = cls_deremove(cls, i, k, &disi)
       + cls_deadd(cls, i, k, j, &disj);
/*
  printf("metro: %d, i %d, j %d, ene %g, %g; dene %g\n", cls->iter, i, j, cls_ene(cls, 0), cls->ene, dene);
*/
  acc = ((dene < 0.0) || rnd0() < exp(-cls->bet*dene));
  if ((flags & CLUS_NOGIANT) && cls->nc == 1) /* always encourage forming two clusters */
    acc = 1;
  if (acc) { /* accept the move */
    cls_pmove(cls, i, k, j, disi, disj, dene);
  }
  return 0;
}

/* choose one from a heat bath choice */
static int heatbathchoose(double *dene, int n, double bet)
{
  double *prob, demin, deb, r;
  int j;

  /* select a cluster to join */
  xnew(prob, n);
  for (demin = 1e9, j = 0; j < n; j++) {
    if (dene[j] < demin) demin = dene[j];
  }
  for (j = 0; j < n; j++) { /* probability */
    deb = bet*(dene[j] - demin);
    if (deb > 100.0) prob[j] = 0.;
    else prob[j] = exp(-deb);
  }
  for (j = 1; j < n; j++) {
    prob[j] = prob[j-1] + prob[j];
  }
  r = prob[n - 1]*rnd0();
  for (j = 0; j < n; j++) {
    if (r < prob[j]) break;
  }
  die_if (j >= n, "bad index %d > %d\n", j, n);
  free(prob);
  return j;
}

/* heat bath algorithm for ip, if ip == -1, randomly pick a particle */
static int cls_heatbath(clsys_t *cls, int ip, unsigned flags)
{
  clus_t *ci;
  int i, j, k = -1, mvtype = 0;
  double dei, disi;
  double *dene, *disj;

  if (ip >= 0 && ip < cls->np) {
    i = cls_find(cls, ip, &k);
    ci = cls->c + i;
  } else {
    i = (int)(cls->nc*rnd0());
    ci = cls->c + i;
    k = (int)(ci->cnt*rnd0());
  }
  die_if(ci->cnt <= 0 || k < 0, "empty cluster %d or bad k %d", ci->cnt, k);

  if (flags & CLUS_NOGIANT) {
    /* forbid the transition from cluster i to the other (giant) */
    if (cls->nc == 2 && ci->cnt == 1)
      return 0;
  }

  xnew(dene, cls->nc + 1); /* energy change vector */
  xnew(disj, cls->nc + 1);
  /* energy of removing k'th point from cluster i */
  dei = cls_deremove(cls, i, k, &disi);
  /* energy of adding that point to cluster j */
  for (j = 0; j <= cls->nc; j++) {
    if (j == i) continue;
    dene[j] = dei + cls_deadd(cls, i, k, j, &disj[j]);
  }
  if (ci->cnt == 1) dene[cls->nc] = 1e9; /* disable the last option for an alone cluster */
  dene[i] = 0.0;

  /* choose from the heat bath */
  if ((flags & CLUS_NOGIANT) && cls->nc == 1) {
    j = 1;
  } else {
    j = heatbathchoose(dene, cls->nc + 1, cls->bet);
  }
  if (j == i) goto EXIT; /* no move */

  /* accept the move */
  mvtype = cls_pmove(cls, i, k, j, disi, disj[j], dene[j]);
EXIT:
  free(dene);
  free(disj);
  return mvtype;
}

/* energy minimization */
static int cls_minimize(clsys_t *cls, unsigned flags)
{
  int iter, ip, changed = 1, nc0 = cls->nc, nc1, verbose = flags & (CLUS_VERBOSE|CLUS_VVERBOSE);
  double bet, ene0 = cls->ene;

  bet = cls->bet;
  cls->bet = 1e9;
  iter = cls->iter;
  for (cls->iter = 0; ; cls->iter++) {
    changed = 0;
    nc1 = cls->nc;
    for (ip = 0; ip < cls->np; ip++) {
      if (cls_heatbath(cls, ip, 0))
        changed++;
    }
    if (verbose >= 2) printf("%d: nc: %d -> %d, changed = %d\n", cls->iter, nc1, cls->nc, changed);
    if (!changed) break;
  }
  cls->bet = bet;
  if (verbose)
    printf("enemin %4d iter: (%3d %12.7f) --> (%3d %12.7f)\n",
      cls->iter, nc0, ene0, cls->nc, cls->ene);
  ip = cls->iter > 1;
  cls->iter = iter;
  return ip;
}

/* do multidimensional scaling, cls_centroid should be called
 * assuming clusters are in descending order */
static int cls_mdscal(clsys_t *cls, int nmax, int cntmin)
{
  int i, j, ip, jp, n;
  clus_t *ci, *cj;
  real *dm, *xy;

  /* construct cluster-cluster distance matrix */
  n = intmin(cls->nc, nmax);
  for (i = 0; i < n; i++) {
    if (cls->c[i].cnt <= cntmin)
      break;
  }
  if (i < n) n = i;
  if (n < 2) return 0;

  printf("doing multidimensional scaling n %d\n", n);

  xnew(dm, n*n);
  for (i = 0; i < n; i++) {
    ci = cls->c + i;
    ip = ci->idx[ci->centroid];
    for (j = i+1; j < n; j++) {
      cj = cls->c + j;
      jp = cj->idx[cj->centroid];
      dm[i*n+j] = dm[j*n+i] = (real) cls_pdis(cls, ip, jp);
    }
    dm[i*n+i] = 0.;
  }

  /* initialize coordinates */
  xnew(xy, n*2);

  /* low level multidimensional scaling */
  mds_min0(xy, dm, n, 2, 1e-16);

  /* copy coordinates */
  for (i = 0; i < n; i++) {
    ci = cls->c + i;
    ci->x = xy[i*2];
    ci->y = xy[i*2+1];
  }

  free(xy);
  free(dm);
  return 0;
}

/* prepare cls for a better representation */
static void cls_trim(clsys_t *cls)
{
  int mds_nmax = 100, cmin = 0;

  cls_sort(cls); /* sort the cluster list */
  cls_centroid(cls);
  cls_mdscal(cls, mds_nmax, cmin);
}

/* evenly spaced nc clusters */
static int cls_evensplit(clsys_t *cls, int nc)
{
  int i, ic, ppc;
  clus_t *ci;

  die_if (nc > cls->np, "too many clusters %d > %d\n", nc, cls->np);
  cls->nc = nc;

  /* compute number of points in each cluster */
  ppc = cls->np / nc;

  for (ic = 0; ic < nc; ic++) {
    ci = cls->c + ic;
    ci->cnt = (ic == nc - 1) ? (cls->np - ppc*(nc-1)) : ppc;
    ci->cap = ci->cnt;
    die_if(ci->cnt <= 0, "cnt %d, np %d, ic %d, nc %d, ppc %d\n",
        ci->cnt, cls->np, ic, nc, ppc);
    xrenew(ci->idx, ci->cap);
    for (i = 0; i < ci->cnt; i++) {
      ci->idx[i] = ic*ppc + i;
    }
  }
  for (ic = nc; ic < cls->np; ic++)
    cl_free(cls->c + ic);
  cls->ene = cls_ene(cls, 0);
  return 0;
}


/* main function for clustering: given a distance matrix return a clustering conf. */
clsys_t *cls_anneal(clsys_t *cls,
    int itmax, int method, double bet0, double bet1)
{
  for (cls->iter = 0; cls->iter < itmax; cls->iter++) {
    cls->bet = bet0 + (bet1 - bet0)*cls->iter/itmax;
    if (method == CLUS_HEATBATH) {
      cls_heatbath(cls, -1, 0);
    } else {
      cls_metropolis(cls, 0);
    }
  }
  cls_minimize(cls, CLUS_VERBOSE);
  cls_trim(cls);
  return cls;
}

clsys_t *cls_zalgo(clsys_t *cls, int itermax, int method,
    double bet0, double bet1, int nbet,
    int nstmin, int verbose)
{
  int nstage = 30, ncm = 10;
  int isz, is, ib, jb, i, it, freemode = 0;
  double lnf, lnfree, r, gemin, runmin = 1e9;
  double *barr, *lnz, *hist, *esum;
  double *muhist;
  clsys_t **clsb, *clsm, *clstmp;

  /* size dependent cluster configuration */
  if (ncm > cls->np-1) ncm = cls->np-1;
  gemin = 1e9;
  xnew(clsb, ncm+1);
  xnew(muhist, ncm+1);
  for (i = 0; i <= ncm; i++) {
    clsb[i] = cls_init(cls->mat, cls->wt, cls->np, cls->mu0);
    if (i > 0) {
      cls_evensplit(clsb[i], i);
    }
  } /* 0 is for all cluster config. w/ size > ncm */
  xnew(clsm, 1);
  clsm = cls_init(cls->mat, cls->wt, cls->np, cls->mu0);
  xnew(clstmp, 1);
  clstmp = cls_init(cls->mat, cls->wt, cls->np, cls->mu0);

  if (nbet < 2) nbet = 2;
  xnew(lnz, nbet);
  xnew(barr, nbet);
  xnew(hist, nbet);
  xnew(esum,  nbet);
  for (ib = 0; ib < nbet; ib++) {
    barr[ib] = exp(log(bet0) + ib*(log(bet1)  - log(bet0))/(nbet-1));
    lnz[ib] = 0.;
  }
  ib = 0;
  cls->bet = barr[0];
  cls->iter = 1;
  if (itermax <= 0) { /* automatically determine */
    itermax = (cls->np < 10000) ? 2*cls->np*cls->np : 10000000;
    if (verbose)
      printf("automatically determine itermax = %d for n = %d\n", itermax, cls->np);
  }
  lnfree = 0.;
  gemin = 1e9;
  for (lnf = 1., is = 0; is <= nstage; is++, lnf *= .316227766) {
    /* clear histogram */
    for (i = 0; i < nbet; i++) esum[i] = hist[i] = 0.;

    for (it = 1; ; it++) {
      int cl_flags = CLUS_NOGIANT; /* do not sample a single cluster */
      if (method == CLUS_HEATBATH) {
        cls_heatbath(cls, -1, cl_flags);
      } else {
        cls_metropolis(cls, cl_flags);
      }
      /* try a temperature transition */
      jb = (int)(ib + rnd0()*(nbet-1) + 1) % nbet;
      die_if (jb < 0 || jb > nbet, "bad jb = %d\n", jb);
      r = cls->ene*(barr[jb] - barr[ib]) + lnz[jb] - lnz[ib];
      if (r < 0. || rnd0() < exp(-r)) {
        ib = jb;
        cls->bet = barr[ib];
      }
      lnz[ib] += lnf;
      hist[ib] += 1.;
      esum[ib] += cls->ene;

      isz = (cls->nc > ncm) ? 0 : cls->nc;
      muhist[isz] += 1.;
      if (cls->ene < clsb[isz]->ene) {
        cls_copy(clsb[isz], cls);
        if (verbose >= 2)
          printf("found new emin[%d]  = %g     \r", isz, clsb[isz]->ene);
      }
      if (cls->ene < gemin) {
        gemin = cls->ene;
        if (verbose)
          printf("found new gemin = %g     \r", gemin);
      }
      if (++cls->iter >= itermax) break;

      if (it % 100 == 0) {
        /* clean up lnz */
        for (i = 0; i < nbet; i++) lnz[i] -= lnz[nbet-1];
        lnfree = 1.*nbet/cls->iter;
        if (lnf < lnfree && is > 3)
          freemode = 1;
        if (freemode) {
          /* once enter freemode never quit */
          lnf = lnfree;
        } else {  /* check histogram */
          double hmin = 1e9, hmax = 0.;
          for (i = 0; i < nbet; i++) {
            if (hist[i] < hmin) hmin = hist[i];
            if (hist[i] > hmax) hmax = hist[i];
          }
          if ((hmax-hmin)/(hmax+hmin) < 0.3) break; /* each bet met once */
        }
      }
      if (it % nstmin == 0) { /* try to minimize */
        cls_copy(clstmp, cls);
        cls_minimize(clstmp, 0);
        if (clstmp->ene < runmin) {
          if (runmin - clstmp->ene > 1e-6)
            printf("runtime emin %g, %d clusters\n", clstmp->ene, clstmp->nc);
          runmin = clstmp->ene;
          cls_copy(clsm, clstmp);
        }
      }
    }
    if (verbose) {
      printf("stage %d is complete after %d/%d, emin = %g, lnf = %g, lnfree = %g\n",
          is, it, cls->iter, gemin, lnf, lnfree);
    }
    if (verbose >= 3 || (verbose >=2 && cls->iter >= itermax)) {
      for (i = 0; i < nbet; i++) {
        double eav;
        if (hist[i] > 0.) eav = esum[i]/hist[i]; else eav = 0.;
        printf("%8.4f %8.2f %g %g\n", barr[i], lnz[i], hist[i], eav);
      }
    }
    if (cls->iter >= itermax) {
      printf("exceeds the maximal iterations %d in stage %d\n", cls->iter, is);
      break;
    }
  }

  free(lnz);
  free(barr);
  free(hist);
  free(esum);

  /* search for the best */
  for (gemin = 1e9, i = -1, isz = 0; isz <= ncm; isz++) {
    printf("%4d, %10.0f ", isz, muhist[isz]);
    cls_minimize(clsb[isz], CLUS_VERBOSE);
    if (clsb[isz]->ene < gemin) {
      gemin = clsb[isz]->ene;
      i = isz;
    }
  }
  if (runmin < gemin) {
    gemin = runmin;
    cls_copy(cls, clsm);
  } else {
    cls_copy(cls, clsb[i]);
  }
  for (isz = 0; isz <= ncm; isz++)
    cls_free(clsb[isz], 0);
  cls_free(clsm, 0);
  free(clsb);
  free(muhist);
  cls_trim(cls);
  return cls;
}

/* write cluster results
 * `whead' is a call-back function for writing extra information */
int cls_write(clsys_t *cls, const char *fn,
    void (*whead)(FILE *, const clsys_t *cls, const void *data), const void *data,
    int version)
{
  FILE *fp;
  int ic, ni, k, ip, k1;
  clus_t *ci;
  double wtot;

  xfopen(fp, fn, "w", return -1);

  /* basic information */
  fprintf(fp, "# %d %d %g %d\n", cls->np, cls->nc, cls->mu0, version);

  /* call the callback function */
  if (whead != NULL) {
    (*whead)(fp, cls, data);
  } else {
    for (k = 0; k < cls->np; k++) {
      fprintf(fp, "# %d %g\n", k, cls_getwt(cls, k));
    }
  }

  /* write the rmsd matrix */
  for (k = 0; k < cls->np - 1; k++) {
    fprintf(fp, "# %d ", k);
    for (k1 = k+1; k1 < cls->np; k1++) {
      fprintf(fp, "%.3f ", cls->mat[k][k1]);
    }
    fprintf(fp, "\n");
  }

  for (ic = 0; ic < cls->nc; ic++) {
    ci = cls->c + ic;
    ni = ci->cnt;
    /* compute cluster weight */
    for (wtot = 0., k = 0; k < ni; k++) {
      ip = ci->idx[k];
      wtot += cls_getwt(cls, ip);
    }
    fprintf(fp, "%d %d %g %d %g %g: ",
        ic, ni, wtot, ci->idx[ci->centroid], ci->x, ci->y);
    for (k = 0; k < ni; ) {
      ip = ci->idx[k];
      for (k1 = k; k1 < ni-1; k1++) {
        if (ci->idx[k1]+1 != ci->idx[k1+1])
          break;
      }
      if (k1 == k || k == ni-1) {
        fprintf(fp, "%d ", ip);;
      } else {
        fprintf(fp, "%d-%d ", ip, ci->idx[k1]);
      }
      k = k1 + 1;
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
  return 0;
}

/* read a cluster file and construct a rmsd matrix */
clsys_t *cls_read(const char *fn,
    void (*rhead)(FILE *, clsys_t *, void *data), void *data)
{
  FILE *fp;
  int ic, ni, k, ip, k1, np, nc, itmp, ret, ver;
  clsys_t *cls;
  clus_t *cl;
  char buf[1024] = "", word[128], *p;
  float **dismat;
  double *wt, wtot, mu, x, y;

  xfopen(fp, fn, "r", return NULL);

  /* read in basic information */
  die_if (NULL == fgets(buf, sizeof buf, fp), "%s: no first line\n", fn);
  die_if (4 != sscanf(buf, "#%d%d%lf%d", &np, &nc, &mu, &ver),
      "%s: first line broken\n", fn);

  /* allocate space */
  xnew(wt, np);
  dismat = dismat_alloc(np);

  /* read wt */
  for (k = 0; k < np; k++) {
    die_if (NULL == fgets(buf, sizeof buf, fp), "no weight %d\n", k);
    ret = sscanf(buf, "#%d%lf", &itmp, &wt[k]);
    die_if (2 != ret, "no weight information at k = %d, ret = %d\n", k, ret);
    die_if (k != itmp, "index mismatch %d vs. %d", itmp, k);
  }

  /* read the rmsd matrix */
  for (k = 0; k < np - 1; k++) {
    ret = fscanf(fp, " #%d", &itmp);
    die_if (1 != ret, "cannot scan index k = %d, ret = %d\n", k, ret);
    die_if (k != itmp, "wrong id %d should be %d\n", itmp, k);
    for (k1 = k+1; k1 < np; k1++) {
      die_if (1 != fscanf(fp, "%f", &dismat[k][k1]),
          "cannot read matrix %d, %d\n", k, k1);
    }
  }

  /* initialize a configuration */
  cls = cls_init(dismat, wt, np, mu);

  /* read cluster configuration */
  cls->nc = nc;
  for (ic = 0; ic < nc; ic++) {
    die_if (6 != fscanf(fp, " %d%d%lf%d%lf%lf : ", &k1, &ni, &wtot, &itmp, &x, &y),
        "cannot read tag info for cluster %d", ic);
    cl = cls->c + ic;
    cl->cnt = ni;
    cl->cap = cl->cnt;
    cl->x = x;
    cl->y = y;
    xrenew(cl->idx, cl->cap);
    /* start reading indices */
    for (k = 0; k < ni; ) {
      word[0] = '\0';
      die_if (1 != fscanf(fp, "%s", word), "no atoms left, ic = %d, k = %d", ic, k);
      p = strchr(word, '-');
      if (p != NULL) {
        *p = '\0';
        ip = atoi(word);
        itmp = atoi(p+1);
        die_if (ip >= itmp, "%d >= %d\n", ip, itmp);
        die_if (k+itmp+1-ip > ni, "%d + (%d,%d) > %d", k, ip, itmp, ni);
        for (k1 = ip; k1 <= itmp; k1++)
          cl->idx[k++] = k1;
      } else {
        cl->idx[k++] = atoi(word);
      }
    }
  }
  for (ic = nc; ic < cls->np; ic++) /* free the rest */
    cl_free(cls->c + ic);
  cls->ene = cls_ene(cls, 0);
  cls_centroid(cls);

  /* start reading additional info. callback */
  rewind(fp);
  die_if(NULL == fgets(buf, sizeof buf, fp), "%s: no first line (rescan)\n", fn);
  if (rhead != NULL) (*rhead)(fp, cls, data);

  fclose(fp);
  return cls;
}

#endif /* ZCOM_CLUS__ */
#endif /* ZCOM_CLUS */

#ifdef  ZCOM_MD
#ifndef ZCOM_MD__
#define ZCOM_MD__

#define md_shiftcom(x, n, d) md_shiftcomw(x, NULL, n, d)
#define md_shiftcom3d(x, n) md_shiftcomw3d(x, NULL, n)
#define md_shiftcom2d(x, n) md_shiftcomw2d(x, NULL, n)
INLINE void md_shiftcomw(real * RESTRICT x, const real * RESTRICT w, int n, int d);
/* these two are inline instead macros because they offer type checks */
INLINE void md_shiftcomw2d(rv2_t * RESTRICT x, const real * RESTRICT w, int n)
  { md_shiftcomw((real *) x, w, n, 2); }
INLINE void md_shiftcomw3d(rv3_t * RESTRICT x, const real * RESTRICT w, int n)
  { md_shiftcomw((real *) x, w, n, 3); }

INLINE void md_shiftang2d(rv2_t * RESTRICT x, rv2_t * RESTRICT v, int n);
INLINE void md_shiftang3d(rv3_t * RESTRICT x, rv3_t * RESTRICT v, int n);
INLINE void md_shiftang(real * RESTRICT x, real * RESTRICT v, int n, int d)
{
  if (d == 2) md_shiftang2d((rv2_t *) x, (rv2_t *) v, n);
  else md_shiftang3d((rv3_t *) x, (rv3_t *) v, n);
}

INLINE real md_ekin(const real *v, int nd, int dof, real * RESTRICT tkin);
INLINE real md_ekin2d(rv2_t * RESTRICT v, int n, int dof, real * RESTRICT tkin)
  { return md_ekin((const real *) v, n*2, dof, tkin); }
INLINE real md_ekin3d(rv3_t * RESTRICT v, int n, int dof, real * RESTRICT tkin)
  { return md_ekin((const real *) v, n*3, dof, tkin); }

INLINE void md_vscale(real * RESTRICT v, int nd, int dof, real tp, real ekt, real * RESTRICT ekin, real * RESTRICT tkin);
INLINE void md_vscale2d(rv2_t * RESTRICT v, int n, int dof, real tp, real ekt, real * RESTRICT ekin, real * RESTRICT tkin)
    { md_vscale((real *) v, n*2, dof, tp, ekt, ekin, tkin); }
INLINE void md_vscale3d(rv3_t * RESTRICT v, int n, int dof, real tp, real ekt, real * RESTRICT ekin, real * RESTRICT tkin)
    { md_vscale((real *) v, n*3, dof, tp, ekt, ekin, tkin); }

INLINE void md_vrescale(real * RESTRICT v, int nd, int dof, real tp, real dt, real * RESTRICT ekin, real * RESTRICT tkin);
INLINE void md_vrescale2d(rv2_t * RESTRICT v, int n, int dof, real tp, real dt, real * RESTRICT ekin, real * RESTRICT tkin)
    { md_vrescale((real *) v, n*2, dof, tp, dt, ekin, tkin); }
INLINE void md_vrescale3d(rv3_t * RESTRICT v, int n, int dof, real tp, real dt, real * RESTRICT ekin, real * RESTRICT tkin)
    { md_vrescale((real *) v, n*3, dof, tp, dt, ekin, tkin); }

INLINE void md_vrescalex(real * RESTRICT v, int nd, int dof, real tp, real dt, real * RESTRICT ekin, real * RESTRICT tkin);
INLINE void md_vrescalex2d(rv2_t * RESTRICT v, int n, int dof, real tp, real dt, real * RESTRICT ekin, real * RESTRICT tkin)
    { md_vrescalex((real *) v, n*2, dof, tp, dt, ekin, tkin); }
INLINE void md_vrescalex3d(rv3_t * RESTRICT v, int n, int dof, real tp, real dt, real * RESTRICT ekin, real * RESTRICT tkin)
    { md_vrescalex((real *) v, n*3, dof, tp, dt, ekin, tkin); }


/* shift the center of mass to zero */
INLINE void md_shiftcomw(real * RESTRICT x, const real * RESTRICT w, int n, int d)
{
  int i, j;
  real rc, wtot = 0;

  if (w) for (i = 0; i < n; i++) wtot += w[i];
  else wtot = (real) n;
  for (j = 0; j < d; j++) {
    for (rc = 0, i = 0; i < n; i++)
      rc += x[i*d+j]*(w ? w[i] : 1.f);
    rc /= wtot;
    for (i = 0; i < n; i++)
      x[i*d+j] -= rc;
  }
}

/* annihilate angular momentum 2d */
INLINE void md_shiftang2d(rv2_t * RESTRICT x, rv2_t * RESTRICT v, int n)
{
  int i;
  real am, r2, xc[2] = {0,0}, xi[2];

  for (i = 0; i < n; i++) rv2_inc(xc, x[i]);
  rv2_smul(xc, 1.f/n);
  for (am = r2 = 0.f, i = 0; i < n; i++) {
    rv2_diff(xi, x[i], xc);
    am += rv2_cross(xi, v[i]);
    r2 += rv2_sqr(x[i]);
  }
  am = -am/r2;
  for (i = 0; i < n; i++) {
    rv2_diff(xi, x[i], xc);
    v[i][0] += -am*xi[1];
    v[i][1] +=  am*xi[0];
  }
}

/* annihilate angular momentum 3d
 * solve
 *   /  y^2 + z^2    -x y      -x y      \
 *   |  -x y       X^2 + z^2   -y z      |  c  =  I
 *   \  -x z         -y z     x^2 + y^2  /
 * use a velocity field
 *    v = c X r
 *   */

INLINE void md_shiftang3d(rv3_t *x, rv3_t *v, int n)
{
  int i;
  real xc[3] = {0,0,0}, xi[3], ang[3], am[3] = {0,0,0}, dv[3], mat[3][3], inv[3][3];
  real xx = 0, yy = 0, zz = 0, xy = 0, zx = 0, yz = 0;

  for (i = 0; i < n; i++) rv3_inc(xc, x[i]);
  rv3_smul(xc, 1.f/n);
  for (i = 0; i < n; i++) {
    rv3_diff(xi, x[i], xc);
    rv3_cross(ang, xi, v[i]);
    rv3_inc(am, ang);
    xx += xi[0]*xi[0];
    yy += xi[1]*xi[1];
    zz += xi[2]*xi[2];
    xy += xi[0]*xi[1];
    yz += xi[1]*xi[2];
    zx += xi[2]*xi[0];
  }
  mat[0][0] = yy+zz;
  mat[1][1] = xx+zz;
  mat[2][2] = xx+yy;
  mat[0][1] = mat[1][0] = -xy;
  mat[1][2] = mat[2][1] = -yz;
  mat[0][2] = mat[2][0] = -zx;
  rm3_inv(inv, mat);
  ang[0] = -rv3_dot(inv[0], am);
  ang[1] = -rv3_dot(inv[1], am);
  ang[2] = -rv3_dot(inv[2], am);
  /* ang is the solution of M^(-1) * I */
  for (i = 0; i < n; i++) {
    rv3_diff(xi, x[i], xc);
    rv3_cross(dv, ang, xi);
    rv3_inc(v[i], dv);
  }
}

/* return kinetic energy */
INLINE real md_ekin(const real *v, int nd, int dof, real *tkin)
{
  int i;
  real ekin;

  for (ekin = 0, i = 0; i < nd; i++) ekin += v[i]*v[i];
  if (tkin) *tkin = ekin/dof;
  return ekin *= .5f;
}

/* compute the kinetic energy for the thermostats, if ekin != NULL */
INLINE real md_getekin(real *ekin, const real *v, int nd)
{
  int i;
  real ek;

  if (ekin) {
    ek = *ekin;
  } else {
    for (ek = 0, i = 0; i < nd; i++) ek += v[i] * v[i];
    ek *= 0.5f;
  }
  return ek;
}

/* velocity scaling: for regular (no thermostat) MD during equilibration
 * `tp' is the target temperature
 * `ekt' is the observed average kinetic energy, may not be the current *ekin  */
INLINE void md_vscale(real *v, int nd, int dof, real tp, real ekt, real *ekin, real *tkin)
{
  int i;
  real ekav = .5f*tp*dof, s;

  s = (real) sqrt( ekav / ekt );
  for (i = 0; i < nd; i++)
    v[i] *= s;
  if (ekin) *ekin *= s*s;
  if (tkin) *tkin *= s*s;
}

/* velocity rescaling thermostat */
INLINE void md_vrescale(real *v, int nd, int dof, real tp, real dt, real *ekin, real *tkin)
{
  int i;
  real ekav = .5f*tp*dof, ek1, ek2, s;
  double amp;

  ek1 = md_getekin(ekin, v, nd);
  amp = 2*sqrt(ek1*ekav*dt/dof);
  ek2 = ek1 + (ekav - ek1)*dt + (real)(amp*grand0());
  if (ek2 < 0) ek2 = 0;
  s = (real) sqrt(ek2/ek1);
  for (i = 0; i < nd; i++)
    v[i] *= s;
  if (ekin) *ekin = ek2;
  if (tkin) *tkin *= s*s;
}


/* Exact velocity rescaling thermostat */
INLINE void md_vrescalex(real *v, int nd, int dof, real tp, real dt, real *ekin, real *tkin)
{
  int i;
  real ekav = .5f*tp*dof, ek1, ek2, s, c = 0., r;

  if (dt < 10.0) c = exp(-dt);
  r = (real) grand0();
  ek1 = md_getekin(ekin, v, nd);
  ek2 = (real)( ek1 + (1.f-c)*(ekav*(randgausssum(dof-1) + r*r)/dof - ek1)
    + 2.0f*r*sqrt(c*(1.f-c)*ekav/dof*ek1) );
  if (ek2 < 0) ek2 = 0;
  s = (real) sqrt(ek2/ek1);
  for (i = 0; i < nd; i++)
    v[i] *= s;
  if (ekin) *ekin = ek2;
  if (tkin) *tkin *= s*s;
}

/* backup thermostat: velocity-rescaling according to a Monte-Carlo move */
INLINE int md_mcvrescale(real *v, int nd, int dof, real tp, real dt, real *ekin, real *tkin)
{
  int i;
  real ek1, ek2, s;
  double logek1, logek2, r;

  ek1 = md_getekin(ekin, v, nd);
  logek1 = log(ek1);
  logek2 = logek1 + dt*(2.f*rnd0() - 1);
  ek2 = exp(logek2);
  r = (ek2-ek1)/tp - .5*dof*(logek2 - logek1);
  if (r <= 0 || rnd0() < exp(-r)) {
    s = (real) sqrt(ek2/ek1);
    for (i = 0; i < nd; i++)
      v[i] *= s;
    if (ekin) *ekin = ek2;
    if (tkin) *tkin *= s*s;
    return 1;
  } else { /* do nothing otherwise */
    return 0;
  }
}

INLINE int md_mcvrescale2d(rv2_t * RESTRICT v, int n, int dof, real tp, real dt, real * RESTRICT ekin, real * RESTRICT tkin)
    { return md_mcvrescale((real *) v, n*2, dof, tp, dt, ekin, tkin); }
INLINE int md_mcvrescale3d(rv3_t * RESTRICT v, int n, int dof, real tp, real dt, real * RESTRICT ekin, real * RESTRICT tkin)
    { return md_mcvrescale((real *) v, n*3, dof, tp, dt, ekin, tkin); }

/* Nose-Hoover thermostat */
INLINE void md_hoover(real *v, int nd, int dof, real tp, real dt,
   real *zeta, real Q, real *ekin, real *tkin)
{
  int i;
  real ek1, ek2, s, dt2 = .5f*dt;

  ek1 = md_getekin(ekin, v, nd);
  *zeta += (2.f*ek1 - dof * tp)/Q*dt2;

  s = (real) exp(-(*zeta)*dt);
  for (i = 0; i < nd; i++) v[i] *= s;
  ek2 = ek1 * (s*s);
  if (ekin) *ekin = ek2;
  if (tkin) *tkin *= s*s;

  *zeta += (2.f*ek2 - dof * tp)/Q*dt2;
}

INLINE void md_hoover2d(rv2_t *v, int n, int dof, real tp, real dt,
   real *zeta, real Q, real *ekin, real *tkin)
  { md_hoover((real *)v, n*2, dof, tp, dt, zeta, Q, ekin, tkin); }

INLINE void md_hoover3d(rv3_t *v, int n, int dof, real tp, real dt,
   real *zeta, real Q, real *ekin, real *tkin)
  { md_hoover((real *)v, n*3, dof, tp, dt, zeta, Q, ekin, tkin); }

/* Nose-Hoover chain thermostat */
INLINE void md_nhchain(real *v, int nd, int dof, real tp, real scl, real dt,
   real *zeta, const real *Q, int M, real *ekin, real *tkin)
{
  int i, j;
  real ek1, ek2, s, dt2 = .5f*dt, dt4 = .25f*dt, G, xp = 1.f;

  ek1 = md_getekin(ekin, v, nd);

  /* propagate the chain */
  for (j = M-1; j > 0; j--) {
    if (j < M-1) {
      xp = (real) exp(-dt4*zeta[j+1]);
      zeta[j] *= xp;
    }
    G = (Q[j-1]*zeta[j-1]*zeta[j-1] - tp)/Q[j];
    zeta[j] += G * dt2;
    if (j < M-1)
      zeta[j] *= xp;
  }

  /* the first thermostat variable */
  if (M >= 2) {
    xp = exp(-dt4*zeta[1]);
    zeta[0] *= xp;
  }
  G = (scl * 2.f * ek1 - dof * tp)/Q[0];
  zeta[0] += G * dt2;
  if (M >= 2)
    zeta[0] *= xp;

  /* scale the velocities */
  s = (real) exp(-(*zeta)*dt);
  for (i = 0; i < nd; i++) v[i] *= s;
  ek2 = ek1 * (s*s);
  if (ekin) *ekin = ek2;
  if (tkin) *tkin *= s*s;

  /* the first thermotat variable */
  if (M >= 2) {
    xp = exp(-dt4*zeta[1]);
    zeta[0] *= xp;
  }
  G = (scl * 2.f * ek1 - dof * tp)/Q[0];
  zeta[0] += G * dt2;
  if (M >= 2)
    zeta[0] *= xp;

  /* propagate the chain */
  for (j = M-1; j > 0; j--) {
    if (j < M-1) {
      xp = (real) exp(-dt4*zeta[j+1]);
      zeta[j] *= xp;
    }
    G = (Q[j-1]*zeta[j-1]*zeta[j-1] - tp)/Q[j];
    zeta[j] += G * dt2;
    if (j < M-1)
      zeta[j] *= xp;
  }
}

INLINE void md_nhchain2d(rv3_t *v, int n, int dof, real tp, real scl, real dt,
   real *zeta, const real *Q, int M, real *ekin, real *tkin)
  { md_nhchain((real *)v, n*2, dof, tp, scl, dt, zeta, Q, M, ekin, tkin); }

INLINE void md_nhchain3d(rv3_t *v, int n, int dof, real tp, real scl, real dt,
   real *zeta, const real *Q, int M, real *ekin, real *tkin)
  { md_nhchain((real *)v, n*3, dof, tp, scl, dt, zeta, Q, M, ekin, tkin); }

/* velocity-scaling Langevin thermostat */
INLINE void md_vslang(real *v, int nd, int dof, real tp, real dt,
   real *zeta, real zeta2, real Q, real *ekin, real *tkin)
{
  int i;
  real ek1, ek2, s, dt2 = .5f*dt, xp, amp;

  ek1 = md_getekin(ekin, v, nd);
  xp = (real) exp(-zeta2*.25*dt);
  amp = (real) sqrt(2*zeta2/Q*dt2);
  *zeta *= xp;
  *zeta += (2.f*ek1 - dof * tp)/Q*dt2;
  *zeta += amp * grand0(); /* white noise */
  *zeta *= xp;

  s = (real) exp(-(*zeta)*dt);
  for (i = 0; i < nd; i++) v[i] *= s;
  ek2 = ek1 * (s*s);
  if (ekin) *ekin = ek2;
  if (tkin) *tkin *= s*s;

  *zeta *= xp;
  *zeta += (2.f*ek2 - dof * tp)/Q*dt2;
  *zeta += amp * grand0(); /* white noise */
  *zeta *= xp;
}

INLINE void md_vslang2d(rv2_t *v, int n, int dof, real tp, real dt,
   real *zeta, real zeta2, real Q, real *ekin, real *tkin)
  { md_vslang((real *)v, n*2, dof, tp, dt, zeta, zeta2, Q, ekin, tkin); }

INLINE void md_vslang3d(rv3_t *v, int n, int dof, real tp, real dt,
   real *zeta, real zeta2, real Q, real *ekin, real *tkin)
  { md_vslang((real *)v, n*3, dof, tp, dt, zeta, zeta2, Q, ekin, tkin); }


/* Anderson thermostat */
INLINE void md_andersen(real *v, int n, int d, real tp)
{
  int i, j;

  tp = sqrt(tp);
  i = (int)(rnd0() * n);
  for (j = 0; j < d; j++) v[i*d + j] = tp * grand0();
}

/* Langevin thermostat */
INLINE void md_langevin(real *v, int n, int d, real tp, real dt)
{
  int i;
  real c = (real) exp(-dt), amp;

  amp = sqrt((1 - c*c) * tp);
  for (i = 0; i < n*d; i++)
    v[i] = c*v[i] + amp*grand0();
}

/* Nose-Hoover thermostat/barostat
 * set cutoff to half of the box */
INLINE void md_hoovertp(real *v, int n, int d, int dof, real dt,
    real tp, real pext, real *zeta, real *eta, real Q, real W,
    real vol, real vir, real ptail, int ensx,
    real *ekin, real *tkin)
{
  int i;
  real xp, pint, s, dt2 = dt*.5f, dt4 = dt*.25f;

  /* thermostat */
  *zeta += (2.f * (*ekin) + W * (*eta) * (*eta) - (dof + 1) * tp) * dt2/Q;
  xp = (real) exp(-(*zeta)*dt4); /* zeta won't change until the end */

  /* barostat */
  *eta *= xp;
  pint = (vir + 2.f * (*ekin))/ (d * vol) + ptail;
  *eta += ((pint - pext)*vol + (1 - ensx) * tp)*d*dt2/W;
  *eta *= xp;

  /* scaling velocity */
  s = exp( -dt * (*zeta + *eta) );
  for (i = 0; i < d * n; i++) v[i] *= s;
  *ekin *= s*s;
  *tkin *= s*s;

  /* barostat */
  *eta *= xp;
  pint = (vir + 2.f * (*ekin))/ (d * vol) + ptail;
  *eta += ((pint - pext)*vol + (1 - ensx) * tp)*d*dt2/W;
  *eta *= xp;

  /* thermostat */
  *zeta += (2.f * (*ekin) + W * (*eta) * (*eta) - (dof + 1) * tp) * dt2/Q;
}

/* Nose-Hoover chain thermostat/barostat
 * set cutoff to half of the box */
INLINE void md_nhchaintp(real *v, int n, int d, int dof, real dt,
    real tp, real pext, real *zeta, real *eta, const real *Q, int M, real W,
    real vol, real vir, real ptail, int ensx,
    real *ekin, real *tkin)
{
  int i, j;
  real xpz, pint, s, dt2 = dt*.5f, dt4 = dt*.25f, G, xp;

  /* 1. thermostat */
  /* 1.A propagate the chain */
  for (j = M-1; j > 0; j--) {
    if (j < M-1) {
      xp = (real) exp(-dt4*zeta[j+1]);
      zeta[j] *= xp;
    }
    G = (Q[j-1]*zeta[j-1]*zeta[j-1] - tp)/Q[j];
    zeta[j] += G * dt2;
    if (j < M-1)
      zeta[j] *= xp;
  }

  /* 1.B the first thermostat variable */
  if (M >= 2) {
    xp = exp(-dt4*zeta[1]);
    zeta[0] *= xp;
  }
  G = (2.f * (*ekin) + W * (*eta) * (*eta) - (dof + 1) * tp) / Q[0];
  zeta[0] += G * dt2;
  if (M >= 2)
    zeta[0] *= xp;
  xpz = (real) exp(-zeta[0]*dt4); /* zeta won't change until the end */

  /* 2. barostat */
  *eta *= xpz;
  pint = (vir + 2.f * (*ekin))/ (d * vol) + ptail;
  *eta += ((pint - pext)*vol + (1 - ensx) * tp)*d*dt2/W;
  *eta *= xpz;

  /* 3. scaling velocity */
  s = exp( -dt * (zeta[0] + *eta) );
  for (i = 0; i < d * n; i++) v[i] *= s;
  *ekin *= s*s;
  *tkin *= s*s;

  /* 4. barostat */
  *eta *= xpz;
  pint = (vir + 2.f * (*ekin))/ (d * vol) + ptail;
  *eta += ((pint - pext)*vol + (1 - ensx) * tp)*d*dt2/W;
  *eta *= xpz;

  /* 5. thermostat */
  /* 5.A the first thermotat variable */
  if (M >= 2) {
    xp = exp(-dt4*zeta[1]);
    zeta[0] *= xp;
  }
  G = (2.f * (*ekin) + W * (*eta) * (*eta) - (dof + 1) * tp) / Q[0];
  zeta[0] += G * dt2;
  if (M >= 2)
    zeta[0] *= xp;

  /* 5.B propagate the chain */
  for (j = M-1; j > 0; j--) {
    if (j < M-1) {
      xp = (real) exp(-dt4*zeta[j+1]);
      zeta[j] *= xp;
    }
    G = (Q[j-1]*zeta[j-1]*zeta[j-1] - tp)/Q[j];
    zeta[j] += G * dt2;
    if (j < M-1)
      zeta[j] *= xp;
  }
}

/* Langevin barostat
 *   d eta / dt = -zeta * eta
 *      + [ (Pint - Pext) * V + (1 - ensx) T ] * d / W
 *      + sqrt( 2 * zeta * T / W ) xi
 * the ideal-gas part of the pressure, Pint, is computed as \sum p^2/m / V
 * the additional volume distribution weight is V^(-ensx)
 * the scaling is r = r*s, p = p/s;
 * set the cutoff rc to half of the box */
INLINE void md_langtp(real *v, int n, int d, real dt,
    real tp, real pext, real zeta, real *eta, real W,
    real vol, real vir, real ptail, int ensx,
    real *ekin, real *tkin)
{
  int i;
  real xp, pint, s, dt2 = dt*.5f, dt4 = dt*.25f, amp;

  xp = (real) exp(-zeta*dt4);
  amp = (real) sqrt(2.f*zeta*tp/W*dt2);

  /* barostat: first half to update *eta */
  *eta *= xp;
  pint = (vir + 2.f * (*ekin))/ (d * vol) + ptail;
  *eta += ((pint - pext)*vol + (1 - ensx) * tp)*d*dt2/W;
  *eta += amp*grand0(); /* random noise */
  *eta *= xp;

  /* scaling velocity */
  s = exp( -dt * (*eta) );
  for (i = 0; i < d * n; i++) v[i] *= s;
  *ekin *= s*s;
  *tkin *= s*s;

  /* barostat: second half to update *eta */
  *eta *= xp;
  pint = (vir + 2.f * (*ekin))/ (d * vol) + ptail;
  *eta += ((pint - pext)*vol + (1 - ensx) * tp)*d*dt2/W;
  *eta += amp*grand0(); /* random noise */
  *eta *= xp;
}

/* position Langevin barostat
 * limiting case, zeta -> inf., of the full Langevin barostat
 * barodt = dt/(W*zeta), and d * d(eta) = d lnv
 * the ideal-gas part of the pressure is computed as \sum p^2/m / V
 * the scaling is r = r*s, p = p/s;
 * set cutoff to half of the box */
INLINE void md_langtp0(real *v, int n, int d, real barodt,
   real tp, real pext, real *vol, real vir, real ptail, int ensx,
   real *ekin, real *tkin)
{
  int i;
  real pint, amp, vn, s, dlnv;

  /* compute the internal pressure */
  /* note only with half-box cutoff, the formula is accurate */
  pint = (vir + 2.f * (*ekin))/ (d * (*vol)) + ptail;

  amp = (real) sqrt(2.f * barodt);
  dlnv = ((pint - pext) * (*vol)/tp + 1 - ensx)*barodt + amp*grand0();
  vn = *vol * exp( dlnv );

  s = (real) exp( dlnv/d );
  for (i = 0; i < d * n; i++) v[i] *= s;
  *ekin *= s*s;
  *tkin *= s*s;

  *vol = vn;
}

/* position Langevin barostat, with coordinates only
 * NOTE: the first parameter is the degree of freedom
 * the scaling is r = r*s
 * set cutoff to half of the box */
INLINE void md_langp0(int dof, int d, real barodt,
   real tp, real pext, real *vol, real vir, real ptail, int ensx)
{
  real pintv, amp, dlnv;

  pintv = (vir + dof * tp)/d + ptail * (*vol);
  amp = (real) sqrt(2.f * barodt);
  dlnv = ((pintv - pext * (*vol))/tp + 1 - ensx)*barodt + amp*grand0();
  *vol *= exp( dlnv );
}

/* sinc(x) = (e^x - e^(-x))/(2 x) */
INLINE double md_mysinc(double x)
{
  double x2 = x*x;

  if (fabs(x) < 1e-2) /* series expansion */
    return 1 + (1 + (1 + x2/42.0)*x2/20.0)*x2/6.0;
  else
    return .5 * (exp(x) - exp(-x))/x;
}

/* Nose-Hoover position update */
INLINE void md_hoovertpdr(real *r, const real *v, int nd,
    real *xp, real l, real eta, real dt)
{
  int i;
  real dtxp, xph, etadt2;

  /* r' = r*exp(eta*dt) + v*(exp(eta*dt) - 1)/eta
   * now exp(eta*dt) is the volume scaling factor
   * so for the reduced coordinates R = r*exp(-eta*dt)
   * R' = R + v*(1 - exp(-eta*dt))/eta; */
  etadt2 = eta * dt * .5f;
  xph = (real) exp(etadt2);
  *xp = xph * xph;
  dtxp = 1.f/xph * dt * md_mysinc(etadt2) / l;
/*
  dtxp = (1 - 1/(*xp))/eta/l;
*/
  for (i = 0; i < nd; i++)
    r[i] += v[i] * dtxp;
}

#define md_mutv2d(v, n, tp) md_mutv((real *)(rv2_t *)v, n * 2, tp)
#define md_mutv3d(v, n, tp) md_mutv((real *)(rv3_t *)v, n * 3, tp)

/* mutate velocities */
INLINE int md_mutv(real *v, int nd, real tp)
{
  int i;
  real vamp = sqrt(tp);

  for (i = 0; i < nd; i++)
    v[i] = vamp * grand0();
  return 0;
}

/* multiply velocities by a random unitary matrix */
INLINE int md_unimatv3d(rv3_t *v, int n)
{
  int i;
  real mat[3][3], v1[3];

  rm3_rnduni(mat);
  for (i = 0; i < n; i++) {
    rm3_mulvec(v1, mat, v[i]);
    rv3_copy(v[i], v1);
  }
  return 0;
}

#endif /* ZCOM_MD__ */
#endif /* ZCOM_MD */

#ifdef  ZCOM_WLCVG
#ifndef ZCOM_WLCVG__
#define ZCOM_WLCVG__
#include <stdio.h>

typedef struct {
  double lnf0;  /* lnf of the first stage, also the maximal value */
  double lnffac; /* factor to multiply on passing to another stage */
  double lnfc;  /* lnf to be used in formula */
  double lnfmin; /* minimal lnf */
  double lnfwl; /* lnf as given by Wang-Landau algorithm */
  double lnfinvt; /* lnf as given value given by lnfc/nupd; */
  double lnf; /* lnf adjusted by both wl and invt */
  double perc, percutoff;
  double nupd; /* the total number of updates */
  int stage; /* stage id */
  int nstcheck; /* frequency of checking histogram flatness */
  unsigned flags;
  hist_t *hs;
} wlcvg_t;

#define WLCVG_UPDLNFC 0x0001

/* to use a pure Wang-Landau scheme, set lnfc = 0
 * to use a pure formula scheme, set percutoff = 0 */
INLINE wlcvg_t *wlcvg_open(double lnfc, double lnf0, double lnffac, double percutoff, double lnfmin,
    double xmin, double xmax, double dx, unsigned flags)
{
  wlcvg_t *wl;

  xnew(wl, 1);
  wl->hs = hs_open(1, xmin, xmax, dx);
  wl->lnf = wl->lnfwl = wl->lnf0 = lnf0;
  wl->lnffac = lnffac;
  wl->lnfc = lnfc;
  wl->lnfmin = lnfmin;
  wl->percutoff = percutoff;
  wl->perc = 1.0;
  wl->nupd = 0.0;
  wl->stage = 0;
  wl->nstcheck = 10 * ((int)((xmax - xmin)/dx + 0.99999999));
  wl->flags = flags;
  return wl;
}

INLINE void wlcvg_close(wlcvg_t *wl)
{
  hs_close(wl->hs);
  free(wl);
}

/* compute histogram flatness */
INLINE double wlcvg_hsflatness(wlcvg_t *wl)
{
  double hmin = 1.0e30, hmax = 0.0, h;
  int i;

  for (i = 0; i < wl->hs->n; i++) {
    h = wl->hs->arr[i];
    if (h < hmin) hmin = h;
    else if (h > hmax) hmax = h;
  }
  return wl->perc = (hmax > 0 ? (hmax - hmin)/(hmax + hmin) : 1.0);
}

/* register x to the histogram */
INLINE void wlcvg_add(wlcvg_t *wl, double x)
{
  wl->nupd += 1.0;
  hs_add(wl->hs, &x, 1, 0);
}

INLINE void wlcvg_shiftstage(wlcvg_t *wl)
{
  wl->stage++;
  wl->perc = 1.0;
  if ((wl->flags & WLCVG_UPDLNFC) && wl->lnfinvt < wl->lnfwl)
    wl->lnfc = wl->nupd * wl->lnfwl;
  wl->lnfwl *= wl->lnffac;
  hs_clear(wl->hs);
}

/* easy driver for updating lnf, return lnf */
INLINE double wlcvg_update(wlcvg_t *wl, double x)
{
  wlcvg_add(wl, x);
  if (fmod(wl->nupd, wl->nstcheck) < 0.1) /* compute histogram flatness */
    wlcvg_hsflatness(wl);
  wl->lnfinvt = wl->lnfc / wl->nupd; /* value given by formula */
  if (wl->percutoff > 0 && wl->lnfinvt < wl->lnfwl) { /* consult the Wang-Landau scheme */
    wl->lnf = wl->lnfwl;
    if (wl->perc < wl->percutoff) wlcvg_shiftstage(wl);
  } else {
    wl->lnf = dblmin(wl->lnfinvt, wl->lnf0);
  }
  return wl->lnf = dblmax(wl->lnf, wl->lnfmin);
}

INLINE void wlcvg_setnupd(wlcvg_t *wl, double nupd, double lnfwl, double lnfc)
{
  modf(nupd, &wl->nupd); /* truncate to the nearest integer */
  if (lnfwl > 0) wl->lnfwl = lnfwl;
  if (lnfc > 0) wl->lnfc = lnfc;
}
#endif /* ZCOM_WLCVG__ */
#endif /* ZCOM_WLCVG */

#ifdef  ZCOM_TMH
#ifndef ZCOM_TMH__
#define ZCOM_TMH__

/* tempering with modified Hamiltonian */

/* 0: low energy; 1: high energy
 * if tp0 < tp1: tp is a temperature-like quantity, and rho ~ exp[ -H(erg)/tp ];
 * if tp0 > tp1: tp is a beta-like quantity, and rho ~ exp[ -H(erg)*tp ]
 * */
typedef struct {
  double tp, ec; /* current temperature, and the expected energy there */
  int itp, iec; /* indices of tp and ec */
  double tp0, tp1, dtp; /* temperature range */
  int tpn, dum1_; /* number of temperature */
  double emin, emax; /* energy range */
  double de; /* bin size of energy histogram */
  int en, dum2_; /* number of energy bins */
  double erg0, erg1; /* energy range (erg0, erg1) */
  double derg; /* bin size for the updating energy range */
  int ergn, dum3_; /* number of the updating energy bins */
  double scl; /* prefactor in effective Hamiltonian */
  double dergdt; /* (erg1 - erg0)/(tp1 - tp0) */
  int dhdeorder, dum4_; /* order of dhde interpolation */
  double dhdemin; /* minimal of dhde */
  double dhdemax; /* maximal of dhde */
  double *dhde; /* dH / dE - 1 */
  double *dhdecnt; /* number of visits */
  double *tpehis; /* multipl-temperature energy histogram */
  double ensexp; /* w(T) = 1/T^ensexp */
  double *lnz; /* partition function */
  double *lng; /* density of states */
  double *mh; /* modified Hamiltonian  */
  double *dum5_;
  double elimit; /* energy limit */
  double springk; /* elastic constant to ensure smoothness of dH/dE */
  unsigned flags; /* flags */
  wlcvg_t *wl; /* Wang-Landau convergence */
} tmh_t;

STRCLS tmh_t *tmh_open(double tp0, double tp1, double dtp,
    double erg0, double erg1, double derg,
    double emin, double emax, double de,
    double ensexp, int dhdeorder);
STRCLS void tmh_close(tmh_t *m);
STRCLS int tmh_savedhde(tmh_t *m, const char *fn, double amp, double t);
STRCLS int tmh_loaddhde(tmh_t *m, const char *fn, double *amp, double *t);
STRCLS int tmh_savetp(tmh_t *m, const char *fn);
STRCLS int tmh_loaderange(const char *fn,
    double *tp0, double *tp1, double *dtp,
    double *erg0, double *erg1, double *derg,
    double *emin, double *emax, double *de,
    double *ensexp, int *dhdeorder);
STRCLS int tmh_calcdos(tmh_t *m, int itmax, double tol,
    const char *fndos, const char *fnlnz);

/* set the current temperature */
INLINE void tmh_settp(tmh_t *m, double tp)
{
  die_if ((m->tp1 - tp) * m->dtp < 0.0 || (tp - m->tp0) * m->dtp < 0.0,
      "temperature %g not in (%g, %g), dtp %g", tp, m->tp0, m->tp1, m->dtp);
  m->tp = tp;
  m->itp = (int)((m->tp - m->tp0)/m->dtp);
  if (m->itp >= m->tpn) m->itp = m->tpn - 1;
  m->ec = m->erg0 + (m->tp - m->tp0)*m->dergdt;
  if (m->dhdeorder == 0) { /* to the bin */
    m->iec = (int)((m->ec - m->erg0)/m->derg);
    if (m->iec >= m->ergn) m->iec = m->ergn - 1;
  } else { /* to the nearest bin boundary */
    m->iec = (int)((m->ec - m->erg0)/m->derg + .5);
  }
}

/* return dH/dE at given energy 'erg', which should be the current potential energy */
INLINE double tmh_getdhde(tmh_t *m, double erg)
{
  double erg0 = m->erg0, erg1 = m->erg1, derg = m->derg, *dhde = m->dhde, x, ix;
  int ergn = m->ergn, ie, order = m->dhdeorder;

  if (erg <= erg0) return dhde[0];
  else if (erg >= erg1) return dhde[order ? ergn : ergn - 1];

  if (order == 0) {
    return dhde[ (int)( (erg - erg0) /derg) ];
  } else {
    x = modf((erg - erg0) / derg, &ix);
    ie = (int) ix;
    return dhde[ie] * (1 - x) + dhde[ie + 1] * x;
  }
}

/* update dH/dE curve
 * Note: the location of updating correspond to m->ec instead of erg */
INLINE void tmh_updhde(tmh_t *m, double del)
{
  m->dhde[m->iec] = dblconfine(m->dhde[m->iec] + del, m->dhdemin, m->dhdemax);
}

/* update dhde with spring constant */
INLINE void tmh_updhdek(tmh_t *m, double del, double amp)
{
  int  i = m->iec;
  double x = m->dhde[i];

  if (i > 0)
    del += m->springk * (m->dhde[i-1] - x);
  if (i < (m->dhdeorder ? m->ergn : m->ergn - 1))
    del += m->springk * (m->dhde[i+1] - x);
  m->dhde[i] = dblconfine(x + del * amp, m->dhdemin, m->dhdemax);
}

#define tmh_eadd(m, erg) tmh_eaddw(m, erg, 1.0)
INLINE void tmh_eaddw(tmh_t *m, double erg, double w)
{
  int ie;
#ifndef TMH_NOCHECK
  if (erg < m->emin || erg > m->emax) return;
#endif
  ie = (int)((erg - m->emin)/m->de);
#ifndef TMH_NOCHECK
  die_if (ie < 0 || ie >= m->en, "ie = %d, erg %g emin %g de %g output range\n",
      ie, erg, m->emin, m->de);
  die_if (m->itp > m->tpn, "itp = %d, tpn = %d, tp = %g, dtp = %g\n",
      m->itp, m->tpn, m->tp, m->dtp);
#endif
  m->tpehis[m->itp*m->en + ie] += w;
}

/* compute dH = H(e1) - H(e0) from integrating the dhde curve */
INLINE double tmh_hdif(tmh_t *m, double e1, double e0)
{
  int ie, iel, ieh, sgn, order = m->dhdeorder, ergn = m->ergn;
  double dh = 0, de, k, el0, eh0, el, eh;
  double erg0 = m->erg0, erg1 = m->erg1, derg = m->derg, *dhde = m->dhde;

  /* ensure e1 > e0 */
  if (e1 < e0) { eh = e0; el = e1; sgn = -1; }
  else { eh = e1; el = e0; sgn = 1; }

  if (eh < erg0) { /* first energy bin */
    dh = (eh - el) * dhde[0];
  } else if (el > erg1) { /* last energy bin */
    dh = (eh - el) * dhde[order ? ergn : ergn - 1];
  } else {
    /* energy index */
    if (el < erg0) {
      dh += (erg0 - el) * dhde[0];
      el = erg0;
      iel = 0;
    } else {
      iel = (int)((el - erg0) / derg);
    }
    if (eh > erg1) {
      dh += (eh - erg1) * dhde[order ? ergn : ergn - 1];
      eh = erg1;
      ieh = ergn - 1;
    } else {
      ieh = (int)((eh - erg0) / derg);
    }
    if (order == 0) { /* zeroth order: dhde is constant within a bin */
      if (iel == ieh) {
        dh += (eh - el) * dhde[iel];
      } else if (iel < ieh) {
        /* dh at the two terminal energy bin */
        dh += (erg0 + (iel+1)*derg - el) * dhde[iel]
            + (eh - (erg0 + derg*ieh)) * dhde[ieh];
        for (ie = iel+1; ie < ieh; ie++) /* integrate dH/dE */
          dh += dhde[ie] * derg;
      }
    } else { /* first order: dhde is linear to erg */
      if (iel == ieh) {
        k = (dhde[iel+1] - dhde[iel]) / derg;
        el0 = erg0 + iel * derg;
        dh += (eh - el) * (dhde[iel] + k * (.5f*(el+eh) - el0));
      } else if (iel < ieh) {
        /* dh at the two terminal energy bin */
        el0 = erg0 + (iel + 1) * derg;
        de = el0 - el;
        k = (dhde[iel + 1] - dhde[iel]) / derg;
        dh += de * (dhde[iel + 1] - .5 * k * de);
        eh0 = erg0 + derg * ieh;
        de = eh - eh0;
        k = (dhde[ieh + 1] - dhde[ieh]) / derg;
        dh += de * (dhde[ieh] + .5 * k * de);
        for (ie = iel + 1; ie < ieh; ie++) /* integrate dH/dE */
          dh += .5 * (dhde[ie] + dhde[ie + 1]) * derg;
      }
    }
  }
  return dh * sgn;
}

/* temperature move using a Langevin equation */
#define tmh_lgvmove(m, enow, lgvdt) \
  tmh_langvmove(m, tmh_hdif(m, enow, m->ec), lgvdt)
INLINE int tmh_langvmove(tmh_t *m, double dh, double lgvdt)
{
  double bexp, amp, scl = m->scl;

  if (m->dtp > 0) { /* temperature-like move */
    double tp, tp2, tpl = m->tp0, tph = m->tp1;

    tp = m->tp / scl;
    amp = tp * sqrt(2 * lgvdt);
    bexp = 2. - m->ensexp;
    tp2 = tp + (dh + bexp * tp) * lgvdt + grand0() * amp;
    tp2 *= scl;
    if (tp2 >= tpl && tp2 <= tph) {
      tmh_settp(m, tp2);
      return 1;
    }
  } else { /* beta-like move */
    double bet, bet2, betl = m->tp1, beth = m->tp0;

    bet = m->tp * scl;
    amp = sqrt(2 * lgvdt);
    bet2 = bet - (dh + m->ensexp * bet) * lgvdt + grand0() * amp;
    bet2 /= scl;
    if (bet2 >= betl && bet2 <= beth) {
      tmh_settp(m, bet2);
      return 1;
    }
  }
  return 0;
}

/* set ec and iec */
INLINE void tmh_setec(tmh_t *m, double erg)
{
  int order = m->dhdeorder;

  if (erg < m->erg0) {
    m->ec = m->erg0;
    m->iec = 0;
  } else if (erg > m->erg1) {
    m->ec = m->erg1;
    m->iec = order ? m->ergn : m->ergn - 1;
  } else {
    double x = (erg - m->erg0) / m->derg;
    m->ec = erg;
    if (order == 0) {
      m->iec = (int) x;
    } else {
      m->iec = (int) (x + .5); /* to the nearest grid */
      if (m->iec == 1 && x - (int) x >= .5) /* high half of the first bin */
        m->iec = 0; /* update dhde[0] */
      else if (m->iec == m->ergn - 1 && x - (int) x < .5) /* low half of the last bin */
        m->iec = m->ergn; /* update dhde[n] */
    }
  }
}

/* initialize amplitude of updating */
INLINE void tmh_initwlcvg(tmh_t *m, double ampc, double ampmax,
    double ampfac, double perc, double ampmin, unsigned flags)
{
  m->wl = wlcvg_open(ampc, ampmax, ampfac, perc, ampmin,
      m->erg0, m->erg1, m->derg, flags);
}

/* easy move for tempering, return 1 if successful
 * famp: tweaking factor */
INLINE int tmh_ezmove(tmh_t *m, double epot, double famp, double lgvdt)
{
  tmh_eadd(m, epot);
  if (fabs(epot - m->ec) < m->elimit || epot > m->erg1 || epot < m->erg0) {
    die_if (m->wl == NULL, "call tmh_initamp first, %p\n", (void *) m->wl);
    wlcvg_update(m->wl, m->ec); /* compute updating amplitude */
    tmh_updhdek(m, epot - m->ec, m->wl->lnf * famp);
  }
  return tmh_lgvmove(m, epot, lgvdt);
}

/* easy move for entropic sampling */
INLINE void tmh_ezmoves(tmh_t *m, double epot, double ampe)
{
  tmh_eadd(m, epot);
  wlcvg_update(m->wl, m->ec);
  tmh_updhde(m, (epot - m->ec) * m->wl->lnf * ampe);
  tmh_setec(m, epot);
}

INLINE int tmh_saveehis(tmh_t *m, const char *fn)
{
  return histsave(m->tpehis, m->tpn,
      m->en, m->emin, m->de, HIST_ADDAHALF|HIST_OVERALL, fn);
}

INLINE int tmh_loadehis(tmh_t *m, const char *fn)
{
  return histload(m->tpehis, m->tpn,
      m->en, m->emin, m->de, HIST_ADDAHALF, fn);
}

INLINE int tmh_save(tmh_t *m, const char *fntp, const char *fnehis,
    const char *fndhde, double amp, double t)
{
  tmh_savetp(m, fntp);
  tmh_savedhde(m, fndhde, amp, t);
  tmh_saveehis(m, fnehis);
  return 0;
}

INLINE int tmh_load(tmh_t *m, const char *fnehis,
    const char *fndhde, double *amp, double *t)
{
  if (tmh_loaddhde(m, fndhde, amp, t) != 0) return -1;
  if (tmh_loadehis(m, fnehis) != 0) return -1;
  return 0;
}


tmh_t *tmh_open(double tp0, double tp1, double dtp,
    double erg0, double erg1, double derg,
    double emin, double emax, double de,
    double ensexp, int dhdeorder)
{
  tmh_t *m;
  int i;

  xnew(m, 1);

  m->scl = 1; /* Hamiltonian scaling factor */

  /* energy histogram range */
  m->de = de;
  die_if(emin >= emax, "Error: emin %g >= emax %g\n", emin, emax);
  m->emin = emin;
  m->emax = emin + dblround(emax - emin, de);
  m->en = (int)((m->emax - m->emin)/de + .5); /* number of energy bins */

  /* the updating energy range */
  die_if(erg0 >= erg1, "Error: erg0 %g >= erg1 %g\n", erg0, erg1);
  m->derg = derg;
  m->erg0 = erg0;
  m->erg1 = erg0 + dblround(erg1 - erg0, derg);
  m->ergn = (int)((m->erg1 - m->erg0)/m->derg + .5);

  /* dhde parameters */
  m->dhdeorder = dhdeorder;
  m->dhdemin = 0.1;
  m->dhdemax = 10.0;
  /* to enable dhde[-1] to dhde[ergn + 1] */
  xnew(m->dhde, m->ergn + 3);
  for (i = 0; i < m->ergn + 3; i++)
    m->dhde[i] = 1.;
  m->dhde++;
  xnew(m->dhdecnt, m->ergn + 3);
  m->dhdecnt++;

  die_if((tp1 - tp0)*dtp < 0, "Error: tp0 %g, tp1 %g, dtp %g\n", tp0, tp1, dtp);
  if (fabs(dtp) > 0) { /* dtp is explicitly specified */
    m->dtp = dtp;
    m->tp0 = dblround(tp0, dtp); /* round tp0, tp1 to multiples of dtp */
    m->tp1 = dblround(tp1, dtp);
    m->tpn = (int)((m->tp1 - m->tp0)/m->dtp + .5);
  } else {
    m->tp0 = tp0;
    m->tp1 = tp1;
    m->tpn = m->ergn;
    m->dtp = (m->tp1 - m->tp0)/m->tpn * (1. + 1e-12);
  }
  xnew(m->tpehis, m->tpn * m->en);

  m->ensexp = ensexp;
  tmh_settp(m, m->tp0 + (m->tp1 - m->tp0) * 1e-8);
  m->dergdt = (m->erg1 - m->erg0)/(m->tp1 - m->tp0);

  xnew(m->lnz, m->tpn);
  xnew(m->lng, m->en);
  xnew(m->mh, m->en + 1);
  for (i = 0; i <= m->en; i++)
    m->mh[i] = m->emin + i * m->de;

  m->elimit = 1e9; /* default with no elimit */
  m->springk = 0.0; /* no spring */

  m->wl = NULL;
  return m;
}

void tmh_close(tmh_t *m)
{
  if (m == NULL) return;
  free(m->dhde - 1);
  free(m->dhdecnt - 1);
  free(m->tpehis);
  free(m->lnz);
  free(m->lng);
  free(m->mh);
  if (m->wl) wlcvg_close(m->wl);
  free(m);
}

/* write dhde and overall energy distribution */
int tmh_savedhde(tmh_t *m, const char *fn, double amp, double t)
{
  int ie;
  FILE *fp;
  double nupd = t, lnfwl = amp, lnfc = amp*t;

  xfopen(fp, fn, "w", return -1);
  if (m->wl) {
    nupd = m->wl->nupd;
    lnfwl = m->wl->lnfwl;
    lnfc = m->wl->lnfc;
  }
  fprintf(fp, "# 3 %g %g %d %g %g %d %g %g %d %g %d %g %g %g %.f %g %g\n",
      m->erg0, m->derg, m->ergn,
      m->emin, m->de,   m->en,
      m->tp0,  m->dtp,  m->tpn,
      m->ensexp, m->dhdeorder,
      amp, t, m->tp, nupd, lnfwl, lnfc);
  if (m->dhdeorder == 0) m->dhde[m->ergn] = m->dhde[m->ergn - 1];
  for (ie = 0; ie <= m->ergn; ie++) {
    fprintf(fp, "%g %g\n", m->erg0 + ie*m->derg, m->dhde[ie]);
  }
  fclose(fp);
  return 0;
}

/* read the dhde curve and wlcvg data */
int tmh_loaddhde(tmh_t *m, const char *fn, double *amp, double *t)
{
  int ie, ergn, en, ver, tpn, dhdeorder, next;
  FILE *fp;
  char s[1024], *p;
  double emin, de, derg, erg, erg0, tp, tp0, dtp, dhde, ensexp;

  xfopen(fp, fn, "r", return -1);
  if (fgets(s, sizeof s, fp) == NULL) {
    fprintf(stderr, "cannot read the first line %s\n", fn);
    goto ERR;
  }
  if (7 != sscanf(s, " # %d%lf%lf%d%lf%lf%d%n",
        &ver, &erg0, &derg, &ergn, &emin, &de, &en, &next)) {
    fprintf(stderr, "corrupted info line %s", s);
    goto ERR;
  }
  if (ver < 1 ||
      ergn != m->ergn || fabs(derg - m->derg) > 1e-5 || fabs(erg0 - m->erg0) > 1e-5 ||
      en != m->en || fabs(de - m->de) > 1e-5 || fabs(emin - m->emin) > 1e-5) {
    fprintf(stderr, "bad energy ergn %d %d, erg0 %g %g, derg %g %g, en %d %d, emin %g %g, de %g %g\n",
        ergn, m->ergn, erg0, m->erg0, derg, m->derg,
        en, m->en, emin, m->emin, de, m->de);
    goto ERR;
  }
  p = s + next;
  if (ver >= 2) {
    if (5 != sscanf(p, "%lf%lf%d%lf%d%n", &tp0, &dtp, &tpn, &ensexp, &dhdeorder, &next)) {
      fprintf(stderr, "corrupted info line p2 %s", s);
      goto ERR;
    }
    p += next;
    if (tpn != m->tpn || fabs(tp0 - m->tp0) > 1e-6 || fabs(dtp - m->dtp) > 1e-6) {
      fprintf(stderr, "bad temperature range tpn %d %d, tp0 %g %g, dtp %g %g\n",
          tpn, m->tpn, tp0, m->tp0, dtp, m->dtp);
      goto ERR;
    }
  }
  if (3 != sscanf(p, "%lf%lf%lf%n", amp, t, &tp, &next)) {
    fprintf(stderr, "corrupted info line p3 %s", s);
    goto ERR;
  }
  tmh_settp(m, tp);
  p += next;
  if (m->wl) {
    double nupd = *t, lnfwl = *amp, lnfc = (*amp) * (*t);
    if (ver >= 3 && 3 == sscanf(p, "%lf%lf%lf%n", &nupd, &lnfwl, &lnfc, &next))
      p += next;
    if (!(m->wl->flags & WLCVG_UPDLNFC)) lnfc = m->wl->lnfc;
    wlcvg_setnupd(m->wl, nupd, lnfwl, lnfc);
  }

  for (ie = 0; ie <= m->ergn; ie++) {
    if (fgets(s, sizeof s, fp) == NULL) {
      fprintf(stderr, "cannot read line %d\n", ie);
      goto ERR;
    }
    if (2 != sscanf(s, "%lf%lf", &erg, &dhde)) {
      fprintf(stderr, "cannot read energy and dhde at %d\n, s = %s", ie, s);
      goto ERR;
    }
    erg0 = m->erg0 + ie*m->derg;
    if (fabs(erg0 - erg) > m->derg*.1) {
      fprintf(stderr, "energy %g, should be %g\n", erg, erg0);
      goto ERR;
    }
    m->dhde[ie] = dhde;
  }
  fclose(fp);
  return 0;
ERR:
  fclose(fp);
  return -1;
}

/* get energy range from dhde file */
int tmh_loaderange(const char *fn,
    double *tp0, double *tp1, double *dtp,
    double *erg0, double *erg1, double *derg,
    double *emin, double *emax, double *de,
    double *ensexp, int *dhdeorder)
{
  int en, ergn, tpn, ver, next;
  FILE *fp;
  char s[1024];

  xfopen(fp, fn, "r", return -1);
  if (fgets(s, sizeof s, fp) == NULL) {
    fprintf(stderr, "cannot read the first line %s\n", fn);
    goto ERR;
  }

  if (7 != sscanf(s, " # %d%lf%lf%d%lf%lf%d%n",
        &ver, erg0, derg, &ergn, emin, de, &en, &next) || ver < 1) {
    fprintf(stderr, "corrupted info line %s", s);
    goto ERR;
  }
  *erg1 = *erg0 + ergn*(*derg);
  *emax = *emin + en*(*de);

  if (ver >= 2) { /* additional information */
    if (5 != sscanf(s+next, "%lf%lf%d%lf%d", tp0, dtp, &tpn, ensexp, dhdeorder)) {
      fprintf(stderr, "corrupted info line %s", s);
      goto ERR;
    }
    *tp1 = *tp0 + tpn * (*dtp);
  }

  fclose(fp);
  return 0;
ERR:
  fclose(fp);
  return -1;
}

/* write temperature histogram */
int tmh_savetp(tmh_t *m, const char *fn)
{
  int i, j;
  double *eh, erg;
  av_t av[1];
  FILE *fp;

  xfopen(fp, fn, "w", return -1);
  fprintf(fp, "# %g %g %d\n", m->tp0, m->dtp, m->tpn);
  for (i = 0; i < m->tpn; i++) {
    eh = m->tpehis + i*m->en;
    av_clear(av);
    for (j = 0; j < m->en; j++) {
      erg = m->emin + (j + .5) * m->de;
      av_addw(av, erg, eh[j]);
    }
    erg = av_getave(av);
    fprintf(fp, "%g %g %g %g\n",
        m->tp0 + (i+.5)*m->dtp, av->s, erg, av_getdev(av));
  }
  fclose(fp);
  return 0;
}

/* calculate the modified Hamiltonian */
INLINE int tmh_calcmh(tmh_t *m)
{
  int i, en = m->en;
  double erg, hm, dh, de = m->de, emin = m->emin;

  hm = emin;
  for (i = 0; i < en; i++) {
    erg = emin + (i + .5) * de;
    dh = de * tmh_getdhde(m, erg);
    m->mh[i] = hm + .5 * dh;
    hm += dh;
  }
  return 0;
}

/* iteratively compute the density of states
 * we inline the function as it's rarely used */
INLINE int tmh_calcdos(tmh_t *m, int itmax, double tol,
    const char *fndos, const char *fnlnz)
{
  int i, j, it, ie0, ie1, en = m->en, tpn = m->tpn;
  double x, dif, lnz0, db;
  double *lnn, *lnm, *bet, *lnz1;
  const double LOG0 = -1e10;
  FILE *fp;

  if (itmax <= 0) itmax = 1000;

  /* determine nonempty energy range for more efficient loops */
  for (ie0 = 0; ie0 < en; ie0++) {
    for (j = 0; j < m->tpn; j++)
      if (m->tpehis[j*en + ie0] > 0.) break;
    if (j < m->tpn) break;
  }
  for (ie1 = en; ie1 > ie0; ie1--) {
    for (j = 0; j < m->tpn; j++)
      if (m->tpehis[j*en + ie1-1] > 0.) break;
    if (j < m->tpn) break;
  }

  /* n[j] is the total number of visits to temperature j
   * m[i] is the total number of visits to energy i */
  xnew(lnn, tpn);
  xnew(lnm, en);
  for (i = 0; i < en; i++) lnm[i] = 0.;
  for (j = 0; j < tpn; j++) {
    lnn[j] = 0.;
    for (i = ie0; i < ie1; i++) {
      x = m->tpehis[j*en + i];
      lnn[j] += x;
      lnm[i] += x;
    }
  }
  for (j = 0; j < tpn; j++)
    lnn[j] = (lnn[j] > 0.) ? log(lnn[j]) : LOG0;
  for (i = 0; i < en; i++)
    lnm[i] = (lnm[i] > 0.) ? log(lnm[i]) : LOG0;

  xnew(bet, tpn);
  for (j = 0; j < tpn; j++) {
    double tp = m->tp0 + (j + .5) * m->dtp;
    if (m->dtp > 0.) bet[j] = m->scl / tp;
    else bet[j] = m->scl * tp;
  }

  /* get mh and lnz */
  for (i = 0; i < en; i++) m->lng[i] = LOG0;
  tmh_calcmh(m);
  /* estimate initial lnz */
  for (lnz0 = 0., j = 0; j < tpn; j++) {
    x = m->erg0 + (j+.5)*m->dtp * m->dergdt;
    i = (int)((x - m->emin)/m->de);
    die_if (i < 0 || i >= en, "i %d, x %g\n", i, x);
    db = 1.0/(m->tp0 + (j+1)*m->dtp)
       - 1.0/(m->tp0 + j*m->dtp);
    x = m->mh[i]*db;
    m->lnz[j] = lnz0 - x*.5;
    lnz0 -= x;
  }
  for (j = tpn - 1; j >= 0; j--)
     m->lnz[j] -= m->lnz[0];

  xnew(lnz1, tpn);

  /* repeat until convergence */
  for (it = 0; it < itmax; it++) {
    /* compute the density of states */
    for (i = ie0; i < ie1; i++) {
      for (x = LOG0, j = 0; j < tpn; j++) {
        x = lnadd(x, lnn[j] - bet[j]*m->mh[i] - m->lnz[j]);
      }
      m->lng[i] = (lnm[i] < LOG0+.1) ? LOG0 : (lnm[i] - x);
    }

    /* update partition function */
    for (j = 0; j < tpn; j++) {
      for (x = LOG0, i = ie0; i < ie1; i++)
        x = lnadd(x, m->lng[i] - bet[j]*m->mh[i]);
      lnz1[j] = x;
    }
    for (j = tpn - 1; j >= 0; j--)
      lnz1[j] -= lnz1[0];

    /* check difference */
    for (dif = 0., j = 1; j < tpn; j++) {
      x = fabs(m->lnz[j] - lnz1[j]);
      if (x > dif) dif = x;
    }
    for (j = 0; j < tpn; j++) m->lnz[j] = lnz1[j];
    if (dif < tol) break;
  }

  /* write dos */
  if (fndos && (fp = fopen(fndos, "w")) != NULL) {
    for (i = ie0; i < ie1; i++) {
      x = m->emin + (i + .5)*m->de;
      fprintf(fp, "%g %g %g %g\n", x, m->lng[i] - m->lng[ie0],
          exp(lnm[i]), m->mh[i]);
    }
    fclose(fp);
  }

  /* write lnz */
  if (fnlnz && (fp = fopen(fnlnz, "w")) != NULL) {
    for (j = 0; j < tpn; j++) {
      fprintf(fp, "%g %g %g\n", bet[j], m->lnz[j], exp(lnn[j]));
    }
    fclose(fp);
  }
  free(lnm);
  free(lnn);
  free(bet);
  free(lnz1);
  return 0;
}

#endif /* ZCOM_TMH__ */
#endif /* ZCOM_TMH */

#ifdef  ZCOM_ISING2
#ifndef ZCOM_ISING2__
#define ZCOM_ISING2__


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

typedef struct {
  int d, l, n;
  int M, E;
  int *s; /* 0 or 1 */
  double *logdos; /* logarithmic density of states */
  /* helper vars */
  uint32_t *uproba; /* temporary probability for MC transitions */
} ising_t;

INLINE int     is2_em(ising_t *is);
INLINE int     is2_check(ising_t *is);
INLINE int     is2_load(ising_t *is, const char *fname);
INLINE int     is2_save(const ising_t *is, const char *fname);
INLINE double  is2_exact(ising_t *is, double beta, double *eav, double *cv);
INLINE int     is2loadlogdos(double *logdos, int n, int m, const char *fn);
#define is2_loadlogdos(is, fn)  is2loadlogdos(is->logdos, is->l, is->l, fn)
INLINE int     is2_pick(const ising_t *is, int *h);
INLINE int     is2_flip(ising_t *is, int id, int h);
ising_t*  is2_open(int l);
STRCLS void      is2_close(ising_t *is);

/* set transition probability */
#define IS2_SETPROBA(is, bet) { \
  double x_ = exp(-4. * bet); \
  is->uproba[2] = (uint32_t) ((double)(0xffffffff) * x_); \
  is->uproba[4] = (uint32_t) ((double)(0xffffffff) * x_*x_); }

/* faster macros for systems with fixed (upon compiling) size
 * to use them one must define IS2_LB before including
 * IS2_PICK()/IS2_PSEQ() and IS2_FLIP() */
#ifdef  IS2_LB  /* L = 2^LB, N = L*L */
#define IS2_L   (1 << IS2_LB)
#define IS2_N   (IS2_L * IS2_L)

#define IS2_GETH(is, id, h) { \
  unsigned ix, iy; \
  iy = id / IS2_L, ix = id % IS2_L; \
  h = is->s[id]*(is->s[iy*IS2_L + (ix+1)%IS2_L] \
               + is->s[iy*IS2_L + (ix+IS2_L-1)%IS2_L] \
               + is->s[(iy+1)%IS2_L*IS2_L + ix] \
               + is->s[(iy-1+IS2_L)%IS2_L*IS2_L + ix]); }
#define IS2_IRND(is, id)  id = rand32() >> (32 - 2*IS2_LB);
/* random picking */
#define IS2_PICK(is, id, h) { IS2_IRND(is, id); IS2_GETH(is, id, h); }
#define IS2_ISEQ(is, id)  id = (id + 1) % IS2_N;
/* sequential picking */
#define IS2_PSEQ(is, id, h) { IS2_ISEQ(is, id); IS2_GETH(is, id, h); }

#define IS2_FLIP(is, id, h) { \
  is->M += (is->s[id] = -is->s[id]) * 2; \
  is->E += h * 2; }

#else

#define IS2_PICK(is, id, h)  id = is2_pick(is, &h)
#define IS2_FLIP(is, id, h)  is2_flip(is, id, h)
#endif /* IS2_LB */


/* compute total energy and magnetization */
INLINE int is2_em(ising_t *is)
{
  int l, i, j, s, u, e, m, *p, *pu;

  e = m = 0;
  p = is->s;
  l = is->l;
  for (i = 0; i < l; ) {
    pu = (++i == l) ? is->s : p+l;
    for (j = 0; j < l; ) {
      m += (s = *p++);
      u = *pu++;
      e += s*(u + ((++j == l) ? *(p-l) : *p));
    }
  }
  is->M = m;
  return is->E = -e;
}

INLINE int is2_check(ising_t *is)
{
  int i, e, m;

  for (i = 0; i < is->n; i++)
    if (is->s[i] != 1 && is->s[i] != -1) {
      fprintf(stderr, "error: s[%d] = %d\n", i, is->s[i]);
      return -1;
    }
  e = is->E;
  m = is->M;
  is2_em(is);
  if  (e != is->E || e < -2*is->n || e > 2*is->n
    || m != is->M || m < -is->n   || m > is->n) {
    fprintf(stderr, "error: E = %d, %d; M = %d, %d\n",
        e, is->E, m, is->M);
    return -1;
  }
  return 0;
}

/* pick a random site, count neighbors with different spins */
INLINE int is2_pick(const ising_t *is, int *h)
{
  int id, ix, iy, l, lm, n, nm, *p;

  lm = (l = is->l) - 1;
  nm = (n = is->n) - l;
  id = (int)(rnd0() * n);
  iy = id / l, ix = id % l;
  p = is->s + id;
  *h = *p * ( ((ix != 0 ) ? *(p-1) : *(p+lm))   /* left  */
            + ((ix != lm) ? *(p+1) : *(p-lm))   /* right */
            + ((iy != 0 ) ? *(p-l) : *(p+nm))   /* down  */
            + ((iy != lm) ? *(p+l) : *(p-nm))); /* up    */
  return id;
}

/* flip site id, with h different neighbors */
INLINE int is2_flip(ising_t *is, int id, int h)
{
  assert(id < is->n);
  is->M += (is->s[id] = -is->s[id])*2;
  return is->E += h*2;
}

INLINE int is2_load(ising_t *is, const char *fname)
{
  FILE *fp;
  int i, lx, ly, n, c;
  char s[80];

  xfopen(fp, fname, "r", return -1);
  if (fgets(s, sizeof s, fp) == NULL) {
    fprintf(stderr, "missing first line %s\n", fname);
    return -1;
  }
  if (4 != sscanf(s, "%d%d%d%d", &i, &lx, &ly, &n)
      || i != 2 || lx != ly || lx != is->l || n != is->n) {
    fprintf(stderr, "bad setting: %dD, %dx%d = %d\n", i, lx, ly, n);
    return -1;
  }
  for (i = 0; i < n; i++) {
    while ((c=fgetc(fp)) != EOF && c == '\n') ;
    if (c == EOF) break;
    is->s[i] = (c == ' ') ? -1 : 1;
  }
  if (i < n)
    fprintf(stderr, "%s: data stopped at i = %d\n", fname, i);
  fclose(fp);
  is2_em(is);
  return 0;
}

INLINE int is2_save(const ising_t *is, const char *fname)
{
  FILE *fp;
  int i, j, l, *p;

  xfopen(fp, fname, "w", return -1);
  l = is->l;
  fprintf(fp, "%d %d %d %d\n", is->d, l, l, is->n);
  for (p = is->s, i = 0; i < l; i++) {
    for (j = 0; j < l; j++, p++)
      fprintf(fp, "%c", (*p > 0) ? '#' : ' ');
    fprintf(fp, "\n");
  }
  fclose(fp);
  return 0;
}

/* initialize an lxl Ising model */
ising_t *is2_open(int l)
{
  int i, n;
  ising_t *is;

  xnew(is, 1);
  is->d = 2;
  is->l = l;
  is->n = n = l*l;
  xnew(is->s, n);
  for (i = 0; i < n; i++) is->s[i] = -1;
  is->M = -n;
  is->E = -2*n;
  xnew(is->logdos, n + 1);
  xnew(is->uproba, 2*is->d+1);
  is->uproba[0] = 0xffffffff;
  return is;
}

void is2_close(ising_t *is)
{
  if (is != NULL) {
    free(is->s);
    free(is->logdos);
    free(is->uproba);
    free(is);
  }
}

/* exact solution of ising model */
INLINE double is2_exact(ising_t *is, double beta, double *eav, double *cv)
{
  double lxh, n, ex, f, th, sech, bet2, bsqr, log2, x;
  double lnz, lnz1, lnz2, lnz3, lnz4, dz, ddz;
  double z21, z31, z41, za1;
  double dr1, dr2, dr3, dr4, ddr1, ddr2, ddr3, ddr4;
  double g, g0, dg, ddg, dg0;
  double xn2b, sh2b, coth2b;
  double lnch2b, lncc2b, lncl, lnsl, cd, cdsqr, lnddcl;
  int r, sgn4 = 1, lx, ly;

  lx = is->l;
  ly = is->l;
  lxh = .5*lx;
  n = lx * ly;
  log2 = log(2.0);
  bet2 = 2.*beta;
  bsqr = beta*beta;
  xn2b = exp(-bet2);
  if (lx == 2 && ly == 2) { /* 2x2 system */
    double lnc, lnd;
    x = 8.*beta;
    lnc = lnadd(x, -x);
    lnd = lnaddn(lnc, 6.);
    lnz = lnd + log2;
    if (eav) *eav = -8.*exp(lndif(x, -x) - lnd); /* -8*sinh(8*b)/(3+cosh(8*h)) */
    if (cv) *cv = bsqr * 384. * exp(lnaddn(lnc,2./3) - 2.0*lnd); /* 64*(1+3cosh(8*b))/(3+cosh(8*b))^2 */
    return lnz;
  } else if (fabs(beta) < 1e-6) { /* high T approx. normal branch unstable if beta < 1e-6 */
    lnz = n * (2.*lnadd(beta, -beta) - log2);
    x = 1. + xn2b;
    if (eav) *eav = -2. * n * (1. - xn2b)/x;
    if (cv) *cv = bsqr * 8.*n*xn2b/(x*x);
    return lnz; /* +n*tanh(beta)^4 */
  }

  lnz1 = lnz2 = lnz3 = lnz4 = 0;
  dr1 = dr2 = dr3 = dr4 = 0;
  ddr1 = ddr2 = ddr3 = ddr4 = 0;
  lnch2b = lnadd(bet2, -bet2) - log2;
  coth2b = 2./(1. - xn2b*xn2b) - 1.;
  lncc2b = lnch2b + log(coth2b); /* ln[ cosh(2b) * coth(2b) ] */
  g0 = bet2 + log(2./(1. + xn2b) - 1.);
  sgn4 = (g0 >= 0) ? 1 : -1;

  sh2b = 0.5*(1./xn2b - xn2b);
  dg0 = 2. + 2./sh2b;
  x = sh2b*sh2b;
  cd = 2. - 2./x; /* cl' = cd * cosh(2b) */
  cdsqr = cd*cd;
  lnddcl = lnaddn(lncc2b, 2.0/(x * sh2b)) + 2.*log2; /* log(cl'') */

  for (r = 0; r < ly; r++) { /* for odd number */
    lncl = lnaddn(lncc2b, -cos((2.*r + 1.)*M_PI/ly));
    lnsl = lncl + 0.5*log(1. - exp(-2.*lncl));
    g = lnadd(lncl, lnsl);
    f = lxh*g;
    lnz1 += lnadd(f, -f);
    lnz2 += lndif(f, -f);

    dg = exp(lnch2b - lnsl)*cd; /* g' = cl'/sl; */
    ex = exp(-f);
    th = 2./(1. + ex*ex) - 1.;
    x = lxh*dg;
    dr1 += x*th;
    dr2 += x/th;

    /* g''=cl''/sl - cl' ^2 *cl/sl^3; */
    ddg = exp(lnddcl - lnsl);
    ddg -= exp(lnch2b*2. + lncl - 3.*lnsl)*cdsqr;
    sech = 2.0*dg/(ex + 1.0/ex); /* g' * sech(0.5*lx*g) */
    ddr1 += lxh*(ddg*th + lxh*(sech*sech));
    sech = 2.0*dg/(ex - 1.0/ex); /* g' * sech(0.5*lx*g) */
    ddr2 += lxh*(ddg/th - lxh*(sech*sech));

    if (r == 0) {
      g = g0;
    } else {
      lncl = lnaddn(lncc2b, -cos(2.0*M_PI*r/ly));
      lnsl = lncl+0.5*log(1-exp(-2*lncl));
      g = lnadd(lncl, lnsl);
      die_if (g < 0.0, "g = %g < 0.\n", g);;
    }
    f = lxh*g;
    lnz3 += lnadd(f, -f); /* log [2 cosh(f)] */
    lnz4 += (f < 0) ? lndif(-f, f) : lndif(f, -f); /* avoid neg. g0 */

    ex = exp(-f);
    th = 2./(1. + ex*ex) - 1.;
    dg = (r == 0) ? dg0 : exp(lnch2b - lnsl)*cd;
    dr3 += lxh*dg*th;
    dr4 += lxh*dg/th;

    if (r == 0) {
      ddg = -4*coth2b*coth2b*exp(-lnch2b);
    } else {
      ddg = exp(lnddcl - lnsl);
      ddg -= exp(lnch2b*2. + lncl - 3.*lnsl)*cdsqr;
    }
    sech = 2.0*dg/(ex + 1.0/ex);
    ddr3 += lxh*(ddg*th + lxh*(sech*sech));
    sech = 2.0*dg/(ex - 1.0/ex);
    ddr4 += lxh*(ddg/th - lxh*(sech*sech));
  }

  z21 = exp(lnz2 - lnz1);
  z31 = exp(lnz3 - lnz1);
  z41 = sgn4*exp(lnz4 - lnz1);
  za1 = 1.0 + z21 + z31 + z41;
  lnz = lnz1 + log(za1);
  lnz += .5*n*log(2.*sh2b) - log2;
  dz = (dr1 + z21*dr2 + z31*dr3 + z41*dr4)/za1;
  if (eav) *eav = - n*coth2b - dz;
  ddr1 += dr1*dr1;
  ddr2 += dr2*dr2;
  ddr3 += dr3*dr3;
  ddr4 += dr4*dr4;
  ddz = (ddr1 + z21*ddr2 + z31*ddr3 + z41*ddr4)/za1;
  if (cv) *cv = bsqr * (-2.*n/(sh2b*sh2b) + ddz - dz*dz);
  return lnz;
}

/* load the exact logarithmic density of states from file
 * both n and m should be is->l
 * Minimal Mathematica script to generate exact DOS files

NDOS[m_, n_] := Module[{x, xp, prec = Floor[1.5 n m Log[2]/Log[10]], b, a, c2, s2, c0, s0, cn, sn},
  b = 2 x (1 - x^2);
  a[k_] := (1 + x^2)^2 - b Cos[Pi k/n];
  c0 = (1 - x)^m + x^m (1 + x)^m;
  s0 = (1 - x)^m - x^m (1 + x)^m;
  cn = (1 + x)^m + x^m (1 - x)^m;
  sn = (1 + x)^m - x^m (1 - x)^m;
  c2[k_] := (Sum[ m!/(2 j)!/(m - 2 j)! (a[k]^2 - b^2)^j a[k]^(m - 2 j), {j, 0, IntegerPart[m/2]}] + b^m)/2^(m - 1);
  s2[k_] := (Sum[ m!/(2 j)!/(m - 2 j)! (a[k]^2 - b^2)^j a[k]^(m - 2 j), {j, 0, IntegerPart[m/2]}] - b^m)/2^(m - 1);
  xp = Expand[ N[ (1/2) If[Mod[n, 2] == 0,
    Product[c2[2 k + 1], {k, 0, n/2 - 1}]
  + Product[s2[2 k + 1], {k, 0, n/2 - 1}]
  + c0 cn Product[c2[2 k], {k, 1, n/2 - 1}]
  + s0 sn Product[s2[2 k], {k, 1, n/2 - 1}],
    cn Product[c2[2 k + 1], {k, 0, (n - 3)/2}]
  + sn Product[s2[2 k + 1], {k, 0, (n - 3)/2}]
  + c0 Product[c2[2 k], {k, 1, (n - 1)/2}]
  + s0 Product[s2[2 k], {k, 1, (n - 1)/2}]], prec]];
  Take[Round[Chop[CoefficientList[xp, x]]], {1, -1, 2}]];

savels[fn_, ls_] := Module[{fp = OpenWrite[fn], i},
  For[i = 1, i <= Length[ls], i++, Write[fp, ls[[i]]]]; Close[fp]];

easydos[n_, m_] := Module[{dos = NDOS[n, m], logdos = Table[0, {n m + 1}], i},
  savels["IsingDOS" <> ToString[n] <> "x" <> ToString[m] <> ".txt", dos];
  For[i = 1, i <= n m + 1, i++,
    logdos[[i]] = If[dos[[i]] == 0, -10000, N[Log[dos[[i]]], 17]]];
  savels["islogdos" <> ToString[n] <> "x" <> ToString[m] <> ".txt", logdos]];
  */
INLINE int is2loadlogdos(double *logdos, int n, int m, const char *fn)
{
  char s[1024];
  FILE *fp;
  int i, err = 0;

  if (fn == NULL) { /* use standard file name */
    sprintf(s, "islogdos%dx%d.txt", n, m);
    fn = s;
  }
  xfopen(fp, fn, "r", return -1);

  for (i = 0; i <= n*m;  i++) {
    if (fgets(s, sizeof s, fp) == NULL) {
      printf("file %s ended at line %d/%d\n", fn, i, n*m);
      err = 1;
      break;
    }
    if (1 != sscanf(s, "%lf", &logdos[i])) {
      printf("sscanf failed in reading %s, line %d/%d\n", fn, i, n*m);
      err = 2;
      break;
    }
  }
  fclose(fp);
  return err;
}

#endif /* ZCOM_ISING2__ */
#endif /* ZCOM_ISING2 */

#ifdef  ZCOM_POTTS2
#ifndef ZCOM_POTTS2__
#define ZCOM_POTTS2__


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

typedef struct {
  int d; /* dimension */
  int q; /* number of states of each spin */
  int l, n;
  int E;  /* potential energy */
  int *M; /* M[0..q-1] number of spins in each state */
  int *s; /* s[0..n-1], each s[i] in 0..q-1 */
  /* helper vars */
  double *accprb; /* temporary accumulated probabilities, for heat bath */
  uint32_t *uproba; /* temporary probability for MC transitions */
  double *dproba;
} potts_t;

INLINE int pt2_em(potts_t *pt);
INLINE int pt2_load(potts_t *pt, const char *fname);
INLINE int pt2_save(const potts_t *pt, const char *fname);
STRCLS potts_t *pt2_open(int l, int q);
STRCLS void pt2_close(potts_t *pt);

INLINE int pt2_check(potts_t *pt)
{
  int i, e, *mg, q = pt->q;

  for (i = 0; i < pt->n; i++) /* check spin value */
    die_if (pt->s[i] < 0 || pt->s[i] >= q, "s[%d] %d, q %d\n", i, pt->s[i], q);
  e = pt->E;
  xnew(mg, q);
  for (i = 0; i < q; i++) mg[i] = pt->M[i];
  die_if (e != pt2_em(pt), "error: E = %d, should be %d\n", e, pt->E);
  for (i = 0; i < q; i++)
    die_if (mg[i] != pt->M[i], "error: M(%d) = %d, should be %d", i, mg[i], pt->M[i]);
  free(mg);
  return 0;
}

#define PT2_SETPROBA(pt, bet) { \
  double x_ = exp(-bet), prd_; \
  prd_  = x_; pt->dproba[1] = prd_; pt->uproba[1] = (uint32_t) (4294967295. * prd_); \
  prd_ *= x_; pt->dproba[2] = prd_; pt->uproba[2] = (uint32_t) (4294967295. * prd_); \
  prd_ *= x_; pt->dproba[3] = prd_; pt->uproba[3] = (uint32_t) (4294967295. * prd_); \
  prd_ *= x_; pt->dproba[4] = prd_; pt->uproba[4] = (uint32_t) (4294967295. * prd_); \
}

/* faster macros for systems with fixed (upon compiling) size
 * to use them one must define PT2_LB and PT2_Q before including
 * PT2_PICK()/PT2_PSEQ() and PT2_FLIP() */
#ifdef  PT2_LB  /* L = 2^LB, N = L*L */
#define PT2_L   (1 << PT2_LB)
#define PT2_N   (PT2_L * PT2_L)

#define PT2_GETH(pt, id, h) { \
  unsigned ix, iy; \
  for (ix = 0; ix < PT2_Q; ix++) h[ix] = 0; \
  iy = id / PT2_L, ix = id % PT2_L; \
  h[ pt->s[iy*PT2_L + (ix+1)%PT2_L]       ]++; \
  h[ pt->s[iy*PT2_L + (ix+PT2_L-1)%PT2_L] ]++; \
  h[ pt->s[(iy+1)%PT2_L*PT2_L + ix]       ]++; \
  h[ pt->s[(iy-1+PT2_L)%PT2_L*PT2_L + ix] ]++; }
#define PT2_IRND(pt, id)  id = rand32() >> (32 - 2*PT2_LB);
/* random pick */
#define PT2_PICK(pt, id, h) { PT2_IRND(pt, id); PT2_GETH(pt, id, h); }
#define PT2_ISEQ(pt, id)  id = (id + 1) % PT2_N;
/* sequential pick */
#define PT2_PSEQ(pt, id, h) { PT2_ISEQ(pt, id); PT2_GETH(pt, id, h); }

/* change spin id from so to sn (use PT2_Q instead of pt->q) */
#define PT2_NEWFACE(pt, id, so, sn) { \
  so = pt->s[id]; sn = (so + 1 + (int)(rnd0()*(PT2_Q - 1))) % PT2_Q; }

/* change spin id from so to sn according to heat bath algorithm
 * local accprb is somehow faster */
#define PT2_HEATBATH(pt, id, so, sn, h) { \
  static double accprb[PT2_Q+1] = {0.,}; double rs_; \
  so = pt->s[id]; \
  for (sn = 0; sn < PT2_Q; sn++) accprb[sn+1] = accprb[sn] + pt->dproba[4-h[sn]]; \
  for (rs_ = accprb[PT2_Q]*rnd0(), sn = 0; sn < PT2_Q; sn++) if (accprb[sn+1] > rs_) break; \
}

#define PT2_FLIP(pt, id, so, sn, h) { \
  pt->s[id] = sn; \
  pt->M[so]--; \
  pt->M[sn]++; \
  pt->E += h[so] - h[sn];  }

#else  /* non-macro version */

#define PT2_PICK(pt, id, h)  id = pt2_pick(pt, h)
#define PT2_NEWFACE(pt, id, so, sn) { \
  so = pt->s[id]; sn = (so + 1 + (int)(rnd0()*(pt->q - 1))) % (pt->q); }
#define PT2_HEATBATH(pt, id, so, sn, h) \
  pt2_heatbath(pt, id, &so, &sn, h)
#define PT2_FLIP(pt, id, so, sn, h) {so = pt->s[id]; pt2_flip(pt, id, sn, h); }

INLINE int pt2_pick(const potts_t *pt, int h[])
{
  int i, id, ix, iy, l, lm, n, nm, *p;
  int sl, sr, sd, su;

  lm = (l = pt->l) - 1;
  nm = (n = pt->n) - l;
  id = (int)(rnd0() * n);
  iy = id / l, ix = id % l;
  p = pt->s + id;
  for (i = 0; i < pt->q; i++) h[i] = 0;
  sl = ((ix != 0 ) ? *(p-1) : *(p+lm)); h[sl]++;
  sr = ((ix != lm) ? *(p+1) : *(p-lm)); h[sr]++;
  sd = ((iy != 0 ) ? *(p-l) : *(p+nm)); h[sd]++;
  su = ((iy != lm) ? *(p+l) : *(p-nm)); h[su]++;
  return id;
}

INLINE int pt2_heatbath(potts_t *pt, int id, int *so, int *sn,
    const int h[])
{
  double rs_;
  int i, mx_ = 4;
  *so = pt->s[id];
  for (i = 0; i < pt->q; i++)
    pt->accprb[i+1] = pt->accprb[i] + pt->dproba[mx_-h[i]];
  for (rs_ = pt->accprb[pt->q]*rnd0(), i = 0; i < pt->q; i++)
    if (pt->accprb[i+1] > rs_) break;
  die_if (i >= pt->q, "no suitable selection, i = %d\n", i);
  *sn = i;
  return 0;
}

/* flip site `id' to `sn', with h different neighbors */
INLINE int pt2_flip(potts_t *pt, int id, int sn, const int h[])
{
  int so = pt->s[id];
  die_if(id >= pt->n, "id %d >= n %d\n", id, pt->n);
  die_if(sn >= pt->q || sn < 0, "invalid sn %d (q = %d)\n", sn, pt->q);
  pt->s[id] = sn;
  pt->M[so]--;
  pt->M[sn]++;
  return pt->E += h[so] - h[sn];
}

#endif /* PT2_LB */



/* compute the total energy and magnetization */
INLINE int pt2_em(potts_t *pt)
{
  int i, j, l, s, s1, s2, *p;

  pt->E = 0;
  p = pt->s;
  l = pt->l;
  for (i = 0; i < pt->q; i++) pt->M[i] = 0;
  for (i = 0; i < l; i++)
    for (j = 0; j < l; j++) {
      s = p[i*l + j];
      s1 = p[((i+1)%l)*l + j];
      if (s1 == s) pt->E--;
      s2 = p[i*l + (j+1)%l];
      if (s2 == s) pt->E--;
      pt->M[s]++;
    }
  return pt->E;
}

/* pick a random site (return its id)
 * compute h[j], the numbers of neighboring spins with value j */
/* load spin configuration */
INLINE int pt2_load(potts_t *pt, const char *fname)
{
  FILE *fp;
  int i, lx, ly, n, c;
  char s[80];

  xfopen(fp, fname, "r", return -1);
  if (fgets(s, sizeof s, fp) == NULL) {
    fprintf(stderr, "missing first line %s\n", fname);
    return -1;
  }
  if (4 != sscanf(s, "%d%d%d%d", &i, &lx, &ly, &n)
      || i != 2 || lx != ly || lx != pt->l || n != pt->n) {
    fprintf(stderr, "bad setting: %dD, %dx%d = %d\n", i, lx, ly, n);
    return -1;
  }
  for (i = 0; i < n; i++) {
    while ((c=fgetc(fp)) != EOF && c == '\n') ;
    if (c == EOF) break;
    c -= '0';
    if (c < 0 || c >= pt->q) {
      fprintf(stderr, "BAD %s s[%d] = %d, q = %d\n", fname, i, c, pt->q);
      break;
    }
    pt->s[i] = c;
  }
  if (i < n) {
    fprintf(stderr, "%s: data stopped at i = %d, clear\n", fname, i);
    for (i = 0; i < n; i++) pt->s[i] = 0;
  }
  fclose(fp);
  pt2_em(pt); /* re-compute energy/magnetization */
  return 0;
}

/* save spin configuration */
INLINE int pt2_save(const potts_t *pt, const char *fname)
{
  FILE *fp;
  int i, j, l, *p;

  xfopen(fp, fname, "w", return -1);
  l = pt->l;
  fprintf(fp, "%d %d %d %d\n", pt->d, l, l, pt->n);
  for (p = pt->s, i = 0; i < l; i++) {
    for (j = 0; j < l; j++, p++)
      fprintf(fp, "%c", *p+'0');
    fprintf(fp, "\n");
  }
  fclose(fp);
  return 0;
}

/* initialize an lxl q-state Potts model */
potts_t *pt2_open(int l, int q)
{
  int i, n;
  potts_t *pt;

  xnew(pt, 1);
  pt->d = 2;
  pt->q = q;
  pt->l = l;
  pt->n = n = l*l;
  xnew(pt->s, n);
  xnew(pt->M, q);
  for (i = 0; i < n; i++)
    pt->s[i] = 0;
  for (pt->M[0] = n, i = 1; i < q; i++)
    pt->M[i] = 0;
  pt->E = -pt->d * n;
  xnew(pt->accprb, q+1);
  pt->accprb[0] = 0.;
  /* dynamic array of uproba/dproba seems to be faster */
  xnew(pt->uproba, 2*pt->d+1);
  pt->uproba[0] = 0xffffffffu;
  xnew(pt->dproba, 2*pt->d+1);
  pt->dproba[0] = 1.;
  return pt;
}

void pt2_close(potts_t *pt)
{
  if (pt != NULL) {
    free(pt->s);
    free(pt->M);
    free(pt->accprb);
    free(pt->uproba);
    free(pt->dproba);
    free(pt);
  }
}

#endif /* ZCOM_POTTS2__ */
#endif /* ZCOM_POTTS2 */

#ifdef  ZCOM_LJ
#ifndef ZCOM_LJ__
#define ZCOM_LJ__

typedef struct {
  int i, j, in;
  real phi, psi, xi, dx[3], dr2;
} ljpair_t;


#define LJ_SWALLPAIRS 0x100 /* flag of usesw, save all (including out-of-range) pairs */

typedef struct {
  int d; /* dimension = 3 */
  int n; /* number of particles */
  int dof; /* degrees of freedom */
  real rho;
  real l, vol; /* side length and volume */
  real rc2, rc, rcdef; /* real / preferred rc */

  real * RESTRICT x; /* reduced unit (0, 1) */
  real * RESTRICT v, * RESTRICT f;
  real epot0, epot, epots; /* potential energy: pure, with tail correction and shifted potential energy */
  int iepot;  /* integer energy for square-well potential */
  real ekin, tkin, etot;
  real vir; /* virial */
  real epot_shift, epot_tail, p_tail;
  double t;

  int usesw; /* switched potential */
  real rs, a4, a5, a6, a7; /* parameters */
  ljpair_t *pr;
  int npr;
  real lap, f2, *gdg, *xdg;

  int usesq; /* square well potential */
  int esqinf;
  real ra, ra2, rb, rb2; /* -1 for (ra, rb) */
  real rmin; /* minimal pair distance */

  hist_t *rdf; /* histogram for radial distribution function */
  int rdfnfr; /* number of frames in rdf */

  unsigned isclone; /* is a clone copy, don't free pointers */
} lj_t;

/* copy flags */
#define LJ_CPX   0x0001
#define LJ_CPV   0x0002
#define LJ_CPF   0x0004
#define LJ_CPRDF 0x0010
#define LJ_CPPR  0x0020
#define LJ_CPGDG 0x0040
#define LJ_CPXDG 0x0080
#define LJ_CPXVF (LJ_CPX|LJ_CPV|LJ_CPF)

STRCLS lj_t *lj_open(int n, int d, real rho, real rcdef);
STRCLS void lj_close(lj_t *lj);
INLINE lj_t *lj_copy(lj_t *dest, const lj_t *src, unsigned flags);
INLINE lj_t *lj_clone(const lj_t *src, unsigned flags);

INLINE int lj_writepos(lj_t *lj, const real *x, const real *v, const char *fn);
#define LJ_LOADBOX 0x10
INLINE int lj_readpos(lj_t *lj, real *x, real *v, const char *fn, unsigned flags);

/* open rdf */
INLINE hist_t *lj_rdfopen(lj_t *lj, double dr, double rmax);
/* add pairs to the RDF data */
INLINE int lj_rdfadd(lj_t *lj);
/* save rdf, flags can have HIST_NOZEROES */
INLINE int lj_rdfsave(lj_t *lj, const char *fn, unsigned flags);
/* load rdf, flags can have HIST_ADDITION and/or HIST_VERBOSE */
INLINE int lj_rdfload(lj_t *lj, const char *fn, unsigned flags);

/* compute the equation of states */
INLINE double lj_eos3d(double rho, double T, double *P, double *Ar, double *Gr);

/* initialize the square well potential */
INLINE void lj_initsq(lj_t *lj, real ra, real rb);

/* initialize the switched potential */
INLINE void lj_initsw(lj_t *lj, real rs);

STRCLS real lj_energy(lj_t *lj);

INLINE real lj_energyx(lj_t *lj, real *x, real *vir, int *iep, real *rmin,
    real *ep0, real *eps, real *lap);

STRCLS real lj_force(lj_t *lj);

/* Metropolis algorithm */
INLINE int lj_metro(lj_t *lj, real amp, real bet);

/* returns the energy change of a local perturbation */
INLINE real lj_dupertl(lj_t *lj, real amp);

/* return the energy change by an all-atom perturbation */
INLINE real lj_dupertg(lj_t *lj, real amp);

/* compute the configuration temperature */
INLINE real lj_bconfsw3d(lj_t *lj, real *udb);

/* compute pressure */
INLINE real lj_calcp(lj_t *lj, real tp)
  { return (lj->dof * tp + lj->vir) / (lj->d * lj->vol) + lj->p_tail; }

/* compute pressure, ideal gas part from the kinetic energy  */
INLINE real lj_calcpk(lj_t *lj)
  { return (2.f * lj->ekin + lj->vir) / (lj->d * lj->vol) + lj->p_tail; }

/* set density, compute tail corrections, etc */
INLINE void lj_setrho(lj_t *lj, real rho);

#define lj_vv(lj, dt) lj_vvx(lj, 1.f, dt)
INLINE void lj_vvx(lj_t *lj, real fscal, real dt);

#define lj_shiftcom(lj, v)    md_shiftcom(v, lj->n, lj->d)
#define lj_shiftang(lj, x, v) md_shiftang(x, v, lj->n, lj->d)

/* velocity scaling for regular (no thermostat) MD during equilibration
 * `tp' is the target temperature
 * `ekt' is the observed average kinetic energy over several steps */
INLINE void lj_vscale(lj_t *lj, real tp, real ekt)
 { md_vscale(lj->v, lj->n * lj->d, lj->dof, tp, ekt, &lj->ekin, &lj->tkin); }

INLINE void lj_vrescale(lj_t *lj, real tp, real thermdt)
 { md_vrescale(lj->v, lj->n * lj->d, lj->dof, tp, thermdt, &lj->ekin, &lj->tkin); }

INLINE void lj_vrescalex(lj_t *lj, real tp, real thermdt)
 { md_vrescalex(lj->v, lj->n * lj->d, lj->dof, tp, thermdt, &lj->ekin, &lj->tkin); }

INLINE int lj_mcvrescale(lj_t *lj, real tp, real thermdt)
 { return md_mcvrescale(lj->v, lj->n * lj->d, lj->dof, tp, thermdt, &lj->ekin, &lj->tkin); }

/* Nose-Hoover thermostat/barostat
 * set cutoff to half of the box */
INLINE void lj_hoovertp(lj_t *lj, real dt, real tp, real pext,
    real *zeta, real *eta, real Q, real W, int ensx)
{
  md_hoovertp(lj->v, lj->n, lj->d, lj->dof, dt, tp, pext, zeta, eta,
      Q, W, lj->vol, lj->vir, lj->p_tail, ensx, &lj->ekin, &lj->tkin);
}

/* Nose-Hoover chain thermostat/barostat
 * set cutoff to half of the box */
INLINE void lj_nhchaintp(lj_t *lj, real dt, real tp, real pext,
    real *zeta, real *eta, const real *Q, int M, real W, int ensx)
{
  md_nhchaintp(lj->v, lj->n, lj->d, lj->dof, dt, tp, pext, zeta, eta,
      Q, M, W, lj->vol, lj->vir, lj->p_tail, ensx, &lj->ekin, &lj->tkin);
}

/* velocity verlet with the scaling step in the Nose-Hoover barostat */
INLINE void lj_vv_hoovertp(lj_t *lj, real dt, real eta);

/* Berendsen barostat: as a backup for a constant pressure simulation */
INLINE void lj_pberendsen(lj_t *lj, real barodt, real tp, real pext);

/* Langevin barostat, with kinetic-energy scaling */
INLINE void lj_langtp(lj_t *lj, real dt, real tp, real pext,
    real zeta, real *eta, real W, int ensx)
{
  md_langtp(lj->v, lj->n, lj->d, dt, tp, pext, zeta, eta,
      W, lj->vol, lj->vir, lj->p_tail, ensx, &lj->ekin, &lj->tkin);
}

/* position Langevin barostat, with kinetic-energy scaling */
INLINE void lj_langtp0(lj_t *lj, real barodt, real tp, real pext, int ensx)
{
  md_langtp0(lj->v, lj->n, lj->d, barodt, tp, pext, &lj->vol,
     lj->vir, lj->p_tail, ensx, &lj->ekin, &lj->tkin);
  lj_setrho(lj, lj->n/lj->vol);
  lj_force(lj);
}

/* old interface */
#define lj_lgvvolmove(lj, barodt, tp, p) lj_langp0(lj, barodt, tp, p, 0)

/* Langevin barostat, with coordinates only, barodt ~ 1e-5 for n = 108 */
INLINE void lj_langp0(lj_t *lj, real barodt, real tp, real pext, int ensx)
{
  md_langp0(lj->dof, lj->d, barodt, tp, pext, &lj->vol, lj->vir, lj->p_tail, ensx);
  lj_setrho(lj, lj->n/lj->vol);
  lj_force(lj);
}

/* In Monte Carlo barostats, we compute the energy directly */
#define LJ_FIXEDRC 0x4000

#define lj_mcprescale(lj, lnvamp, tp, pext, vmin, vmax, ensx) \
  lj_mctp(lj, lnvamp, tp, pext, vmin, vmax, ensx, 0)

/* Monte Carlo barostat, with kinetic-energy scaling */
INLINE int lj_mctp(lj_t *lj, real lnvamp, real tp, real pext,
    real vmin, real vmax, int ensx, unsigned flags);

/* old interface */
#define lj_volmove(lj, lnlamp, tp, p) \
  lj_mcp(lj, lnlamp*lj->d, tp, p, 0, 1e300, 0, LJ_FIXEDRC)

/* Monte Carlo barostat, coordinate only */
INLINE int lj_mcp(lj_t *lj, real vamp, real tp, real pext,
    real vmin, real vmax, int ensx, unsigned flags);


/* initialize a fcc lattice */
static void lj_initfcc2d(lj_t *lj)
{
  int i, j, id, n1, n = lj->n;
  real a;

  n1 = (int) (pow(2*n, 1.0/lj->d) + .999999); /* # of particles per side */
  a = 1.f/n1;
  for (id = 0, i = 0; i < n1 && id < n; i++)
    for (j = 0; j < n1 && id < n; j++) {
      if ((i+j) % 2 != 0) continue;
      lj->x[id*2 + 0] = (i + .5f) * a;
      lj->x[id*2 + 1] = (j + .5f) * a;
      id++;
    }
}

/* initialize a fcc lattice */
static void lj_initfcc3d(lj_t *lj)
{
  int i, j, k, id, n1, n = lj->n;
  real a;

  n1 = (int) (pow(2*n, 1.0/lj->d) + .999999); /* # of particles per side */
  a = 1.f/n1;
  for (id = 0, i = 0; i < n1 && id < n; i++)
    for (j = 0; j < n1 && id < n; j++)
      for (k = 0; k < n1 && id < n; k++) {
        if ((i+j+k) % 2 != 0) continue;
        lj->x[id*3 + 0] = (i + .5f) * a;
        lj->x[id*3 + 1] = (j + .5f) * a;
        lj->x[id*3 + 2] = (k + .5f) * a;
        id++;
      }
}

/* set density and compute tail corrections */
INLINE void lj_setrho(lj_t *lj, real rho)
{
  double irc, irc3, irc6;
  int i;

  lj->rho = rho;
  lj->l = (real) pow(1.*lj->n/rho, 1./lj->d);
  for (lj->vol = 1.f, i = 0; i < lj->d; i++) lj->vol *= lj->l;
  if ((lj->rc = lj->rcdef) > lj->l * .5f) lj->rc = lj->l * .5f;
  lj->rc2 = lj->rc * lj->rc;
  irc = 1.0/lj->rc;
  irc3 = irc*irc*irc; irc6 = irc3*irc3;
  if (lj->usesw) { /* assume u(L/2) = 0 */
    lj->epot_shift = 0.f;
    lj->epot_tail = 0.f;
    lj->p_tail = 0.f;
  } else {
    lj->epot_shift = (real)( 4*irc6*(irc6-1) );
    if (lj->d == 3) {
      lj->epot_tail = (real)( 8*M_PI*rho*lj->n/9*(irc6 - 3)*irc3 );
      lj->p_tail = (real)( 32*M_PI*rho*rho/9*(irc6 - 1.5)*irc3 );
    } else if (lj->d == 2) {
      lj->epot_tail = (real) (M_PI*rho*lj->n*(.4*irc6 - 1)*irc3*irc);
      lj->p_tail = (real) (M_PI*rho*rho*(1.6*irc6 - 2)*irc3*irc);
    }
  }
}

INLINE real lj_pbc(real x, real l)
  { return (real)((x - ((int)((x)+1000.5) - 1000))*l) ; }

INLINE real *lj_vpbc2d(real *v, real l)
  { v[0] = lj_pbc(v[0], l); v[1] = lj_pbc(v[1], l); return v; }

INLINE real *lj_vpbc3d(real *v, real l)
  { v[0] = lj_pbc(v[0], l); v[1] = lj_pbc(v[1], l); v[2] = lj_pbc(v[2], l); return v; }

INLINE real lj_pbcdist2_2d(real *dx, const real *a, const real *b, real l)
  { return rv2_sqr(lj_vpbc2d(rv2_diff(dx, a, b), l)); }

INLINE real lj_pbcdist2_3d(real *dx, const real *a, const real *b, real l)
  { return rv3_sqr(lj_vpbc3d(rv3_diff(dx, a, b), l)); }

/* create an open structure */
lj_t *lj_open(int n, int d, real rho, real rcdef)
{
  lj_t *lj;
  int i;

  xnew(lj, 1);
  lj->n = n;
  lj->d = d;
  lj->dof = n * d - d * (d+1)/2;
  xnew(lj->f, n * d);
  xnew(lj->v, n * d);
  xnew(lj->x, n * d);

  lj->rcdef = rcdef;
  lj_setrho(lj, rho);

  lj->esqinf = 1000000;

  if (lj->d == 3) lj_initfcc3d(lj); else lj_initfcc2d(lj);

  /* init. random velocities */
  for (i = 0; i < n * d; i++) lj->v[i] = (real) (rnd0() - .5);

  lj_shiftcom(lj, lj->v);
  lj_shiftang(lj, lj->x, lj->v);
  lj->ekin = md_ekin(lj->v, lj->n * lj->d, lj->dof, &lj->tkin);

  lj->isclone = 0;

  lj_force(lj);
  return lj;
}

/* copy from src to dest
 * cannot copy vectors other than xvf */
INLINE lj_t *lj_copy(lj_t *dest, const lj_t *src, unsigned flags)
{
  int nd = src->n * src->d;
  /* to preserve the pointers */
  real *x = dest->x, *v = dest->v, *f = dest->f;

  memcpy(dest, src, sizeof(lj_t));

  if (flags & LJ_CPX) memcpy(x, src->x, sizeof(real) * nd);
  dest->x = x;
  if (flags & LJ_CPV) memcpy(v, src->v, sizeof(real) * nd);
  dest->v = v;
  if (flags & LJ_CPF) memcpy(f, src->f, sizeof(real) * nd);
  dest->f = f;
  return dest;
}

/* make new copy */
INLINE lj_t *lj_clone(const lj_t *src, unsigned flags)
{
  int nd = src->n * src->d;
  lj_t *dest;

  xnew(dest, 1);
  memcpy(dest, src, sizeof(lj_t));
  /* unless specified in flags,
   * arrays are copied literally as pointers */
  dest->isclone = LJ_CPRDF | LJ_CPPR | LJ_CPGDG | LJ_CPXDG;
  if (flags & LJ_CPX) {
    xnew(dest->x, nd);
    memcpy(dest->x, src->x, sizeof(real) * nd);
  } else {
    dest->isclone |= LJ_CPX;
  }
  if (flags & LJ_CPV) {
    xnew(dest->v, nd);
    memcpy(dest->v, src->v, sizeof(real) * nd);
  } else {
    dest->isclone |= LJ_CPV;
  }
  if (flags & LJ_CPF) {
    xnew(dest->f, nd);
    memcpy(dest->f, src->f, sizeof(real) * nd);
  } else {
    dest->isclone |= LJ_CPF;
  }
  return dest;
}

void lj_close(lj_t *lj)
{
  if ( !(lj->isclone & LJ_CPX) ) free(lj->x);
  if ( !(lj->isclone & LJ_CPV) ) free(lj->v);
  if ( !(lj->isclone & LJ_CPF) ) free(lj->f);
  if ( !(lj->isclone & LJ_CPPR)  && lj->pr)
    free(lj->pr);
  if ( !(lj->isclone & LJ_CPGDG) && lj->gdg)
    free(lj->gdg);
  if ( !(lj->isclone & LJ_CPXDG) && lj->xdg)
    free(lj->xdg);
  if ( !(lj->isclone & LJ_CPRDF) && lj->rdf)
    hs_close(lj->rdf);
  free(lj);
}

/* write position (and velocity)
 * Note 1: *actual* position, not unit position is used
 * Note 2: coordinates are *not* wrapped back into the box */
INLINE int lj_writepos(lj_t *lj, const real *x, const real *v, const char *fn)
{
  FILE *fp;
  int i, j, d = lj->d, n = lj->n;
  real l = lj->l;

  if (fn == NULL) fn = "lj.pos";
  xfopen(fp, fn, "w", return -1);

  fprintf(fp, "# %d %d %d %.14e\n", d, lj->n, (v != NULL), l);
  for (i = 0; i < n; i++) {
    for (j = 0; j < d; j++) fprintf(fp, "%16.14f ", x[i*d + j] * l);
    if (v)
      for (j = 0; j < d; j++) fprintf(fp, "%16.14f ", v[i*d + j]);
    fprintf(fp, "\n");
  }
  fclose(fp);
  return 0;
}

/* read position file (which may include velocity) */
INLINE int lj_readpos(lj_t *lj, real *x, real *v, const char *fn, unsigned flags)
{
  char s[1024], *p;
  FILE *fp;
  int i, j, hasv = 0, next, d = lj->d, n = lj->n;
  const char *fmt;
  real l = lj->l, xtmp;
  double l0;

  if (fn == NULL) fn = "lj.pos";
  xfopen(fp, fn, "r", return -1);

  if (fgets(s, sizeof s, fp) == NULL || s[0] != '#') { /* simplified format, old version */
    fprintf(stderr, "Warning: %s has no information line\n", fn);
    rewind(fp);
  } else {
    if (4 != sscanf(s + 1, "%d%d%d%lf", &i, &j, &hasv, &l0)
        || i != d || j != lj->n) {
      fprintf(stderr, "first line is corrupted:\n%s", s);
      goto ERR;
    }
    if (fabs(l0 - l) > 1e-5*l) { /* verify the box size */
      if (flags & LJ_LOADBOX) {
        lj->l = l = (real) l0;
        for (lj->vol = 1, j = 0; j < lj->d; j++) lj->vol *= lj->l;
        lj_setrho(lj, lj->n/lj->vol);
      } else {
        fprintf(stderr, "box mismatch l %g, should be %g\n", l0, l);
        goto ERR;
      }
    }
  }

  fmt = (sizeof(double) == sizeof(real)) ? "%lf%n" : "%f%n";
  for (i = 0; i < n; i++) {
    if (fgets(s, sizeof s, fp) == NULL) goto ERR;
    if (strlen(s) < 10) goto ERR;
    for (p = s, j = 0; j < d; j++, p += next) {
      if (1 != sscanf(p, fmt, &xtmp, &next)) {
        fprintf(stderr, "cannot read i = %d, j = %d\n", i, j);
        goto ERR;
      }
      x[i*d + j] = xtmp / l;
    }
    if (hasv && v != NULL) {
      for (j = 0; j < d; j++, p += next)
        if (1 != sscanf(p, fmt, v + i*d + j, &next)) {
          fprintf(stderr, "cannot read i = %d, j = %d\n", i, j);
          goto ERR;
        }
    }
  }
  fclose(fp);
  return 0;

ERR:
  fprintf(stderr, "position file [%s] appears to be broken on line %d!\n%s\n", fn, i, s);
  fclose(fp);
  return 1;
}

/* code for RDF, cf. hist/testrdf.c */

/* header information in writing rdf */
INLINE int lj_rdffwheader(FILE *fp, void *pdata)
{
  lj_t *lj = (lj_t *) pdata;
  fprintf(fp, "RDF %d %d %d %.10e | ",
      lj->d, lj->rdfnfr, lj->n, lj->l);
  return 0;
}

/* header information in reading rdf */
INLINE int lj_rdffrheader(const char *s, void *pdata)
{
  lj_t *lj = (lj_t *) pdata;
  int ret, d, n;
  double l;

  ret = sscanf(s, " RDF %d%d%d%lf | ", &d, &(lj->rdfnfr), &n, &l);
  die_if (d != lj->d, "dimension mismatch %d vs. %d (file)\n", lj->d, d);
  die_if (n != lj->n, "# of particle mismatch %d vs. %d (file)\n", lj->n, n);
  die_if (fabs(l - lj->l) > 1e-3, "box size mismatch %d vs. %d (file)\n", lj->l, l);
  return (ret == 4) ? 0 : 1;
}

INLINE double lj_rdfnorm(int row, int i, double xmin, double dx, void *pdata)
{
  lj_t *lj = (lj_t *) pdata;
  int npr;
  double x, vsph;

  (void)row;
  x = xmin + i*dx;
  if (lj->d == 2)
    vsph = 2.*M_PI*dx*(2*x + dx);
  else
    vsph = (4.*M_PI/3)*dx*(3*x*(x+dx) + dx*dx);
  npr = lj->n * (lj->n - 1)/2;
  return lj->vol / (vsph * npr * lj->rdfnfr);
}

INLINE hist_t *lj_rdfopen(lj_t *lj, double dr, double rmax)
{
  lj->rdfnfr = 0;
  if (rmax <= 0) rmax = lj->l * .5;
  return lj->rdf = hs_openx(1, 0, rmax, dr,
      lj_rdffwheader, lj_rdffrheader, lj_rdfnorm);
}

/* add pairs to the RDF data */
INLINE int lj_rdfadd(lj_t *lj)
{
  int i, j;
  real rc2, dr2, dx[3];
  double dr;

  rc2 = lj->l/2;
  rc2 = rc2*rc2;
  for (i = 0; i < lj->n; i++) {
    for (j = i + 1; j < lj->n; j++) {
      if (lj->d == 2)
        dr2 = lj_pbcdist2_2d(dx, lj->x + 2*i, lj->x + 2*j, lj->l);
      else
        dr2 = lj_pbcdist2_3d(dx, lj->x + 3*i, lj->x + 3*j, lj->l);
      if (dr2 >= rc2) continue;
      dr = sqrt(dr2);
      hs_add(lj->rdf, &dr, 1.0, HIST_VERBOSE);
    }
  }
  return ++lj->rdfnfr; /* number of frames */
}

/* save rdf, flags can have HIST_NOZEROES */
INLINE int lj_rdfsave(lj_t *lj, const char *fn, unsigned flags)
{
  return hs_savex(lj->rdf, fn, lj, (HIST_ADDAHALF|HIST_KEEPHIST)^flags);
}

/* load rdf, flags can have HIST_ADDITION and/or HIST_VERBOSE */
INLINE int lj_rdfload(lj_t *lj, const char *fn, unsigned flags)
{
  return hs_loadx(lj->rdf, fn, lj, flags);
}

/* compute reference thermal dynamics variables using the equation of states
   return the average potential energy
   *P:  pressure
   *Ar: Helmholtz free energy (potential part)
   *Gr: Gibbs free energy (potential part)
   Reference:
   J. Karl Johnson et al. The Lennard-Jones equation of states revisited,
   Molecular Physics (1993) Vol. 78, No 3, 591-618 */
INLINE double lj_eos3d(double rho, double T, double *P, double *Ar, double *Gr)
{
  const double x1  =  0.8623085097507421;
  const double x2  =  2.976218765822098;
  const double x3  = -8.402230115796038;
  const double x4  =  0.1054136629203555;
  const double x5  = -0.8564583828174598;
  const double x6  =  1.582759470107601;
  const double x7  =  0.7639421948305453;
  const double x8  =  1.753173414312048;
  const double x9  =  2.798291772190376e+03;
  const double x10 = -4.8394220260857657e-02;
  const double x11 =  0.9963265197721935;
  const double x12 = -3.698000291272493e+01;
  const double x13 =  2.084012299434647e+01;
  const double x14 =  8.305402124717285e+01;
  const double x15 = -9.574799715203068e+02;
  const double x16 = -1.477746229234994e+02;
  const double x17 =  6.398607852471505e+01;
  const double x18 =  1.603993673294834e+01;
  const double x19 =  6.805916615864377e+01;
  const double x20 = -2.791293578795945e+03;
  const double x21 = -6.245128304568454;
  const double x22 = -8.116836104958410e+03;
  const double x23 =  1.488735559561229e+01;
  const double x24 = -1.059346754655084e+04;
  const double x25 = -1.131607632802822e+02;
  const double x26 = -8.867771540418822e+03;
  const double x27 = -3.986982844450543e+01;
  const double x28 = -4.689270299917261e+03;
  const double x29 =  2.593535277438717e+02;
  const double x30 = -2.694523589434903e+03;
  const double x31 = -7.218487631550215e+02;
  const double x32 =  1.721802063863269e+02;
  const double gamma = 3.0;
  double a[8], b[6], c[8], d[6], G[6], F, rhop, rho2 = rho*rho, Pa = 0., Pb = 0., U;
  int i;

  a[0] = x1*T + x2*sqrt(T) + x3 + x4/T + x5/(T*T);
  a[1] = x6*T + x7 + x8/T + x9/(T*T);
  a[2] = x10*T + x11 + x12/T;
  a[3] = x13;
  a[4] = x14/T + x15/(T*T);
  a[5] = x16/T;
  a[6] = x17/T + x18/(T*T);
  a[7] = x19/(T*T);
  b[0] = (x20 + x21/T)/(T*T);
  b[1] = (x22 + x23/(T*T))/(T*T);
  b[2] = (x24 + x25/T)/(T*T);
  b[3] = (x26 + x27/(T*T))/(T*T);
  b[4] = (x28 + x29/T)/(T*T);
  b[5] = (x30 + x31/T + x32/(T*T))/(T*T);
  c[0] = x2*sqrt(T)/2 + x3 + 2*x4/T + 3*x5/(T*T);
  c[1] = x7 + 2*x8/T + 3*x9/(T*T);
  c[2] = x11 + 2*x12/T;
  c[3] = x13;
  c[4] = 2*x14/T + 3*x15/(T*T);
  c[5] = 2*x16/T;
  c[6] = 2*x17/T + 3*x18/(T*T);
  c[7] = 3*x19/(T*T);
  d[0] = (3*x20 + 4*x21/T)/(T*T);
  d[1] = (3*x22 + 5*x23/(T*T))/(T*T);
  d[2] = (3*x24 + 4*x25/T)/(T*T);
  d[3] = (3*x26 + 5*x27/(T*T))/(T*T);
  d[4] = (3*x28 + 4*x29/T)/(T*T);
  d[5] = (3*x30 + 4*x31/T + 5*x32/(T*T))/(T*T);

  F = exp(-gamma*rho*rho);
  G[0] = (1 - F)/(2*gamma);
  for (rhop = 1, i = 1; i < 6; i++) {
    rhop *= rho*rho;
    G[i] = -(F*rhop - 2*i*G[i-1])/(2*gamma);
  }

  if (Ar) *Ar = 0.;
  if (P)  Pa = Pb = 0;
  for (U = 0, i = 7; i >= 0; i--) {
    U = rho * (c[i]/(i+1) + U);
    if (Ar) *Ar = rho * (a[i]/(i+1) + (*Ar));
    if (P)  Pa  = rho * (a[i] + Pa);
  }

  for (i = 5; i >= 0; i--) {
    U += d[i]*G[i];
    if (Ar) *Ar += b[i]*G[i];
    if (P) Pb = rho2*(b[i] + Pb);
  }
  if (P) *P = rho*(T + Pa + F*Pb);
  if (Gr) *Gr = *Ar + *P/rho - T;
  return U;
}

/* initialize square well potential */
INLINE void lj_initsq(lj_t *lj, real ra, real rb)
{
  lj->ra2 = (lj->ra = ra) * ra;
  lj->rb2 = (lj->rb = rb) * rb;
  lj->usesq = 1;
  lj_energy(lj);
}

/* initialize coefficients for the switched potential */
INLINE void lj_initsw(lj_t *lj, real rs)
{
  real rs2, rs3, rs6, rs15, dr, dr2, dr3, dr4, f1, f2, f26, f13;

  lj->rs = rs;
  dr = lj->rs - lj->rc;
  die_if (dr > 0, "rs %g, rc %g\n", lj->rs, lj->rc);

  rs2 = rs*rs;
  rs3 = rs2*rs;
  rs6 = rs3*rs3;
  rs15 = rs6*rs6*rs3;
  dr2 = dr*dr;
  dr3 = dr2*dr;
  dr4 = dr3*dr;
  f1 = rs6 - 1.f;
  f2 = rs6 - 2.f;
  f13 = 2.f*rs6 - 13.f;
  f26 = 7.f*rs6 - 26.f;

  f1 *= rs3;
  f2 *= dr*rs2;
  f13 *= dr3;
  f26 *= dr2*rs;
  lj->a4 = -4.f*(35.f*f1 + 90.f*f2 + 28.f*f13 + 15.f*f26)/(dr4*rs15);
  lj->a5 = 24.f*(14.f*f1 + 39.f*f2 + 14.f*f13 + 7.f*f26)/(dr2*dr3*rs15);
  lj->a6 = -4.f*(70.f*f1 + 204.f*f2 + 84.f*f13 + 39.f*f26)/(dr3*dr3*rs15);
  lj->a7 = 16.f*(5.f*f1 + 15.f*f2 + 7.f*f13 + 3.f*f26)/(dr3*dr4*rs15);

  xnew(lj->pr, lj->n * lj->n);
  xnew(lj->gdg, lj->n * lj->d);
  lj->npr = 0;
  lj->usesw = 1;
}

/* compute the switch potential phi(r) and its derivatives
 * fscal = -phi = uij'/rij
 * psi = phi'/rij
 * xi = psi'/rij
 * laplacian = psi*rij^2 + 3*phi = psi*rij^2 - 3*fscal */
INLINE real lj_potsw(lj_t *lj, real r, real *fscal, real *psi, real *xi)
{
  if (r < lj->rs) { /* normal lj */
    real invr2, invr6, invr8;
    invr2 = 1 / (r*r);
    invr6 = invr2 * invr2 * invr2;
    invr8 = invr6 * invr2;
    *fscal = (48 * invr6 - 24) * invr8;
    *psi = (672 * invr6 - 192) * invr8 * invr2;
    *xi = -(10752 * invr6 - 1920) * invr6 * invr6;
    return 4 * invr6 * (invr6 - 1);
  } else if (r < lj->rc) { /* polynomial */
    real dr, dr2, dr3, fs, ps, xs, invr, invr2;
    real a4 = lj->a4, a5 = lj->a5, a6 = lj->a6, a7 = lj->a7;
    invr = 1/r;
    dr = r - lj->rc;
    invr2 = invr * invr;
    dr2 = dr * dr;
    dr3 = dr2 * dr;
    fs = dr3*(4*a4 + dr*(5*a5 + dr*(6*a6 + dr*7*a7)))*invr;
    *fscal = -fs;
    ps = dr2*(12*a4 + dr*(20*a5 + dr*(30*a6 + dr*42*a7)));
    *psi = (ps - fs)*invr2;
    xs = dr*(24*a4 + dr*(60*a5 + dr*(120*a6 + dr*210*a7)));
    *xi = (xs*invr - 3*(*psi))*invr2;
    return (dr2*dr2)*(a4 + dr*(a5 + dr*(a6 + dr*a7)));
  } else { /* out of range */
    *fscal = 0;
    *psi = 0;
    *xi = 0;
    return 0;
  }
}

/* 2D energy for square, lj members are not altered */
static int lj_energysq2d(lj_t *lj, rv2_t *x, real *rmin)
{
  real dx[2], dr2, ra2 = lj->ra2, rb2 = lj->rb2, l = lj->l, rm2 = 1e30;
  int i, j, iu = 0, n = lj->n, col = 0;

  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_2d(dx, x[i], x[j], l);
      if (dr2 < ra2) {
        iu += lj->esqinf;
        col++;
      } else if (dr2 < rb2) {
        iu--;
      }
      if (dr2 < rm2) rm2 = dr2;
    }
  }
  if (rmin != NULL) *rmin = (real) sqrt(rm2);
  /* force the energy to zero in the hard sphere case */
  if (fabs(ra2 - rb2) < 1e-6 && col == 0) {
    iu = 0;
  }
  return iu;
}

/* 3D energy for square, lj members are not altered */
static int lj_energysq3d(lj_t *lj, rv3_t *x, real *rmin)
{
  real dx[3], dr2, ra2 = lj->ra2, rb2 = lj->rb2, l = lj->l, rm2 = 1e30;
  int i, j, iu = 0, n = lj->n, col = 0;

  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_3d(dx, x[i], x[j], l);
      if (dr2 < ra2) {
        iu += lj->esqinf;
        col++;
      } else if (dr2 < rb2) {
        iu--;
      }
      if (dr2 < rm2) rm2 = dr2;
    }
  }
  if (rmin != NULL) *rmin = (real) sqrt(rm2);
  /* force the energy to zero in the hard sphere case */
  if (fabs(ra2 - rb2) < 1e-6 && col == 0) {
    iu = 0;
  }
  return iu;
}

/* compute 2D energy for switched potential */
INLINE real lj_energysw2d(lj_t *lj, rv2_t *x, real *virial, real *laplace)
{
  int i, j, n = lj->n;
  real dx[2], dr2, dr, l = lj->l, d = (real) lj->d;
  real fscal, psi, xi, ep, vir, lap;

  ep = lap = vir = 0.f;
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_2d(dx, x[i], x[j], l);
      if (dr2 > lj->rc2) continue;

      dr = (real) sqrt(dr2);
      ep += lj_potsw(lj, dr, &fscal, &psi, &xi);
      lap += 2.f*(psi*dr2 - d*fscal);
      vir += fscal*dr2;
      rv2_smul(dx, fscal);
    }
  }
  if (virial) *virial = vir;
  if (laplace) *laplace = lap;
  return ep;
}

/* compute 3D energy for switched potential */
INLINE real lj_energysw3d(lj_t *lj, rv3_t *x, real *virial, real *laplace)
{
  int i, j, n = lj->n;
  real dx[3], dr2, dr, l = lj->l, d = (real) lj->d;
  real fscal, psi, xi, ep, vir, lap;

  ep = lap = vir = 0.f;
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_3d(dx, x[i], x[j], l);
      if (dr2 > lj->rc2) continue;

      dr = (real) sqrt(dr2);
      ep += lj_potsw(lj, dr, &fscal, &psi, &xi);
      lap += 2.f*(psi*dr2 - d*fscal);
      vir += fscal*dr2;
      rv3_smul(dx, fscal);
    }
  }
  if (virial) *virial = vir;
  if (laplace) *laplace = lap;
  return ep;
}

/* 2D compute force and virial, return energy */
static real lj_energylj2d(lj_t *lj, rv2_t *x, real *virial, real *ep0, real *eps)
{
  real dx[2], dr2, dr6, ep, vir, l = lj->l, rc2 = lj->rc2;
  int i, j, prcnt = 0, n = lj->n;

  if (virial) *virial = 0.f;
  for (ep = vir = 0, i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_2d(dx, x[i], x[j], l);
      if (dr2 > rc2) continue;
      dr2 = 1.f / dr2;
      dr6 = dr2 * dr2 * dr2;
      vir += dr6 * (48.f * dr6 - 24.f); /* f.r */
      ep += 4 * dr6 * (dr6 - 1);
      prcnt++;
    }
  }
  if (ep0) *ep0 = ep;
  if (eps) *eps = ep - prcnt * lj->epot_shift; /* shifted energy */
  if (virial) *virial = vir;
  return ep + lj->epot_tail; /* unshifted energy */
}

/* 3D compute force and virial, return energy */
static real lj_energylj3d(lj_t *lj, rv3_t *x, real *virial, real *ep0, real *eps)
{
  real dx[3], dr2, dr6, ep, vir, l = lj->l, rc2 = lj->rc2;
  int i, j, prcnt = 0, n = lj->n;

  if (virial) *virial = 0.f;
  for (ep = vir = 0, i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_3d(dx, x[i], x[j], l);
      if (dr2 > rc2) continue;
      dr2 = 1.f / dr2;
      dr6 = dr2 * dr2 * dr2;
      vir += dr6 * (48.f * dr6 - 24.f); /* f.r */
      ep += 4 * dr6 * (dr6 - 1);
      prcnt++;
    }
  }
  if (ep0) *ep0 = ep;
  if (eps) *eps = ep - prcnt * lj->epot_shift; /* shifted energy */
  if (virial) *virial = vir;
  return ep + lj->epot_tail; /* unshifted energy */
}

/* energy evaluation, do not change members of `lj' */
INLINE real lj_energyx2d(lj_t *lj, rv2_t *x, real *vir, int *iep, real *rmin,
    real *ep0, real *eps, real *lap)
{
  real u;
  if (lj->usesq) {
    *iep = lj_energysq2d(lj, x, rmin);
    u = (real) (*iep);
  } else if (lj->usesw) {
    u = lj_energysw2d(lj, x, vir, lap);
  } else {
    u = lj_energylj2d(lj, x, vir, ep0, eps);
  }
  if (lj->usesq || lj->usesw) {
    if (ep0) *ep0 = u;
    if (eps) *eps = u;
  }
  return u;
}

/* energy evaluation, do not change members of `lj' */
INLINE real lj_energyx3d(lj_t *lj, rv3_t *x, real *vir, int *iep, real *rmin,
    real *ep0, real *eps, real *lap)
{
  real u;
  if (lj->usesq) {
    *iep = lj_energysq3d(lj, x, rmin);
    u = (real) (*iep);
  } else if (lj->usesw) {
    u = lj_energysw3d(lj, x, vir, lap);
  } else {
    u = lj_energylj3d(lj, x, vir, ep0, eps);
  }
  if (lj->usesq || lj->usesw) {
    if (ep0) *ep0 = u;
    if (eps) *eps = u;
  }
  return u;
}

/* energy evaluation, do not change members of `lj' */
INLINE real lj_energyx(lj_t *lj, real *x, real *vir, int *iep, real *rmin,
    real *ep0, real *eps, real *lap)
{
  return lj->d == 2 ?
         lj_energyx2d(lj, (rv2_t *)x, vir, iep, rmin, ep0, eps, lap) :
         lj_energyx3d(lj, (rv3_t *)x, vir, iep, rmin, ep0, eps, lap);
}

/* compute the energy of the current configuration and set lj->epot */
INLINE real lj_energy2d(lj_t *lj)
{
  return lj->epot = lj_energyx2d(lj, (rv2_t *) lj->x, &lj->vir, &lj->iepot,
      &lj->rmin, &lj->epot0, &lj->epots, &lj->lap);
}

/* compute the energy of the current configuration and set lj->epot */
INLINE real lj_energy3d(lj_t *lj)
{
  return lj->epot = lj_energyx3d(lj, (rv3_t *) lj->x, &lj->vir, &lj->iepot,
      &lj->rmin, &lj->epot0, &lj->epots, &lj->lap);
}

real lj_energy(lj_t *lj)
{
  return (lj->d == 2) ? lj_energy2d(lj) : lj_energy3d(lj);
}

/* compute 2D switched force, save derivative information to lj->pr */
INLINE real lj_forcesw2d(lj_t *lj, rv2_t *x, rv2_t *f, ljpair_t *pr,
    int *ljnpr, real *virial, real *f2, real *laplace)
{
  int i, j, n = lj->n, npr;
  real dx[2], dr2, dr, l = lj->l, d = (real) lj->d;
  real fscal, psi, xi, ep, vir, lap;

  npr = 0;
  ep = lap = vir = 0.f;
  for (i = 0; i < n; i++) rv2_zero(f[i]);
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_2d(dx, x[i], x[j], l);
      if (dr2 > lj->rc2) {
        if (lj->usesw & LJ_SWALLPAIRS) { /* save out-of-range pairs, so we can later
            * locate the pair from indices i and j using getpairindex() */
          rv2_copy(pr->dx, dx);
          pr->i = i;
          pr->j = j;
          pr->phi = pr->psi = pr->xi = 0.f;
          pr->dr2 = dr2;
          pr->in = 0;
          pr++; npr++;
        }
        continue;
      }

      rv2_copy(pr->dx, dx);
      pr->dr2 = dr2;
      dr = (real) sqrt(dr2);
      ep += lj_potsw(lj, dr, &fscal, &psi, &xi);
      pr->phi = -fscal; /* phi = u'/r */
      pr->psi = psi;  /* psi = phi'/r */
      pr->xi = xi;  /* xi = psi'/r */
      lap += 2.f*(psi*dr2 - d*fscal);
      vir += fscal*dr2; /* f.r */
      rv2_smul(dx, fscal);
      pr->i = i;
      pr->j = j;
      rv2_inc(f[i], dx);
      rv2_dec(f[j], dx);
      pr->in = 1;
      pr++; npr++;
    }
  }
  if (ljnpr) *ljnpr = npr;
  if (virial) *virial = vir;
  if (laplace) *laplace = lap;
  if (f2) for (*f2 = 0.0, i = 0; i < n; i++) *f2 += rv2_sqr(f[i]);
  return ep;
}

/* compute 3D switched force, save derivative information to lj->pr */
INLINE real lj_forcesw3d(lj_t *lj, rv3_t *x, rv3_t *f, ljpair_t *pr,
    int *ljnpr, real *virial, real *f2, real *laplace)
{
  int i, j, n = lj->n, npr;
  real dx[3], dr2, dr, l = lj->l, d = (real) lj->d;
  real fscal, psi, xi, ep, vir, lap;

  npr = 0;
  ep = lap = vir = 0.f;
  for (i = 0; i < n; i++) rv3_zero(f[i]);
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_3d(dx, x[i], x[j], l);
      if (dr2 > lj->rc2) {
        if (lj->usesw & LJ_SWALLPAIRS) { /* save out-of-range pairs, so we can later
            * locate the pair from indices i and j using getpairindex() */
          rv3_copy(pr->dx, dx);
          pr->i = i;
          pr->j = j;
          pr->phi = pr->psi = pr->xi = 0.f;
          pr->dr2 = dr2;
          pr->in = 0;
          pr++; npr++;
        }
        continue;
      }

      rv3_copy(pr->dx, dx);
      pr->dr2 = dr2;
      dr = (real) sqrt(dr2);
      ep += lj_potsw(lj, dr, &fscal, &psi, &xi);
      pr->phi = -fscal; /* phi = u'/r */
      pr->psi = psi;  /* psi = phi'/r */
      pr->xi = xi;  /* xi = psi'/r */
      lap += 2.f*(psi*dr2 - d*fscal);
      vir += fscal*dr2; /* f.r */
      rv3_smul(dx, fscal);
      pr->i = i;
      pr->j = j;
      rv3_inc(f[i], dx);
      rv3_dec(f[j], dx);
      pr->in = 1;
      pr++; npr++;
    }
  }
  if (ljnpr) *ljnpr = npr;
  if (virial) *virial = vir;
  if (laplace) *laplace = lap;
  if (f2) for (*f2 = 0.0, i = 0; i < n; i++) *f2 += rv3_sqr(f[i]);
  return ep;
}

/* 2D compute force and virial, return energy */
static real lj_forcelj2d(lj_t *lj, rv2_t *x, rv2_t *f, real *virial,
    real *ep0, real *eps, real *f2, real *laplace)
{
  real dx[2], fi[2], dr2, dr6, fs, tmp, ep, vir, lap, l = lj->l, rc2 = lj->rc2;
  int i, j, d, prcnt = 0, n = lj->n;

  for (i = 0; i < n; i++) rv2_zero(f[i]);
  for (ep = vir = lap = 0, i = 0; i < n - 1; i++) {
    rv2_zero(fi);
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_2d(dx, x[i], x[j], l);
      if (dr2 > rc2) continue;
      dr2 = 1.f / dr2;
      dr6 = dr2 * dr2 * dr2;
      fs = dr6 * (48.f * dr6 - 24.f); /* f.r */
      vir += fs; /* f.r */
      if (laplace) /* 2.f for it applies to both particles */
        lap += 2.f * ((168 - 12*2) * dr6 - (48 - 6*2)) * dr6 * dr2;

      fs *= dr2; /* f.r / r^2 */
      for (d = 0; d < 2; d++) {
        tmp = dx[d] * fs;
        fi[d] += tmp;
        f[j][d] -= tmp;
      }

      ep += 4 * dr6 * (dr6 - 1);
      prcnt++;
    }
    rv2_inc(f[i], fi);
  }
  if (ep0) *ep0 = ep;
  if (eps) *eps = ep - prcnt * lj->epot_shift; /* shifted energy */
  if (virial) *virial = vir;
  if (laplace) *laplace = 4*lap;
  if (f2) for (*f2 = 0.f, i = 0; i < n; i++) *f2 += rv2_sqr(f[i]);
  return ep + lj->epot_tail; /* unshifted energy */
}

/* 3D compute force and virial, return energy */
static real lj_forcelj3d(lj_t *lj, rv3_t *x, rv3_t *f, real *virial,
    real *ep0, real *eps, real *f2, real *laplace)
{
  real dx[3], fi[3], dr2, dr6, fs, tmp, ep, vir, lap, l = lj->l, rc2 = lj->rc2;
  int i, j, d, prcnt = 0, n = lj->n;

  for (i = 0; i < n; i++) rv3_zero(f[i]);
  for (ep = vir = lap = 0, i = 0; i < n - 1; i++) {
    rv3_zero(fi);
    for (j = i + 1; j < n; j++) {
      dr2 = lj_pbcdist2_3d(dx, x[i], x[j], l);
      if (dr2 > rc2) continue;
      dr2 = 1.f / dr2;
      dr6 = dr2 * dr2 * dr2;
      fs = dr6 * (48.f * dr6 - 24.f); /* f.r */
      vir += fs; /* f.r */
      if (laplace) /* 2.f for it applies to both particles */
        lap += 2.f * ((168 - 12*3) * dr6 - (48 - 6*3)) * dr6 * dr2;

      fs *= dr2; /* f.r / r^2 */
      for (d = 0; d < 3; d++) {
        tmp = dx[d] * fs;
        fi[d] += tmp;
        f[j][d] -= tmp;
      }

      ep += 4 * dr6 * (dr6 - 1);
      prcnt++;
    }
    rv3_inc(f[i], fi);
  }
  if (ep0) *ep0 = ep;
  if (eps) *eps = ep - prcnt * lj->epot_shift; /* shifted energy */
  if (virial) *virial = vir;
  if (laplace) *laplace = 4*lap;
  if (f2) for (*f2 = 0.f, i = 0; i < n; i++) *f2 += rv3_sqr(f[i]);
  return ep + lj->epot_tail; /* unshifted energy */
}

INLINE real lj_force2d(lj_t *lj)
{
  if (lj->usesq) return lj->epot = lj->epot0 = lj->epots = (real) lj_energysq2d(lj,
    (rv2_t *) lj->x, &lj->rmin); /* no force for square well */
  if (lj->usesw) return lj->epot = lj->epot0 = lj->epots = lj_forcesw2d(lj,
    (rv2_t *) lj->x, (rv2_t *) lj->f,
    lj->pr, &lj->npr, &lj->vir, &lj->f2, &lj->lap);
  return lj->epot = lj_forcelj2d(lj, (rv2_t *) lj->x, (rv2_t *) lj->f,
    &lj->vir, &lj->epot0, &lj->epots, &lj->f2, &lj->lap);
}

INLINE real lj_force3d(lj_t *lj)
{
  if (lj->usesq) return lj->epot = lj->epot0 = lj->epots = (real) lj_energysq3d(lj,
    (rv3_t *) lj->x, &lj->rmin); /* no force for square well */
  if (lj->usesw) return lj->epot = lj->epot0 = lj->epots = lj_forcesw3d(lj,
    (rv3_t *) lj->x, (rv3_t *) lj->f,
    lj->pr, &lj->npr, &lj->vir, &lj->f2, &lj->lap);
  return lj->epot = lj_forcelj3d(lj, (rv3_t *) lj->x, (rv3_t *) lj->f,
    &lj->vir, &lj->epot0, &lj->epots, &lj->f2, &lj->lap);
}

real lj_force(lj_t *lj)
{
  return (lj->d == 2) ? lj_force2d(lj) : lj_force3d(lj);
}

/* randomly displace particle i with random amplitude */
INLINE int lj_randmv2d(lj_t *lj, real *xi, real amp)
{
  int i, d;

  i = (int)(rnd0() * lj->n);
  amp /= lj->l;
  rv2_copy(xi, lj->x + i*2);
  for (d = 0; d < 2; d++) /* displacement */
    xi[d] += (real)(amp * (2.*rnd0() - 1.));
  return i;
}

/* randomly displace particle i with random amplitude */
INLINE int lj_randmv3d(lj_t *lj, real *xi, real amp)
{
  int i, d;

  i = (int)(rnd0() * lj->n);
  amp /= lj->l;
  rv3_copy(xi, lj->x + i*3);
  for (d = 0; d < 3; d++) /* displacement */
    xi[d] += (real)(amp * (2.*rnd0() - 1.));
  return i;
}

/* compute energy data for a 2D pair with a square well potential */
INLINE int lj_pairsq2d(const real *xi, const real *xj, real l,
   real ra2, real rb2, real *pdr2, int inf)
{
  real dx[2], dr2;
  dr2 = lj_pbcdist2_2d(dx, xi, xj, l);
  if (pdr2) *pdr2 = dr2;
  if (dr2 < ra2) return -inf;
  else if (dr2 < rb2) return 1;
  else return 0;
}

/* compute energy data for a 3D pair with a square well potential */
INLINE int lj_pairsq3d(const real *xi, const real *xj, real l,
   real ra2, real rb2, real *pdr2, int inf)
{
  real dx[3], dr2;
  dr2 = lj_pbcdist2_3d(dx, xi, xj, l);
  if (pdr2) *pdr2 = dr2;
  if (dr2 < ra2) return -inf;
  else if (dr2 < rb2) return 1;
  else return 0;
}

/* return the energy change (square well) from displacing x[i] to xi */
INLINE int lj_depotsq2d(lj_t *lj, int i, const real *xi, real *rm)
{
  int j, n = lj->n, npr = 0, inf = lj->esqinf, recalc = 0;
  real l = lj->l, ra2 = lj->ra2, rb2 = lj->rb2;
  real r2o, r2n, rm2o = 0, rm2 = 0;
  rv2_t *x = (rv2_t *) lj->x;
  const real tol = 1e-5;

  if (rm) rm2o = rm2 = (*rm) * (*rm);
  for (j = 0; j < n; j++) { /* pair */
    if (j == i) continue;
    npr -= lj_pairsq2d(x[i], x[j], l, ra2, rb2, &r2o, inf);
    npr += lj_pairsq2d(xi,   x[j], l, ra2, rb2, &r2n, inf);
    if (fabs(r2o - rm2o) < tol) { /* need to re-compute rmin */
      recalc |= 1;
    }
    if (r2n < rm2) { /* new rmin is found */
      recalc |= 2; /* no need to recalc */
      rm2 = r2n;
    }
  }

  /* in order to compute the minimal distance,
   * we need to occasionally recompute the entire system */
  if (recalc == 1) { /* 0, 2, 3 are safe */
    rv2_t xio;
    rv2_copy(xio, x[i]);
    rv2_copy(x[i], xi); /* apply xi */
    lj_energysq2d(lj, x, rm);
    rv2_copy(x[i], xio); /* recover */
  } else {
    if (rm) *rm = (real) sqrt(rm2);
  }

  /* hard sphere, no collision */
  if (fabs(ra2 - rb2) < 2e-6 && npr > -inf/10 && npr < inf/10) {
    npr = 0; /* number of neighbors */
  }
  return -npr; /* increased number of pairs == decreased energy */
}

/* return the energy change (square well) from displacing x[i] to xi */
INLINE int lj_depotsq3d(lj_t *lj, int i, const real *xi, real *rm)
{
  int j, n = lj->n, npr = 0, inf = lj->esqinf, recalc = 0;
  real l = lj->l, ra2 = lj->ra2, rb2 = lj->rb2;
  real r2o, r2n, rm2o = 0, rm2 = 0;
  rv3_t *x = (rv3_t *) lj->x;
  const real tol = 1e-5;

  if (rm) rm2o = rm2 = (*rm) * (*rm);
  for (j = 0; j < n; j++) { /* pair */
    if (j == i) continue;
    npr -= lj_pairsq3d(x[i], x[j], l, ra2, rb2, &r2o, inf);
    npr += lj_pairsq3d(xi,   x[j], l, ra2, rb2, &r2n, inf);
    if (fabs(r2o - rm2o) < tol) { /* need to re-compute rmin */
      recalc |= 1;
    }
    if (r2n < rm2) { /* new rmin is found */
      recalc |= 2; /* no need to recalc */
      rm2 = r2n;
    }
  }

  /* in order to compute the minimal distance,
   * we need to occasionally recompute the entire system */
  if (recalc == 1) { /* 0, 2, 3 are safe */
    rv3_t xio;
    rv3_copy(xio, x[i]);
    rv3_copy(x[i], xi); /* apply xi */
    lj_energysq3d(lj, x, rm);
    rv3_copy(x[i], xio); /* recover */
  } else {
    if (rm) *rm = (real) sqrt(rm2);
  }

  /* hard sphere, no collision */
  if (fabs(ra2 - rb2) < 2e-6 && npr > -inf/10 && npr < inf/10) {
    npr = 0; /* number of neighbors */
  }
  return -npr; /* increased number of pairs == decreased energy */
}

/* commit a particle displacement for a square wel potential */
INLINE void lj_commitsq2d(lj_t *lj, int i, const real *xi, int du)
{
  rv2_copy(lj->x + i*2, xi);
  lj->iepot += du;
  lj->epot += du;
}

/* commit a particle displacement for a square wel potential */
INLINE void lj_commitsq3d(lj_t *lj, int i, const real *xi, int du)
{
  rv3_copy(lj->x + i*3, xi);
  lj->iepot += du;
  lj->epot += du;
}

/* metropolis for a square well */
INLINE int lj_metrosq2d(lj_t *lj, real amp, real bet)
{
  int i, du;
  real xi[2], rm;

  i = lj_randmv2d(lj, xi, amp);
  rm = lj->rmin;
  du = lj_depotsq2d(lj, i, xi, &rm);
  /* patch for bet = 0 */
  if (bet >= 0 && du > lj->esqinf/2) return 0;
  if (metroacc1(du, bet)) {
    lj_commitsq2d(lj, i, xi, du);
    lj->rmin = rm;
    return 1;
  }
  return 0;
}

/* metropolis for a square well */
INLINE int lj_metrosq3d(lj_t *lj, real amp, real bet)
{
  int i, du;
  real xi[3], rm;

  i = lj_randmv3d(lj, xi, amp);
  rm = lj->rmin;
  du = lj_depotsq3d(lj, i, xi, &rm);
  /* patch for bet = 0 */
  if (bet >= 0 && du > lj->esqinf/2) return 0;
  if (metroacc1(du, bet)) {
    lj_commitsq3d(lj, i, xi, du);
    lj->rmin = rm;
    return 1;
  }
  return 0;
}

/* compute energy data for a particle pair, with switched potential  */
INLINE int lj_pairsw2d(lj_t *lj, real *xi, real *xj, real *u, real *vir)
{
  real dx[2], dr2, dr, fscal, psi, ksi;
  dr2 = lj_pbcdist2_2d(dx, xi, xj, lj->l);
  if (dr2 < lj->rc2) {
    dr = (real) sqrt(dr2);
    *u = lj_potsw(lj, dr, &fscal, &psi, &ksi);
    *vir = fscal * dr2; /* f.r */
    return 1;
  } else return 0;
}

/* compute energy data for a particle pair, with switched potential  */
INLINE int lj_pairsw3d(lj_t *lj, real *xi, real *xj, real *u, real *vir)
{
  real dx[3], dr2, dr, fscal, psi, ksi;
  dr2 = lj_pbcdist2_3d(dx, xi, xj, lj->l);
  if (dr2 < lj->rc2) {
    dr = (real) sqrt(dr2);
    *u = lj_potsw(lj, dr, &fscal, &psi, &ksi);
    *vir = fscal * dr2; /* f.r */
    return 1;
  } else return 0;
}

/* return the energy change from displacing x[i] to xi */
INLINE real lj_depotsw2d(lj_t *lj, int i, real *xi, real *vir)
{
  int j, n = lj->n;
  real u = 0.f, du = 0.f, dvir = 0.f;
  rv2_t *x = (rv2_t *) lj->x;

  *vir = 0.0f;
  for (j = 0; j < n; j++) { /* pair */
    if (j == i) continue;
    if (lj_pairsw2d(lj, x[i], x[j], &du, &dvir)) {
      u -= du;
      *vir -= dvir;
    }
    if (lj_pairsw2d(lj, xi, x[j], &du, &dvir)) {
      u += du;
      *vir += dvir;
    }
  }
  return u;
}

/* return the energy change from displacing x[i] to xi */
INLINE real lj_depotsw3d(lj_t *lj, int i, real *xi, real *vir)
{
  int j, n = lj->n;
  real u = 0.f, du = 0.f, dvir = 0.f;
  rv3_t *x = (rv3_t *) lj->x;

  *vir = 0.0f;
  for (j = 0; j < n; j++) { /* pair */
    if (j == i) continue;
    if (lj_pairsw3d(lj, x[i], x[j], &du, &dvir)) {
      u -= du;
      *vir -= dvir;
    }
    if (lj_pairsw3d(lj, xi, x[j], &du, &dvir)) {
      u += du;
      *vir += dvir;
    }
  }
  return u;
}

/* commit a particle displacement
 * like energysw3d, it does not set pair data, lj->pr
 * call lj_forcesw2d() if it is needed */
INLINE void lj_commitsw2d(lj_t *lj, int i, const real *xi, real du, real dvir)
{
  rv2_copy(lj->x + i*2, xi);
  lj->epot += du;
  lj->vir += dvir;
}

/* commit a particle displacement
 * like energysw3d, it does not set pair data, lj->pr
 * call lj_forcesw3d() if it is needed */
INLINE void lj_commitsw3d(lj_t *lj, int i, const real *xi, real du, real dvir)
{
  rv3_copy(lj->x + i*3, xi);
  lj->epot += du;
  lj->vir += dvir;
}

/* Metropolis algorithm */
INLINE int lj_metrosw2d(lj_t *lj, real amp, real bet)
{
  int i;
  real xi[2], du, dvir;

  i = lj_randmv2d(lj, xi, amp);
  du = lj_depotsw2d(lj, i, xi, &dvir);
  if (metroacc1(du, bet)) {
    lj_commitsw2d(lj, i, xi, du, dvir);
    return 1;
  }
  return 0;
}

/* Metropolis algorithm */
INLINE int lj_metrosw3d(lj_t *lj, real amp, real bet)
{
  int i;
  real xi[3], du, dvir;

  i = lj_randmv3d(lj, xi, amp);
  du = lj_depotsw3d(lj, i, xi, &dvir);
  if (metroacc1(du, bet)) {
    lj_commitsw3d(lj, i, xi, du, dvir);
    return 1;
  }
  return 0;
}

/* compute energy data for a 2D Lennard-Jones pair */
INLINE int lj_pairlj2d(real *xi, real *xj, real l, real rc2,
    real *u, real *vir)
{
  real dx[2], dr2, invr2, invr6;
  dr2 = lj_pbcdist2_2d(dx, xi, xj, l);
  if (dr2 < rc2) {
    invr2 = 1.0f / dr2;
    invr6 = invr2 * invr2 * invr2;
    *vir = invr6 * (48.f * invr6 - 24.f); /* f.r */
    *u  = 4.f * invr6 * (invr6 - 1.f);
    return 1;
  } else return 0;
}

/* compute energy data for a 3D Lennard-Jones pair */
INLINE int lj_pairlj3d(real *xi, real *xj, real l, real rc2,
    real *u, real *vir)
{
  real dx[3], dr2, invr2, invr6;
  dr2 = lj_pbcdist2_3d(dx, xi, xj, l);
  if (dr2 < rc2) {
    invr2 = 1.0f / dr2;
    invr6 = invr2 * invr2 * invr2;
    *vir = invr6 * (48.f * invr6 - 24.f); /* f.r */
    *u  = 4.f * invr6 * (invr6 - 1.f);
    return 1;
  } else return 0;
}

/* return the energy change from displacing x[i] to xi */
INLINE real lj_depotlj2d(lj_t *lj, int i, real *xi, real *vir)
{
  int j, n = lj->n;
  real l = lj->l, rc2 = lj->rc2, u = 0.f, du = 0.f, dvir = 0.f;
  rv2_t *x = (rv2_t *) lj->x;

  *vir = 0.0f;
  for (j = 0; j < n; j++) { /* pair */
    if (j == i) continue;
    if (lj_pairlj2d(x[i], x[j], l, rc2, &du, &dvir)) {
      u -= du;
      *vir -= dvir;
    }
    if (lj_pairlj2d(xi, x[j], l, rc2, &du, &dvir)) {
      u += du;
      *vir += dvir;
    }
  }
  return u;
}

/* return the energy change from displacing x[i] to xi */
INLINE real lj_depotlj3d(lj_t *lj, int i, real *xi, real *vir)
{
  int j, n = lj->n;
  real l = lj->l, rc2 = lj->rc2, u = 0.f, du = 0.f, dvir = 0.f;
  rv3_t *x = (rv3_t *) lj->x;

  *vir = 0.0f;
  for (j = 0; j < n; j++) { /* pair */
    if (j == i) continue;
    if (lj_pairlj3d(x[i], x[j], l, rc2, &du, &dvir)) {
      u -= du;
      *vir -= dvir;
    }
    if (lj_pairlj3d(xi, x[j], l, rc2, &du, &dvir)) {
      u += du;
      *vir += dvir;
    }
  }
  return u;
}

/* commit a particle displacement */
INLINE void lj_commitlj2d(lj_t *lj, int i, const real *xi, real du, real dvir)
{
  rv2_copy(lj->x + i*2, xi);
  lj->epot += du;
  lj->vir += dvir;
}

/* commit a particle displacement */
INLINE void lj_commitlj3d(lj_t *lj, int i, const real *xi, real du, real dvir)
{
  rv3_copy(lj->x + i*3, xi);
  lj->epot += du;
  lj->vir += dvir;
}

INLINE int lj_metrolj2d(lj_t *lj, real amp, real bet)
{
  int i;
  real xi[2], du = 0.f, dvir = 0.f;

  i = lj_randmv2d(lj, xi, amp);
  du = lj_depotlj2d(lj, i, xi, &dvir);
  if (metroacc1(du, bet)) {
    lj_commitlj2d(lj, i, xi, du, dvir);
    return 1;
  }
  return 0;
}

INLINE int lj_metrolj3d(lj_t *lj, real amp, real bet)
{
  int i;
  real xi[3], du = 0.f, dvir = 0.f;

  i = lj_randmv3d(lj, xi, amp);
  du = lj_depotlj3d(lj, i, xi, &dvir);
  if (metroacc1(du, bet)) {
    lj_commitlj3d(lj, i, xi, du, dvir);
    return 1;
  }
  return 0;
}

/* return the pair energy between two particles at xi and xj */
INLINE int lj_pair2d(lj_t *lj, real *xi, real *xj, real *u, real *vir)
{
  if (lj->usesq) return lj_pairsq2d(xi, xj, lj->l, lj->ra2, lj->rb2, NULL, lj->esqinf);
  if (lj->usesw) return lj_pairsw2d(lj, xi, xj, u, vir);
  return lj_pairlj2d(xi, xj, lj->l, lj->rc2, u, vir);
}

/* return the pair energy between two particles at xi and xj */
INLINE int lj_pair3d(lj_t *lj, real *xi, real *xj, real *u, real *vir)
{
  if (lj->usesq) return lj_pairsq3d(xi, xj, lj->l, lj->ra2, lj->rb2, NULL, lj->esqinf);
  if (lj->usesw) return lj_pairsw3d(lj, xi, xj, u, vir);
  return lj_pairlj3d(xi, xj, lj->l, lj->rc2, u, vir);
}

/* return the pair energy between two particles at xi and xj */
INLINE int lj_pair(lj_t *lj, real *xi, real *xj, real *u, real *vir)
{
  return lj->d == 2 ?  lj_pair2d(lj, xi, xj, u, vir) : lj_pair3d(lj, xi, xj, u, vir);
}

/* return the energy change from displacing x[i] to xi */
INLINE real lj_depot2d(lj_t *lj, int i, real *xi, real *vir, real *rmin)
{
  if (lj->usesq) return (real) lj_depotsq2d(lj, i, xi, rmin);
  if (lj->usesw) return lj_depotsw2d(lj, i, xi, vir);
  return lj_depotlj2d(lj, i, xi, vir);
}

/* return the energy change from displacing x[i] to xi */
INLINE real lj_depot3d(lj_t *lj, int i, real *xi, real *vir, real *rmin)
{
  if (lj->usesq) return (real) lj_depotsq3d(lj, i, xi, rmin);
  if (lj->usesw) return lj_depotsw3d(lj, i, xi, vir);
  return lj_depotlj3d(lj, i, xi, vir);
}

/* return the energy change from displacing x[i] to xi */
INLINE real lj_depot(lj_t *lj, int i, real *xi, real *vir, real *rmin)
{
  return lj->d == 2 ?  lj_depot2d(lj, i, xi, vir, rmin)
    : lj_depot3d(lj, i, xi, vir, rmin);
}

/* this is defined as a macro for du is `int' in sq case, but real in other cases */
#define lj_commit2d(lj, i, xi, du, dvir) { \
  (lj->usesq) ? lj_commitsq2d(lj, i, xi, du) : \
  (lj->usesw) ? lj_commitsw2d(lj, i, xi, du, dvir) : \
  lj_commitlj2d(lj, i, xi, du, dvir); }

/* this is defined as a macro for du is `int' in sq case, but real in other cases */
#define lj_commit3d(lj, i, xi, du, dvir) { \
  (lj->usesq) ? lj_commitsq3d(lj, i, xi, du) : \
  (lj->usesw) ? lj_commitsw3d(lj, i, xi, du, dvir) : \
  lj_commitlj3d(lj, i, xi, du, dvir); }

/* commit a move */
#define  lj_commit(lj, i, xi, du, dvir) \
  (lj->d == 2 ? lj_commit2d(lj, i, xi, du, dvir) : lj_commit3d(lj, i, xi, du, dvir); )

INLINE int lj_metro2d(lj_t *lj, real amp, real bet)
{
  if (lj->usesq) return lj_metrosq2d(lj, amp, bet);
  if (lj->usesw) return lj_metrosw2d(lj, amp, bet);
  return lj_metrolj2d(lj, amp, bet);
}

INLINE int lj_metro3d(lj_t *lj, real amp, real bet)
{
  if (lj->usesq) return lj_metrosq3d(lj, amp, bet);
  if (lj->usesw) return lj_metrosw3d(lj, amp, bet);
  return lj_metrolj3d(lj, amp, bet);
}

/* Metropolis algorithm */
INLINE int lj_metro(lj_t *lj, real amp, real bet)
{ return lj->d == 2 ? lj_metro2d(lj, amp, bet) : lj_metro3d(lj, amp, bet); }

/* return the energy change of locally displacing a single atom */
INLINE real lj_dupertl2d(lj_t *lj, real amp)
{
  real dvir, xi[2], rmin;
  int i;

  i = lj_randmv2d(lj, xi, amp);
  return lj_depot2d(lj, i, xi, &dvir, &rmin);
}

/* return the energy change of locally displacing a single atom */
INLINE real lj_dupertl3d(lj_t *lj, real amp)
{
  real dvir, xi[3], rmin;
  int i;

  i = lj_randmv3d(lj, xi, amp);
  return lj_depot3d(lj, i, xi, &dvir, &rmin);
}

INLINE real lj_dupertl(lj_t *lj, real amp)
{ return lj->d == 2 ? lj_dupertl2d(lj, amp) : lj_dupertl3d(lj, amp); }

/* return the energy change by random displacements of all atoms */
INLINE real lj_dupertg2d(lj_t *lj, real amp)
{
  int i, d, iep;
  rv2_t *nx;
  real du, vir, rmin, ep0, eps, lap;

  xnew(nx, lj->n);
  amp /= lj->l; /* convert to the reduced unit */
  for (i = 0; i < lj->n; i++)
    for (d = 0; d < 2; d++)
      nx[i][d] = (real) (lj->x[i*2 + d] + amp * (2*rnd0() - 1));
  du = lj_energyx2d(lj, nx, &vir, &iep, &rmin, &ep0, &eps, &lap) - lj->epot;
  free(nx);
  return du;
}

/* return the energy change by random displacements of all atoms */
INLINE real lj_dupertg3d(lj_t *lj, real amp)
{
  int i, d, iep;
  rv3_t *nx;
  real du, vir, rmin, ep0, eps, lap;

  xnew(nx, lj->n);
  amp /= lj->l; /* convert to the reduced unit */
  for (i = 0; i < lj->n; i++)
    for (d = 0; d < 3; d++)
      nx[i][d] = (real) (lj->x[i*3 + d] + amp * (2*rnd0() - 1));
  du = lj_energyx3d(lj, nx, &vir, &iep, &rmin, &ep0, &eps, &lap) - lj->epot;
  free(nx);
  return du;
}

INLINE real lj_dupertg(lj_t *lj, real amp)
{ return lj->d == 2 ? lj_dupertg2d(lj, amp) : lj_dupertg3d(lj, amp); }

/* return the energy caused by inserting a random atom
   the tail correction is not applied */
INLINE real lj_duinsert2d(lj_t *lj, real *xt)
{
  int j, n = lj->n;
  real xt0[2], u, du, dvir;

  if (xt == NULL) for (xt = xt0, j = 0; j < 3; j++) xt[j] = (real) rnd0();
  for (u = 0.f, j = 0; j < n; j++) /* pair energy */
    if (lj_pair(lj, xt, lj->x + 2*j, &du, &dvir))
      u += du;
  return u;
}

/* return the energy caused by inserting a random atom
   the tail correction is not applied */
INLINE real lj_duinsert3d(lj_t *lj, real *xt)
{
  int j, n = lj->n;
  real xt0[3], u, du, dvir;

  if (xt == NULL) for (xt = xt0, j = 0; j < 3; j++) xt[j] = (real) rnd0();
  for (u = 0.f, j = 0; j < n; j++) /* pair energy */
    if (lj_pair(lj, xt, lj->x + 3*j, &du, &dvir))
      u += du;
  return u;
}

INLINE real lj_duinsert(lj_t *lj, real *xt)
{ return lj->d == 2 ? lj_duinsert2d(lj, xt) : lj_duinsert3d(lj, xt); }

/* velocity verlet */
INLINE void lj_vvx(lj_t *lj, real fscal, real dt)
{
  int i, nd = lj->n*lj->d;
  real dtl = dt/lj->l, dthf = dt * .5f * fscal;

  for (i = 0; i < nd; i++) { /* VV part 1 */
    lj->v[i] += lj->f[i] * dthf;
    lj->x[i] += lj->v[i] * dtl;
  }
  lj_force(lj); /* calculate the new force */
  for (i = 0; i < nd; i++) /* VV part 2 */
    lj->v[i] += lj->f[i] * dthf;

  lj->ekin = md_ekin(lj->v, nd, lj->dof, &lj->tkin);
  lj->t += dt;
}

/* calculate the configurational temperature (bc) for switched potential
 * bc = div(v), where v = g/(g.g), g = grad U,
 * udb = v . grad bc
 * bvir = x . grad bc */
INLINE real lj_bconfsw3d(lj_t *lj, real *udb)
{
  int i, j, ipr, npr = lj->npr, n = lj->n;
  ljpair_t *pr;
  real dg[3], dh[3];
  real phi, psi, xi, d = (real) lj->d;
  real dgdx, dg2, dr2, m = 0.f, h2;
  real gdlap = 0.f, gdm = 0.f, bc, invg2, invg4;
  real dlap, dgdx2;
  rv3_t *h = (rv3_t *) lj->gdg, *f = (rv3_t *) lj->f;

  if(udb) for (i = 0; i < n; i++) rv3_zero(h[i]);  /* g * grad g */

  for (ipr = 0; ipr < npr; ipr++) {
    pr = lj->pr + ipr;
    i = pr->i;
    j = pr->j;
    phi = pr->phi;
    psi = pr->psi;

    dg2 = rv3_sqr( rv3_diff(dg, f[j], f[i]) );
    dgdx = rv3_dot(dg, pr->dx);
    m += psi*(dgdx2 = dgdx*dgdx) + phi*dg2; /* M = g g : grad grad U */
    if (udb) {
      dr2 = pr->dr2;
      xi = pr->xi;
      dlap = xi*dr2 + (2.f + d)*psi;
      gdlap += dlap * dgdx; /* 0.5 g . grad laplace U */
      gdm += (xi*dgdx2 + 3.f*psi*dg2)*dgdx; /* g g g : grad grad grad U, first larger */
      rv3_lincomb2(dh, pr->dx, dg, psi * dgdx, phi);
      rv3_sinc(h[i], dh,  2.f);
      rv3_sinc(h[j], dh, -2.f);
    }
  }
  m *= 2.f;
  gdlap *= 2.f;
  gdm *= 2.f;
  invg2 = 1.f/lj->f2;
  invg4 = invg2 * invg2;
  bc = (lj->lap - m*invg2)*invg2; /* configuration temperature */

  if (udb) {
    for (h2 = 0.f, i = 0; i < n; i++) h2 += rv3_sqr(h[i]);
    /* (1/g) \partial^2 g/ \partial E^2 = <bc*bc + udb>
       \partial bc/ \partial E = <d(bc)^2 + udb> */
    *udb = invg4*(gdlap - (lj->lap*m + h2 + gdm)*invg2 + 2.f*m*m*invg4);
  }

  return bc;
}

/* return r r : grad grad U, must be called after force */
INLINE real lj_vir2sw3d(lj_t *lj)
{
  int ipr, npr = lj->npr;
  real vir2 = 0.f;

  for (ipr = 0; ipr < npr; ipr++) {
    ljpair_t *pr = lj->pr + ipr;
    vir2 += (pr->psi * pr->dr2 + pr->phi) * pr->dr2;
  }
  return vir2;
}

/* velocity verlet with the scaling step in the Nose-Hoover barostat */
INLINE void lj_vv_hoovertp(lj_t *lj, real dt, real eta)
{
  int i, nd = lj->n*lj->d;
  real dt2 = dt * .5f, xp;

  for (i = 0; i < nd; i++) /* VV part 1 */
    lj->v[i] += lj->f[i] * dt2;

  /* position update with scaling */
  md_hoovertpdr(lj->x, lj->v, nd, &xp, lj->l, eta, dt);
  lj->l *= xp;
  lj_setrho(lj, lj->rho/(xp*xp*xp));
  lj_force(lj); /* calculate the new force */

  for (i = 0; i < nd; i++) /* VV part 2 */
    lj->v[i] += lj->f[i] * dt2;

  lj->ekin = md_ekin(lj->v, nd, lj->dof, &lj->tkin);
  lj->t += dt;
}

/* Berendsen barostat: as a backup for constant pressure simulation */
INLINE void lj_pberendsen(lj_t *lj, real barodt, real tp, real pext)
{
  int i;
  real pint, vn, lo = lj->l, s, dlnv;

  pint = (lj->vir + 2.f * lj->ekin)/ (lj->d * lj->vol) + lj->p_tail;

  /* proposed change of log V */
  dlnv = (pint - pext)*lj->vol/tp*barodt;
  if (dlnv < -0.1) dlnv = -0.1; else if (dlnv > 0.1) dlnv = 0.1;
  vn = log(lj->vol) + dlnv;
  vn = exp(vn);
  lj_setrho(lj, lj->n/vn);
  s = lo/lj->l;
  for (i = 0; i < lj->d * lj->n; i++) lj->v[i] *= s;
  lj->ekin *= s*s;
  lj->tkin *= s*s;
}

/* Monte Carlo barostat
 * the ideal gas part computed as \sum p^2/m / V
 * the scaling is r = r*s, p = p/s;
 * set cutoff to half of the box */
INLINE int lj_mctp(lj_t *lj, real lnvamp, real tp, real pext,
    real vmin, real vmax, int ensx, unsigned flags)
{
  int acc = 0, i, d = lj->d;
  real lnlo, lnln, lo, ln, vo, vn, s, epo, bet = 1.f/tp;
  double dex;
  lj_t *lj1;

  vo = lj->vol;
  lo = lj->l;
  lnlo = (real) log(lo);
  lnln = (real) (lnlo + lnvamp/d * (2.f * rnd0() - 1.f));
  ln = (real) exp(lnln);
  for (vn = 1, i = 0; i < d; i++) vn *= ln;
  if (vn < vmin || vn >= vmax)
    return 0;
  if ((flags & LJ_FIXEDRC) && ln < lj->rc * 2)
    return 0; /* box too small */

  epo = lj->epot;
  lj1 = lj_clone(lj, LJ_CPF); /* make a copy */
  lj_setrho(lj, lj->n/vn);
  lj_force(lj); /* we change force here */
  dex = bet * (lj->epot - epo + pext * (vn - vo))
      + bet * (pow(vo/vn, 2.0/d) - 1)*lj->ekin
      + d * (lnlo - lnln) * (1 - ensx);
  if (metroacc1(dex, 1.f)) { /* scale the velocities */
    s = lo/lj->l;
    for (i = 0; i < d * lj->n; i++) lj->v[i] *= s;
    lj->ekin *= s*s;
    lj->tkin *= s*s;
    acc = 1;
  } else {
    lj_copy(lj, lj1, LJ_CPF); /* restore force etc. */
  }
  lj_close(lj1);
  return acc;
}

/* Monte Carlo barostat for the square-well potential, for coordiantes only
 * suppose lj->rmin has been correctly set
 * use lnvamp 0.03 ~ 0.06 for 256 system */
INLINE int lj_mcpsq(lj_t *lj, real lnvamp, real tp, real pext,
    real vmin, real vmax, int ensx, unsigned flags)
{
  int acc = 0, i, d = lj->d, iep;
  real lnlo, lnln, vo, vn, lo, ln, rmn = 0, epo, bet = 1.f/tp;
  double dex;

  (void) flags;
  vo = lj->vol;
  lo = lj->l;
  lnlo = (real) log(lo);
  lnln = (real) (lnlo + lnvamp/d * (2.f * rnd0() - 1.f));
  ln = (real) exp(lnln);
  for (vn = 1, i = 0; i < d; i++) vn *= ln;
  if (vn < vmin || vn >= vmax) return 0;

  /* check if there is a clash */
  rmn = lj->rmin * ln / lo;
  if (ln < lo) {
    if (ln < lj->rb * 2) return 0; /* box too small */
    if (rmn < lj->ra) return 0;
  }

  /* compute the change of the square-well energy */
  epo = lj->epot;
  lj_setrho(lj, lj->n/vn); /* commit to the new box */
  if (fabs(lj->ra - lj->rb) < 1e-6) { /* skip the energy calculation */
    iep = 0;
  } else {
    if (d == 3) {
      iep = lj_energysq3d(lj, (rv3_t *) lj->x, &rmn);
    } else {
      iep = lj_energysq2d(lj, (rv2_t *) lj->x, &rmn);
    }
  }
  dex = bet * ((real) iep - epo + pext * (vn - vo))
      - (lj->dof + (1 - ensx) * d) * (lnln - lnlo);
  if (rmn > lj->ra && metroacc1(dex, 1.0)) {
    lj->iepot = iep;
    lj->epot = iep;
    lj->rmin = rmn;
    acc = 1;
  } else {
    lj_setrho(lj, lj->n/vo);
  }
  return acc;
}

/* Monte Carlo barostat, coordiantes only
 * use lnvamp 0.03 ~ 0.06 for 256 system */
INLINE int lj_mcplj(lj_t *lj, real lnvamp, real tp, real pext,
    real vmin, real vmax, int ensx, unsigned flags)
{
  int acc = 0, i, d = lj->d;
  real lnlo, lnln, lo, ln, vo, vn, epo, bet = 1.f/tp;
  double dex;
  lj_t *lj1;

  vo = lj->vol;
  lo = lj->l;
  lnlo = (real) log(lo);
  lnln = (real) (lnlo + lnvamp/d * (2.f * rnd0() - 1.f));
  ln = (real) exp(lnln);
  for (vn = 1, i = 0; i < d; i++) vn *= ln;
  if (vn < vmin || vn >= vmax)
    return 0;
  if ((flags & LJ_FIXEDRC) && ln < lj->rc * 2)
    return 0; /* box too small */

  epo = lj->epot;
  lj1 = lj_clone(lj, LJ_CPF); /* save a copy */
  lj_setrho(lj, lj->n/vn); /* commit to the new box */
  lj_force(lj);
  dex = bet * (lj->epot - epo + pext * (vn - vo))
      - (lj->dof + (1 - ensx) * d) * (lnln - lnlo);
  if (metroacc1(dex, 1.0)) {
    acc = 1;
  } else {
    lj_copy(lj, lj1, LJ_CPF);
  }
  lj_close(lj1);
  return acc;
}

/* Monte Carlo barostat, coordiantes only */
INLINE int lj_mcp(lj_t *lj, real lnvamp, real tp, real pext,
    real vmin, real vmax, int ensx, unsigned flags)
{
  if (lj->usesq) { /* use the specialized square-well version */
    return lj_mcpsq(lj, lnvamp, tp, pext, vmin, vmax, ensx, flags);
  } else { /* use the generic version */
    return lj_mcplj(lj, lnvamp, tp, pext, vmin, vmax, ensx, flags);
  }
}

#endif /* ZCOM_LJ__ */
#endif /* ZCOM_LJ */

#ifdef  ZCOM_ABPRO
#ifndef ZCOM_ABPRO__
#define ZCOM_ABPRO__
/* AB beads protein models */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif

typedef struct {
  int i, j;
  int on; /* constraint is active */
  real dx0[3]; /* difference */
  real r2ref; /* square of the reference distance */
} lgconstr_t;

typedef struct {
  int i, j;
  int tid; /* thread */
  real c;
} abpairid_t; /* pair index */

typedef struct {
  int d; /* dimension */
  int model; /* 1 or 2 */
  int seqid; /* model sequence id */
  int n; /* number of atoms */
  int dof, dof0; /* number of degrees of freedom */
  real clj[2][2], sla, slb;
  int *type; /* 0: A, 1: B */
  real *x, *x1, *dx;
  real *v;
  real *f;
  real *lmx, *xmin;
  real emin, epot, ekin, tkin;
  double t;

  int lgcon; /* enable local constraints */
  int lgcnt; /* total local constraints */
  int lgact; /* active local constraints */
  lgconstr_t *lgc;

#define AB_XXCNT 6
  real *xx[AB_XXCNT]; /* extra memory allocations, each of the size of x */

#ifdef _OPENMP
  int nthreads; /* number of threads */
  real *f_l; /* local force */
  int *homeid; /* [homeid[tid], homeid[tid + 1]): atoms belongs to thread id */
  int paircnt; /* number of pairs */
  abpairid_t *pair; /* the entire pair */
  int *pairid; /* [pairid[tid], pairid[tid + 1]): pairs belong to thread tid */
#endif
} abpro_t;

#define AB_VERBOSE    0x0001
#define AB_SOFTFORCE  0x0010
#define AB_MILCSHAKE  0x0020
#define AB_LMREGISTER 0x0100
#define AB_LMWRITE    0x0200

STRCLS abpro_t *ab_open(int seqid, int d, int model, real randdev);
STRCLS void ab_close(abpro_t *ab);

STRCLS int ab_checkconn(abpro_t *ab, const real *x, double tol);
#define ab_shiftcom(ab, v)      md_shiftcom(v, ab->n, ab->d)
#define ab_shiftang(ab, x, v)   md_shiftang(x, v, ab->n, ab->d)
/* shift center of x to the origin, remove center velocity and angular momentum */
INLINE void ab_rmcom(abpro_t *ab, real *x, real *v)
{
  ab_shiftcom(ab, x);
  ab_shiftcom(ab, v);
  ab_shiftang(ab, x, v); /* remove angular momentum */
}


STRCLS int ab_writepos(abpro_t *ab, const real *x, const real *v, const char *fname);
STRCLS int ab_readpos(abpro_t *ab, real *x, real *v, const char *fname);
STRCLS int ab_initpos(abpro_t *ab, real *x, real randev);

STRCLS int ab_shake(abpro_t *ab, const real *x0, real *x1, real *v, real dt,
    int itmax, double tol, int verbose);
STRCLS int ab_rattle(abpro_t *ab, const real *x0, real *v,
    int itmax, double tol, int verbose);
STRCLS int ab_milcshake(abpro_t *ab, const real *x0, real *x1, real *v, real dt,
    int itmax, double tol, int verbose);
STRCLS int ab_milcrattle(abpro_t *ab, const real *x0, real *v);

STRCLS real ab_localmin(abpro_t *ab, const real *r, int itmax, double tol,
    int sh_itmax, double sh_tol, unsigned flags);
STRCLS real ab_energy(abpro_t *ab, const real *r, int soft);
STRCLS real ab_force(abpro_t *ab, const real *r, real *f, int soft);

INLINE real ab_ekin(abpro_t *ab)
  { return ab->ekin = md_ekin(ab->v, ab->n*ab->d, ab->dof, &ab->tkin); }
INLINE void ab_vrescale(abpro_t *ab, real tp, real dt)
  { md_vrescale(ab->v, ab->n*ab->d, ab->dof, tp, dt, &ab->ekin, &ab->tkin); }
STRCLS int ab_vv(abpro_t *ab, real fscal, real dt, unsigned flags);
STRCLS int ab_brownian(abpro_t *ab, real T, real fscal, real dt, unsigned flags);


#ifdef _OPENMP
/* compare pair by thread id */
static int ab_prcmp(const void *a, const void *b)
{ return ((abpairid_t *) a)->tid - ((abpairid_t *) b)->tid; }
#endif

/* initialization
 * seqid: 8: 34, 9: 55, 10: 89 */
abpro_t *ab_open(int seqid, int d, int model, real randdev)
{
  abpro_t *ab;
  int i, j, nd;
  double x;
  const int verbose = 0;

  die_if (d == 2 && model != 1, "%dd only for model 1", d);
  die_if (seqid < 0, "bad seqid %d\n", seqid);

  xnew(ab, 1);
  ab->d = d;

  ab->model = model;
  if (model == 1) { /* initialize model */
    ab->clj[0][0] = 1; ab->clj[1][1] = .5f;
    ab->clj[0][1] = ab->clj[1][0] = -.5f;
    ab->sla = ab->slb = 24;
  } else {
    ab->clj[0][0] = 1;
    ab->clj[0][1] = ab->clj[1][0] = ab->clj[1][1] = .5f;
    ab->sla = ab->slb = 24;
  }

  ab->seqid = seqid;
  /* determine # of atoms */
  x = pow(.5*(sqrt(5.) + 1), seqid + 1);
  i = (seqid % 2) ? (-1) : 1;
  ab->n = (int)( (x + i/x)/sqrt(5.) + .5);

  /* construct sequence */
  xnew(ab->type, ab->n);
  if (seqid < 2) {
    ab->type[0] = seqid;
  } else {
    int *s[2], sl[2], who;
    xnew(s[0], ab->n);
    xnew(s[1], ab->n);
    s[0][0] = 0; sl[0] = 1;
    s[1][0] = 1; sl[1] = 1;
    for (who = 0, i = 2; i <= seqid; i++, who = !who) {
      /* s[who] += s[!who]; */
      die_if (sl[0] + sl[1] > ab->n, "combined length > %d\n", ab->n);
      for (j = 0; j < sl[!who]; j++)
        s[who][sl[who] + j] = s[!who][j];
      sl[who] += sl[!who];
    }
    for (who = !who, j = 0; j < ab->n; j++) {
     ab->type[j] = s[who][j];
    }
    free(s[0]);
    free(s[1]);
  }

  /* number of degrees of freedom */
  ab->dof = ab->dof0 = (ab->d == 2) ? (ab->n - 2) : (2*ab->n - 5);
  if (verbose) {
    printf("n = %3d, d = %d, dof = %3d: ", ab->n, ab->d, ab->dof);
    for (i = 0; i < ab->n; i++)
      printf("%c", ab->type[i]+'A');
    printf("\n");
  }

  nd = ab->n * ab->d;
  xnew(ab->x, nd);
  xnew(ab->x1, nd);
  xnew(ab->v, nd);
  xnew(ab->f, nd);
  xnew(ab->dx, nd);
  xnew(ab->lmx, nd);
  xnew(ab->xmin, nd);

  xnew(ab->xx[0], nd * AB_XXCNT);
  for (i = 1; i < AB_XXCNT; i++)
    ab->xx[i] = ab->xx[0] + i * nd;

#ifdef _OPENMP
  {
    int sz, ir, jr, k;
    abpairid_t *pr;

    ab->nthreads = omp_get_max_threads();
    xnew(ab->f_l, nd * ab->nthreads);

    /* partition home atoms, for thread i: [ab->homeid[i], ab->homeid[i+1]) */
    xnew(ab->homeid, ab->nthreads + 1);
    sz = (ab->n + ab->nthreads - 1) / ab->nthreads; /* chunck size */
    for (i = 0; i < ab->nthreads; i++)
      ab->homeid[ i ] = sz * i;
    ab->homeid[ ab->nthreads ] = ab->n;

    /* make a list of pairs */
    xnew(ab->pair, ab->n * (ab->n - 1) / 2 * sizeof(*ab->pair));
    pr = ab->pair;
    for (i = 0; i < ab->n - 2; i++) {
      for (ir = 0; ir < ab->nthreads; ir++) /* home thread */
        if (i >= ab->homeid[ ir ] && i < ab->homeid[ ir+1 ]) break;
      for (j = i + 2; j < ab->n; j++) {
        for (jr = ir; jr < ab->nthreads; jr++) /* home thread */
          if (j >= ab->homeid[ jr ] && j < ab->homeid[ jr+1 ]) break;
        pr->i = i;
        pr->j = j;
        pr->c = ab->clj[ ab->type[i] ][ ab->type[j] ];
        pr->tid =  (jr > ir && (i + j) % 2 == 0) ? jr : ir;
        pr++;
      }
    }
    ab->paircnt = pr - ab->pair;
    qsort(ab->pair, ab->paircnt, sizeof(*ab->pair), &ab_prcmp);

    /* set up pairid, [pairid[tid], pairid[tid + 1]) pairs for thread tid */
    xnew(ab->pairid, ab->nthreads + 1);
    for (k = 0, ir = 0; ir < ab->nthreads; ir++) {
      for (; k < ab->paircnt; k++)
        if (ab->pair[k].tid == ir) break;
      ab->pairid[ir] = k;
    }
    ab->pairid[ ab->nthreads ] = ab->paircnt;
  }
#endif
  ab_initpos(ab, ab->x, randdev);
  ab->emin = ab->epot = ab_force(ab, ab->x, ab->f, 0);
  return ab;
}

/* initialize an almost straight chain,
 * randomness given by del */
int ab_initpos(abpro_t *ab, real *x, real del)
{
  int i, j;
  real dx[3];

  for (j = 0; j < ab->d; j++) ab->x[j] = 0;
  for (i = 0; i < ab->n - 1; i++) {
    for (j = 0; j < ab->d; j++) {
      dx[j] = (2.f*rand()/RAND_MAX - 1)*del + ((j == 0) ? 1.f : 0.f);
    }
    if (ab->d == 3) {
      rv3_normalize(dx);
      rv3_add(x + (i+1)*ab->d, x + i*ab->d, dx);
    } else {
      rv2_normalize(dx);
      rv2_add(x + (i+1)*ab->d, x + i*ab->d, dx);
    }
  }
  ab_shiftcom(ab, x);
  die_if (ab_checkconn(ab, x, 0) != 0, "initpos failed, with del = %g\n", del);
  return 0;
}

/* close ab */
void ab_close(abpro_t *ab)
{
  if (!ab) return;
  free(ab->type);
  free(ab->x);
  free(ab->x1);
  free(ab->dx);
  free(ab->v);
  free(ab->f);
  free(ab->lmx);
  free(ab->xmin);
  free(ab->xx[0]);
#ifdef _OPENMP
  free(ab->f_l);
#endif
  free(ab);
}

/* check connectivity */
int ab_checkconn(abpro_t *ab, const real *x, double tol)
{
  int i, d = ab->d;
  real r;

  if (tol <= 0.) tol = 1e-3;
  for (i = 0; i < ab->n-1; i++) {
    if (d == 3) {
      r = rv3_dist(x + i*3, x + (i+1)*3);
    } else {
      r = rv2_dist(x + i*2, x + (i+1)*2);
    }
    if (fabs(r-1) > tol) {
      fprintf(stderr, "link (%d,%d) is broken, r = %g\n", i, i+1, r);
      return 1;
    }
  }
  return 0;
}

/* write position file (which may include velocity) */
int ab_writepos(abpro_t *ab, const real *x, const real *v, const char *fn)
{
  FILE *fp;
  int i, j, d = ab->d, n = ab->n;

  if (fn == NULL) fn = "ab.pos";
  xfopen(fp, fn, "w", return -1);

  fprintf(fp, "# %d %d %d %d %d\n", d, ab->model, ab->seqid, ab->n, (v != NULL));
  for (i = 0; i < n; i++) {
    for (j = 0; j < d; j++) fprintf(fp, "%16.14f ", x[i*d+j]);
    if (v)
      for (j = 0; j < d; j++) fprintf(fp, "%16.14f ", v[i*d+j]);
    fprintf(fp, "%d ", ab->type[i]);
    fprintf(fp, "\n");
  }
  fclose(fp);
  return 0;
}

/* read position file (which may include velocity) */
int ab_readpos(abpro_t *ab, real *x, real *v, const char *fn)
{
  char s[1024], *p;
  FILE *fp;
  int i, j, seq, hasv = 0, next, d = ab->d, n = ab->n;
  const char *fmt;
  real vtmp[3], *vi;

  if (fn == NULL) fn = "ab.pos";
  xfopen(fp, fn, "r", return -1);

  if (fgets(s, sizeof s, fp) == NULL || s[0] != '#') {
    fprintf(stderr, "Warning: %s has no information line\n", fn);
    rewind(fp);
  } else {
    if (5 != sscanf(s+1, "%d%d%d%d%d", &i, &j, &seq, &next, &hasv)
       || i != d || j != ab->model || seq != ab->seqid || next != n) {
      fprintf(stderr, "first line is corrupted:\n%s", s);
      goto ERR;
    }
  }

  fmt = (sizeof(double) == sizeof(real)) ? "%lf%n" : "%f%n";
  for (i = 0; i < n; i++) {
    if (fgets(s, sizeof s, fp) == NULL) goto ERR;
    if (strlen(s) < 10) goto ERR;
    for (p = s, j = 0; j < d; j++, p += next)
      if (1 != sscanf(p, fmt, x+i*d+j, &next)) {
        fprintf(stderr, "cannot read i = %d, j = %d\n", i, j);
        goto ERR;
      }
    if (hasv) {
      vi = (v != NULL) ? (v + i*d) : vtmp;
      for (j = 0; j < d; j++, p += next)
        if (1 != sscanf(p, fmt, vi+j, &next)) {
          fprintf(stderr, "cannot read i = %d, j = %d\n", i, j);
          goto ERR;
        }
    }
    if (1 != sscanf(p, "%d", &j) || j != ab->type[i]) {
      fprintf(stderr, "bad type on i = %d, j = %d\n", i, j);
      goto ERR;
    }
  }
  fclose(fp);
  return 0;

ERR:
  fprintf(stderr, "position file [%s] appears to be broken on line %d!\n%s\n", fn, i, s);
  fclose(fp);
  return 1;
}

/* 2D shake with additional constraints */
static int ab_shake2d(abpro_t *ab, crv2_t *x0, rv2_t *x1, rv2_t *v, real dt,
    int itmax, double tol, int verbose)
{
  int i, j, k, again, it, n = ab->n, lgcon = ab->lgcon, lgcnt = ab->lgcnt;
  real dxi[2], g, r2, r2bad, r2ref, tmp, *lgdx0;
  rv2_t *dx0 = (rv2_t *) ab->dx;
  static const real glow = .5, r2max = 4.0;
  lgconstr_t *lgc = ab->lgc;

#pragma omp threadprivate(r2max, glow)

  /* pre-compute reference difference */
  for (i = 0; i < n-1; i++)
    rv2_diff(dx0[i], x0[i+1], x0[i]);

  /* compute distance in x0 for local constraints */
  for (k = 0; lgcon && k < lgcnt; k++) {
    if (!lgc[k].on) continue;
    i = lgc[k].i;
    j = lgc[k].j;
    rv2_diff(lgc[k].dx0, x0[j], x0[i]);
  }

  for (it = 0; it < itmax; it++) {
    again = 0;
#pragma omp parallel firstprivate(n) private(i, r2, dxi, g)
   {
#ifdef _OPENMP
    int ip = omp_get_thread_num();
    int np = omp_get_num_threads();
    int n1 = n - 1;
    int sz = (n1 + np - 1)/np;
    int imin = ip * sz, imax = (ip + 1) * sz;
    if (imax > n1) imax = n1;
#else
    int imin = 0, imax = n - 1;
#endif

    for (i = imin; i < imax; i++) { /* standard constaints */
      r2 = rv2_sqr(rv2_diff(dxi, x1[i+1], x1[i]));
      if (r2 > r2max) { /* too large, impossible to correct */
        if (verbose)
          fprintf(stderr, "shake: r(%d, %d) = %g\n", i,i+1, sqrt(r2));
        r2 = r2max;
      }

      if (fabs(r2-1) > tol) {
        if (!again) { again = 1; r2bad = r2; }

        g = rv2_dot(dxi, dx0[i]);
        if (fabs(g) < glow) { /* inner product too small */
          if (verbose)
            fprintf(stderr, "shake: bad alignment %d-%d, %g, dot = %g\n", i,i+1, sqrt(r2), g);
          g = (g > 0) ? glow : -glow;
        }
        g = (1 - r2) / (4 * g);
        rv2_sinc(x1[i],   dx0[i], -g);
        if (v) rv2_sinc(v[i], dx0[i], -g/dt);
        if (i == imax - 1) {
#pragma omp critical
         {
          rv2_sinc(x1[i+1], dx0[i],  g);
          if (v) rv2_sinc(v[i+1], dx0[i],  g/dt);
         }
        } else {
          rv2_sinc(x1[i+1], dx0[i],  g);
          if (v) rv2_sinc(v[i+1], dx0[i],  g/dt);
        }
      }
    }
   } /* end of parallel code */

    /* local constraints */
    if (lgcon) {
      for (k = 0; k < lgcnt; k++) {
        if (!lgc[k].on) continue;
        i = lgc[k].i;
        j = lgc[k].j;
        r2 = rv2_sqr(rv2_diff(dxi, x1[j], x1[i]));
        tmp = (r2ref = lgc[k].r2ref) * r2max;
        if (r2 > tmp) r2 = tmp;
        if (fabs(r2 - r2ref) > tol * r2ref) {
          if (!again) again = 1;
          g = rv2_dot(dxi, lgc[k].dx0);
          tmp = glow * r2ref;
          if (fabs(g) < tmp) g = g > 0 ? tmp : -tmp;
          g = (r2ref - r2) / (4 * g);
          lgdx0 = lgc[k].dx0;
          rv2_sinc(x1[i], lgdx0, -g);
          rv2_sinc(x1[j], lgdx0, +g);
          if (v) {
            rv2_sinc(v[i], lgdx0, -g/dt);
            rv2_sinc(v[j], lgdx0, +g/dt);
          }
        }
      }
    }

    if (!again) break;
  }

  if (it >= itmax) {
    if (verbose) {
      const char *fnf = "shakefail.pos";
      fprintf(stderr, "shake: failed after %d iter. r = 1%+g, see %s\n", it, sqrt(r2bad)-1, fnf);
      ab_writepos(ab, (real *)x1, NULL, fnf);
    }
    return -1;
  }

  return 0;
}

/* 3D shake with additional constraints */
static int ab_shake3d(abpro_t *ab, crv3_t *x0, rv3_t *x1, rv3_t *v, real dt,
    int itmax, double tol, int verbose)
{
  int i, j, k, again, it, n = ab->n, lgcon = ab->lgcon, lgcnt = ab->lgcnt;
  real dxi[3], g, r2, r2bad, r2ref, tmp, *lgdx0;
  rv3_t *dx0 = (rv3_t *) ab->dx;
  static const real glow = .5, r2max = 4.0;
  lgconstr_t *lgc = ab->lgc;

#pragma omp threadprivate(r2max, glow)

  /* pre-compute reference difference */
  for (i = 0; i < n-1; i++)
    rv3_diff(dx0[i], x0[i+1], x0[i]);

  /* compute distance in x0 for local constraints */
  for (k = 0; lgcon && k < lgcnt; k++) {
    if (!lgc[k].on) continue;
    i = lgc[k].i;
    j = lgc[k].j;
    rv3_diff(lgc[k].dx0, x0[j], x0[i]);
  }

  for (it = 0; it < itmax; it++) {
    again = 0;
#pragma omp parallel firstprivate(n) private(i, r2, dxi, g)
   {
#ifdef _OPENMP
    int ip = omp_get_thread_num();
    int np = omp_get_num_threads();
    int n1 = n - 1;
    int sz = (n1 + np - 1)/np;
    int imin = ip * sz, imax = (ip + 1) * sz;
    if (imax > n1) imax = n1;
#else
    int imin = 0, imax = n - 1;
#endif

    for (i = imin; i < imax; i++) { /* standard constaints */
      r2 = rv3_sqr(rv3_diff(dxi, x1[i+1], x1[i]));
      if (r2 > r2max) { /* too large, impossible to correct */
        if (verbose)
          fprintf(stderr, "shake: r(%d, %d) = %g\n", i,i+1, sqrt(r2));
        r2 = r2max;
      }

      if (fabs(r2-1) > tol) {
        if (!again) { again = 1; r2bad = r2; }

        g = rv3_dot(dxi, dx0[i]);
        if (fabs(g) < glow) { /* inner product too small */
          if (verbose)
            fprintf(stderr, "shake: bad alignment %d-%d, %g, dot = %g\n", i,i+1, sqrt(r2), g);
          g = (g > 0) ? glow : -glow;
        }
        g = (1 - r2) / (4 * g);
        rv3_sinc(x1[i],   dx0[i], -g);
        if (v) rv3_sinc(v[i], dx0[i], -g/dt);
        if (i == imax - 1) {
#pragma omp critical
         {
          rv3_sinc(x1[i+1], dx0[i],  g);
          if (v) rv3_sinc(v[i+1], dx0[i],  g/dt);
         }
        } else {
          rv3_sinc(x1[i+1], dx0[i],  g);
          if (v) rv3_sinc(v[i+1], dx0[i],  g/dt);
        }
      }
    }
   } /* end of parallel code */

    /* local constraints */
    if (lgcon) {
      for (k = 0; k < lgcnt; k++) {
        if (!lgc[k].on) continue;
        i = lgc[k].i;
        j = lgc[k].j;
        r2 = rv3_sqr(rv3_diff(dxi, x1[j], x1[i]));
        tmp = (r2ref = lgc[k].r2ref) * r2max;
        if (r2 > tmp) r2 = tmp;
        if (fabs(r2 - r2ref) > tol * r2ref) {
          if (!again) again = 1;
          g = rv3_dot(dxi, lgc[k].dx0);
          tmp = glow * r2ref;
          if (fabs(g) < tmp) g = g > 0 ? tmp : -tmp;
          g = (r2ref - r2) / (4 * g);
          lgdx0 = lgc[k].dx0;
          rv3_sinc(x1[i], lgdx0, -g);
          rv3_sinc(x1[j], lgdx0, +g);
          if (v) {
            rv3_sinc(v[i], lgdx0, -g/dt);
            rv3_sinc(v[j], lgdx0, +g/dt);
          }
        }
      }
    }

    if (!again) break;
  }

  if (it >= itmax) {
    if (verbose) {
      const char *fnf = "shakefail.pos";
      fprintf(stderr, "shake: failed after %d iter. r = 1%+g, see %s\n", it, sqrt(r2bad)-1, fnf);
      ab_writepos(ab, (real *)x1, NULL, fnf);
    }
    return -1;
  }

  return 0;
}


/* shake x1 according to x0 */
int ab_shake(abpro_t *ab, const real *x0, real *x1, real *v, real dt,
    int itmax, double tol, int verbose)
{
  if (itmax <= 0) itmax = 3000;
  if (tol <= 0.) tol = (sizeof(real) == sizeof(double)) ? 1e-6 : 1e-4;
  return (ab->d == 3) ?
    ab_shake3d(ab, (crv3_t *)x0, (rv3_t *)x1, (rv3_t *)v, dt, itmax, tol, verbose) :
    ab_shake2d(ab, (crv2_t *)x0, (rv2_t *)x1, (rv2_t *)v, dt, itmax, tol, verbose);
}

static int ab_rattle2d(abpro_t *ab, crv2_t *x0, rv2_t *v,
    int itmax, double tol, int verbose)
{
  int i, j, k, again, it, n = ab->n, lgcon = ab->lgcon, lgcnt = ab->lgcnt;
  real dv[2], g, rvbad, *lgdx0;
  rv2_t *dx = (rv2_t *) ab->dx;
  lgconstr_t *lgc = ab->lgc;

  for (i = 0; i < n-1; i++)
    rv2_diff(dx[i], x0[i+1], x0[i]);

  for (k = 0; lgcon && k < lgcnt; k++) { /* local constraints */
    if (!lgc[k].on) continue;
    i = lgc[k].i;
    j = lgc[k].j;
    rv2_diff(lgc[k].dx0, x0[j], x0[i]);
  }

  for (it = 0; it < itmax; it++) {
    for (again = 0, i = 0; i < n-1; i++) {
      rv2_diff(dv, v[i+1], v[i]);
      g = .5f * rv2_dot(dx[i], dv);
      if (fabs(g) > tol) {
        if (!again) { again = 1; rvbad = g; }
        rv2_sinc(v[i],   dx[i],  g);
        rv2_sinc(v[i+1], dx[i], -g);
      }
    }

    for (k = 0; lgcon && k < lgcnt; k++) { /* local constraints */
      if (!lgc[k].on) continue;
      i = lgc[k].i;
      j = lgc[k].j;
      rv2_diff(dv, v[j], v[i]);
      lgdx0 = lgc[k].dx0;
      g = .5f * rv2_dot(lgdx0, dv);
      if (fabs(g) > tol) {
        if (!again) again = 1;
        rv2_sinc(v[i], lgdx0, +g);
        rv2_sinc(v[j], lgdx0, -g);
      }
    }

    if (!again) break;
  }
  if (it >= itmax) {
    if (verbose) {
      const char *fnf = "rattlefail.pos";
      fprintf(stderr, "rattle: failed after %d iter. rv = %+g, see %s\n", it, rvbad, fnf);
      ab_writepos(ab, (real *)x0, (real *)v, fnf);
    }
    return -1;
  }
  return 0;
}

static int ab_rattle3d(abpro_t *ab, crv3_t *x0, rv3_t *v,
    int itmax, double tol, int verbose)
{
  int i, j, k, again, it, n = ab->n, lgcon = ab->lgcon, lgcnt = ab->lgcnt;
  real dv[3], g, rvbad, *lgdx0;
  rv3_t *dx = (rv3_t *) ab->dx;
  lgconstr_t *lgc = ab->lgc;

  for (i = 0; i < n-1; i++)
    rv3_diff(dx[i], x0[i+1], x0[i]);

  for (k = 0; lgcon && k < lgcnt; k++) { /* local constraints */
    if (!lgc[k].on) continue;
    i = lgc[k].i;
    j = lgc[k].j;
    rv3_diff(lgc[k].dx0, x0[j], x0[i]);
  }

  for (it = 0; it < itmax; it++) {
    for (again = 0, i = 0; i < n-1; i++) {
      rv3_diff(dv, v[i+1], v[i]);
      g = .5f * rv3_dot(dx[i], dv);
      if (fabs(g) > tol) {
        if (!again) { again = 1; rvbad = g; }
        rv3_sinc(v[i],   dx[i],  g);
        rv3_sinc(v[i+1], dx[i], -g);
      }
    }

    for (k = 0; lgcon && k < lgcnt; k++) { /* local constraints */
      if (!lgc[k].on) continue;
      i = lgc[k].i;
      j = lgc[k].j;
      rv3_diff(dv, v[j], v[i]);
      lgdx0 = lgc[k].dx0;
      g = .5f * rv3_dot(lgdx0, dv);
      if (fabs(g) > tol) {
        if (!again) again = 1;
        rv3_sinc(v[i], lgdx0, +g);
        rv3_sinc(v[j], lgdx0, -g);
      }
    }

    if (!again) break;
  }
  if (it >= itmax) {
    if (verbose) {
      const char *fnf = "rattlefail.pos";
      fprintf(stderr, "rattle: failed after %d iter. rv = %+g, see %s\n", it, rvbad, fnf);
      ab_writepos(ab, (real *)x0, (real *)v, fnf);
    }
    return -1;
  }
  return 0;
}

/* shake v according to x0 */
int ab_rattle(abpro_t *ab, const real *x0, real *v, int itmax, double tol, int verbose)
{
  if (itmax <= 0) itmax = 3000;
  if (tol <= 0.) tol = 1e-4;
  return (ab->d == 3) ?
    ab_rattle3d(ab, (crv3_t *)x0, (rv3_t *)v, itmax, tol, verbose) :
    ab_rattle2d(ab, (crv2_t *)x0, (rv2_t *)v, itmax, tol, verbose);
}

static int ab_milcshake2d(abpro_t *ab, crv2_t *x0, rv2_t *x1, rv2_t *v, real dt,
    int itmax, double tol, int verbose)
{
  int i, again, it, n = ab->n, nl;
  rv2_t *dx0 = (rv2_t *) ab->xx[0], *dx1 = (rv2_t *) ab->xx[1], *x = (rv2_t *) ab->xx[2];
  real *dl = ab->xx[2], *dm = dl + n, *du = dm + n, *lam = du + n, *rhs = lam + n;
  real y;

  nl = n - 1;
  for (i = 0; i < nl; i++) {
    rv2_diff(dx1[i], x1[i], x1[i+1]);
    rv2_diff(dx0[i], x0[i], x0[i+1]);
    rhs[i] = 1 - rv2_sqr(dx1[i]);
  }

  /* dm[0..nl-1], du[0..nl-2], dl[1..nl-1] */
  dm[0] =  4*rv2_dot(dx0[0], dx1[0]);
  du[0] = -2*rv2_dot(dx0[1], dx1[0]);
  for (i = 1; i < nl; i++) {
    dl[i] = -2*rv2_dot(dx1[i], dx0[i-1]);
    dm[i] =  4*rv2_dot(dx1[i], dx0[i]);
    du[i] = -2*rv2_dot(dx1[i], dx0[i+1]); /* no dx0[nl], but doesn't matter */
  }

  /* solve matrix equation D lam = rhs
   * first LU decompose D;
   * U --> du with diagonal being unity;
   * L --> dm and dl with dl unchanged */
  if (fabs(dm[0]) < 1e-6) return 1;
  for (i = 1; i < nl; i++) {
    dm[i] -= dl[i] * (du[i-1] /= dm[i-1]);
    if (fabs(dm[i]) < 1e-6) return i+1;
  }

  for (it = 1; it <= itmax; it++) {
    lam[0] = rhs[0]/dm[0];
    for (i = 1; i < nl; i++) /* solving L v = rhs */
      lam[i] = (rhs[i] - dl[i]*lam[i-1])/dm[i];
    for (i = nl - 1; i > 0; i--) /* solving U lam = v */
      lam[i-1] -= du[i-1]*lam[i];

    rv2_ncopy(x, x1, n);
    /* update the new position */
    for (i = 0; i < nl; i++) {
      rv2_sinc(x[i],   dx0[i],  lam[i]);
      rv2_sinc(x[i+1], dx0[i], -lam[i]);
    }

    /* calcualte the maximal error */
    for (again = 0, i = 0; i < nl; i++) {
      y = 1 - rv2_dist2(x[i], x[i+1]);
      if (fabs(y) > tol) again = 1;
      rhs[i] += y;
    }
    if (!again) break;
  }

  rv2_ncopy(x1, x, n);
  if (v != NULL) { /* correct velocities */
    for (i = 0; i < n-1; i++) {
      rv2_sinc(v[i],   dx0[i],  lam[i]/dt);
      rv2_sinc(v[i+1], dx0[i], -lam[i]/dt);
    }
  }

  if (it >= itmax) {
    if (verbose) {
      const char *fnf = "shakefail.pos";
      fprintf(stderr, "milcshake: failed after %d iter. see %s\n", it, fnf);
      ab_writepos(ab, (real *)x1, NULL, fnf);
    }
    return -1;
  }
  return 0;
}

static int ab_milcshake3d(abpro_t *ab, crv3_t *x0, rv3_t *x1, rv3_t *v, real dt,
    int itmax, double tol, int verbose)
{
  int i, again, it, n = ab->n, nl;
  rv3_t *dx0 = (rv3_t *) ab->xx[0], *dx1 = (rv3_t *) ab->xx[1], *x = (rv3_t *) ab->xx[2];
  real *dl = ab->xx[3], *dm = dl + n, *du = dm + n, *lam = du + n, *rhs = lam + n;
  real y;

  nl = n - 1;
  for (i = 0; i < nl; i++) {
    rv3_diff(dx1[i], x1[i], x1[i+1]);
    rv3_diff(dx0[i], x0[i], x0[i+1]);
    rhs[i] = 1 - rv3_sqr(dx1[i]);
  }

  /* dm[0..nl-1], du[0..nl-2], dl[1..nl-1] */
  dm[0] =  4*rv3_dot(dx0[0], dx1[0]);
  du[0] = -2*rv3_dot(dx0[1], dx1[0]);
  for (i = 1; i < nl; i++) {
    dl[i] = -2*rv3_dot(dx1[i], dx0[i-1]);
    dm[i] =  4*rv3_dot(dx1[i], dx0[i]);
    du[i] = -2*rv3_dot(dx1[i], dx0[i+1]); /* no dx0[nl], but doesn't matter */
  }

  /* solve matrix equation D lam = rhs
   * first LU decompose D;
   * U --> du with diagonal being unity;
   * L --> dm and dl with dl unchanged */
  if (fabs(dm[0]) < 1e-6) return 1;
  for (i = 1; i < nl; i++) {
    dm[i] -= dl[i] * (du[i-1] /= dm[i-1]);
    if (fabs(dm[i]) < 1e-6) return i+1;
  }

  for (it = 1; it <= itmax; it++) {
    lam[0] = rhs[0]/dm[0];
    for (i = 1; i < nl; i++) /* solving L v = rhs */
      lam[i] = (rhs[i] - dl[i]*lam[i-1])/dm[i];
    for (i = nl - 1; i > 0; i--) /* solving U lam = v */
      lam[i-1] -= du[i-1]*lam[i];

    rv3_ncopy(x, x1, n);
    /* update the new position */
    for (i = 0; i < nl; i++) {
      rv3_sinc(x[i],   dx0[i],  lam[i]);
      rv3_sinc(x[i+1], dx0[i], -lam[i]);
    }

    /* calcualte the maximal error */
    for (again = 0, i = 0; i < nl; i++) {
      y = 1 - rv3_dist2(x[i], x[i+1]);
      if (fabs(y) > tol) again = 1;
      rhs[i] += y;
    }
    if (!again) break;
  }

  rv3_ncopy(x1, x, n);
  if (v != NULL) { /* correct velocities */
    for (i = 0; i < n-1; i++) {
      rv3_sinc(v[i],   dx0[i],  lam[i]/dt);
      rv3_sinc(v[i+1], dx0[i], -lam[i]/dt);
    }
  }

  if (it >= itmax) {
    if (verbose) {
      const char *fnf = "shakefail.pos";
      fprintf(stderr, "milcshake: failed after %d iter. see %s\n", it, fnf);
      ab_writepos(ab, (real *)x1, NULL, fnf);
    }
    return -1;
  }
  return 0;
}

/* MILC shake, make |dr| = 1
 * for a random config., about 30~40% faster than shake
 * but slower than shake for near-minimum config.  */
int ab_milcshake(abpro_t *ab, const real *x0, real *x1, real *v, real dt,
    int itmax, double tol, int verbose)
{
  if (itmax <= 0) itmax = 3000;
  if (tol <= 0.) tol = (sizeof(real) == sizeof(double)) ? 1e-6 : 1e-4;
  return (ab->d == 3) ?
    ab_milcshake3d(ab, (crv3_t *)x0, (rv3_t *)x1, (rv3_t *)v, dt, itmax, tol, verbose) :
    ab_milcshake2d(ab, (crv2_t *)x0, (rv2_t *)x1, (rv2_t *)v, dt, itmax, tol, verbose);
}

static int ab_milcrattle2d(abpro_t *ab, crv2_t *x, rv2_t *v)
{
  int i, n = ab->n, nl;
  rv2_t *dx = (rv2_t *) ab->xx[0], *dv = (rv2_t *) ab->xx[1];
  real *dl = ab->xx[2], *dm = dl + n, *du = dm + n, *lam = du + n, *rhs = lam + n;

  nl = n - 1;
  for (i = 0; i < nl; i++) {
    rv2_diff(dx[i], x[i], x[i+1]);
    rv2_diff(dv[i], v[i], v[i+1]);
  }

  /* dm[0..nl-1], du[0..nl-2], dl[1..nl-1] */
  dm[0] = 2*rv2_dot(dx[0], dx[0]);
  du[0] =  -rv2_dot(dx[1], dx[0]);
  for (i = 1; i < nl; i++) {
    dl[i] =  -rv2_dot(dx[i], dx[i-1]);
    dm[i] = 2*rv2_dot(dx[i], dx[i]);
    du[i] =  -rv2_dot(dx[i], dx[i+1]); /* no dx[nl], but doesn't matter */
  }
  for (i = 0; i < nl; i++)
    rhs[i] = -rv2_dot(dv[i], dx[i]);

  /* solve matrix equation D lam = rhs
   * first LU decompose D;
   * U --> du with diagonal being unity;
   * L --> dm and dl with dl unchanged */
  if (fabs(dm[0]) < 1e-6) return 1;
  for (i = 1; i < nl; i++) {
    dm[i] -= dl[i] * (du[i-1] /= dm[i-1]);
    if (fabs(dm[i]) < 1e-6) return i+1;
  }

  lam[0] = rhs[0]/dm[0];
  for (i = 1; i < nl; i++) /* solving L v = rhs */
    lam[i] = (rhs[i] - dl[i]*lam[i-1])/dm[i];
  for (i = nl - 1; i > 0; i--) /* solving U lam = v */
    lam[i-1] -= du[i-1]*lam[i];

  /* update the new position */
  for (i = 0; i < nl; i++) {
    rv2_sinc(v[i],   dx[i],  lam[i]);
    rv2_sinc(v[i+1], dx[i], -lam[i]);
  }
  return 0;
}

static int ab_milcrattle3d(abpro_t *ab, crv3_t *x, rv3_t *v)
{
  int i, n = ab->n, nl;
  rv3_t *dx = (rv3_t *) ab->xx[0], *dv = (rv3_t *) ab->xx[1];
  real *dl = ab->xx[2], *dm = dl + n, *du = dm + n, *lam = du + n, *rhs = lam + n;

  nl = n - 1;
  for (i = 0; i < nl; i++) {
    rv3_diff(dx[i], x[i], x[i+1]);
    rv3_diff(dv[i], v[i], v[i+1]);
  }

  /* dm[0..nl-1], du[0..nl-2], dl[1..nl-1] */
  dm[0] = 2*rv3_dot(dx[0], dx[0]);
  du[0] =  -rv3_dot(dx[1], dx[0]);
  for (i = 1; i < nl; i++) {
    dl[i] =  -rv3_dot(dx[i], dx[i-1]);
    dm[i] = 2*rv3_dot(dx[i], dx[i]);
    du[i] =  -rv3_dot(dx[i], dx[i+1]); /* no dx[nl], but doesn't matter */
  }
  for (i = 0; i < nl; i++)
    rhs[i] = -rv3_dot(dv[i], dx[i]);

  /* solve matrix equation D lam = rhs
   * first LU decompose D;
   * U --> du with diagonal being unity;
   * L --> dm and dl with dl unchanged */
  if (fabs(dm[0]) < 1e-6) return 1;
  for (i = 1; i < nl; i++) {
    dm[i] -= dl[i] * (du[i-1] /= dm[i-1]);
    if (fabs(dm[i]) < 1e-6) return i+1;
  }

  lam[0] = rhs[0]/dm[0];
  for (i = 1; i < nl; i++) /* solving L v = rhs */
    lam[i] = (rhs[i] - dl[i]*lam[i-1])/dm[i];
  for (i = nl - 1; i > 0; i--) /* solving U lam = v */
    lam[i-1] -= du[i-1]*lam[i];

  /* update the new position */
  for (i = 0; i < nl; i++) {
    rv3_sinc(v[i],   dx[i],  lam[i]);
    rv3_sinc(v[i+1], dx[i], -lam[i]);
  }
  return 0;
}

/* MILC rattle, make dr.v = 0 */
int ab_milcrattle(abpro_t *ab, const real *x, real *v)
{
  return (ab->d == 3) ?
    ab_milcrattle3d(ab, (crv3_t *)x, (rv3_t *)v) :
    ab_milcrattle2d(ab, (crv2_t *)x, (rv2_t *)v);
}

static real ab_energy2dm1(abpro_t *ab, crv2_t *r, int soft)
{
  int i, j, n = ab->n;
  real ua = 0, ulj = 0;
  rv2_t *dx = (rv2_t *) ab->dx;

  for (i = 0; i < n - 1; i++)
    rv2_diff(dx[i], r[i+1], r[i]);

  for (i = 0; i < n - 2; i++)
    ua += 1.f - rv2_dot(dx[i+1], dx[i]);

#pragma omp parallel for reduction(+:ulj) private(i, j)
  for (i = 0; i < n - 2; i++) {
    real dr, dr2, dr6;
    for (j = i+2; j < n; j++) {
      dr2 = rv2_dist2(r[j], r[i]);
      if (soft && dr2 < 1.f) {
        dr = (real) sqrt(dr2);
        ulj += (52 - 48*dr) - ab->clj[ab->type[i]][ab->type[j]]*(28 - 24*dr);
      } else {
        dr2 = 1/dr2;
        dr6 = dr2*dr2*dr2;
        ulj += 4*dr6*(dr6 - ab->clj[ab->type[i]][ab->type[j]]);
      }
    }
  }
  return ua * .25f  + ulj;
}

static real ab_energy3dm1(abpro_t *ab, crv3_t *r, int soft)
{
  int i, j, n = ab->n;
  real ua = 0, ulj = 0;
  rv3_t *dx = (rv3_t *) ab->dx;

  for (i = 0; i < n - 1; i++)
    rv3_diff(dx[i], r[i+1], r[i]);

  for (i = 0; i < n - 2; i++)
    ua += 1.f - rv3_dot(dx[i+1], dx[i]);

#pragma omp parallel for reduction(+:ulj) private(i, j)
  for (i = 0; i < n - 2; i++) {
    real dr, dr2, dr6;
    for (j = i+2; j < n; j++) {
      dr2 = rv3_dist2(r[j], r[i]);
      if (soft && dr2 < 1.f) {
        dr = (real) sqrt(dr2);
        ulj += (52 - 48*dr) - ab->clj[ab->type[i]][ab->type[j]]*(28 - 24*dr);
      } else {
        dr2 = 1/dr2;
        dr6 = dr2*dr2*dr2;
        ulj += 4*dr6*(dr6 - ab->clj[ab->type[i]][ab->type[j]]);
      }
    }
  }
  return ua * .25f  + ulj;
}

static real ab_energy3dm2(abpro_t *ab, crv3_t *r, int soft)
{
  int i, j, n = ab->n;
  real ua = 0, ud = 0, ulj = 0;
  rv3_t *dx = (rv3_t *) ab->dx;

  for (i = 0; i < n - 1; i++)
    rv3_diff(dx[i], r[i+1], r[i]);

  for (i = 1; i < n-1; i++)
    ua += rv3_dot(dx[i], dx[i-1]);

  for (i = 1; i < n-2; i++)
    ud -= .5f * rv3_dot(dx[i+1], dx[i-1]);

#pragma omp parallel for reduction(+:ulj) private(i, j)
  for (i = 0; i < n-2; i++) {
    real dr2, dr6;
    for (j = i+2; j < n; j++) {
      dr2 = rv3_dist2(r[j], r[i]);
      if (soft && dr2 < 1.f) {
        ulj += ab->clj[ab->type[i]][ab->type[j]]*(ab->sla - ab->slb*(real)sqrt(dr2));
      } else {
        dr2 = 1.f/dr2;
        dr6 = dr2*dr2*dr2;
        ulj += 4.f*ab->clj[ab->type[i]][ab->type[j]]*dr6*(dr6 - 1.f);
      }
    }
  }
  return ua + ud + ulj;
}

real ab_energy(abpro_t *ab, const real *r, int soft)
{
  if (ab->model == 2)
    return ab_energy3dm2(ab, (crv3_t *)r, soft);
  else if (ab->d == 3)
    return ab_energy3dm1(ab, (crv3_t *)r, soft);
  else
    return ab_energy2dm1(ab, (crv2_t *)r, soft);
}

static real ab_force2dm1(abpro_t *ab, crv2_t *r, rv2_t *f_g, int soft)
{
  int i, j, n = ab->n;
  rv2_t *dx = (rv2_t *) ab->dx;
  real U = 0.0f, ua = 0.0f, *dxm, *dxp;

  for (i = 0; i < n - 1; i++)
    rv2_diff(dx[i], r[i+1], r[i]);

  for (i = 0; i < n; i++) rv2_zero(f_g[i]);
  for (i = 1; i < n - 1; i++) {
    dxp = dx[i];
    dxm = dx[i-1];
    ua += 1.f - rv2_dot(dxp, dxm);
    rv2_sinc(f_g[i-1], dxp, -.25f);
    rv2_sinc(f_g[i],   dxp,  .25f);
    rv2_sinc(f_g[i],   dxm, -.25f);
    rv2_sinc(f_g[i+1], dxm,  .25f);
  }

#pragma omp parallel firstprivate(n) private(i, j)
{ /* parallel code starts here */
  real dr2, dr6, ff, c;
  rv2_t *f, dxi;
  real ulj = 0.f;

#ifdef _OPENMP
  int ip = omp_get_thread_num();
  int np = omp_get_num_threads();
  int imin = ab->homeid[ip], imax = ab->homeid[ip + 1];
  int ipr, ipr0 = ab->pairid[ip], ipr1 = ab->pairid[ip + 1];
  rv2_t *f_l = (rv2_t *) ab->f_l;
  f = f_l + n * ip; /* point to the proper local force */
  /* clear the local force */
  for (i = 0; i < n; i++) rv2_zero(f[i]);
#else
  f = f_g;
#endif

#ifdef _OPENMP
  for (ipr = ipr0; ipr < ipr1; ipr++) {
    i = ab->pair[ipr].i;
    j = ab->pair[ipr].j;
    c = ab->pair[ipr].c;
#else
  for (i = 0; i < n - 2; i++)
  for (j = i + 2; j < n; j++) {
    c = ab->clj[ ab->type[i] ][ ab->type[j] ];
#endif

    dr2 = rv2_sqr( rv2_diff(dxi, r[i], r[j]) );

    if (soft && dr2 < 1.) {
      dr2 = (real) sqrt(dr2);
      ulj += (52.f - 28.f*c) - 24.f*dr2*(2.f-c);
      ff = 24.f*(2.f - c)/dr2;
    } else {
      dr2 = 1.f/dr2;
      dr6 = dr2*dr2*dr2;
      ulj += 4.f*dr6*(dr6 - c);
      ff = 24.f*dr2*dr6*(dr6*2.f - c);
    }
    rv2_sinc(f[i], dxi, +ff);
    rv2_sinc(f[j], dxi, -ff);
  }
#ifdef _OPENMP
#pragma omp barrier
  for (i = imin; i < imax; i++) /* collect global force, f_l flushed by barrier */
    for (j = 0; j < np; j++) {
      rv2_inc(f_g[i], f_l[n*j + i]);
    }
#endif
#pragma omp atomic
  U += ulj;
} /* parallel code stops */
  return ua * 0.25f + U;
}

static real ab_force3dm1(abpro_t *ab, crv3_t *r, rv3_t *f_g, int soft)
{
  int i, j, n = ab->n;
  rv3_t *dx = (rv3_t *) ab->dx;
  real U = 0.0f, ua = 0.0f, *dxm, *dxp;

  for (i = 0; i < n - 1; i++)
    rv3_diff(dx[i], r[i+1], r[i]);

  for (i = 0; i < n; i++) rv3_zero(f_g[i]);
  for (i = 1; i < n - 1; i++) {
    dxp = dx[i];
    dxm = dx[i-1];
    ua += 1.f - rv3_dot(dxp, dxm);
    rv3_sinc(f_g[i-1], dxp, -.25f);
    rv3_sinc(f_g[i],   dxp,  .25f);
    rv3_sinc(f_g[i],   dxm, -.25f);
    rv3_sinc(f_g[i+1], dxm,  .25f);
  }

#pragma omp parallel firstprivate(n) private(i, j)
{ /* parallel code starts here */
  real dr2, dr6, ff, c;
  rv3_t *f, dxi;
  real ulj = 0.f;

#ifdef _OPENMP
  int ip = omp_get_thread_num();
  int np = omp_get_num_threads();
  int imin = ab->homeid[ip], imax = ab->homeid[ip + 1];
  int ipr, ipr0 = ab->pairid[ip], ipr1 = ab->pairid[ip + 1];
  rv3_t *f_l = (rv3_t *) ab->f_l;
  f = f_l + n * ip; /* point to the proper local force */
  /* clear the local force */
  for (i = 0; i < n; i++) rv3_zero(f[i]);
#else
  f = f_g;
#endif

#ifdef _OPENMP
  for (ipr = ipr0; ipr < ipr1; ipr++) {
    i = ab->pair[ipr].i;
    j = ab->pair[ipr].j;
    c = ab->pair[ipr].c;
#else
  for (i = 0; i < n - 2; i++)
  for (j = i + 2; j < n; j++) {
    c = ab->clj[ ab->type[i] ][ ab->type[j] ];
#endif

    dr2 = rv3_sqr( rv3_diff(dxi, r[i], r[j]) );

    if (soft && dr2 < 1.) {
      dr2 = (real) sqrt(dr2);
      ulj += (52.f - 28.f*c) - 24.f*dr2*(2.f-c);
      ff = 24.f*(2.f - c)/dr2;
    } else {
      dr2 = 1.f/dr2;
      dr6 = dr2*dr2*dr2;
      ulj += 4.f*dr6*(dr6 - c);
      ff = 24.f*dr2*dr6*(dr6*2.f - c);
    }
    rv3_sinc(f[i], dxi, +ff);
    rv3_sinc(f[j], dxi, -ff);
  }
#ifdef _OPENMP
#pragma omp barrier
  for (i = imin; i < imax; i++) /* collect global force, f_l flushed by barrier */
    for (j = 0; j < np; j++) {
      rv3_inc(f_g[i], f_l[n*j + i]);
    }
#endif
#pragma omp atomic
  U += ulj;
} /* parallel code stops */
  return ua * 0.25f + U;
}

static real ab_force3dm2(abpro_t *ab, crv3_t *r, rv3_t *f_g, int soft)
{
  int i, j, n = ab->n;
  rv3_t *dx = (rv3_t *) ab->dx;
  real U = 0.f, ua = 0.f, ud = 0.f, *dxm, *dxp;

  for (i = 0; i < n - 1; i++)
    rv3_diff(dx[i], r[i+1], r[i]);

  for (i = 0; i < n; i++) rv3_zero(f_g[i]);

  for (i = 1; i < n-1; i++) {
    dxp = dx[i];
    dxm = dx[i-1];
    rv3_inc(f_g[i-1], dxp);
    rv3_dec(f_g[i],   dxp);
    rv3_inc(f_g[i],   dxm);
    rv3_dec(f_g[i+1], dxm);
    ua += rv3_dot(dxp, dxm);
  }

  for (i = 1; i < n-2; i++) {
    dxp = dx[i+1];
    dxm = dx[i-1];
    rv3_sinc(f_g[i-1], dxp, -.5f);
    rv3_sinc(f_g[i],   dxp,  .5f);
    rv3_sinc(f_g[i+1], dxm, -.5f);
    rv3_sinc(f_g[i+2], dxm,  .5f);
    ud -= .5f*rv3_dot(dxp, dxm);
  }

#pragma omp parallel firstprivate(n) private(i, j)
{ /* parallel code starts here */
  real dr2, dr6, ff, c;
  rv3_t *f, dxi;
  real ulj = 0.f;

#ifdef _OPENMP
  int ip = omp_get_thread_num();
  int np = omp_get_num_threads();
  int imin = ab->homeid[ip], imax = ab->homeid[ip + 1];
  int ipr, ipr0 = ab->pairid[ip], ipr1 = ab->pairid[ip + 1];
  rv3_t *f_l = (rv3_t *) ab->f_l;
  f = f_l + n * ip; /* point to the proper local force */
  /* clear the local force */
  for (i = 0; i < n; i++) rv3_zero(f[i]);
#else
  f = f_g;
#endif

#ifdef _OPENMP
  for (ipr = ipr0; ipr < ipr1; ipr++) {
    i = ab->pair[ipr].i;
    j = ab->pair[ipr].j;
    c = ab->pair[ipr].c;
#else
  for (i = 0; i < n - 2; i++)
  for (j = i + 2; j < n; j++) {
    c = ab->clj[ ab->type[i] ][ ab->type[j] ];
#endif

    dr2 = rv3_sqr( rv3_diff(dxi, r[i], r[j]) );

    if (soft && dr2 < 1.f) {
      dr2 = (real) sqrt(dr2);
      ulj += c*(ab->sla - ab->slb*dr2);
      ff = (ab->slb*c)/dr2;
    } else {
      dr2 = 1.f/dr2;
      dr6 = dr2*dr2*dr2;
      ulj += 4.f*c*dr6*(dr6 - 1.f);
      ff = 48.f*c*dr2*dr6*(dr6 - .5f);
    }
    rv3_sinc(f[i], dxi, +ff);
    rv3_sinc(f[j], dxi, -ff);
  }
#ifdef _OPENMP
#pragma omp barrier
  for (i = imin; i < imax; i++) /* collect global force, barrier flushes f_l */
    for (j = 0; j < np; j++)
      rv3_inc(f_g[i], f_l[n*j + i]);
#endif
#pragma omp atomic
  U += ulj;
}
  return ua + ud + U;
}

/* compute force f */
real ab_force(abpro_t *ab, const real *r, real *f, int soft)
{
  if (ab->d == 2)
    return ab_force2dm1(ab, (crv2_t *)r, (rv2_t *)f, soft);
  else if (ab->model == 1)
    return ab_force3dm1(ab, (crv3_t *)r, (rv3_t *)f, soft);
  else
    return ab_force3dm2(ab, (crv3_t *)r, (rv3_t *)f, soft);
}

/* minimizes the energy of a given configuration.
   The minimized configuration is saved in ab->lmx
   When a lowest energy configuration is found, the result is
   saved to global variable ab->xmin, with ab->emin updated. */
real ab_localmin(abpro_t *ab, const real *r, int itmax, double tol,
    int sh_itmax, double sh_tol, unsigned flags)
{
  int t, i, j, id, n = ab->n, d = ab->d;
  real up, u = 0, step = 0.02, del, mem = 1;
  real **x = ab->xx, **f = ab->xx + 2, *v = ab->xx[4];
  const real DELMAX = 0.20f;

  if (itmax <= 0) itmax = 10000;
  if (tol <= 0.) tol = 1e-12;
  /* to make a working copy */
  memcpy(x[id = 0], r, n*d*sizeof(real));
  up = ab_force(ab, x[id], f[id], 0);
  memset(v, 0, n*d*sizeof(real));

  for (t = 1; t <= itmax; t++) {
    for (i = 0; i < n; i++)
      for (j = 0; j < d; j++) {
        del = v[i*d+j] = v[i*d+j] * mem + f[id][i*d+j] * step;
        if (del > DELMAX) del = DELMAX; else if (del < -DELMAX) del = -DELMAX;
        x[!id][i*d+j] = x[id][i*d+j]+del;
      }

    if (flags & AB_MILCSHAKE) {
      if (ab_milcshake(ab, x[id], x[!id], NULL, 0., sh_itmax, sh_tol, 0) != 0) goto SHRINK;
    } else {
      if (ab_shake(ab, x[id], x[!id], NULL, 0., sh_itmax, sh_tol, 0) != 0) goto SHRINK;
    }
    u = ab_force(ab, x[!id], f[!id], 0);
    if (u > up) { mem = 0; goto SHRINK; }

    id = !id;
    if (up - u < tol) break;
    up = u;
    mem = 0.9;
    step *= 1.1;
    continue;

SHRINK:
    step *= 0.5;
  }
  if (t > itmax && (flags & AB_VERBOSE))
    fprintf(stderr, "localmin failed to converge, t = %d.\n", t);

  memcpy(ab->lmx, x[id], n*d*sizeof(real));
  if (u < ab->emin && (flags & AB_LMREGISTER)) {
    ab->emin = u;
    memcpy(ab->xmin, x[id], n*d*sizeof(real));
    if (flags & AB_LMWRITE)
      ab_writepos(ab, ab->xmin, NULL, "abmin.pos");
  }

  return u;
}

static int ab_vv2d(abpro_t *ab, real fscal, real dt, int soft, int milc)
{
  int i, verbose = 1, n = ab->n;
  real dth = .5f*dt*fscal;
  rv2_t *v = (rv2_t *)ab->v, *x = (rv2_t *)ab->x, *x1 = (rv2_t *)ab->x1, *f = (rv2_t *)ab->f;

#pragma omp parallel for schedule(static)
  for (i = 0; i < n; i++) { /* vv part 1 */
    rv2_sinc(v[i], f[i], dth);
    rv2_lincomb2(x1[i], x[i], v[i], 1, dt);
  }
  if (milc) {
    i = ab_milcshake(ab, ab->x, ab->x1, ab->v, dt, 0, 0., verbose);
  } else {
    i = ab_shake(ab, ab->x, ab->x1, ab->v, dt, 0, 0., verbose);
  }
  die_if (i != 0, "t=%g: shake failed\n", ab->t);
  rv2_ncopy(x, x1, n);

  ab->epot = ab_force(ab, ab->x, ab->f, soft); /* calculate force */

#pragma omp parallel for schedule(static)
  for (i = 0; i < n; i++) { /* vv part 2 */
    rv2_sinc(v[i], f[i], dth);
  }
  if (milc) {
    i = ab_milcrattle(ab, ab->x, ab->v);
  } else {
    i = ab_rattle(ab, ab->x, ab->v, 0, 0., verbose);
  }

  ab_ekin(ab);

  die_if (i != 0, "t=%g: failed rattle\n", ab->t);
  ab->t += dt;
  return 0;
}

static int ab_vv3d(abpro_t *ab, real fscal, real dt, int soft, int milc)
{
  int i, verbose = 1, n = ab->n;
  real dth = .5f*dt*fscal;
  rv3_t *v = (rv3_t *)ab->v, *x = (rv3_t *)ab->x, *x1 = (rv3_t *)ab->x1, *f = (rv3_t *)ab->f;

#pragma omp parallel for schedule(static)
  for (i = 0; i < n; i++) { /* vv part 1 */
    rv3_sinc(v[i], f[i], dth);
    rv3_lincomb2(x1[i], x[i], v[i], 1, dt);
  }
  if (milc) {
    i = ab_milcshake(ab, ab->x, ab->x1, ab->v, dt, 0, 0., verbose);
  } else {
    i = ab_shake(ab, ab->x, ab->x1, ab->v, dt, 0, 0., verbose);
  }
  die_if (i != 0, "t=%g: shake failed\n", ab->t);
  rv3_ncopy(x, x1, n);

  ab->epot = ab_force(ab, ab->x, ab->f, soft); /* calculate force */

#pragma omp parallel for schedule(static)
  for (i = 0; i < n; i++) { /* vv part 2 */
    rv3_sinc(v[i], f[i], dth);
  }
  if (milc) {
    i = ab_milcrattle(ab, ab->x, ab->v);
  } else {
    i = ab_rattle(ab, ab->x, ab->v, 0, 0., verbose);
  }

  ab_ekin(ab);

  die_if (i != 0, "t=%g: failed rattle\n", ab->t);
  ab->t += dt;
  return 0;
}

/* one step of velocity verlet integrator */
int ab_vv(abpro_t *ab, real fscal, real dt, unsigned flags)
{
  int soft = (flags & AB_SOFTFORCE), milc = (flags & AB_MILCSHAKE);
  return (ab->d == 3) ?
    ab_vv3d(ab, fscal, dt, soft, milc) :
    ab_vv2d(ab, fscal, dt, soft, milc);
}

/* Brownian dynamics */
int ab_brownian(abpro_t *ab, real T, real fscal, real dt, unsigned flags)
{
  int soft = (flags & AB_SOFTFORCE), milc = (flags & AB_MILCSHAKE);
  int i, nd = ab->n * ab->d, verbose = 1;
  real amp = (real) sqrt(2*dt*T);

  for (i = 0; i < nd; i++)
    ab->x1[i] = ab->x[i] + fscal*ab->f[i]*dt + (real)(grand0()*amp);

  if (milc) {
    i = ab_milcshake(ab, ab->x, ab->x1, NULL, 0.f, 0, 0., verbose);
  } else {
    i = ab_shake(ab, ab->x, ab->x1, NULL, 0.f, 0, 0., verbose);
  }
  die_if (i != 0, "t=%g: failed shake\n", ab->t);
  memcpy(ab->x, ab->x1, nd*sizeof(real));

  ab->epot = ab_force(ab, ab->x, ab->f, soft); /* calculate force */
  ab->t += dt;
  return 0;
}

/* local geometric constraints (LGC) */

/* initialize local constraints,
 * level 1: aba, 2: abba, 3: both */
INLINE void ab_initconstr(abpro_t *ab, int level)
{
  int i, di, n = ab->n;
  real dr0, rref[2][2] = {{1.115f, 1.16f}, {1.09f, 1.2f}}; /* empirical constraint distances */

  if (level < 0) { /* default level */
    if (ab->model == 2) level = 1; else level = 3;
  }
  if (ab->d == 2 || level == 0) return;
  ab->lgcnt = 0;
  xnew(ab->lgc, 1);
  for (di = 2; di <= 3; di++) { /* loop over ABA and ABBA */
    if ( !(level & (di - 1)) ) continue;
    dr0 = rref[ab->model - 1][di - 2];

    for (i = 0; i < n - di; i++) {
      if (ab->type[i] != 0 || ab->type[i + di] != 0) continue;
      xrenew(ab->lgc, ab->lgcnt + 1);
      ab->lgc[ab->lgcnt].i = i;
      ab->lgc[ab->lgcnt].j = i + di;
      ab->lgc[ab->lgcnt].on = 0;
      ab->lgc[ab->lgcnt].r2ref = dr0 * dr0;
      ab->lgcnt++;
    }
  }
  ab->lgcon = 1; /* turn on constraints by default */
  ab->lgact = 0; /* no constraint is active yet */
}

/* update constraints if atoms are close enough*/
INLINE void ab_updconstr(abpro_t *ab, double r2max)
{
  int i, j, k, lgcnt = ab->lgcnt;
  real dr2;

  if (!ab->lgcon) return;
  if (r2max <= 0) r2max = 0.3; /* default value */
  for (k = 0; k < lgcnt; k++) { /* try to turn on constraints */
    if (ab->lgc[k].on) continue;
    i = ab->lgc[k].i;
    j = ab->lgc[k].j;
    dr2 = rv3_dist2(ab->x + 3*i, ab->x + 3*j);
    if (fabs(dr2 - ab->lgc[k].r2ref) < r2max) {
      ab->lgc[k].on = 1;
      ab->lgact++;
    }
  }
  ab->dof = ab->dof0 - ab->lgact;
}
#endif /* ZCOM_ABPRO__ */
#endif /* ZCOM_ABPRO */

#ifdef  ZCOM_CAGO
#ifndef ZCOM_CAGO__
#define ZCOM_CAGO__

/* alpha-carbon based Go-model
 * J. Mol. Biol, Vol. 298 (2000) 937-953 */
typedef struct {
  int n; /* number of residues */
  int dof; /* degree of freedom */
  real kb; /* .5 kb (b - b0)^2, usually 200 */
  real ka; /* .5 ka (a - a0)^2, usually 40 */
  real kd1, kd3; /* kd1 (1 - cos(d - d0)) + kd3 (1 - cos(3*(d-d0))), 1 & 0.5 */
  real nbe, nbc; /* nbc = 4 A */
  unsigned flags; /* input flags */

  rv3_t *xref;
  real epotref; /* energy of the reference structure */
  int *aa;
  real *bref; /* bonds */
  real *aref; /* angle */
  real *dref; /* dihedral */
  real *r2ref; /* pair distance */
  int ncont; /* number of defined contacts */
  int *iscont;

  /* variables for MD simulations */
  rv3_t *x, *v, *f, *x1;
  real ekin, tkin, epot, etot, t;
  real rmsd; /* root-mean-square deviation, result from a rotfit call  */
} cago_t;

#define CAGO_VERBOSE 0x1000
#define CAGO_NCWCA   0x2000  /* use WCA-potential for noncontact pairs,
                              * otherwise, use r^12 repulsion */

#define cago_open(fnpdb, kb, ka, kd1, kd3, nbe, nbc, rcc) \
        cago_openx(fnpdb, kb, ka, kd1, kd3, nbe, nbc, rcc, \
                  CAGO_VERBOSE + (unsigned) PDB_CONTACT_HEAVY)
/* by default, we use heavy atoms to define contacts,
 * and we are print out the contact information */

STRCLS cago_t *cago_openx(const char *fnpdb, real kb, real ka, real kd1, real kd3,
    real nbe, real nbc, real rcc, unsigned flags);
STRCLS void cago_close(cago_t *go);

INLINE void cago_rmcom(cago_t *go, rv3_t *x, rv3_t *v);
INLINE int cago_initmd(cago_t *go, double rndamp, double T0);
INLINE real cago_force(cago_t *go, rv3_t *x, rv3_t *f);
INLINE int cago_vv(cago_t *go, real fscal, real dt);
INLINE real cago_ekin(cago_t *go, rv3_t *v)
  { return go->ekin = md_ekin((real *)v, go->n*3, go->dof, &go->tkin); }
INLINE void cago_vrescale(cago_t *go, real tp, real dt)
  { md_vrescale3d(go->v, go->n, go->dof, tp, dt, &go->ekin, &go->tkin); }
INLINE int cago_mcvrescale(cago_t *go, real tp, real dt)
  { return md_mcvrescale3d(go->v, go->n, go->dof, tp, dt, &go->ekin, &go->tkin); }
INLINE int cago_metro(cago_t *go, real amp, real bet);
INLINE int cago_writepos(cago_t *go, rv3_t *x, rv3_t *v, const char *fn);
INLINE int cago_readpos(cago_t *go, rv3_t *x, rv3_t *v, const char *fn);
INLINE int cago_writepdb(cago_t *go, rv3_t *x, const char *fn);

/* convenient macro for computing rmsd from the reference structure */
#define cago_rmsd(go, x, xf) rotfit3(x, xf, go->xref, NULL, go->n, NULL, NULL)
#define cago_rotfit(go, x, xf) { go->rmsd = cago_rmsd(go, x, xf); }

/* compute the number of contacts from the current configuration */
INLINE int cago_ncontacts(cago_t *go, rv3_t *x, real gam, real *Q, int *mat);

/* copy position or velocities */
#define cago_copyvec(go, t, s) rv3_ncopy(t, s, go->n)


/* initialize data for the potential energy function
 * compute the reference bonds and angles */
INLINE int cago_initpot(cago_t *go)
{
  int i, j, n = go->n;
  real dr2;

  /* calculate reference geometric parameters */
  xnew(go->bref, n - 1); /* bonds */
  for (i = 0; i < n - 1; i++)
    go->bref[i] = rv3_dist(go->xref[i], go->xref[i+1]);

  xnew(go->aref, n - 2); /* angles */
  for (i = 1; i < n - 1; i++) {
    go->aref[i-1]  = rv3_ang(go->xref[i-1], go->xref[i], go->xref[i+1],
      NULL, NULL, NULL);
  }

  xnew(go->dref, n - 3); /* dihedrals */
  for (i = 0; i < n - 3; i++) {
    go->dref[i] = rv3_calcdih(NULL,
      go->xref[i], go->xref[i+1], go->xref[i+2], go->xref[i+3], 0);
  }

  /* reference pair distances */
  xnew(go->r2ref, n*n);
  for (i = 0; i < n - 1; i++) {
    for (j = i+1; j < n; j++) {
      dr2 = rv3_dist2(go->xref[i], go->xref[j]);
      go->r2ref[j*n + i] = go->r2ref[i*n + j] = dr2;
    }
  }
  return 0;
}

/* return cago_t from pdb file fnpdb
 * `rcc' is the cutoff radius for defining contacts
 * the last fours bits of `flags' is reserved for defining PDB_CONTACT_XXX */
cago_t *cago_openx(const char *fnpdb, real kb, real ka, real kd1, real kd3,
    real nbe, real nbc, real rcc, unsigned flags)
{
  cago_t *go;
  int i, j;
  pdbmodel_t *pm;
  pdbaac_t *c;

  xnew(go, 1);

  /* read all atoms from the .pdb file */
  if ((pm = pdbm_read(fnpdb, 0)) == NULL)
    return NULL;
  go->iscont = pdbm_contact(pm, rcc,
      flags & 0xf, /* the last four bits is translated to PDB_CONTACT_XXX */
      3, /* `a' and `d' in -a-b-c-d- are excluded from being contacts */
      flags & CAGO_VERBOSE);
  /* parse it into amino-acid residues */
  if ((c = pdbaac_parse(pm, 0)) == NULL)
    return NULL;
  pdbm_free(pm);

  go->n = c->nres;
  go->dof = go->n*3 - 6;
  go->kb = kb;
  go->ka = ka;
  go->kd1 = kd1;
  go->kd3 = kd3;
  go->nbe = nbe;
  go->nbc = nbc;
  xnew(go->xref, go->n);
  xnew(go->aa, go->n);
  /* extract the C-alpha coordinates */
  for (i = 0; i < go->n; i++) {
    for (j = 0; j < 3; j++)
      go->xref[i][j] = (real) c->res[i].xca[j];
    go->aa[i] = c->res[i].aa;
  }
  pdbaac_free(c); /* throw away pdbaac */

  /* compute the reference bond length, angles, etc. */
  cago_initpot(go);

  for (go->ncont = 0, i = 0; i < go->n - 1; i++)
    for (j = i+1; j < go->n; j++)
      go->ncont += go->iscont[ i*go->n + j ];
  return go;
}

/* destroy cago_t */
void cago_close(cago_t *go)
{
  if (go->x) free(go->x);
  if (go->v) free(go->v);
  if (go->f) free(go->f);
  if (go->x1) free(go->x1);
  if (go->iscont) free(go->iscont);
  free(go->bref);
  free(go->aref);
  free(go->dref);
  free(go->r2ref);
  free(go->xref);
  free(go->aa);
  memset(go, '\0', sizeof(*go));
  free(go);
}

/* remove center of mass motion, linear and angular */
INLINE void cago_rmcom(cago_t *go, rv3_t *x, rv3_t *v)
{
  md_shiftcom3d(x, go->n);
  md_shiftcom3d(v, go->n);
  md_shiftang3d(x, v, go->n);
}

/* initialize molecular dynamics
 *  o create an initial structure
 *    if rndamp >= 0, start from the reference structure,
 *      with a random disturbance of rndamp
 *    if rndamp < 0, start from a nearly-straight chain,
 *      with a disturbance of rndamp in the x, y directions
 *  o initialize the velocity with the center of mass motion removed
 *  o compute the initial force and energy
 * */
INLINE int cago_initmd(cago_t *go, double rndamp, double T0)
{
  int i, j, n = go->n;
  real s, dx[3];

  xnew(go->f, n);
  xnew(go->v, n);
  xnew(go->x, n);
  xnew(go->x1, n);

  /* initialize position */
  if (rndamp < 0) { /* open chain */
    rndamp *= -1;
    for (i = 0; i < n-1; i++) {
      for (j = 0; j < 3; j++)
        dx[j] = (j == 0) ? 1.f : rndamp*(2.f*rnd0() - 1);
      rv3_normalize(dx);
      rv3_smul(dx, go->bref[i]);
      rv3_add(go->x[i+1], go->x[i], dx);
    }
  } else { /* copy from xref, slightly disturb it */
    for (i = 0; i < n; i++) {
      rv3_copy(go->x[i], go->xref[i]);
      for (j = 0; j < 3; j++)
        go->x[i][j] += rndamp*(2.f*rnd0() - 1);
    }
  }
  go->epotref = cago_force(go, go->xref, go->f);
  go->epot = cago_force(go, go->x, go->f);

  /* initialize velocities */
  for (j = 0; j < 3; j++)
    for (i = 0; i < n; i++)
      go->v[i][j] = rnd0() - .5;
  cago_rmcom(go, go->x, go->v); /* remove center of mass motion */
  for (s = 0, i = 0; i < n; i++)
    s += rv3_sqr(go->v[i]);
  s = sqrt( (3*n*T0)/s );
  for (i = 0; i < n; i++) {
    rv3_smul(go->v[i], s);
  }
  go->ekin = cago_ekin(go, go->v);
  go->rmsd = cago_rmsd(go, go->x, NULL);
  go->t = 0;
  return 0;
}

/* bond energy 1/2 k (r - r0)^2 */
INLINE real potbond(rv3_t a, rv3_t b, real r0, real k,
    rv3_t fa, rv3_t fb)
{
  real dx[3], r, dr, amp;

  r = rv3_norm( rv3_diff(dx, a, b) );
  dr = r - r0;
  if (fa != NULL) {
    amp = k * dr / r;
    rv3_sinc(fa, dx, -amp);
    rv3_sinc(fb, dx,  amp);
  }
  return .5f * k * dr * dr;
}

/* harmonic angle 1/2 k (ang - ang0)^2 */
INLINE real potang(rv3_t a, rv3_t b, rv3_t c, real ang0, real k,
    rv3_t fa, rv3_t fb, rv3_t fc)
{
  real dang, amp, ga[3], gb[3], gc[3];

  if (fa) { /* compute gradient */
    dang = rv3_ang(a, b, c, ga, gb, gc) - ang0;
    amp = -k * dang;
    rv3_sinc(fa, ga, amp);
    rv3_sinc(fb, gb, amp);
    rv3_sinc(fc, gc, amp);
  } else {
    dang = rv3_ang(a, b, c, NULL, NULL, NULL) - ang0;
  }
  return .5f * k * dang * dang;
}

/* 1-3 dihedral: k1 * (1 - cos(dang)) + k3 * (1 - cos(3*dang)) */
INLINE real potdih13(rv3_t a, rv3_t b, rv3_t c, rv3_t d, real ang0,
    real k1, real k3, rv3_t fa, rv3_t fb, rv3_t fc, rv3_t fd)
{
  real dang, amp, ga[3], gb[3], gc[3], gd[3];

  if (fa) {
    dang = rv3_dih(a, b, c, d, ga, gb, gc, gd) - ang0;
    amp  = (real)( -k1 * sin(dang) - 3 * k3 * sin(3*dang));
    rv3_sinc(fa, ga, amp);
    rv3_sinc(fb, gb, amp);
    rv3_sinc(fc, gc, amp);
    rv3_sinc(fd, gd, amp);
  } else {
    dang = rv3_dih(a, b, c, d, NULL, NULL, NULL, NULL) - ang0;
  }
  return (real)( k1 * (1 - cos(dang)) + k3 * (1 - cos(3 * dang)) );
}

/* 12-10 potential: u = 5(rc/r)^12 - 6(rc/r)^10,
 * the minimum is at r = rc, and u = -1 */
INLINE real pot1210(rv3_t a, rv3_t b, real rc2, real eps, rv3_t fa, rv3_t fb)
{
  real dx[3], dr2, invr2, invr4, invr6, invr10, amp;

  dr2 = rv3_sqr( rv3_diff(dx, a, b) );
  invr2 = rc2 / dr2;
  invr4 = invr2 * invr2;
  invr6 = invr4 * invr2;
  invr10 = invr4 * invr6;
  if (fa) {
    amp = 60 * eps * (invr2 - 1) * invr10 * (1/dr2);
    rv3_sinc(fa, dx,  amp);
    rv3_sinc(fb, dx, -amp);
  }
  return eps * (5 * invr2 - 6) * invr10;
}

/* WCA potential: u = (rc/r)^12 - 2 (rc/r)^6 + 1 if r < rc, or 0 otherwise
 * without the truncation, the minimum is at r = rc, and u = 0 there */
INLINE real potwca(rv3_t a, rv3_t b, real rc2, real eps, rv3_t fa, rv3_t fb)
{
  real dx[3], dr2, invr2, invr6, amp;

  dr2 = rv3_sqr( rv3_diff(dx, a, b) );
  if (dr2 > rc2) return 0;
  invr2 = rc2 / dr2;
  invr6 = invr2 * invr2 * invr2;
  if (fa) {
    amp = 12 * eps * (invr6 - 1) * invr6 * (1/dr2);
    rv3_sinc(fa, dx,  amp);
    rv3_sinc(fb, dx, -amp);
  }
  return eps * (invr6 * (invr6 - 2) + 1);
}

/* repulsive potential: (rc/r)^12 */
INLINE real potr12(rv3_t a, rv3_t b, real rc2, real eps, rv3_t fa, rv3_t fb)
{
  real dx[3], dr2, invr2, invr6, u, amp;

  dr2 = rv3_sqr( rv3_diff(dx, a, b) );
  invr2 = rc2 / dr2;
  invr6 = invr2 * invr2 * invr2;
  u = eps * invr6 * invr6;
  if (fa) {
    amp = 12 * u / dr2;
    rv3_sinc(fa, dx,  amp);
    rv3_sinc(fb, dx, -amp);
  }
  return u;
}


INLINE real cago_force(cago_t *go, rv3_t *x, rv3_t *f)
{
  int i, j, id, n = go->n, ncwca = go->flags & CAGO_NCWCA;
  real ene = 0, kb = go->kb, ka = go->ka, kd1 = go->kd1, kd3 = go->kd3,
       nbe = go->nbe, nbc2 = go->nbc*go->nbc;

  if (f != NULL) {
    for (i = 0; i < n; i++) rv3_zero(f[i]);
  }

  /* bonds */
  for (i = 0; i < n-1; i++)
    ene += potbond(x[i], x[i+1], go->bref[i], kb, f[i], f[i+1]);

  /* angles */
  for (i = 1; i < n-1; i++)
    ene += potang(x[i-1], x[i], x[i+1], go->aref[i-1], ka, f[i-1], f[i], f[i+1]);

  /* dihedrals */
  for (i = 0; i < n - 3; i++)
    ene += potdih13(x[i], x[i+1], x[i+2], x[i+3], go->dref[i],
        kd1, kd3, f[i], f[i+1], f[i+2], f[i+3]);

  /* nonbonded */
  for (i = 0; i < n - 4; i++)
    for (j = i + 4; j < n; j++) {
      id = i*n + j;
      if ( go->iscont[id] ) { /* contact pair */
        ene += pot1210(x[i], x[j], go->r2ref[id], nbe, f[i], f[j]);
      } else { /* noncontact pair */
        ene += ncwca ? potwca(x[i], x[j], nbc2, nbe, f[i], f[j])
          : potr12(x[i], x[j], nbc2, nbe, f[i], f[j]);
      }
    }
  return ene;
}

/* velocity verlet */
INLINE int cago_vv(cago_t *go, real fscal, real dt)
{
  int i, n = go->n;
  real dth = .5f*dt;
  rv3_t *v = go->v, *x = go->x, *f = go->f;

  for (i = 0; i < n; i++) { /* vv part 1 */
    rv3_sinc(v[i], f[i], dth*fscal);
    rv3_sinc(x[i], v[i], dt);
  }

  go->epot = cago_force(go, go->x, go->f); /* calculate force */

  for (i = 0; i < n; i++) { /* vv part 2 */
    rv3_sinc(v[i], f[i], dth*fscal);
  }
  go->ekin = cago_ekin(go, go->v);
  go->t += dt;
  return 0;
}

/* the change of the potential energy */
INLINE real cago_depot(cago_t *go, rv3_t *x, int i, rv3_t xi)
{
  int j, id, n = go->n, ncwca = go->flags & CAGO_NCWCA;
  rv3_t *xn = go->x1; /* we use x1 freely here */
  real ene = 0;
  real ka = go->ka, kb = go->kb, kd1 = go->kd1, kd3 = go->kd3;
  real nbe = go->nbe, nbc2 = go->nbc * go->nbc;

  /* copy coordinates */
  for (j = 0; j < n; j++) {
    if (j == i) rv3_copy(xn[i], xi);
    else rv3_copy(xn[j], x[j]);
  }

  /* bonds */
  for (j = i - 1; j <= i; j++) {
    if (j < 0 || j >= n - 1) continue;
    ene -= potbond(x[j], x[j+1], go->bref[j], kb, NULL, NULL);
    ene += potbond(xn[j], xn[j+1], go->bref[j], kb, NULL, NULL);
  }

  /* angles */
  for (j = i - 1; j <= i + 1; j++) {
    if (j < 1 || j >= n - 1) continue;
    ene -= potang(x[j-1], x[j], x[j+1], go->aref[j-1], ka,
       NULL, NULL, NULL);
    ene += potang(xn[j-1], xn[j], xn[j+1], go->aref[j-1], ka,
       NULL, NULL, NULL);
  }

  /* dihedrals */
  for (j = i - 3; j <= i; j++) {
    if (j < 0 || j >= n - 3) continue;
    ene -= potdih13(x[j], x[j+1], x[j+2], x[j+3], go->dref[j],
        kd1, kd3, NULL, NULL, NULL, NULL);
    ene += potdih13(xn[j], xn[j+1], xn[j+2], xn[j+3], go->dref[j],
        kd1, kd3, NULL, NULL, NULL, NULL);
  }

  /* nonbonded interaction */
  for (j = 0; j < n; j++) {
    if (abs(i - j) < 4) continue;

    /* subtract the old energies */
    id = i*n + j;
    if ( go->iscont[id] ) { /* contact pair */
      ene -= pot1210(x[i], x[j], go->r2ref[id], nbe, NULL, NULL);
    } else { /* noncontact pair */
      ene -= ncwca ? potwca(x[i], x[j], nbc2, nbe, NULL, NULL)
        : potr12(x[i], x[j], nbc2, nbe, NULL, NULL);
    }

    /* add the new energies */
    if ( go->iscont[id] ) { /* contact pair */
      ene += pot1210(x[i], x[j], go->r2ref[id], nbe, NULL, NULL);
    } else { /* noncontact pair */
      ene += ncwca ? potwca(x[i], x[j], nbc2, nbe, NULL, NULL)
        : potr12(x[i], x[j], nbc2, nbe, NULL, NULL);
    }
  }
  return ene;
}

/* metropolis algorithm */
INLINE int cago_metro(cago_t *go, real amp, real bet)
{
  int i;
  rv3_t xi;
  real du;

  i = (int) (go->n * rnd0());
  rv3_inc(rv3_rnd(xi, -amp, 2.f*amp), go->x[i]);
  du = cago_depot(go, go->x, i, xi);
  if (du < 0 || rnd0() < exp(-bet * du)) {
    rv3_copy(go->x[i], xi);
    go->epot += du;
    return 1;
  } else {
    return 0;
  }
}

/* write position/velocity file */
INLINE int cago_writepos(cago_t *go, rv3_t *x, rv3_t *v, const char *fn)
{
  FILE *fp;
  int i, n = go->n;

  if (fn == NULL) fn = "cago.pos";
  xfopen(fp, fn, "w", return -1);

  fprintf(fp, "# %d %d\n", go->n, (v != NULL));
  for (i = 0; i < n; i++) {
    fprintf(fp, "%16.12f %16.12f %16.12f ", x[i][0], x[i][1], x[i][2]);
    if (v)
      fprintf(fp, "%16.12f %16.12f %16.12f ", v[i][0], v[i][1], v[i][2]);
    fprintf(fp, "\n");
  }
  fclose(fp);
  return 0;
}

/* count the number of native contacts that are formed in the structure `x'
 * this counting process is independent of the process of defining contacts
 *   although the two processes are very similar, and may be the same
 * here, given a set of defined contacts, we simple observe how many pairs
 *   are close enough to be regarded as contacts
 * a contact is formed if the pair distance is <= gam * native-distance
 * return the number of contacts
 * `*Q' is the ratio of formed contacts / the total number of contacts  */
INLINE int cago_ncontacts(cago_t *go, rv3_t *x, real gam, real *Q, int *mat)
{
  int i, j, id, nct = 0, n = go->n;

  if (gam < 0) gam = 1.2; /* default value */
  if (mat) for (id = 0; id < n * n; id++) mat[id] = 0;

  for (i = 0; i < n - 1; i++)
    for (j = i+1; j < n; j++) {
      if (!go->iscont[ (id = i*n + j) ]) continue;
      if (rv3_dist(x[i], x[j]) < sqrt(go->r2ref[id]) * gam) {
        if (mat) mat[id] = mat[j*n + i] = 1;
        nct++;
      }
    }

  if (Q) *Q = nct / go->ncont;
  return nct;
}

/* read position/velocity file */
INLINE int cago_readpos(cago_t *go, rv3_t *x, rv3_t *v, const char *fn)
{
  char s[1024], *p;
  FILE *fp;
  int i, hasv = 0, next, n = go->n;
  const char *fmt;
  real vtmp[3], *vi;

  if (fn == NULL) fn = "cago.pos";
  xfopen(fp, fn, "r", return -1);

  if (fgets(s, sizeof s, fp) == NULL || s[0] != '#') {
    fprintf(stderr, "Warning: %s has no information line\n", fn);
    rewind(fp);
  } else {
    if (2 != sscanf(s+1, "%d%d", &i, &hasv) || i != n ) {
      fprintf(stderr, "first line is corrupted:\n%s", s);
      goto ERR;
    }
  }

  if (sizeof(double) == sizeof(real))
    fmt = "%lf%lf%lf%n";
  else
    fmt = "%f%f%f%n";
  for (i = 0; i < n; i++) {
    fgets(s, sizeof s, fp);
    if (strlen(s) < 10) goto ERR;
    if (3 != sscanf(s, fmt, &x[i][0], &x[i][1], &x[i][2], &next)) {
      fprintf(stderr, "cannot read x, i = %d\n", i);
      goto ERR;
    }
    p = s+next;
    if (hasv) {
      vi = (v != NULL) ? v[i] : vtmp;
      if (3 != sscanf(p, fmt, &vi[0], &vi[1], &vi[2], &next)) {
        fprintf(stderr, "cannot read v, i = %d\n", i);
        goto ERR;
      }
    }
  }
  fclose(fp);
  return 0;

ERR:
  fprintf(stderr, "position file [%s] appears to be broken on line %d!\n%s\n", fn, i, s);
  fclose(fp);
  return -1;
}

/* output pdb format */
INLINE int cago_writepdb(cago_t *go, rv3_t *x, const char *fn)
{
  FILE *fp;
  int i, n = go->n;

  xfopen(fp, fn, "w", return -1);
  for (i = 0; i < n; i++)
    fprintf(fp, "ATOM  %5d  CA  %-4sA%4d    %8.3f%8.3f%8.3f  1.00  0.00           C  \n",
        i+1, pdbaaname(go->aa[i]), i+1, x[i][0], x[i][1], x[i][2]);
  fprintf(fp, "END%77s\n", " ");
  fclose(fp);
  return 0;
}

#endif /* ZCOM_CAGO__ */
#endif /* ZCOM_CAGO */

#ifdef  ZCOM_GLEZ
#ifndef ZCOM_GLEZ__
#define ZCOM_GLEZ__
#if defined(Macintosh) || defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

static int glez_x, glez_y; /* current position */
static int glez_msdown; /* mouse state */

typedef struct tag_glez_menukey_t {
  int id;
  int key;
  const char *str;
  struct tag_glez_menukey_t *sub; /* pointer to sub menus */
} glez_menukey_t;

static glez_menukey_t *glez_user_menukey;

enum { GLEZ_MENU0 = 1000,
  GLEZ_MOVXM, GLEZ_MOVXP, GLEZ_MOVYM, GLEZ_MOVYP, GLEZ_MOVZM, GLEZ_MOVZP,
  GLEZ_ROTXM, GLEZ_ROTXP, GLEZ_ROTYM, GLEZ_ROTYP, GLEZ_ROTZM, GLEZ_ROTZP,
  GLEZ_SCLM, GLEZ_SCLP, GLEZ_FULLS, GLEZ_MENU1 };

/* rotation sub-menu */
STRCLS glez_menukey_t glez_menukey_rot[] = {
  {GLEZ_ROTXM,  'x', "Rotate around -x", NULL},
  {GLEZ_ROTXP,  'X', "Rotate around +x", NULL},
  {GLEZ_ROTYM,  'y', "Rotate around -y", NULL},
  {GLEZ_ROTYP,  'Y', "Rotate around +y", NULL},
  {GLEZ_ROTZM,  'z', "Rotate around -z", NULL},
  {GLEZ_ROTZP,  'Z', "Rotate around +z", NULL},
  {-1, '\0', NULL, NULL}};

/* scaling sub-menu */
STRCLS glez_menukey_t glez_menukey_scl[] = {
  {GLEZ_SCLM,   's', "Zoom out", NULL},
  {GLEZ_SCLP,   'S', "Zoom in", NULL},
  {GLEZ_FULLS,  'f', "Toggle fullscreen", NULL},
  {-1, '\0', NULL, NULL}};

STRCLS glez_menukey_t glez_menukey_mov[] = {
  {GLEZ_MOVXM,  'l', "Move toward -x", NULL},
  {GLEZ_MOVXP,  'r', "Move toward +x", NULL},
  {GLEZ_MOVYM,  'd', "Move toward -y", NULL},
  {GLEZ_MOVYP,  'u', "Move toward +y", NULL},
  {GLEZ_MOVZM,  'f', "Move toward -y", NULL},
  {GLEZ_MOVZP,  'n', "Move toward +y", NULL},
  {-1, '\0', NULL, NULL}};

/* main menu */
STRCLS glez_menukey_t glez_menukey[] = {
  {0,           0, "Move",   glez_menukey_mov},
  {0,           0, "Rotate", glez_menukey_rot},
  {0,           0, "Zoom",   glez_menukey_scl},
  {-1, '\0', NULL, NULL}};

STRCLS int glezInitWindow(int *argc, char **argv, int w, int h, const char *name);

static void (*glez_user_reshapefunc)(int w, int h) = NULL;
#define glezReshapeFunc(f)  { glez_user_reshapefunc = f;  glutReshapeFunc(glez_reshapefunc); }

static void (*glez_user_menufunc)(int id) = NULL;
static void (*glez_user_keyboardfunc)(unsigned char c, int x, int y) = NULL;
STRCLS void glezMenuKeyFunc(void (*menuf)(int), void (*keyf)(unsigned char, int, int),
    glez_menukey_t *mk);

static void (*glez_user_mousefunc)(int button, int state, int w, int h) = NULL;
#define glezMouseFunc(f)    { glez_user_mousefunc = f;  glutMouseFunc(glez_mousefunc); }

static void (*glez_user_motionfunc)(int w, int h) = NULL;
#define glezMotionFunc(f)   { glez_user_motionfunc = f;  glutMotionFunc(glez_motionfunc); }

STRCLS void glez_fullscreen(void);

STRCLS void glez_drawstick(real a[], real b[], real r, int nface);


/* standard reshape function for GLUT
 * x: (-1, 1), y: (-1, 1), z: (-10, 10) */
static void glez_reshapefunc(int w, int h)
{
  double xs = 1, ys = 1, zs = 10;

  if (w > h) xs = 1.*w/h;
  else ys = 1.*h/w;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-xs, xs, -ys, ys, -zs, zs);
  glMatrixMode(GL_MODELVIEW);

  if (glez_user_reshapefunc) (*glez_user_reshapefunc)(w, h);
}

/* menu function */
static void glez_menufunc(int id)
{
  GLfloat mat[4][4], amp;

  if (id <= GLEZ_MENU0 || id >= GLEZ_MENU1) {
    if (glez_user_menufunc) (*glez_user_menufunc)(id);
  } else if (id == GLEZ_SCLM || id == GLEZ_SCLP) { /* scaling */
    GLfloat s = (id == GLEZ_SCLP) ? 1.02f : 1.0f/1.02f;

    glScalef(s, s, s);
    glutPostRedisplay();
  } else if (id == GLEZ_FULLS) { /* full screen */
    glez_fullscreen();
    glutPostRedisplay();
  } else if (id >= GLEZ_MOVXM && id <= GLEZ_MOVZP) { /* translations */
    amp = ((id + GLEZ_MOVXM) % 2) ? .02f : -.02f;
    id = (id - GLEZ_MOVXM) / 2;
    glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *) mat);
    glTranslatef(mat[0][id]*amp, mat[1][id]*amp, mat[2][id]*amp);
    glutPostRedisplay();
  } else if (id >= GLEZ_ROTXM && id <= GLEZ_ROTZP) { /* rotations */
    if (id < GLEZ_ROTXM || id > GLEZ_ROTZP) return;
    amp = ((id + GLEZ_ROTXM) % 2) ? 5.f : -5.f;
    id = (id - GLEZ_ROTXM) / 2;
    glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *) mat);
    glRotatef(amp, mat[0][id], mat[1][id], mat[2][id]);
    glutPostRedisplay();
  }
}

/* recursively match short-cut keys */
static int glez_keylow(unsigned char c, glez_menukey_t *mk)
{
  int i;

  if (mk == NULL) return 0;
  for (i = 0; ; i++) {
    if (mk[i].sub != NULL) {
      if (glez_keylow(c, mk[i].sub)) return 1;
    } else if (mk[i].key == 0) {
      break;
    } else if (c == mk[i].key) {
      glez_menufunc(mk[i].id);
      return 1;
    }
  }
  return 0;
}

/* system keyboard function */
static void glez_keyboardfunc(unsigned char c, int x, int y)
{
  if (glez_keylow(c, glez_menukey)) return;
  if (glez_keylow(c, glez_user_menukey)) return;
  /* pass an unhandle key to glez_user_keyboardfunc */
  if (glez_user_keyboardfunc) (*glez_user_keyboardfunc)(c, x, y);
}

/* create a menu hiararchy as specified by mk */
static void glez_addmenu(glez_menukey_t *mk)
{
  int i, menuid, subid;
  char s[64];

  if (mk == NULL) return;
  for (i = 0; ; i++) {
    if (mk[i].sub != NULL) { /* sub menu */
      menuid = glutGetMenu(); /* get menu id */
      subid = glutCreateMenu(glez_menufunc);
      glez_addmenu(mk[i].sub); /* recursively create submenus */
      glutSetMenu(menuid); /* return to the menu */
      glutAddSubMenu(mk[i].str, subid);
    } else if (mk[i].key == 0) {
      break;
    } else { /* regular menu */
      sprintf(s, "%.32s, key: %c\n", mk[i].str, mk[i].key);
      glutAddMenuEntry(s, mk[i].id);
    }
  }
}

void glezMenuKeyFunc(void (*menuf)(int), void (*keyf)(unsigned char, int, int),
    glez_menukey_t *mk)
{
  glez_user_menufunc = menuf;
  glez_user_keyboardfunc = keyf;
  glez_user_menukey = mk;

  glutCreateMenu(glez_menufunc);
  glez_addmenu(mk); /* add user menu */
  glez_addmenu(glez_menukey); /* add system menu */
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutKeyboardFunc(glez_keyboardfunc);
}

static void glez_mousefunc(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN) {
    glez_msdown++;
    if (button == 3)
      glez_menufunc(GLEZ_SCLP);
    else if (button == 4)
      glez_menufunc(GLEZ_SCLM);
  } else if (--glez_msdown <= 0) {
    glez_msdown = 0;
  }
  glez_x = x;
  glez_y = y;
  if (glez_user_mousefunc) (*glez_user_mousefunc)(button, state, x, y);
}

/* mouse motion function for GLUT */
static void glez_motionfunc(int x, int y)
{
  if (x == glez_x && y == glez_y) return;
  if (glez_msdown) {
    float angx = (float)( (y - glez_y) * 360.f / glutGet(GLUT_WINDOW_HEIGHT) );
    float angy = (float)( (x - glez_x) * 360.f / glutGet(GLUT_WINDOW_WIDTH) );
    float mat[4][4];

    glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *) mat);
    glRotated(angx, mat[0][0], mat[1][0], mat[2][0]);
    glRotated(angy, mat[0][1], mat[1][1], mat[2][1]);
    glutPostRedisplay();
  }
  glez_x = x;
  glez_y = y;
  if (glez_user_motionfunc) (*glez_user_motionfunc)(x, y);
}

/* toggle full screen state */
void glez_fullscreen(void)
{
  static int full = 0, x, y, w, h;

  full = !full;
  if (full) {
    x = glutGet(GLUT_WINDOW_X);
    y = glutGet(GLUT_WINDOW_Y);
    w = glutGet(GLUT_WINDOW_WIDTH);
    h = glutGet(GLUT_WINDOW_HEIGHT);
    glutFullScreen();
  } else {
    glutPositionWindow(x, y);
    glutReshapeWindow(w, h);
  }
}

int glezInitWindow(int *argc, char **argv, int w, int h, const char *name)
{
  int winid;

  glutInit(argc, argv);
  w = intmin(w, glutGet(GLUT_SCREEN_HEIGHT));
  h = intmin(h, glutGet(GLUT_SCREEN_WIDTH));
  glutInitWindowSize(w, h);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  winid = glutCreateWindow(name);

  /* register glez functions */
  glezReshapeFunc(NULL);
  glezMenuKeyFunc(NULL, NULL, NULL);
  glezMouseFunc(NULL);
  glezMotionFunc(NULL);

  return winid;
}

/* draw a stick from a to b, with radius r and nface faces */
void glez_drawstick(real a[], real b[], real r, int nface)
{
  int i;
  real l, c, s, th;
  rv3_t x, y, z, p, q, u;

  rv3_diff(z, b, a);
  l = rv3_norm(z); /* stick length */
  rv3_smul(z, 1.f/l);

  rv3_normalize( rv3_make(x, z[1], -z[0], 0) ); /* a vector perpendicular to v */
  rv3_normalize( rv3_cross(y, z, x) );

  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= nface; i++) {
    th = 2.*M_PI*i/nface;
    c = (real) cos(th);
    s = (real) sin(th);
    rv3_lincomb2(u, x, y, c, s);
    rv3_lincomb2(p, a, u, 1.f, r);
    rv3_lincomb2(q, b, u, 1.f, r);
    glNormal3d(u[0], u[1], u[2]);
    glVertex3d(p[0], p[1], p[2]);
    glVertex3d(q[0], q[1], q[2]);
  }
  glEnd();
}

#endif /* ZCOM_GLEZ__ */
#endif /* ZCOM_GLEZ */

