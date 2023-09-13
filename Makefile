install: src/main.c
	gcc -fopenmp -lm -o schooling src/main.c

clean:
	rm -f *.o
