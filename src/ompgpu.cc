#include <string.h>
#include <omp.h>
#include "minitest.h"

int checkxfers();

void
twork( int iter, int threadnum)
{
  double *d_l1 = lptr[threadnum];
  double *d_r1 = rptr[threadnum];
  double *d_p1 = pptr[threadnum];

#if 0
  fprintf(stderr, "[%d] Iteration %3d,   d_l1[%d] = 0x%016llx;   d_r1[%d] = 0x%016llx;   d_p1[%d] = 0x%016llx\n",
    thispid, iter, threadnum, d_l1, threadnum, d_r1, threadnum, d_p1 );
#endif

  // int threadsPerBlock = 256;
  // int  blocksPerGrid = ( nn + threadsPerBlock -1 ) / threadsPerBlock;
  // #pragma omp teams num_teams(blocksPerGrid) thread_limit(threadsPerBlock)

  #pragma omp target map(to:d_l1[0:nn], d_r1[0:nn]) map(tofrom: d_p1[0:nn])
  #pragma omp teams
  {
    #pragma omp distribute parallel for
    for (size_t i = 0; i < nn; ++i) {
      size_t nelements = nn;

#include "compute.h"

    }
  }
  spacer (50, true);
}

void
initgpu()
{
  /* determine number of GPU's */
  int numdev = omp_get_num_devices();
  fprintf (stderr, "    [%d] Machine has %d GPU device%s\n", thispid, numdev, (numdev==1 ? "" : "s") );

  /* Test if GPU is available */
  int	idev = omp_is_initial_device();

// We don't understand when this is supposed to to work
#if 0
  int runningOnGPU = -1;
  #pragma omp target map(from:runningOnGPU)
  {
    runningOnGPU = omp_is_initial_device();
  }

  /* If still running on CPU, GPU must not be available */
  if (runningOnGPU != 0) {
#ifndef IGNORE_BAD_INITIAL_DEVICE
    fprintf(stderr, " [%d] ERROR unable to use the GPU! idev = %d, runningOnGpU -- omp_is_initial_device() = %d; exiting\n",
      thispid, idev, runningOnGPU);
    exit(1);
#else
    fprintf(stderr, " [%d] ignoring error unable to use gpu! idev = %d, runningOnGpU -- omp_is_initial_device() = %d; trying anyway\n",
      thispid, dev, runningOnGPU );
#endif
  } else {
    fprintf(stderr, "   [%d] gputest is able to use the GPU! idev = %d, runningOnGpU -- omp_is_initial_device()\n",
      thispid, idev );
  }
#endif

  int ret = checkxfers();
  if (ret != 0 ) {
    fprintf(stderr, "[%d] Return from checkxfers = %d\n", thispid, ret);
  }
}

int
checkxfers()
{
  // define original host values
  int origto = 11;
  int origfrom = 13;
  int origtofrom = 17;

  //define values the gpu will set
  int gputo = 4;
  int gpufrom = 5;
  int gputofrom = 6; 

  int to = origto;
  int from = origfrom;
  int tofrom = origtofrom;

  fprintf(stderr, "[%d] ON HOST before: to = %02d, from = %02d, tofrom = %02d\n", thispid, to, from, tofrom);

  #pragma omp target map (to:to) map(from:from) map(tofrom:tofrom)
  {
    // Note that if this and the one below are changed to fprintf(stderr, the compile fails
    //   with a link error.  For now, disable this check, and rely on the HOST checks below.
    // printf("ON GPU: enter to = %02d, from = %02d, tofrom = %02d\n", to, from, tofrom); 

    to = gputo;
    from = gpufrom;
    tofrom = gputofrom; 

    // printf("ON GPU: exit to = %02d, from = %02d, tofrom = %02d\n", to, from, tofrom); 
  }

  fprintf(stderr, "[%d] ON HOST after: to = %02d, from = %02d, tofrom = %02d\n", thispid, to, from, tofrom);
  fprintf(stderr, "[%d] EXPECTED     : to = %02d, from = %02d, tofrom = %02d\n", thispid, origto, gpufrom, gputofrom);

  return 0;
}
