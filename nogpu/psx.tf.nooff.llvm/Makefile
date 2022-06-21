SRCS	= ../../src/psxthreads.cc ../../src/nooffload.cc
TARGET	= psx.tf.nooffload.llvm.ng

default all: $(TARGET)

CXX = clang++
OMPFLAGS = -g -O2 -fopenmp -lm

$(TARGET): ${SRCS}
	$(CXX) $(OMPFLAGS) -o $(TARGET) ${SRCS}

run: run1 run2 run3

run1: $(TARGET)
	export OMP_NUM_THREADS=1; runrun $(TARGET) run1

run2: $(TARGET)
	export OMP_NUM_THREADS=2; runrun $(TARGET) run2

run3: $(TARGET)
	export OMP_NUM_THREADS=3; runrun $(TARGET) run3

hpct: hpct1 hpct2 hpct3

hpct1: $(TARGET)
	export OMP_NUM_THREADS=1; runhpct $(TARGET) "-e CPUTIME -t" hpct1.c

hpct2: $(TARGET)
	export OMP_NUM_THREADS=2; runhpct $(TARGET) "-e CPUTIME -t" hpct2.c

hpct3: $(TARGET)
	export OMP_NUM_THREADS=3; runhpct $(TARGET) "-e CPUTIME -t" hpct3.c

collect: $(TARGET)
	collect -p hi $(TARGET)
	er_print -func test.1.er

clean:
	-/bin/rm -rf meas.*
	-/bin/rm -rf dbase.*
	-/bin/rm -f *core*
	-/bin/rm -f *log.*
	-/bin/rm -rf test.*.er
	@echo ""
	@echo ""

clobber: clean
	-/bin/rm -rf *.o $(TARGET)
	@echo ""
