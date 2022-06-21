SRCS	= ../../src/single.cc ../../src/nooffload.cc
TARGET	= sngl.tf.nooffload.gcc.ng

default all: $(TARGET)

CXX = g++
OMPFLAGS = -g -O2 -fopenmp -lm

$(TARGET): ${SRCS}
	$(CXX) $(OMPFLAGS) -o $(TARGET) ${SRCS}

run: run1

run1: $(TARGET)
	runrun $(TARGET) run1

hpct: hpct1 hpct2

hpct1: $(TARGET)
	runhpct $(TARGET) "-e CPUTIME -t" hpct1.c

hpct2: $(TARGET)
	runhpct $(TARGET) "-e cycles -t" hpct2.c

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
