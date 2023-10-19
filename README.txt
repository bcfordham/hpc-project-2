Repository for the second High Performance Computing project

Developed by: 
Blake Fordham (22708346)
Nicodemus Ong (22607943)


Compilation:
Compile with make and the rule corresponding to whichever implementation you'd 
like to use.
e.g. if you want to compile using the implementation with MPI and OpenMP, run:

make mpi_omp

and for the implementation with only MPI run:

make only_mpi


Available experiments:
mpi_omp
only_mpi
point_to_point


Execution:
Running on a local machine doesn't seem to work properly.
Just run on Setonix.
The executable is called schooling.
Specify how many threads you want in run.sh


Results:
Results of all our experiments are in the results/ directory along with the 
shell files used to run those jobs on Setonix.
Some of them are results from the previous project since they are still 
relevant to this project.
