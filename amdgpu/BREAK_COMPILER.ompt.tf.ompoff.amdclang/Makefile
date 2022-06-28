SRCS	= ../../src/ompthreads.cc ../../src/ompgpu.cc
TARGET	= ompt.tf.ompoff.amdclang.amd

default all: $(TARGET)

MARCH = -march=gfx90a
MARCH = -march=gfx906

CXX = amdclang++
OMPFLAGS = -g -O2 -fopenmp -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa $(MARCH)

LDFLAGS = -fopenmp -lm -L${HIP}/lib64/

$(TARGET): $(SRCS)
	$(CXX) -DGPU_SMALL $(OMPFLAGS) -o $(TARGET) ${LDFLAGS}
	@echo ""
	@echo ""

run: run1 run2 run3 run8 run16 run32 run48 run64 run128 run256

hpct: hpct1 hpct2 hpct3 hpct8 hpct16 hpct32 hpct48 hpct64 hpct128 hpct256

include ../../maketargets/generic.targets
include ../../maketargets/amd.targets
