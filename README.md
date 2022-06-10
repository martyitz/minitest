# minitest
Minitest of various simple CPU/GPU codes

The minitest script and miniconf is in the top-level directory.  The minitest script
will run one of several make commands, and an "ls -lf" in each of a set of directories
as described in miniconf.

The file miniconf has configuration information, and a list of test directories.  An example miniconf
file is /bin/example.miniconfig and /bin also contains "runhpct", a script used to run a single test.

This testsuite is a mix-and-match set of components for

	three front ends (OMPthreads, Pthreads, and single-thread);
	two computations (a weird transcendental-function one, and a vector add); and
	four backends (no offload, omp offload, cuda offload, and hip offload).

The sources for each of the components is in /src 

The tests themselves are in three top-level directories -- amdgpu, nvidiagpu, and nogpu.
Under each of them is a set of subdirectories named by `<frontend>.<compute>.<offload>.<compiler>`
(The `<compute>`'s are all transcendental functions for now). Those directories contain nothing other than a Makefile.
Each Makefile generates one executable, named similarly to the directory, with the type of GPU appended.

Each Makefile also has a target `hpct`, which lists subtargets each of which generates one experiment.
The subtargets each invoke runhpct, which generates a measurement directory, and database,
and a log file. Subtargets are for varying number of threads, GPU profiling with or without PC sampling,
-e cycles, or any other data collection that seems worth testing. Some of them also have targets for
measuring with gprofng.
  
The Makefiles also have targets for "clean" which removes all log files and measurement and
database directories, but leaves the executable; and for "clobber" which does a "clean",
and also removes the executable and any .o files, leaving only the Makefile in the directory.
