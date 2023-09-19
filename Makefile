install: main.o fish_actions.o utilities.o
	gcc -fopenmp -lm -g -o schooling main.o fish_actions.o utilities.o
	rm -f *.o

main.o: src/main.c src/fish.h src/utilities.h
	gcc -c src/main.c

fish_actions.o: src/fish_actions.c src/fish.h
	gcc -c src/fish_actions.c

utilities.o: src/utilities.c src/utilities.h src/fish.h
	gcc -c src/utilities.c

clean:
	rm -f *.o
