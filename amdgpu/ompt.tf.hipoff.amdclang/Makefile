SRCS	= ../../src/ompthreads.cc ../../src/hipgpu.cu
TARGET	= ompt.tf.hip.amdclang.amd

default all: $(TARGET)

CXX = amdclang++
OMPFLAGS = -g -O2 -fopenmp

HIP=$(HIP_PATH)
HIPCXX = $(HIP)/bin/hipcc
HIPCXXFLAGS = -g -opt-info -O2 -std=c++11 -I${HIP}/../include/hip/

LDFLAGS = -fopenmp -lm -L${HIP}/lib64/


ompthreads.o: ../../src/ompthreads.cc
	$(CXX) $(OMPFLAGS) -c -o ompthreads.o  ../../src/ompthreads.cc

hipgpu.o: ../../src/hipgpu.cu
	$(HIPCXX) $(HIPCXXFLAGS) -c -o hipgpu.o ../../src/hipgpu.cu

$(TARGET): ompthreads.o hipgpu.o
	$(HIPCXX) -DGPU_SMALL -fopenmp ompthreads.o hipgpu.o -o $(TARGET) ${LDFLAGS}
	@echo ""
	@echo ""

run: run1 run2 run3 run8 run16 run32 run48 run64 run128 run256

hpct: hpct1 hpct2 hpct3 hpct8 hpct16 hpct32 hpct48 hpct64 hpct128 hpct256

include ../../maketargets/generic.targets
include ../../maketargets/amd.targets
