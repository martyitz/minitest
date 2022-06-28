SRCS	= ../../src/psxthreads.cc ../../src/hipgpu.cu
TARGET	= psx.tf.hip.amdclang.amd

default all: $(TARGET)

CXX = amdclang++
CXXFLAGS = -g -O2

HIP=$(HIP_PATH)
HIPCXX = $(HIP)/bin/hipcc
HIPCXXFLAGS = -g -opt-info -O2 -std=c++11 -I${HIP}/../include/hip/

LDFLAGS = -lm -lpthread -L${HIP}/lib64/


psxthreads.o: ../../src/psxthreads.cc
	$(CXX) $(CXXFLAGS) -c -o psxthreads.o  ../../src/psxthreads.cc

hipgpu.o: ../../src/hipgpu.cu
	$(HIPCXX) $(HIPCXXFLAGS) -c -o hipgpu.o ../../src/hipgpu.cu

$(TARGET): psxthreads.o hipgpu.o
	$(HIPCXX)  -DGPU_SMALL psxthreads.o hipgpu.o -o $(TARGET) ${LDFLAGS} ${MARCH}
	@echo ""
	@echo ""

run: run1 run2 run3 run8 run16 run32 run48 run64 run128 run256

hpct: hpct1 hpct2 hpct3 hpct8 hpct16 hpct32 hpct48 hpct64 hpct128 hpct256

include ../../maketargets/generic.targets
include ../../maketargets/amd.targets
