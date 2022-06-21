SRCS	= ../../src/ompthreads.cc ../../src/cudagpu.cu
TARGET	= ompt.tf.cuda.gcc.nv

default all: $(TARGET)

CUDA = $(CUDA_HOME)
CUDACXX = ${CUDA}/bin/nvcc
CUDACXXFLAGS = -g -O2 -DHAVE_CUDA -std=c++11 -I${CUDA}/include/ $(OPTFLAGS) -Xptxas -v -gencode=arch=compute_60,code=\"sm_60,compute_60\"
CUDACXXFLAGS = -g -lineinfo -opt-info inline -O2 -std=c++11 -I${CUDA}/include/ -Xptxas -v -gencode=arch=compute_60,code=\"sm_60,compute_60\"
CUDACXXFLAGS = -g -lineinfo -O2 -std=c++11 -I${CUDA}/include/

CXX = g++
OMPFLAGS = -g -O2 -fopenmp -lm

LDFLAGS = -lm -L${CUDA}/lib64/ -lcuda -lcudart

ompthreads.o: ../../src/ompthreads.cc
	$(CXX) $(OMPFLAGS) -c -o ompthreads.o  ../../src/ompthreads.cc

cudagpu.o: ../../src/cudagpu.cu
	$(CUDACXX) $(CUDACXXFLAGS) -c -o cudagpu.o ../../src/cudagpu.cu

$(TARGET): ompthreads.o cudagpu.o
	$(CXX) -fopenmp ompthreads.o cudagpu.o -o $(TARGET) ${LDFLAGS}

run: run1 run2 run3

run1: $(TARGET)
	export OMP_NUM_THREADS=1; runrun $(TARGET) run1

run2: $(TARGET)
	export OMP_NUM_THREADS=2; runrun $(TARGET) run2

run3: $(TARGET)
	export OMP_NUM_THREADS=3; runrun $(TARGET) run3

hpct: hpct1 hpct2 hpct3 hpctpc1 hpctpc2

hpct1: $(TARGET)
	export OMP_NUM_THREADS=1; runhpct $(TARGET) "-e CPUTIME -e gpu=nvidia -t" hpct1.cg

hpct2: $(TARGET)
	export OMP_NUM_THREADS=2; runhpct $(TARGET) "-e CPUTIME -e gpu=nvidia -t" hpct2.cg

hpct3: $(TARGET)
	export OMP_NUM_THREADS=3; runhpct $(TARGET) "-e CPUTIME -e gpu=nvidia -t" hpct3.cg

hpctpc1: $(TARGET)
	export OMP_NUM_THREADS=1; runhpct $(TARGET) "-e CPUTIME -e gpu=nvidia,pc -t" hpct1.cgp "--gpucfg yes"

hpctpc2: $(TARGET)
	export OMP_NUM_THREADS=2; runhpct $(TARGET) "-e CPUTIME -e gpu=nvidia,pc -t" hpct2.cgp "--gpucfg yes"

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

