SRCS	= ../../src/psxthreads.cc ../../src/cudagpu.cu
TARGET	= psx.tf.cuda.gcc.nv

default all: $(TARGET)

CUDA = $(CUDA_HOME)
CUDACXX = ${CUDA}/bin/nvcc
CUDACXXFLAGS = -g -lineinfo -O2 -std=c++11 -I${CUDA}/include/

CXX = g++
CXXFLAGS = -g -O2 -lm

LDFLAGS = -lm -lpthread -L${CUDA}/lib64/ -lcuda -lcudart

psxthreads.o: ../../src/psxthreads.cc
	$(CXX) $(CXXFLAGS) -c -o psxthreads.o  ../../src/psxthreads.cc

cudagpu.o: ../../src/cudagpu.cu
	$(CUDACXX) $(CUDACXXFLAGS) -c -o cudagpu.o ../../src/cudagpu.cu

$(TARGET): psxthreads.o cudagpu.o
	$(CXX) psxthreads.o cudagpu.o -o $(TARGET) ${LDFLAGS}
	@echo ""
	@echo ""

run: run1 run2 run3 run8 run16 run32 run48 run64 run128 run256

hpct: hpctnopc hpctpc

hpctnopc: hpct1 hpct2 hpct3 hpct8 hpct16 hpct32 hpct48 hpct64 hpct128 hpct256
hpctpc: hpctpc1 hpctpc2 hpctpc3 hpctpc8 hpctpc16 hpctpc32 hpctpc48 hpctpc64 hpctpc128 hpctpc256

include ../../maketargets/generic.targets
include ../../maketargets/nvidia.targets


