#include <stdlib.h>
#include <stdio.h>

#define NUM_FISH 100		// TODO: find a better way of changing the number of fish, e.g. from the command line
#define SQUARE_SIZE 200
#define INITIAL_WEIGHT 1

struct fish {
	double x;
	double y;
	double w;
};

// Initialises the fish position with random values and sets the weight to the intial weight
void generate_fish(struct fish *fish) {
	for (int i = 0; i < NUM_FISH; i++) {
		fish[i].x = ((rand() / (double)RAND_MAX) - 0.5) * SQUARE_SIZE;	// TODO: tweak the generation to not include the boundaries, as is specified in the project spec
		fish[i].y = ((rand() / (double)RAND_MAX) - 0.5) * SQUARE_SIZE;	// TODO: seed random value generation, decide whether it make it repeatable
		fish[i].w = INITIAL_WEIGHT;
	}
}

// Prints the fish values in a table
void print_fish(struct fish *fish) {
	printf("Fish #\tx\ty\tw\n");

	for (int i = 0; i < NUM_FISH; i++) {
		printf("%d\t%.2f\t%.2f\t%.2f\n", i, fish[i].x, fish[i].y, fish[i].w);
	}
}

int main() {
	struct fish *fish = malloc(NUM_FISH * sizeof(struct fish));

	generate_fish(fish);
	print_fish(fish);
	
	return 0;
}
