SRCS	= ../../src/psxthreads.cc ../../src/ompgpu.cc
TARGET	= psx.tf.ompoff.nvcc.nv

default all: $(TARGET)

CXX = nvc++
OMPFLAGS = -g -O2 -lm -mp -mp=gpu

$(TARGET): ${SRCS}
	$(CXX) $(OMPFLAGS) -o $(TARGET) ${SRCS}
	@echo ""
	@echo ""

run: run1 run2 run3 run8 run16 run32 run48 run64 run128 run256

hpct: hpctnopc hpctpc

hpctnopc: hpct1 hpct2 hpct3 hpct8 hpct16 hpct32 hpct48 hpct64 hpct128 hpct256
hpctpc: hpctpc1 hpctpc2 hpctpc3 hpctpc8 hpctpc16 hpctpc32 hpctpc48 hpctpc64 hpctpc128 hpctpc256

include ../../maketargets/generic.targets
include ../../maketargets/nvidia.targets
