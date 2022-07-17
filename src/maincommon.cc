
// #include "minitest.h"
#ifdef USE_MPI
#include <mpi.h>
#endif


/*==================================================================*/
/* Routine to set up the run*/
/*	process arguments to extract values for nn and niter */
/*	check for environment variable"RUN_POST_REPT"
/*	If USE_MPI is defined, call MPI_Init */

static void Print_Usage(void);

bool run_post_rept = false;

void
setup_run(int argcc, char **argvv)
{
  int		i, j, num;
  int		ii;
  char	*p;

  if (argcc >=2)  /* run testcode with options */ {
    for (i = 1; i < argcc; i++) {
      j = i;

      if(argvv[i][0] != '-') {
  	Print_Usage();
      }

      if (strlen(argvv[i]) == 2) {
  	/* argument has blank separating key and number */
  	j++;
  	if (argcc > j) {
  	    p = argvv[j];
  	    num = atoll(p);
  	} else {
  	    Print_Usage();
  	}
      } else {
  	/* argument has no blank separating key and number */
  	p = argvv[i] + 2;
  	num = atoll(p);
      }
  
      switch (argvv[i][1]) {
  	case 'N':
  	    nn = num;
  	    break;
  
  	case 'I':
  	    niter = num;
  	    break;
  
  	default:
  	    Print_Usage();
      }
      i = j;
    }

  }

  // Check for environment variable to run the post-report binary
  char *s = getenv("RUN_POST_REPT");
  if (s != NULL) { 
    fprintf(stderr, "    Running of post-report enabled\n");
    run_post_rept = true;
  } else {
    fprintf(stderr, "    Running of post-report disabled\n");
    run_post_rept = false;
  }
#ifdef USE_MPI
  MPI_Init(&argcc, &argvv);
#endif

}
static void
Print_Usage(void)
{
  fprintf( stderr, "Usage: <test_name> [-N array_size] [-I iteration_count]\n");

  exit(-1);

}


/*==================================================================*/
/* Routine to tear down the run*/
/*	If USE_MPI is defined, call MPI_Finalize */
void
teardown_run(void)
{
#ifdef USE_MPI
  MPI_Finalize();
#endif
}

/*==================================================================*/
/*	Various routines to allocate and initialize data */
/*	Also, routines to check data, and output results */

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
#if 0
    fprintf(stderr, "  thread %d allocating and initializing data\n", k );
#endif

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
spacer(int timems, bool spin )
{
  if (spin == false ){ 
    // convert the integer millisecond argument to a timespec
    const struct timespec tspec = {0, (long) timems * 10000000 };

    // sleep for that amount of time
    int ret = nanosleep( &tspec, NULL);
    if (ret != 0) {
      fprintf(stderr, "nanosleep interrupted\n" );
    }

  } else {
    // burn CPU which will be visible in the traced callstacks

    int	j,k;	/* temp values for loops */
    volatile float	x;	/* temp variable for f.p. calculation */
    long long count = 0;

    for (k= 0; k < 50; k++) {
      x = 0.0;
      for(j=0; j<1000000; j++) {
        x = x + 1.0;
      }
      count++;
    }
  }
}

/* =============================================================== */
/*  Routines for high-resolution timers */

hrtime_t
gethrvtime(void)
{
  int r;
  struct timespec tp;
  hrtime_t rc = 0;
  
  r =clock_gettime(CLOCK_THREAD_CPUTIME_ID, &tp);
  if (r == 0) {
      rc = ((hrtime_t)tp.tv_sec)*1000000000 + (hrtime_t)tp.tv_nsec; 
  }

  return rc;
}

/* generic gethrtime() -- using clock_gettime(CLOCK_MONOTONIC, ...), and reformatting */
/*
 *  CLOCK_MONOTONIC
 *  Clock that cannot be set and represents monotonic time since some
 *           unspecified starting point.
 */

hrtime_t
gethrtime(void)
{
    int r;
    struct timespec tp;
    hrtime_t rc = 0;

    r =clock_gettime(CLOCK_MONOTONIC, &tp);
    if (r == 0) {
        rc = ((hrtime_t)tp.tv_sec)*1000000000 + (hrtime_t)tp.tv_nsec; 
    }

    return rc;
}

static	char	*prhrdelta(hrtime_t);
static	char	*prhrvdelta(hrtime_t);

/* hrtime routines */
int
whrvlog(hrtime_t delta, hrtime_t vdelta, char *event, char *string)
{
	char	buf[1024];
	int	bytes;

	if(string == NULL) {
		sprintf(buf,
			"  %s wall-secs., %s CPU-secs., in %s\n",
			prhrdelta(delta),
			prhrvdelta(vdelta),
			event);
	} else {
		sprintf(buf,
			"  %s wall-secs., %s CPU-secs., in %s\n\t%s\n",
			prhrdelta(delta),
			prhrvdelta(vdelta),
			event, string);
	}

	bytes = fprintf(stderr, "%s", buf);
	return bytes;
}


/*	prhrdelta (hrtime_t delta)
 *		returns a pointer to a static string in the form:
 *		sec.micros
 *		  1.123456
 *		0123456789
 *
 *	prhrvdelta is the same, but uses a different static buffer
 */

static	char	*
prhrdelta(hrtime_t delta)
{
	static	char	cvdbuf[26];
	double	tempus;

	/* convert to seconds */
	tempus = ( (double) delta) / (double)1000000000.;
	sprintf(cvdbuf, "%10.6f", tempus);
	return(cvdbuf);
}

static	char	*
prhrvdelta(hrtime_t delta)
{
	static	char	cvdbuf[26];
	double	tempus;

	/* convert to seconds */
	tempus = ( (double) delta) / (double)1000000000.;
	sprintf(cvdbuf, "%10.6f", tempus);
	return(cvdbuf);
}


