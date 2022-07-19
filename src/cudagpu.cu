#include "minitest.h"
#include <cuda.h>
#include <cuda_runtime_api.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

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

  cudaError_t err = cudaSuccess;

#if 0
  fprintf(stderr, "[%d]    T %d, I %d, start cuda twork\n",
      thispid, threadnum, iter );
#endif
  //allocate device memory for copying in l1 and r1, copying out p1
  size_t size = nn * sizeof(double);
  double *d_l1 = NULL;
  double *d_r1 = NULL;
  double *d_p1 = NULL;

  err = cudaMalloc((void **)&d_l1, size);
  if (err != cudaSuccess) {
    fprintf(stderr, "[%d]    T %d, I %d, Failed to allocate device vector d_l1 (error code %s)!\n",
      thispid, threadnum, iter, cudaGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "[%d]    T %d, I %d, Alloc device vector d_l1 (%p)\n",
      thispid, threadnum, iter, d_l1 );
#endif
  }
  err = cudaMalloc((void **)&d_r1, size);
  if (err != cudaSuccess) {
    fprintf(stderr, "[%d]    T %d, I %d, Failed to allocate device vector d_r1 (error code %s)!\n",
      thispid, threadnum, iter, cudaGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "[%d]    T %d, I %d, Alloc device vector d_r1 (%p)\n",
      thispid, threadnum, iter, d_r1 );
#endif
  }
  err = cudaMalloc((void **)&d_p1, size);
  if (err != cudaSuccess) {
    fprintf(stderr, "[%d]    T %d, I %d, Failed to allocate device vector d_p1 (error code %s)!\n",
      thispid, threadnum, iter, cudaGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "[%d]    T %d, I %d, Alloc device vector d_p1 (%p)\n",
      thispid, threadnum, iter, d_p1 );
#endif
  }

  // Copy l1,r1 and p1 to the device
  err = cudaMemcpy(d_l1, l1, size, cudaMemcpyHostToDevice);
  if (err != cudaSuccess) {
    fprintf(stderr, "[%d]    T %d, I %d, Failed to copy device l1 to d_l1 (error code %s)!\n",
      thispid, threadnum, iter, cudaGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "[%d]    T %d, I %d, Copied l1 to device vector d_l1\n",
      thispid, threadnum, iter );
#endif
  }
  err = cudaMemcpy(d_r1, r1, size, cudaMemcpyHostToDevice);
  if (err != cudaSuccess) {
    fprintf(stderr, "[%d]    T %d, I %d, Failed to copy device r1 to d_r1 (error code %s)!\n",
      thispid, threadnum, iter, cudaGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "[%d]    T %d, I %d, Copied r1 to device vector d_r1\n",
      thispid, threadnum, iter );
#endif
  }
  err = cudaMemcpy(d_p1, p1, size, cudaMemcpyHostToDevice);
  if (err != cudaSuccess) {
    fprintf(stderr, "[%d]    T %d, I %d, Failed to copy device p1 to d_p1 (error code %s)!\n",
      thispid, threadnum, iter, cudaGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "[%d]    T %d, I %d, Copied p1 to device vector d_p1\n",
      thispid, threadnum, iter );
#endif
  }

  // Set up and launch the CUDA kernel
  int threadsPerBlock = 256;
  int blocksPerGrid = ( nn + threadsPerBlock -1 ) / threadsPerBlock;

#if 0
  fprintf(stderr, "      [%d]  t %d, i%d, threadsPerBlock =  %d;  blocksPerGrid = %d\n",
    thispid, threadnum, iter, threadsPerBlock, blocksPerGrid );
#endif

  xcompute<<<blocksPerGrid, threadsPerBlock>>>(d_l1, d_r1, d_p1, nn);
  err = cudaGetLastError();
  if (err != cudaSuccess) {
    fprintf(stderr, "[%d]    T %d, I %d, Failed to launch compute kernel (error code %s)!\n",
      thispid, threadnum, iter, cudaGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "[%d]    T %d, I %d, Ran GPU kernel for xcompute\n",
      thispid, threadnum, iter );
#endif
  }

  // Copy p1 back to the host
  err = cudaMemcpy(p1, d_p1, size, cudaMemcpyDeviceToHost);
  if (err != cudaSuccess) {
    fprintf(stderr, "[%d]    T %d, I %d, Failed to copy p1 from device (error code %s)!\n",
      thispid, threadnum, iter, cudaGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "[%d]    T %d, I %d, Copied d_p1 back to host\n",
      thispid, threadnum, iter );
#endif
  }

  // Free the device memory
  err = cudaFree(d_l1);
  if (err != cudaSuccess) {
    fprintf(stderr, "[%d]    T %d, I %d, Failed to free d_l1 from device (error code %s)!\n",
      thispid, threadnum, iter, cudaGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "[%d]    T %d, I %d, Freed device vector d_l1 (%p)\n",
      thispid, threadnum, iter, d_l1 );
#endif
  }
  err = cudaFree(d_r1);
  if (err != cudaSuccess) {
    fprintf(stderr, "[%d]    T %d, I %d, Failed to free d_r1 from device (error code %s)!\n",
      thispid, threadnum, iter, cudaGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "[%d]    T %d, I %d, Freed device vector d_r1 (%p)\n",
      thispid, threadnum, iter, d_r1 );
#endif
  }
  err = cudaFree(d_p1);
  if (err != cudaSuccess) {
    fprintf(stderr, "[%d]    T %d, I %d, Failed to free d_p1 from device (error code %s)!\n",
      thispid, threadnum, iter, cudaGetErrorString(err));
    exit(-1);
#if 0
  } else {
    fprintf(stderr, "[%d]    T %d, I %d, Freed device vector d_p1 (%p)\n",
      thispid, threadnum, iter, d_p1 );
#endif
  }
#if 0
  fprintf(stderr, "    [%d] Completed iteration %d, thread %d\n\n",
    thispid, iter, threadnum);
#endif
  spacer (50, true);
}

void
initgpu()
{
#if 0
  /* determine number of GPU's */
  int numdev = omp_get_num_devices();
  fprintf (stderr,     "[%d] Machine has %d GPU device%s\n",
    thispid, numdev, (numdev==1 ? "" : "s") );

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
    fprintf(stderr, "[%d] ERROR unable to use the GPU! idev = %d, runningOnGpU -- omp_is_initial_device() = %d; exiting\n",
      thispid, idev, runningOnGPU);
    exit(1);
#else
    fprintf(stderr, "[%d] ignoring error unable to use gpu! idev = %d, runningOnGpU -- omp_is_initial_device() = %d; trying anyway\n",
      thispid, idev, runningOnGpu );
#endif
  } else {
    fprintfstderr, "   [%d] gputest is able to use the GPU! idev = %d, runningOnGpU -- omp_is_initial_device()\n",
      thispid, idev );
  }

  int ret = checkxfers();
  if (ret != 0 ) {
    fprintf(stderr, "[%d] Return from checkxfers = %d\n", thispid,, ret);
  }
#endif
}

int
checkxfers()
{
// This is only needed for the OpenMP offload version
  return 0;
}
