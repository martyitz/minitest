#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <pthread.h>

#include "minitest.h"

double **lptr;
double **rptr;
double **pptr;

pthread_t *tid;
pid_t	*tnum;

/* Parameters governing the size of the test */
#define        N 40000000      /* size of the data arrays used */
#define        NITER 3         /* number of iterations performed by each thread */

void *do_work(void *);
void output(int threadnum, double *p, size_t size, const char *label, bool check);
void init(double *p, size_t size);

size_t nn = N;
int niter = NITER;
int nthreads;

int
main(int argc, char *argv[], char **envp)
{
  //fprintf(stderr, "sizeof(double) = %d; sizeof(double *) = %d\n", sizeof(double), sizeof(double*) );

  /* check number and accessibility of GPU devices */
  initgpu();

  /* determine thread count */
  char *s = getenv("OMP_NUM_THREADS");
  if (s != NULL) {
    nthreads = atoi(s);
    if ( (nthreads < 1) || (nthreads > 32) ) {
      fprintf(stderr, "OMP_NUM_THREADS (%d) out of range; < 1 or > 32 setting to 2 \n", nthreads );
      nthreads = 2;
    }
  } else {
    fprintf(stderr, "OMP_NUM_THREADS  was not set; setting to 2\n" );
      nthreads = 2;
  }

  fprintf(stderr, "\nThis run of minitest will use %d CPU thread%s with data array size = %ld\n",
    nthreads, (nthreads==1 ? "" : "s"), nn );

  /* Allocate and initialize data */
  allocinitdata(nthreads);

  // now create the threads
  pthread_attr_t attr;
  pthread_attr_init(&attr);

#if 0
#ifdef BOUND
  pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
#endif
#endif

  // allocate the tid array and a thread number array
  tid = new pthread_t (nthreads);
  tnum = new pid_t (nthreads);

  /* create nthreads threads, having each start at do_work */
  for (int i = 0; i < nthreads; i++) {
    int retval;
    tnum[i] = i; 

#if 0
#ifdef BOUND
    retval = pthread_create(&(tid[i]), &attr, &do_work, (void *) &tnum[i]);
#else
#endif
#endif
    retval = pthread_create(&(tid[i]), 0, &do_work, (void *) &tnum[i]);
#if 0
#endif
    if(retval != 0) {
      perror("ERROR:, pthread_create failed");
      exit(1);
    }
    fprintf(stderr, "  created thread %d (tnum = %d)\n", i, tnum[i] );
  }

  // fprintf(stderr, "All threads created; waiting for them to exit\n");

  /* wait for all threads to complete their work and join */
  for (int i = 0; i < nthreads; i++) {
    pthread_join(tid[i], 0);
  }
}


// do_work() is called for each thread
void *
do_work(void *tnum)
{
  volatile int thread_num = (int) *(int *)tnum;
  // fprintf(stderr, "do_work entered for worker thread %d\n", thread_num );

  /* perform the number of iterations requested */
  for (int k = 0; k < NITER; k++) {
      /* invoke the GPU-specific offloaded computation */
      twork(k, thread_num );

    fprintf(stderr, " thread %d -- end iteration %d\n", thread_num, k);
  }

  /* write out various elements of this thread's result array */
  output(thread_num, pptr[thread_num], nn, "result p array" );
  checkdata(thread_num, pptr[thread_num], nn );

  fprintf(stderr, " worker thread %d exiting\n", thread_num);
  pthread_exit(NULL);
}

#include "maincommon.cc"
