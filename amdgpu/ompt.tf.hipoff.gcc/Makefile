SRCS	= ../../src/ompt.cc ../../src/hipgpu.cu
TARGET	= ompt.tf.hip.gcc.amd
MPITARGET = ompt.tf.hip.gcc.amd.mpi

default: $(TARGET)
all: $(TARGET) $(MPITARGET)

CXX = g++
CXXFLAGS = -g -O2 -lm -fopenmp

HIP=$(HIP_PATH)
HIPCXX = $(HIP)/bin/hipcc
HIPCXXFLAGS = -g -opt-info -O2 -std=c++11 -I${HIP}/../include/hip/

LDFLAGS = -fopenmp -lm -L${HIP}/lib64/

ompthreads.o: ../../src/ompthreads.cc ../../src/maincommon.cc
	$(CXX) $(CXXFLAGS) -c -o ompthreads.o  ../../src/ompthreads.cc

ompthreadsmpi.o: ../../src/ompthreads.cc ../../src/maincommon.cc
	$(CXX) -D USE_MPI -I$(MPI_HOME)/include $(OMPFLAGS) $(CXXFLAGS) -c -o ompthreadsmpi.o  ../../src/ompthreads.cc

hipgpu.o: ../../src/hipgpu.cu
	$(HIPCXX) $(HIPCXXFLAGS) -c -o hipgpu.o ../../src/hipgpu.cu

$(TARGET): ompthreads.o hipgpu.o
	$(HIPCXX)  -DGPU_SMALL ompthreads.o hipgpu.o -o $(TARGET) ${LDFLAGS}
	@echo ""
	@echo ""

$(MPITARGET): ompthreadsmpi.o hipgpu.o
	$(HIPCXX)  -DGPU_SMALL ompthreadsmpi.o hipgpu.o -o $(MPITARGET) ${LDFLAGS} -L$(MPI_HOME)/lib -lmpi
	@echo ""
	@echo ""

hpctmpi: $(MPITARGET)
	export RUN_POST_REPT=1; runmpihpc "-N 2" "$(MPITARGET)  -N 100000 -I 1" "-e CPUTIME -e gpu= nvidia -t" hpcmpi

run: run1 run2 run3 run8 run16 run32 run48 run64 run128 run256

hpct: hpct1 hpct2 hpct3 hpct8 hpct16 hpct32 hpct48 hpct64 hpct128 hpct256

include ../../maketargets/generic.targets
include ../../maketargets/amd.targets
include ../../maketargets/mpi.targets
