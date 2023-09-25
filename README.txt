Repository for the High Performance Computing project

Compilation:
Compile with make and the rule corresponding to whichever implementation you'd 
like to use.
e.g. if you want to compile using the sequential implementation, 
use 'make clean sequential', and for the parallel_for implementation 
use 'make clean parallel_for'.

Available experiments:
sequential
parallel_for
parallel_for_scheduling_static
parallel_for_scheduling_dynamic
parallel_for_scheduling_guided
parallel_for_scheduling_runtime
parallel_step_swim
parallel_tasks
barycentre_only
eat_only
swim_only
good_cache
bad_cache


Execute with:
./schooling

Beware that OpenMP will try to use all available threads to execute.

Results:
Results of all our experiments are in the results/ directory along with the 
shell files used to run those jobs on Setonix.
