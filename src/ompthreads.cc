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
  /* setup_run -- parse the arguments, to reset N and NITER, as requested; set postreport flag */
  setup_run(argc, argv);

  /* check number and accessibility of GPU devices */
  initgpu();

  /* determine thread count */
  int nthreads;
  char *s = getenv("OMP_NUM_THREADS");
  if (s != NULL) {
    nthreads = atoi(s);
    if ( (nthreads < 1) || (nthreads > 256) ) {
      fprintf(stderr, "[%d] OMP_NUM_THREADS (%d) out of range (< 1 or > 256); setting to 2 \n", thispid, nthreads );
      nthreads = 2;
    }
  } else {
    fprintf(stderr, "[%d] OMP_NUM_THREADS was not set; setting to 2\n", thispid );
      nthreads = 2;
  }

#if 0
  int maxthreads = omp_get_max_threads();
  fprintf(stderr, "[%d] nthreads = %d; maxthreads = %d\n", thispid, nthreads, maxthreads);
#endif
  omp_num_t = nthreads;
  omp_set_num_threads (omp_num_t);

  /* Scale the size of the arrays, based on number of threads */
  if (omp_num_t >= 16) {
    nn = nn/8;
  }
  if (omp_num_t >= 128) {
    nn = nn/8;
  }

  fprintf(stderr, "    [%d] This run will use %d CPU thread%s with data array size = %ld; for %d iteration%s\n\n",
    thispid, omp_num_t, (omp_num_t==1 ? "" : "s"), nn, niter, (niter==1? "":"s") );

  /*  Allocate and initialize data */
  allocinitdata(omp_num_t);

  /* perform the number of iterations requested */
  for (int k = 0; k < niter; k++) {
#if 0
    fprintf(stderr, " [%d] begin iteration %d for all threads\n", thispid, k);
#endif
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
#if 0
    fprintf(stderr, " [%d] end iteration %d for all threads\n", thispid, k);
#endif
  }
  fprintf(stderr, " [%d] end all iterations (%d) for all threads\n",
    thispid, niter );

  /* write out various elements in each thread's result array */
  for (int k = 0; k < omp_num_t; k++) {
    output(k, pptr[k], nn, "result p array");
    checkdata(k, pptr[k], nn );
  }

  if (run_post_rept == true) {
    system("postrept");
  }

  teardown_run();
  return 0;
}

#include "maincommon.cc"
