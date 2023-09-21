Repository for the High Performance Computing project

Compilation:
Compile with make and the rule corresponding to whichever experiment you'd like to use.
e.g. if you want to compile using the sequential experiment, use 'make clean sequential', 
and for the parallel_for experiment use 'make clean parallel_for'.

Available experiments:
sequential
parallel_for
parallel_for_scheduling
parallel_step_swim
parallel_tasks

Execute with:
./schooling

Beware that OpenMP will try to use all available threads to execute.
