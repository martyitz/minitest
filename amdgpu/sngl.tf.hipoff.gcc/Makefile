SRCS	= ../../src/single.cc ../../src/hipgpu.cu
TARGET	= sngl.tf.hip.gcc.amd

default all: $(TARGET)

CXX = g++
OMPFLAGS = -g -O2 -fopenmp -lm

HIP=$(HIP_PATH)
HIPCXX = $(HIP)/bin/hipcc
HIPCXXFLAGS = -g -opt-info -O2 -std=c++11 -I${HIP}/../include/hip/

LDFLAGS = -fopenmp -lm -L${HIP}/lib64/

single.o: ../../src/single.cc
	$(CXX) $(OMPFLAGS) -c -o single.o  ../../src/single.cc

hipgpu.o: ../../src/hipgpu.cu
	$(HIPCXX) $(HIPCXXFLAGS) -c -o hipgpu.o ../../src/hipgpu.cu

$(TARGET): single.o hipgpu.o
	$(HIPCXX) -fopenmp single.o hipgpu.o -o $(TARGET) ${LDFLAGS}

run: $(TARGET)
	@echo "Running \"$(TARGET)\""
	@echo ""
	/bin/time -p ./$(TARGET)
	@echo ""
	@echo ""

hpct: hpct1

hpct1: $(TARGET)
	runhpct $(TARGET) "-e CPUTIME -e gpu=amd -t" hpct1.cg

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
