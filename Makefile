mpi_omp: collective_main.o fish_actions.o utilities.o
	mpicc -fopenmp -DOPENMP -lm -o schooling collective_main.o fish_actions.o utilities.o

only_mpi: collective_main_no_omp.o fish_actions_no_omp.o utilities.o
	mpicc -lm -o schooling collective_main_no_omp.o fish_actions_no_omp.o utilities.o

point_to_point: point_main.o fish_actions.o utilities.o
	mpicc -fopenmp -DOPENMP -lm -o schooling point_main.o fish_actions.o utilities.o

first_deliverable: first_deliverable.o utilities.o
	mpicc -lm -o schooling first_deliverable.o utilities.o

collective_main.o: src/collective_main.c src/utilities.c src/fish_actions.c src/fish.h src/utilities.h
	mpicc -DOPENMP -c src/collective_main.c

collective_main_no_omp.o: src/collective_main.c src/utilities.c src/fish_actions.c src/fish.h src/utilities.h
	mpicc -c -o collective_main_no_omp.o src/collective_main.c

point_main.o: src/point_main.c src/utilities.c src/fish_actions.c src/fish.h src/utilities.h
	mpicc -DOPENMP -c src/point_main.c

fish_actions.o: src/fish_actions.c src/utilities.c src/fish.h src/utilities.h
	gcc -fopenmp -DOPENMP -c src/fish_actions.c

fish_actions_no_omp.o: src/fish_actions.c src/utilities.c src/fish.h src/utilities.h
	gcc -c -o fish_actions_no_omp.o src/fish_actions.c

utilities.o: src/utilities.c src/utilities.h src/fish.h
	gcc -lm -c src/utilities.c

first_deliverable.o: src/first_deliverable.c src/utilities.c src/fish.h src/utilities.h
	mpicc -c src/first_deliverable.c

clean:
	rm -f *.o
