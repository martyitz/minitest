SRCS	= ../../src/single.cc ../../src/hipgpu.cu
TARGET	= sngl.tf.hip.amdclang.amd

default all: $(TARGET)

CXX = amdclang++
CXXFLAGS = -g -O2

HIP=$(HIP_PATH)
HIPCXX = $(HIP)/bin/hipcc
HIPCXXFLAGS = -g -opt-info -O2 -std=c++11 -I${HIP}/../include/hip/

LDFLAGS = -lm -lpthread -L${HIP}/lib64/


single.o: ../../src/single.cc
	$(CXX) $(CXXFLAGS) -c -o single.o  ../../src/single.cc

hipgpu.o: ../../src/hipgpu.cu
	$(HIPCXX) $(HIPCXXFLAGS) -c -o hipgpu.o ../../src/hipgpu.cu

$(TARGET): single.o hipgpu.o
	$(HIPCXX)  -DGPU_SMALL single.o hipgpu.o -o $(TARGET) ${LDFLAGS} ${MARCH}
	@echo ""
	@echo ""

run: run1

hpct: hpct1

include ../../maketargets/generic.targets
include ../../maketargets/amd.targets
