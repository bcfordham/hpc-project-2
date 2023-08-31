install: main.o timer.o
	gcc -lm -o schooling main.o timer.o
	rm main.o timer.o

main.o: src/main.c timer.o src/timer.h
	gcc -c src/main.c

timer.o: src/timer.c src/timer.h
	gcc -c src/timer.c

clean:
	rm -f *.o
