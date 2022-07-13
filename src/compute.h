//  This file is included as the core of the computations on the GPU or CPU

#if 0
    // do nothing at all
#endif

#if 0
    // set the result to one in the kernel
    d_p1[i] = 1.;
#endif

#if 0
    // decrement the result by one in the kernel
    d_p1[i] = d_p1[i] -1.;
#endif

#if 1
    // do a vector add in the kernel
#ifndef kkmax
#define kkmax 200
#endif
    for (int kk = 0 ; kk < kkmax ; kk++ ) {
      // use transcendental function in the kernel
      d_p1[i] = d_p1[i] + 1.+ (sqrt( exp( log (d_l1[i]*d_l1[i]) ) + exp( log (d_r1[i]*d_r1[i]) ) ) ) /
        ( sqrt (exp( log(d_l1[i]*d_r1[i]) ) + exp( log( (d_r1[i]*d_l1[i]) )) ) );
    }
#endif

#if 0
    // do a vector add in the kernel
#define kkmax 200
    for (int kk = 0 ; kk < kkmax ; kk++ ) {
      d_p1[i] = d_p1[i] + d_l1[nelements - kk] / double(kkmax) + d_r1[kk] / double(kkmax);
    }
#endif
