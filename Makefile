parallel_for_mpi: first_deliverable.o parallel_for_mpi.o utilities.o
	mpicc -fopenmp -g -lm -o schooling first_deliverable.o utilities_mpi.o
	rm -f *.o

sequential: main.o sequential.o utilities.o
	gcc -fopenmp -lm -g -o schooling main.o sequential.o utilities.o
	rm -f *.o

parallel_for: main.o parallel_for.o utilities.o
	gcc -fopenmp -lm -g -o schooling main.o parallel_for.o utilities.o
	rm -f *.o

parallel_for_scheduling_static: main.o parallel_for_scheduling_static.o utilities.o
	gcc -fopenmp -lm -g -o schooling main.o parallel_for_scheduling_static.o utilities.o
	rm -f *.o

parallel_for_scheduling_dynamic: main.o parallel_for_scheduling_dynamic.o utilities.o
	gcc -fopenmp -lm -g -o schooling main.o parallel_for_scheduling_dynamic.o utilities.o
	rm -f *.o

parallel_for_scheduling_guided: main.o parallel_for_scheduling_guided.o utilities.o
	gcc -fopenmp -lm -g -o schooling main.o parallel_for_scheduling_guided.o utilities.o
	rm -f *.o

parallel_for_scheduling_runtime: main.o parallel_for_scheduling_runtime.o utilities.o
	gcc -fopenmp -lm -g -o schooling main.o parallel_for_scheduling_runtime.o utilities.o
	rm -f *.o

parallel_step_swim: main.o parallel_step_swim.o utilities.o
	gcc -fopenmp -lm -g -o schooling main.o parallel_step_swim.o utilities.o
	rm -f *.o

parallel_tasks: main.o parallel_tasks.o utilities.o
	gcc -fopenmp -lm -g -o schooling main.o parallel_tasks.o utilities.o
	rm -f *.o

swim_only: main.o swim_only.o utilities.o
	gcc -fopenmp -lm -g -o schooling main.o swim_only.o utilities.o
	rm -f *.o

eat_only: main.o eat_only.o utilities.o
	gcc -fopenmp -lm -g -o schooling main.o eat_only.o utilities.o
	rm -f *.o

barycentre_only: main.o barycentre_only.o utilities.o
	gcc -fopenmp -lm -g -o schooling main.o barycentre_only.o utilities.o
	rm -f *.o

good_cache: main.o good_cache.o utilities.o
	gcc -fopenmp -lm -g -o schooling main.o good_cache.o utilities.o
	rm -f *.o

bad_cache: main.o bad_cache.o utilities.o
	gcc -fopenmp -lm -g -o schooling main.o bad_cache.o utilities.o
	rm -f *.o

first_deliverable: first_deliverable.o utilities_mpi.o
	mpicc -fopenmp -g -lm -o schooling first_deliverable.o utilities_mpi.o
	rm -f *.o

main.o: src/main.c src/fish.h src/utilities.h
	gcc -fopenmp -c src/main.c

parallel_for_mpi.o: src/parallel_for_mpi src/fish_mpi.h
	gcc -c src/parallel_for_mpi.c

sequential.o: src/sequential.c src/fish.h
	gcc -c src/sequential.c

parallel_for.o: src/parallel_for.c src/fish.h
	gcc -fopenmp -c src/parallel_for.c

parallel_tasks.o: src/parallel_tasks.c src/fish.h
	gcc -fopenmp -c src/parallel_tasks.c

parallel_step_swim.o: src/parallel_step_swim.c src/fish.h
	gcc -fopenmp -c src/parallel_step_swim.c

parallel_for_scheduling_static.o: src/parallel_for_scheduling_static.c src/fish.h
	gcc -fopenmp -c src/parallel_for_scheduling_static.c

parallel_for_scheduling_dynamic.o: src/parallel_for_scheduling_dynamic.c src/fish.h
	gcc -fopenmp -c src/parallel_for_scheduling_dynamic.c

parallel_for_scheduling_guided.o: src/parallel_for_scheduling_guided.c src/fish.h
	gcc -fopenmp -c src/parallel_for_scheduling_guided.c

parallel_for_scheduling_runtime.o: src/parallel_for_scheduling_runtime.c src/fish.h
	gcc -fopenmp -c src/parallel_for_scheduling_runtime.c

swim_only.o: src/swim_only.c src/fish.h
	gcc -fopenmp -c src/swim_only.c

eat_only.o: src/eat_only.c src/fish.h
	gcc -fopenmp -c src/eat_only.c

barycentre_only.o: src/barycentre_only.c src/fish.h
	gcc -fopenmp -c src/barycentre_only.c

good_cache.o: src/good_cache.c src/fish.h
	gcc -fopenmp -c src/good_cache.c

bad_cache.o: src/bad_cache.c src/fish.h
	gcc -fopenmp -c src/bad_cache.c

utilities.o: src/utilities.c src/utilities.h src/fish.h
	gcc -fopenmp -c src/utilities.c

utilities_mpi.o: src/utilities_mpi.c src/utilities_mpi.h src/fish_mpi.h
	gcc -fopenmp -c src/utilities_mpi.c

first_deliverable.o: src/first_deliverable.c src/fish_mpi.h src/utilities_mpi.h
	mpicc -fopenmp -g -c src/first_deliverable.c

clean:
	rm -f *.o
