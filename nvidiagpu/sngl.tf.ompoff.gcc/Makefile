SRCS	= ../../src/single.cc ../../src/ompgpu.cc
TARGET	= sngl.tf.ompoff.gcc.nv

default all: $(TARGET)

CXX = g++
OMPFLAGS = -g -O2 -fopenmp -lm -foffload="-O2 -lm -misa=sm_35"

$(TARGET): ${SRCS}
	$(CXX) $(OMPFLAGS) -o $(TARGET) ${SRCS}

run: $(TARGET)
	@echo "Running \"$(TARGET)\""
	@echo ""
	/bin/time -p ./$(TARGET)
	@echo ""
	@echo ""

hpct: hpct1 hpct2

hpct1: $(TARGET)
	export OMP_NUMTHREADS=1; runhpct $(TARGET) "-e CPUTIME -e gpu=nvidia -t" hpct1.c

hpct2: $(TARGET)
	export OMP_NUMTHREADS=2; runhpct $(TARGET) "-e CPUTIME -e gpu=nvidia,pc -t" hpct2.c

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
