SRCS	= ../../src/ompthreads.cc ../../src/cudagpu.cu
TARGET	= ompt.tf.cuda.gcc.nv
MPITARGET = ompt.tf.cuda.gcc.nv.mpi

default : $(TARGET)
all: $(TARGET) $(MPITARGET)

CUDA = $(CUDA_HOME)
CUDACXX = ${CUDA}/bin/nvcc
CUDACXXFLAGS = -g -lineinfo -O2 -std=c++11 -I${CUDA}/include/

CXX = g++
OMPFLAGS = -g -O2 -fopenmp -lm

LDFLAGS = -lm -L${CUDA}/lib64/ -lcuda -lcudart

ompthreads.o: ../../src/ompthreads.cc  ../../src/maincommon.cc
	$(CXX) $(OMPFLAGS) -c -o ompthreads.o  ../../src/ompthreads.cc

ompthreadsmpi.o: ../../src/ompthreads.cc  ../../src/maincommon.cc
	$(CXX) -D USE_MPI -I$(MPI_HOME)/include $(OMPFLAGS) -c -o ompthreadsmpi.o  ../../src/ompthreads.cc

cudagpu.o: ../../src/cudagpu.cu
	$(CUDACXX) $(CUDACXXFLAGS) -c -o cudagpu.o ../../src/cudagpu.cu

$(TARGET): ompthreads.o cudagpu.o
	$(CXX) -fopenmp ompthreads.o cudagpu.o -o $(TARGET) ${LDFLAGS}
	@echo ""
	@echo ""

$(MPITARGET): ompthreadsmpi.o cudagpu.o
	$(CXX) -fopenmp ompthreadsmpi.o cudagpu.o -o $(MPITARGET) ${LDFLAGS} -L$(MPI_HOME)/lib -lmpi
	@echo ""
	@echo ""

hpctmpi: $(MPITARGET)
	export RUN_POST_REPT=1; mpirun -N 2 hpcrun -e CPUTIME -e gpu=nvidia -t $(MPITARGET)
	hpcstruct hpctoolkit*$(MPITARGET)*measurements
	hpcprof hpctoolkit*$(MPITARGET)*measurements

run: run1 run2 run3 run8 run16 run32 run48 run64 run128 run256

hpct: hpctnopc hpctpc

hpctnopc: hpct1 hpct2 hpct3 hpct8 hpct16 hpct32 hpct48 hpct64 hpct128 hpct256
hpctpc: hpctpc1 hpctpc2 hpctpc3 hpctpc8 hpctpc16 hpctpc32 hpctpc48 hpctpc64 hpctpc128 hpctpc256

include ../../maketargets/generic.targets
include ../../maketargets/nvidia.targets
include ../../maketargets/mpi.targets
