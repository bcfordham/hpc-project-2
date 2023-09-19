install: main.o fish.o
	gcc -fopenmp -lm -g -o schooling main.o fish.o
	rm -f *.o

main.o: src/main.c src/fish.h
	gcc -c src/main.c

fish.o: src/fish.c src/fish.h
	gcc -c src/fish.c

clean:
	rm -f *.o
