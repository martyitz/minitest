SRCS	= ../../src/psxthreads.cc ../../src/ompgpu.cc
TARGET	= psx.tf.ompoff.amdclang.amd

default all: $(TARGET)

MARCH = -march=gfx906
MARCH = -march=gfx90a
MARCH = -march=gfx908

CXX = amdclang++
OMPFLAGS = -g -O2 -fopenmp -lm -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa $(MARCH)

$(TARGET): ${SRCS}
	$(CXX) -DGPU_SMALL -DIGNORE_BAD_INITIAL_DEVICE $(OMPFLAGS) -o $(TARGET) ${SRCS}
	@echo ""
	@echo ""

run: run1 run2 run3 run8 run16 run32 run48 run64 run128 run256

hpct: hpct1 hpct2 hpct3 hpct8 hpct16 hpct32 hpct48 hpct64 hpct128 hpct256

include ../../maketargets/generic.targets
include ../../maketargets/amd.targets
