SRCS	= ../../src/single.cc ../../src/cudagpu.cu
TARGET	= sngl.tf.cuda.gcc.nv

default all: $(TARGET)

CUDA = $(CUDA_HOME)
CUDACXX = ${CUDA}/bin/nvcc
CUDACXXFLAGS = -g -O2 -DHAVE_CUDA -std=c++11 -I${CUDA}/include/ $(OPTFLAGS) -Xptxas -v -gencode=arch=compute_60,code=\"sm_60,compute_60\"
CUDACXXFLAGS = -g -lineinfo -opt-info inline -O2 -std=c++11 -I${CUDA}/include/ -Xptxas -v -gencode=arch=compute_60,code=\"sm_60,compute_60\"
CUDACXXFLAGS = -g -lineinfo -O2 -std=c++11 -I${CUDA}/include/

CXX = g++
OMPFLAGS = -g -O2 -fopenmp -lm

LDFLAGS = -lm -L${CUDA}/lib64/ -lcuda -lcudart

single.o: ../../src/single.cc
	$(CXX) $(OMPFLAGS) -c -o single.o  ../../src/single.cc

cudagpu.o: ../../src/cudagpu.cu
	$(CUDACXX) $(CUDACXXFLAGS) -c -o cudagpu.o ../../src/cudagpu.cu

$(TARGET): single.o cudagpu.o
	$(CXX) -fopenmp single.o cudagpu.o -o $(TARGET) ${LDFLAGS}

run: $(TARGET)
	@echo "Running \"$(TARGET)\""
	@echo ""
	/bin/time -p ./$(TARGET)
	@echo ""
	@echo ""

hpct: hpct1 hpct2

hpct1: $(TARGET)
	runhpct $(TARGET) "-e CPUTIME -e gpu=nvidia -t" hpct1.cg

hpct2: $(TARGET)
	runhpct $(TARGET) "-e CPUTIME -e gpu=nvidia,pc -t" hpct2.cgp

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

