SRCS	= ../../src/psxthreads.cc ../../src/nooffload.cc
TARGET	= psx.tf.nooffload.llvm.ng

default all: $(TARGET)

CXX = clang++
OMPFLAGS = -g -O2 -fopenmp -lm

$(TARGET): ${SRCS}
	$(CXX) $(OMPFLAGS) -o $(TARGET) ${SRCS}
	@echo ""
	@echo ""

run: runa runb runc

runa: $(TARGET)
	export OMP_NUM_THREADS=1; runrun $(TARGET) run1

runb: $(TARGET)
	export OMP_NUM_THREADS=2; runrun $(TARGET) run2

runc: $(TARGET)
	export OMP_NUM_THREADS=3; runrun $(TARGET) run3

hpct: hpcta hpctb hpctc

hpcta: $(TARGET)
	export OMP_NUM_THREADS=1; runhpct $(TARGET) "-e CPUTIME -t" hpct1.c

hpctb: $(TARGET)
	export OMP_NUM_THREADS=2; runhpct $(TARGET) "-e CPUTIME -t" hpct2.c

hpctc: $(TARGET)
	export OMP_NUM_THREADS=3; runhpct $(TARGET) "-e CPUTIME -t" hpct3.c


include ../../maketargets/generic.targets
