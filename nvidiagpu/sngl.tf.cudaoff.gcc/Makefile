SRCS	= ../../src/single.cc ../../src/cudagpu.cu
TARGET	= sngl.tf.cuda.gcc.nv
MPITARGET = sngl.tf.cuda.gcc.nv.mpi

default: $(TARGET)
all: $(TARGET) $(MPITARGET)

CUDA = $(CUDA_HOME)
CUDACXX = ${CUDA}/bin/nvcc
CUDACXXFLAGS = -g -lineinfo -O2 -std=c++11 -I${CUDA}/include/

CXX = g++
OMPFLAGS = -g -O2 -fopenmp -lm

LDFLAGS = -lm -L${CUDA}/lib64/ -lcuda -lcudart

single.o: ../../src/single.cc
	$(CXX) $(OMPFLAGS) -c -o single.o  ../../src/single.cc

singlempi.o: ../../src/single.cc
	$(CXX) -D USE_MPI -I$(MPI_HOME)/include $(OMPFLAGS) -c -o singlempi.o  ../../src/single.cc

cudagpu.o: ../../src/cudagpu.cu
	$(CUDACXX) $(CUDACXXFLAGS) -c -o cudagpu.o ../../src/cudagpu.cu

$(TARGET): single.o cudagpu.o
	$(CXX) -fopenmp single.o cudagpu.o -o $(TARGET) ${LDFLAGS}
	@echo ""
	@echo ""

$(MPITARGET): singlempi.o cudagpu.o
	$(CXX) -fopenmp singlempi.o cudagpu.o -o $(MPITARGET) ${LDFLAGS} -L$(MPI_HOME)/lib -lmpi
	@echo ""
	@echo ""

hpctpost: $(TARGET)
	export RUN_POST_REPT=1; runhpct "$(TARGET) -I 10" "-e CPUTIME -e gpu=nvidia -t" hpctpost.cg

hpctmpi: $(MPITARGET)
	runmpihpc "-N 2" "$(MPITARGET)  -N 100000 -I 1" "-e CPUTIME -e gpu=nvidia -t" hpcmpi.cg

hpctmpipc: $(MPITARGET)
	runmpihpc "-N 2" "$(MPITARGET)  -N 100000 -I 1" "-e CPUTIME -e gpu=nvidia,pc -t" hpctmpi.cgp

run: run1

hpct: hpct1 hpctpc1

include ../../maketargets/generic.targets
include ../../maketargets/nvidia.targets
include ../../maketargets/mpi.targets
