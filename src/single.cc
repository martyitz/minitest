#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "minitest.h"

double **lptr;
double **rptr;
double **pptr;

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

  /* set thread count to one */
  omp_num_t = 1;
  fprintf(stderr, "This test will use a single CPU thread with data array size = %ld\n",
    nn );

  /* Allocate and initialize data */
  allocinitdata(omp_num_t);

  /* perform the number of iterations requested */
  for (int k = 0; k < NITER; k++) {
    fprintf(stderr, " start iteration %d\n", k);
    {
      twork(k, 0 );
    }
    fprintf(stderr, " end   iteration %d\n", k);
  }

  /* write out various elements in each thread's result array */
  for (int k = 0; k < omp_num_t; k++) {
    output(k, pptr[k], nn, "result p array");
    checkdata(k, pptr[k], nn );
  }

  return 0;
}

#include "maincommon.cc"
