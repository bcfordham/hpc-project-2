install: main.o timer.o
	gcc -lm -o schooling main.o timer.o
	rm main.o timer.o

main.o: main.c timer.o timer.h
	gcc -c main.c

timer.o: timer.c timer.h
	gcc -c timer.c

clean:
	rm main.o timer.o
