SRCS	= ../../src/single.cc ../../src/nooffload.cc 
TARGET	= sngl.tf.nooffload.gcc.ng
MPITARGET = sngl.tf.nooffload.gcc.ng.mpi

default: $(TARGET)
all: $(TARGET) $(MPITARGET)

CXX = g++
OMPFLAGS = -g -O2 -fopenmp -lm

$(TARGET): ${SRCS} ../../src/maincommon.cc
	$(CXX) $(OMPFLAGS) -o $(TARGET) ${SRCS}
	@echo ""
	@echo ""

$(MPITARGET): ${SRCS} ../../src/maincommon.cc
	echo "MPI_HOME = $(MPI_HOME)"
	$(CXX) -D USE_MPI $(OMPFLAGS) -I$(MPI_HOME)/include -o $(MPITARGET) ${SRCS} -L$(MPI_HOME)/lib -lmpi
	@echo ""
	@echo ""

run: runa

runa: $(TARGET)
	runrun $(TARGET) run1

hpct: hpcta hpctb

hpcta: $(TARGET)
	runhpct $(TARGET) "-e CPUTIME -t" hpct1.c

hpctb: $(TARGET)
	runhpct $(TARGET) "-e cycles -t" hpct2.c

hpcpost: $(TARGET)
	export RUN_POST_REPT=1; runhpct "$(TARGET) -N 100000 -I 1" "-e CPUTIME -t" hpcpost

hpctmpi: $(MPITARGET)
	mpirun -N 2 hpcrun -e CPUTIME -t $(MPITARGET)
	hpcstruct hpctoolkit*$(MPITARGET)*measurements
	hpcprof hpctoolkit*$(MPITARGET)*measurements

include ../../maketargets/generic.targets
include ../../maketargets/mpi.targets
