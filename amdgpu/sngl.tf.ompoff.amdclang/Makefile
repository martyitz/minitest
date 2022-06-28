SRCS	= ../../src/single.cc ../../src/ompgpu.cc
TARGET	= sngl.tf.ompoff.amdclang.amd

default all: $(TARGET)

MARCH = -march=gfx90a
MARCH = -march=gfx906
MARCH = -march=gfx908

CXX = amdclang++
OMPFLAGS = -g -O2 -fopenmp -lm -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa $(MARCH)

$(TARGET): ${SRCS}
	$(CXX) -DGPU_SMALL -DIGNORE_BAD_INITIAL_DEVICE $(OMPFLAGS) -o $(TARGET) ${SRCS}
	@echo ""
	@echo ""

run: run1

hpct: hpct1

include ../../maketargets/generic.targets
include ../../maketargets/amd.targets
