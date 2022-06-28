SRCS	= ../../src/single.cc ../../src/hipgpu.cu
TARGET	= sngl.tf.hip.gcc.amd

default all: $(TARGET)

CXX = g++
OMPFLAGS = -g -O2 -fopenmp -lm

HIP=$(HIP_PATH)
HIPCXX = $(HIP)/bin/hipcc
HIPCXXFLAGS = -g -opt-info -O2 -std=c++11 -I${HIP}/../include/hip/

LDFLAGS = -fopenmp -lm -L${HIP}/lib64/

single.o: ../../src/single.cc
	$(CXX) $(OMPFLAGS) -c -o single.o  ../../src/single.cc

hipgpu.o: ../../src/hipgpu.cu
	$(HIPCXX) $(HIPCXXFLAGS) -c -o hipgpu.o ../../src/hipgpu.cu

$(TARGET): single.o hipgpu.o
	$(HIPCXX) -fopenmp single.o hipgpu.o -o $(TARGET) ${LDFLAGS}
	@echo ""
	@echo ""

run: run1

hpct: hpct1

include ../../maketargets/generic.targets
include ../../maketargets/amd.targets
