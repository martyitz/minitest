SRCS	= ../../src/psxthreads.cc ../../src/ompgpu.cc
TARGET	= psx.tf.ompoff.amdclang.amd

default all: $(TARGET)

include ../../maketargets/generic.targets
include ../../maketargets/amd.targets

CXX = amdclang++
OMPFLAGS = -g -O2 -fopenmp -lm -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa $(AMD_ARCH)

$(TARGET): ${SRCS}
	$(CXX) -DGPU_SMALL $(OMPFLAGS) -o $(TARGET) ${SRCS}
	@echo ""
	@echo ""

run: run1 run2 run3 run8 run16 run32 run48 run64 run128 run256

hpct: hpct1 hpct2 hpct3 hpct8 hpct16 hpct32 hpct48 hpct64 hpct128 hpct256
