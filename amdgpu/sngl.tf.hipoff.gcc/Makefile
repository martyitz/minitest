SRCS	= ../../src/single.cc ../../src/hipgpu.cu
TARGET	= sngl.tf.hip.gcc.amd
MPITARGET= sngl.tf.hip.gcc.amd.mpi

default: $(TARGET)
all: $(TARGET) $(MPITARGET)

CXX = g++
OMPFLAGS = -g -O2 -fopenmp -lm

HIP=$(HIP_PATH)
HIPCXX = $(HIP)/bin/hipcc
HIPCXXFLAGS = -g -opt-info -O2 -std=c++11 -I${HIP}/../include/hip/

LDFLAGS = -fopenmp -lm -L${HIP}/lib64/

single.o: ../../src/single.cc
	$(CXX) $(OMPFLAGS) -c -o single.o  ../../src/single.cc

singlempi.o: ../../src/single.cc
	$(CXX) -D USE_MPI -I$(MPI_HOME)/include $(OMPFLAGS) -c -o singlempi.o  ../../src/single.cc

hipgpu.o: ../../src/hipgpu.cu
	$(HIPCXX) $(HIPCXXFLAGS) -c -o hipgpu.o ../../src/hipgpu.cu

$(TARGET): single.o hipgpu.o
	$(HIPCXX) -fopenmp single.o hipgpu.o -o $(TARGET) ${LDFLAGS}
	@echo ""
	@echo ""

$(MPITARGET): singlempi.o hipgpu.o
	$(HIPCXX) -fopenmp singlempi.o hipgpu.o -o $(TARGET) ${LDFLAGS} -L$(MPI_HOME)/lib -lmpi
	@echo ""
	@echo ""

hpctpost: $(TARGET)
	export RUN_POST_REPT=1; runhpct "$(TARGET) -N 100000 -I 1" "-e CPUTIME -e gpu=amd -t" hpctpost.cg

hpctmpi: $(MPITARGET)
	 runmpihpc "-N 2" "$(MPITARGET)  -N 100000 -I 1" "-e CPUTIME -e gpu=amd -t" hpctmpi.cg

run: run1

hpct: hpct1

include ../../maketargets/generic.targets
include ../../maketargets/amd.targets
include ../../maketargets/mpi.targets
