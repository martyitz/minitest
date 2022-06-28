# minitest
Minitest of various simple CPU/GPU codes

The Script
----------
The "minitest" script goes through a list of directories, cd's to each, and
runs one of several make commands, based on the argument with which it is invoked.
It should only be run in the top-level directory of the repository.

The supported commands are:
	"default", which builds the test codes;
	"hpct", which collects one or more hpctoolkit experiments on the test code;
	"run", which executes the test code one or more times;
	"clean", which removes all log files and measurement and
		database directories, but leaves the executable;
	"clobber", which does and clean, and also removes the executable and .o's;
	"ll", which executes an "ls -lf" command (not executing make).

Each invocation of "./minitest" generates a "./log.minitest" file with its results;
the results are also written to stdout.

The "minitest" script sources a file named "./miniconfig", which gives
the list of test directories (specified as the variable"$RUNDIRS"),
and the location  of the installation (specified by the variable "$TOPDIR").

An example "./miniconfig" file is "./example.miniconfig".
It should be copied to "./miniconfig", which should then be edited to set
TOPDIR and RUNDIRS as desired.

The "hpct" and "run" targets in a directory Makefile have a list of subtargets.

Each "hpct" subtarget collects a single HPCToolkit experiment, executed
by the script "./bin/runhpct".  It runs the target under "hpcrun"
to collect a measurement directory, then runs "hpcstruct" on that directory
to analyze the binaries executed for that run, and then runs "hpcprof"
on the measurements to generate a database directory.  A log file is generated
with the output of the commands.

The "hpct" subtargets are for running with varying numbers of threads,
for GPU profiling with or without GPU-PC sampling, and for any desired CPU data 
and trace data collection.

Each "run" subtarget executes the target once using the script "./bin/runrun".
It also generates a log file with the output.


The Test Codes
--------------
Each test code is a combination of:

	one of three front ends (OMPthreads, Pthreads, and single-thread);
	one of two computations (a weird transcendental-function one, and a vector add); and
	one of four backends (no offload, omp offload, cuda offload, and hip offload).

The sources for each of the components is in /src 


The Test Directories
--------------------
The tests themselves are in three top-level directories -- amdgpu, nvidiagpu, and nogpu.
Under each of them is a set of subdirectories named by `<frontend>.<compute>.<offload>.<compiler>`
(The `<compute>`'s are all transcendental functions for now). Those directories contain nothing other than a Makefile.
Each Makefile generates one executable, named similarly to the directory, with the type of GPU appended.

The Makefiles also have targets for "clean" which removes all log files and measurement and
database directories, but leaves the executable; and for "clobber" which does a "clean",
and also removes the executable and any .o files, leaving only the Makefile in the directory.
