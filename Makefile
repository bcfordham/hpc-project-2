sequential: main.o sequential.o utilities.o
	gcc -fopenmp -lm -g -o schooling main.o sequential.o utilities.o
	rm -f *.o

parallel_for: main.o parallel_for.o utilities.o
	gcc -fopenmp -lm -g -o schooling main.o parallel_for.o utilities.o
	rm -f *.o

first_deliverable: first_deliverable.o utilities.o
	mpicc -lm -g -o schooling first_deliverable.o utilities.o
	rm -f *.o

main.o: src/main.c src/fish.h src/utilities.h
	gcc -fopenmp -c src/main.c

sequential.o: src/sequential.c src/fish.h
	gcc -c src/sequential.c

utilities.o: src/utilities.c src/utilities.h src/fish.h
	gcc -lm -c src/utilities.c

first_deliverable.o: src/first_deliverable.c src/fish.h src/utilities.h
	mpicc -g -c src/first_deliverable.c

clean:
	rm -f *.o
