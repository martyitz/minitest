#include <string.h>
#include "minitest.h"

void
twork( int iter, int threadnum)
{
  double *d_l1 = lptr[threadnum];
  double *d_r1 = rptr[threadnum];
  double *d_p1 = pptr[threadnum];
  size_t nelements = nn;

  hrtime_t starttime = gethrtime();

#if 0
  fprintf(stderr, "[%d] Iteration %3d,   l1[%d] = 0x%016llx;   r1[%d] = 0x%016llx;   p1[%d] = 0x%016llx\n",
    thispid. iter, threadnum, l1, threadnum, r1, threadnum, p1 );
#endif

  {
    for (size_t i = 0; i < nn; ++i) {

#define kkmax 1
#include "compute.h"

    }
  }

  hrtime_t endtime = gethrtime();
  double  tempus =  (double) (endtime - starttime) / (double)1000000000.;
#if 1
  fprintf(stderr, "    [%d] Completed iteration %d, thread %d in %13.9f s.\n\n",
    thispid, iter, threadnum, tempus);
#endif

  spacer(50, true);
}

void
initgpu()
{
  /* this version does no offloading */
  fprintf(stderr, "    [%d] This run does not use any GPU devices\n", thispid );
}
