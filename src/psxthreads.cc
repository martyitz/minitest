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
#define        ARRAY_SIZE 40000000      /* size of the data arrays used */
#define        NITER 3         /* number of iterations performed by each thread */

void *do_work(void *);
void output(int threadnum, double *p, size_t size, const char *label, bool check);
void init(double *p, size_t size);

size_t nn = ARRAY_SIZE;
int niter = NITER;
int nthreads;

int
main(int argc, char *argv[], char **envp)
{
  /* setup_run -- parse the arguments, to reset N and NITER, as requested; set post report flag */
  setup_run(argc, argv);

  /* check number and accessibility of GPU devices */
  initgpu();

  /* determine thread count */
  char *s = getenv("OMP_NUM_THREADS");
  if (s != NULL) {
    nthreads = atoi(s);
    if ( (nthreads < 1) || (nthreads > 256) ) {
      fprintf(stderr, "[%d] OMP_NUM_THREADS (%d) out of range; < 1 or > 256 setting to 2 \n", thispid, nthreads );
      nthreads = 2;
    }
  } else {
    fprintf(stderr, "[%d] OMP_NUM_THREADS was not set; setting to 2\n", thispid );
      nthreads = 2;
  }

  /* scale the array sizes based on thread count */
  if (nthreads >= 16) {
    nn = nn/8;
  }
  if (nthreads >= 128) {
    nn = nn/8;
  }

  fprintf(stderr, "\n    [%d] This run will use %d CPU thread%s with data array size = %ld; for %d iterations\n\n",
    thispid, nthreads, (nthreads==1 ? "" : "s"), nn, niter );

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
  tid = (pthread_t *) malloc( nthreads * sizeof (pthread_t) );
  tnum = (pid_t *) malloc( nthreads * sizeof(pid_t) );

  /* create nthreads threads, having each start at do_work */
  for (int i = 0; i < nthreads; i++) {
    int retval;
    tnum[i] = i; 

#ifdef BOUND
    retval = pthread_create(&(tid[i]), &attr, &do_work, (void *) &tnum[i]);
#else
    retval = pthread_create(&(tid[i]), 0, &do_work, (void *) &tnum[i]);
#endif

    if(retval != 0) {
      perror("ERROR:, pthread_create failed");
      exit(1);
    }

#if 0
    fprintf(stderr, "  [%d] created thread %d (tnum = %d)\n", i, thispid, tnum[i] );
#endif
  }

#if 0
  fprintf(stderr, "[%d] All threads created; waiting for them to exit\n", thispid );
#endif

  /* wait for all threads to complete their work and join */
  for (int i = 0; i < nthreads; i++) {
    pthread_join(tid[i], 0);
  }
  fprintf(stderr, "[%d] All threads have exited\n", thispid );

  if (run_post_rept == true) {
    system("postrept");
  }

  teardown_run();
  return 0;
}


// do_work() is called for each thread
void *
do_work(void *tnum)
{
  volatile int thread_num = (int) *(int *)tnum;
  // fprintf(stderr, "[%d] do_work entered for worker thread %d\n", thispid, thread_num );

  /* perform the number of iterations requested */
  for (int k = 0; k < niter; k++) {
      /* invoke the GPU-specific offloaded computation */
      twork(k, thread_num );

#if 0
    fprintf(stderr, " [%d[ thread %d -- end iteration %d\n", thispid, thread_num, k);
#endif
  }

  /* write out various elements of this thread's result array */
  output(thread_num, pptr[thread_num], nn, "result p array" );
  checkdata(thread_num, pptr[thread_num], nn );

#if 0
  fprintf(stderr, " [%d] worker thread %d exiting\n", thispid, thread_num);
#endif
  pthread_exit(NULL);
}

#include "maincommon.cc"
