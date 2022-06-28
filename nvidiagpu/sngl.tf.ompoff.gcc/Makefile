SRCS	= ../../src/single.cc ../../src/ompgpu.cc
TARGET	= sngl.tf.ompoff.gcc.nv

default all: $(TARGET)

CXX = g++
OMPFLAGS = -g -O2 -fopenmp -lm -foffload="-O2 -lm -misa=sm_35"

$(TARGET): ${SRCS}
	$(CXX) $(OMPFLAGS) -o $(TARGET) ${SRCS}
	@echo ""
	@echo ""

run: run1

hpct: hpct1 hpctpc1

include ../../maketargets/generic.targets
include ../../maketargets/nvidia.targets
