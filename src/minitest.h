//  This file defines the interface between the various front-ends to minitest
//	and the backends providing the computations, and/or GPU offloading

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <time.h>

extern size_t nn;
extern int omp_num_t;

extern double **lptr;
extern double **rptr;
extern double **pptr;

extern void allocinitdata(int numthreads);
extern void init(double *pp, size_t size);
extern void output( int threadnum, double *p, size_t size, const char *label );
extern void checkdata( int threadnum, double *p, size_t size );
extern void spacer(int time, bool sleep);

/* routine to determine if GPU is available, and how many devices */
void initgpu();

/* routine to do the off-loaded work on the GPU */
void twork(int iter, int threadnum);

