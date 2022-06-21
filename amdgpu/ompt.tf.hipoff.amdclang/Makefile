SRCS	= ../../src/ompthreads.cc ../../src/hipgpu.cu
TARGET	= ompt.tf.hip.amdclang.amd

default all: $(TARGET)

CXX = amdclang++
OMPFLAGS = -g -O2 -fopenmp

HIP=$(HIP_PATH)
HIPCXX = $(HIP)/bin/hipcc
HIPCXXFLAGS = -g -opt-info -O2 -std=c++11 -I${HIP}/../include/hip/

LDFLAGS = -fopenmp -lm -L${HIP}/lib64/


ompthreads.o: ../../src/ompthreads.cc
	$(CXX) $(OMPFLAGS) -c -o ompthreads.o  ../../src/ompthreads.cc

hipgpu.o: ../../src/hipgpu.cu
	$(HIPCXX) $(HIPCXXFLAGS) -c -o hipgpu.o ../../src/hipgpu.cu

$(TARGET): ompthreads.o hipgpu.o
	$(HIPCXX) -DGPU_SMALL -fopenmp ompthreads.o hipgpu.o -o $(TARGET) ${LDFLAGS}

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

