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
main(int argc, char **argv, char **envp)
{
  /* setup_run -- parse the arguments, to reset N and NITER, as requested, set post report flag */
  setup_run(argc, argv);

  /* check number and accessibility of GPU devices */
  initgpu();

  /* set thread count to one */
  omp_num_t = 1;
  fprintf(stderr, "    [%d] This test will use a single CPU thread with data array size = %ld; for %d iterations\n\n",
    thispid, nn, niter );

  /* Allocate and initialize data */
  allocinitdata(omp_num_t);

  /* perform the number of iterations requested */
  fprintf(stderr, "  [%d] start %d iteration%s\n", thispid, niter, (niter ==1 ? "" : "s") );
  for (int k = 0; k < niter; k++) {
#if 0
    fprintf(stderr, "    [%d] start iteration %d\n", thispid, k);
#endif
    {
      twork(k, 0 );
    }
#if 0
    fprintf(stderr, "  [%d] end     iteration %d\n", thispid, k);
#endif
  }
  fprintf(stderr, "  [%d] end %d iteration%s\n", thispid, niter,  (niter ==1 ? "" : "s") );

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
