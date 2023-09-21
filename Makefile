sequential: main.o sequential.o utilities.o
	gcc -fopenmp -lm -g -o schooling main.o sequential.o utilities.o
	rm -f *.o

parallel_for: main.o parallel_for.o utilities.o
	gcc -fopenmp -lm -g -o schooling main.o parallel_for.o utilities.o
	rm -f *.o

parallel_for_scheduling: main.o parallel_for_scheduling.o utilities.o
	gcc -fopenmp -lm -g -o schooling main.o parallel_for_scheduling.o utilities.o
	rm -f *.o

parallel_step_swim_: main.o parallel_step_swim.o utilities.o
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

main.o: src/main.c src/fish.h src/utilities.h
	gcc -fopenmp -c src/main.c

sequential.o: src/sequential.c src/fish.h
	gcc -c src/sequential.c

parallel_for.o: src/parallel_for.c src/fish.h
	gcc -fopenmp -c src/parallel_for.c

parallel_tasks.o: src/parallel_tasks.c src/fish.h
	gcc -fopenmp -c src/parallel_tasks.c

parallel_step_swim.o: src/parallel_step_swim.c src/fish.h
	gcc -fopenmp -c src/parallel_step_swim.c

parallel_for_scheduling.o: src/parallel_for_scheduling.c src/fish.h
	gcc -fopenmp -c src/parallel_for_scheduling.c

swim_only.o: src/swim_only.c src/fish.h
	gcc -fopenmp -c src/swim_only.c

eat_only.o: src/eat_only.c src/fish.h
	gcc -fopenmp -c src/eat_only.c

barycentre_only.o: src/barycentre_only.c src/fish.h
	gcc -fopenmp -c src/barycentre_only.c

utilities.o: src/utilities.c src/utilities.h src/fish.h
	gcc -fopenmp -c src/utilities.c

clean:
	rm -f *.o
