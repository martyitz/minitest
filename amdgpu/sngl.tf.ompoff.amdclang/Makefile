SRCS	= ../../src/single.cc ../../src/ompgpu.cc
TARGET	= sngl.tf.ompoff.amdclang.amd

default all: $(TARGET)

CXX = amdclang++
OMPFLAGS = -g -O2 -fopenmp -lm -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa $(AMD_ARCH)

$(TARGET): ${SRCS}
	$(CXX) -DGPU_SMALL -DIGNORE_BAD_INITIAL_DEVICE $(OMPFLAGS) -o $(TARGET) ${SRCS}
	@echo ""
	@echo ""

run: run1

hpct: hpct1

include ../../maketargets/generic.targets
include ../../maketargets/amd.targets
