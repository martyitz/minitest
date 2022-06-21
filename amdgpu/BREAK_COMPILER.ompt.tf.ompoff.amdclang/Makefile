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

run: run1 run2 run3

run1: $(TARGET)
	export OMP_NUM_THREADS=1; runrun $(TARGET) run1

run2: $(TARGET)
	export OMP_NUM_THREADS=2; runrun $(TARGET) run2

run3: $(TARGET)
	export OMP_NUM_THREADS=3; runrun $(TARGET) run3

hpct: hpct1 hpct2 hpct3

hpct1: $(TARGET)
	export OMP_NUM_THREADS=1; runhpct $(TARGET) "-e CPUTIME -e gpu=amd -t" hpct1.cg

hpct2: $(TARGET)
	export OMP_NUM_THREADS=2; runhpct $(TARGET) "-e CPUTIME -e gpu=amd -t" hpct2.cg

hpct3: $(TARGET)
	export OMP_NUM_THREADS=3; runhpct $(TARGET) "-e CPUTIME -e gpu=amd -t" hpct3.cg

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
	@echo ""

