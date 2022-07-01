SRCS	= ../../src/single.cc ../../src/nooffload.cc
TARGET	= sngl.tf.nooffload.gcc.ng

default all: $(TARGET)

CXX = g++
OMPFLAGS = -g -O2 -fopenmp -lm

$(TARGET): ${SRCS}
	$(CXX) $(OMPFLAGS) -o $(TARGET) ${SRCS}
	@echo ""
	@echo ""

run: runa

runa: $(TARGET)
	runrun $(TARGET) run1

hpct: hpcta hpctb

hpcta: $(TARGET)
	runhpct $(TARGET) "-e CPUTIME -t" hpct1.c

hpctb: $(TARGET)
	runhpct $(TARGET) "-e cycles -t" hpct2.c

include ../../maketargets/generic.targets
