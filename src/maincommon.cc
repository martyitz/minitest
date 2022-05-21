
// #include "minitest.h"


void
allocinitdata(int numthreads)
{
  fprintf(stderr, "Allocating and initializing data for %d threads\n", numthreads );

  /* allocate pointer arrays for the threads */
  rptr = (double **) calloc(numthreads, sizeof(double *) );
  lptr = (double **) calloc(numthreads, sizeof(double *) );
  pptr = (double **) calloc(numthreads, sizeof(double *) );

  /* allocate the l, r, and p arrays for each thread */
  for ( int k = 0; k < numthreads; k++) {
    fprintf(stderr, "  thread %d allocating and initializing data\n", k );

    /* allocate and initialize the l and r arrays */
    lptr[k] = (double *) malloc (nn * sizeof(double) );
    if(lptr[k] == NULL) {
      fprintf(stderr, "Allocation for lptr[%d] failed; aborting\n", k);
      abort();
    }
    init(lptr[k], nn);

    rptr[k] = (double *) malloc (nn * sizeof(double) );
    if(rptr[k] == NULL) {
      fprintf(stderr, "Allocation for rptr[%d] failed; aborting\n", k);
      abort();
    }
    init(rptr[k], nn);

    /* allocate and clear the result array */
    pptr[k] = (double *) calloc(nn, sizeof(double) );
    if(pptr[k] == NULL) {
      fprintf(stderr, "Allocation for pptr[%d] failed; aborting\n", k);
      abort();
    }
    fprintf(stderr, "  thread %d finished allocating and initializing data\n", k );
  }

  // DEBUG -- print addresses and result contents
#if 0
  fprintf(stderr, "Initial allocation of arrays\n");
  for ( int k = 0; k < numthreads; k++) {
    fprintf(stderr,  "Thread %d,      lptr[%d] = %p; rptr[%d] = %p, pptr[%d] = %p\n",
      k, k, lptr[k], k, rptr[k], k, pptr[k] );
  }

  for ( int k = 0; k < omp_num_t; k++) {
    /* write out the last element in each thread's result array */
    // output(k, lptr[k], nn, "initial l array");
    // output(k, rptr[k], nn, "initial r array");
    // output(k, pptr[k], nn, "initial p array");
  }
  fprintf(stderr, "\n");
#endif
}

/* initialize a double array with each element set to its index */
void
init(double *pp, size_t size)
{
  for (size_t i = 0; i < size; ++i) {
    pp[i] = (double) (i+1);
  }
}

/* write out various elements from a double array, with a label */
void
output( int threadnum, double *p, size_t size, const char *label)
{
  size_t i = size -1;
  size_t j = size/8;
  size_t k = size/16;
  fprintf(stderr, "%s -- t %d, p[%zu]=%g; p[%zu]=%g; p[%zu]=%g; p[%zu]=%g; p[%zu]=%g\n",
    label, threadnum, 0UL, p[0], 1UL, p[1], k, p[k], j, p[j], i, p[i]);
}

/* check the elements of the p array */
void
checkdata(int threadnum, double *p, size_t size)
{
  int cnt = 0;
  for( int m = 0; m < size; m++) {
    /* check that the elements of the p array are all the same */
    if (p[m] != p[0])  {
      if ( cnt < 5) {
        fprintf(stderr, "     ==> ERROR -- thread %d: p[%d] (=%g) != p[0] (=%g)\n",
          threadnum, m, p[m], p[0]);
      }
      cnt ++;
    }
  }
  // print the count of errors
  if (cnt != 0) {
    fprintf(stderr, "     ==> ERROR count -- thread %d: %d;  good count = %d\n",
      threadnum, cnt, (int)size - cnt);
  } else {
    fprintf(stderr, "     all good -- thread %d: %d;  good count = %d\n",
      threadnum, cnt, (int)size - cnt);
  }
}

void
spacer(int timems, bool /*sleep */)
{
  // convert the integer millisecond argument to a timespec
  const struct timespec tspec = {0, (long) timems * 1000000 };
  //tspec.tv_sec = 0;
  //tspec.tv_nsec = (long) timems * 1000000;
  
  // sleep for that amount of time
  int ret = nanosleep( &tspec, NULL);
  if (ret != 0) {
    fprintf(stderr, "nanosleep interrupted\n" );
  }
}
