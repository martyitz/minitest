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

hpct: hpcta hpctb hpctpost

hpcta: $(TARGET)
	runhpct $(TARGET) "-e CPUTIME -t" hpcta.c

hpctb: $(TARGET)
	runhpct $(TARGET) "-e cycles -t" hpctb.c

hpctpost: $(TARGET)
	export RUN_POST_REPT=1; runhpct "$(TARGET) -N 100000 -I 1" "-e CPUTIME -t" hpcpost

hpctmpi: $(MPITARGET)
	export RUN_POST_REPT=1; runmpihpc "-N 2" "$(MPITARGET)  -N 100000 -I 1" "-e CPUTIME -t" hpcmpi

include ../../maketargets/generic.targets
include ../../maketargets/mpi.targets
