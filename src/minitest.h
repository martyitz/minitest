//  This file defines the interface between the various front-ends to minitest
//	and the backends providing the computations, and/or GPU offloading
//  It also defines various timing routines

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <time.h>

extern size_t nn;
extern int omp_num_t;

extern double **lptr;
extern double **rptr;
extern double **pptr;

extern bool run_post_rept;

extern void setup_run(int argc, char** argv);
extern void teardown_run(void);
 
extern void allocinitdata(int numthreads);
extern void init(double *pp, size_t size);
extern void output( int threadnum, double *p, size_t size, const char *label );
extern void checkdata( int threadnum, double *p, size_t size );
extern void spacer(int time, bool spin);

/* routine to determine if GPU is available, and how many devices */
void initgpu();

/* routine to do the off-loaded work on the GPU */
void twork(int iter, int threadnum);

typedef long long  hrtime_t;
extern hrtime_t gethrtime();
extern hrtime_t gethrvtime();
