SRCS	= ../../src/ompthreads.cc ../../src/ompgpu.cc
TARGET	= ompt.tf.ompoff.gcc.nv

default all: $(TARGET)

CXX = g++
OMPFLAGS = -g -O2 -fopenmp -lm -foffload="-O2 -lm -misa=sm_35"

$(TARGET): ${SRCS}
	$(CXX) $(OMPFLAGS) -o $(TARGET) ${SRCS}
	@echo ""
	@echo ""

run: run1 run2 run3 run8 run16 run32 run48 run64 run128 run256

hpct: hpct1 hpct2 hpct3 hpct3 hpct8 hpct16 hpct32 hpct48 hpct64 hpct128 hpct256 hpctpc1 hpctpc2

include ../../maketargets/generic.targets
include ../../maketargets/nvidia.targets
