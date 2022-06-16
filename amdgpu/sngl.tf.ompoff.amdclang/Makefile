SRCS	= ../../src/single.cc ../../src/ompgpu.cc
TARGET	= sngl.tf.ompoff.amdclang.amd

default all: $(TARGET)

MARCH = -march=gfx90a
MARCH = -march=gfx906
MARCH = -march=gfx908

CXX = amdclang++
OMPFLAGS = -g -O2 -fopenmp -lm -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa $(MARCH)

$(TARGET): ${SRCS}
	$(CXX) -DGPU_SMALL -DIGNORE_BAD_INITIAL_DEVICE $(OMPFLAGS) -o $(TARGET) ${SRCS}

run: $(TARGET)
	@echo "Running \"$(TARGET)\""
	@echo ""
	/bin/time -p ./$(TARGET)
	@echo ""
	@echo ""

hpct: hpct1

hpct1: $(TARGET)
	export OMP_NUM_THREADS=1; runhpct $(TARGET) "-e CPUTIME -e gpu=amd -t" hpct1.cg

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
