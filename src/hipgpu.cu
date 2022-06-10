#include "minitest.h"
#include <hip_runtime_api.h>
#include <hip_runtime.h>
#include <device_functions.h>

int checkxfers();

__global__ void
xcompute(const double *d_l1, const double *d_r1, double *d_p1, int nelements )
{
  int i = blockDim.x * blockIdx.x + threadIdx.x;
  if (i < nelements) {

#include "compute.h"

  }
}

void
twork( int iter, int threadnum)
{
  double *l1 = lptr[threadnum];
  double *r1 = rptr[threadnum];
  double *p1 = pptr[threadnum];

  hipError_t err = hipSuccess;

  //allocate device memory for copying in l1 and r1, copying out p1
  size_t size = nn * sizeof(double);
  double *d_l1 = NULL;
  double *d_r1 = NULL;
  double *d_p1 = NULL;
  err = hipMalloc((void **)&d_l1, size);
  if (err != hipSuccess) {
    fprintf(stderr, "Failed to allocate device vector d_l1 (error code %s)!\n", hipGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "Allocated device vector d_l1\n" );
#endif
  }
  err = hipMalloc((void **)&d_r1, size);
  if (err != hipSuccess) {
    fprintf(stderr, "Failed to allocate device vector d_r1 (error code %s)!\n", hipGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "Allocated device vector d_r1\n" );
#endif
  }
  err = hipMalloc((void **)&d_p1, size);
  if (err != hipSuccess) {
    fprintf(stderr, "Failed to allocate device vector d_p1 (error code %s)!\n", hipGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "Allocated device vector d_p1\n" );
#endif
  }

  // Copy l1,r1 and p1 to the device
  err = hipMemcpy(d_l1, l1, size, hipMemcpyHostToDevice);
  if (err != hipSuccess) {
    fprintf(stderr, "Failed to copy device l1 to d_l1 (error code %s)!\n", hipGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "Copied l1 to device vector d_l1\n" );
#endif
  }
  err = hipMemcpy(d_r1, r1, size, hipMemcpyHostToDevice);
  if (err != hipSuccess) {
    fprintf(stderr, "Failed to copy device r1 to d_r1 (error code %s)!\n", hipGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "Copied r1 to device vector d_r1\n" );
#endif
  }
  err = hipMemcpy(d_p1, p1, size, hipMemcpyHostToDevice);
  if (err != hipSuccess) {
    fprintf(stderr, "Failed to copy device p1 to d_p1 (error code %s)!\n", hipGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "Copied p1 to device vector d_p1\n" );
#endif
  }

  // Set up and launch the HIP kernel
  int threadsPerBlock = 256;
  int blocksPerGrid = ( nn + threadsPerBlock -1 ) / threadsPerBlock;

  fprintf(stderr, "  threadsPerBlock =  %d;  blocksPerGrid = %d\n", threadsPerBlock, blocksPerGrid );

  xcompute<<<blocksPerGrid, threadsPerBlock>>>(d_l1, d_r1, d_p1, nn);
  err = hipGetLastError();
  if (err != hipSuccess) {
    fprintf(stderr, "Failed to launch compute kernel (error code %s)!\n", hipGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "Ran GPU kernel for xcompute\n" );
#endif
  }

  // Copy p1 back to the host
  err = hipMemcpy(p1, d_p1, size, hipMemcpyDeviceToHost);
  if (err != hipSuccess) {
    fprintf(stderr, "Failed to copy p1 from device (error code %s)!\n", hipGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "Copied d_p1 back to host\n" );
#endif
  }

  // Free the device memory
  err = hipFree(d_l1);
  if (err != hipSuccess) {
    fprintf(stderr, "Failed to free d_l1 from device (error code %s)!\n", hipGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "Freed device vector d_l1\n" );
#endif
  }
  err = hipFree(d_r1);
  if (err != hipSuccess) {
    fprintf(stderr, "Failed to free d_r1 from device (error code %s)!\n", hipGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "Freed device vector d_r1\n" );
#endif
  }
  err = hipFree(d_p1);
  if (err != hipSuccess) {
    fprintf(stderr, "Failed to free d_p1 from device (error code %s)!\n", hipGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "Freed device vector d_p1\n" );
#endif
  }
#if 0
  fprintf(stderr, "\nCompleted iteration %d, thread %d\n\n", iter, threadnum);
#endif
  spacer(50, true);
}

void
initgpu()
{
#if 0
  /* determine number of GPU's */
  int numdev = omp_get_num_devices();
  fprintf (stderr, "Machine has %d GPU device%s\n", numdev, (numdev==1 ? "" : "s") );

  /* Test if GPU is available */
  int	idev = omp_is_initial_device();

  int runningOnGPU = -1;
  #pragma omp target map(from:runningOnGPU)
  {
    runningOnGPU = omp_is_initial_device();
  }

  /* If still running on CPU, GPU must not be available */
  if (runningOnGPU != 0) {
#ifndef IGNORE_BAD_INITIAL_DEVICE
    fprintf(stderr, " ERROR unable to use the GPU! idev = %d, runningOnGpU -- omp_is_initial_device() = %d; exiting\n", idev, runningOnGPU);
    exit(1);
#else
    fprintf(stderr, " ignore error unable to use gpu! idev = %d, runningOnGpU -- omp_is_initial_device() = %d; trying anyway\n",
      idev, runningOnGPU);
#endif
  } else {
    fprintfstderr, "    gputest is able to use the GPU! idev = %d, runningOnGpU -- omp_is_initial_device()\n", idev );
  }

  int ret = checkxfers();
  if (ret != 0 ) {
    fprintf(stderr, "Return from checkxfers = %d\n", ret);
  }
#endif
}

int
checkxfers()
{
// This is only needed for the OpenMP version
  return 0;
}