SRCS	= ../../src/single.cc ../../src/cudagpu.cu
TARGET	= sngl.tf.cuda.gcc.nv

default all: $(TARGET)

CUDA = $(CUDA_HOME)
CUDACXX = ${CUDA}/bin/nvcc
CUDACXXFLAGS = -g -lineinfo -O2 -std=c++11 -I${CUDA}/include/

CXX = g++
OMPFLAGS = -g -O2 -fopenmp -lm

LDFLAGS = -lm -L${CUDA}/lib64/ -lcuda -lcudart

single.o: ../../src/single.cc
	$(CXX) $(OMPFLAGS) -c -o single.o  ../../src/single.cc

cudagpu.o: ../../src/cudagpu.cu
	$(CUDACXX) $(CUDACXXFLAGS) -c -o cudagpu.o ../../src/cudagpu.cu

$(TARGET): single.o cudagpu.o
	$(CXX) -fopenmp single.o cudagpu.o -o $(TARGET) ${LDFLAGS}
	@echo ""
	@echo ""

run: run1

hpct: hpct1 hpctpc1

include ../../maketargets/generic.targets
include ../../maketargets/nvidia.targets
