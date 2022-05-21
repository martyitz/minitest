#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <omp.h>

#include "minitest.h"

double **lptr;
double **rptr;
double **pptr;


#ifdef USE_MPI
#include <mpi.h>
#endif

/* Parameters governing the size of the test */
#define        N 40000000      /* size of the data arrays used */
#define        NITER 3         /* number of iterations performed by each thread */

size_t nn = N;
int niter = NITER;
int omp_num_t;

int
main(int argc, char *argv[], char **envp)
{
  /* check number and accessibility of GPU devices */
  initgpu();

  /* determine thread count */
  omp_num_t = omp_get_max_threads();
  fprintf(stderr, "This run of minitest will use %d CPU thread%s with data array size = %ld\n",
    omp_num_t, (omp_num_t==1 ? "" : "s"), nn );


  /*  Allocate and initialize data */
  allocinitdata(omp_num_t);

  /* perform the number of iterations requested */
  for (int k = 0; k < NITER; k++) {
    #pragma omp parallel
    {
      /* invoke the GPU-specific offloaded computation */
      twork(k, omp_get_thread_num() );
    }

#if 0
    for ( int k = 0; k < omp_num_t; k++) {
      /* write out various elements in each thread's result array */
      // output(k, lptr[k], nn, "current l array");
      // output(k, rptr[k], nn, "current r array");
      output(k, pptr[k], nn, "current p array");
    }
#endif
    fprintf(stderr, " end iteration %d for all threads\n", k);
  }

  /* write out various elements in each thread's result array */
  for (int k = 0; k < omp_num_t; k++) {
    output(k, pptr[k], nn, "result p array");
    checkdata(k, pptr[k], nn );
  }

  return 0;
}

#include "maincommon.cc"
