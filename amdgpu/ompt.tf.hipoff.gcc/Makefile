SRCS	= ../../src/ompt.cc ../../src/hipgpu.cu
TARGET	= ompt.tf.hip.gcc.amd

default all: $(TARGET)

CXX = g++
CXXFLAGS = -g -O2 -lm -fopenmp

HIP=$(HIP_PATH)
HIPCXX = $(HIP)/bin/hipcc
HIPCXXFLAGS = -g -opt-info -O2 -std=c++11 -I${HIP}/../include/hip/

LDFLAGS = -fopenmp -lm -L${HIP}/lib64/


ompthreads.o: ../../src/ompthreads.cc
	$(CXX) $(CXXFLAGS) -c -o ompthreads.o  ../../src/ompthreads.cc

hipgpu.o: ../../src/hipgpu.cu
	$(HIPCXX) $(HIPCXXFLAGS) -c -o hipgpu.o ../../src/hipgpu.cu

$(TARGET): ompthreads.o hipgpu.o
	$(HIPCXX)  -DGPU_SMALL ompthreads.o hipgpu.o -o $(TARGET) ${LDFLAGS} ${MARCH}
	@echo ""
	@echo ""

run: run1 run2 run3 run8 run16 run32 run48 run64 run128 run256

hpct: hpct1 hpct2 hpct3 hpct8 hpct16 hpct32 hpct48 hpct64 hpct128 hpct256

include ../../maketargets/generic.targets
include ../../maketargets/amd.targets
