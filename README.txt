Repository for the second High Performance Computing project

Developed by: 
Blake Fordham (22708346)
Nicodemus Ong (22607943)


Compilation:
Compile with make and the rule corresponding to whichever implementation you'd 
like to use.
e.g. if you want to compile using the sequential implementation, run:

make clean sequential

and for the parallel_for implementation run:

make clean parallel_for


Available experiments:
sequential
parallel_for


Execution:
If you're just running on your local machine then run:

mpirun -np 4 ./schooling


Results:
Results of all our experiments are in the results/ directory along with the 
shell files used to run those jobs on Setonix.
