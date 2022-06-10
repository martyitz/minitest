SRCS	= ../../src/psxthreads.cc ../../src/cudagpu.cu
TARGET	= psx.tf.cuda.gcc.nv

default all: $(TARGET)

CUDA = $(CUDA_HOME)
CUDACXX = ${CUDA}/bin/nvcc
CUDACXXFLAGS = -g -O2 -DHAVE_CUDA -std=c++11 -I${CUDA}/include/ $(OPTFLAGS) -Xptxas -v -gencode=arch=compute_60,code=\"sm_60,compute_60\"
CUDACXXFLAGS = -g -lineinfo -opt-info inline -O2 -std=c++11 -I${CUDA}/include/ -Xptxas -v -gencode=arch=compute_60,code=\"sm_60,compute_60\"
CUDACXXFLAGS = -g -lineinfo -O2 -std=c++11 -I${CUDA}/include/

CXX = g++
CXXFLAGS = -g -O2 -lm

LDFLAGS = -lm -lpthread -L${CUDA}/lib64/ -lcuda -lcudart

psxthreads.o: ../../src/psxthreads.cc
	$(CXX) $(CXXFLAGS) -c -o psxthreads.o  ../../src/psxthreads.cc

cudagpu.o: ../../src/cudagpu.cu
	$(CUDACXX) $(CUDACXXFLAGS) -c -o cudagpu.o ../../src/cudagpu.cu

$(TARGET): psxthreads.o cudagpu.o
	$(CXX) psxthreads.o cudagpu.o -o $(TARGET) ${LDFLAGS}

run: $(TARGET)
	@echo "Running \"$(TARGET)\""
	@echo ""
	/bin/time -p ./$(TARGET)
	@echo ""
	@echo ""

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
