#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fish_mpi.h"

// Initialises the fish position with random values and sets the weight to the intial weight
void generate_fish(struct fish *fish) {
	for (int i = 0; i < NUM_FISH; i++) {
		fish[i].x = ((rand() / (double)RAND_MAX) - 0.5) * SQUARE_SIZE;	// TODO: tweak the generation to not include the boundaries, as is specified in the project spec
		fish[i].y = ((rand() / (double)RAND_MAX) - 0.5) * SQUARE_SIZE;	// TODO: seed random value generation, decide whether it make it repeatable
		fish[i].w = INITIAL_WEIGHT;
	}
}

// Prints the values of one fish
void print_fish(struct fish fish, int num) {
	printf("%d\t%.2f\t%.2f\t%.2f\n", num, fish.x, fish.y, fish.w);
}

// Prints the values of all fish in a table
void print_all_fish(struct fish *fish, double barycentre) {
	printf("Fish #\tx\ty\tw\n");
	
	for (int i = 0; i < NUM_FISH; i++) {
		print_fish(fish[i], i);
	}
	printf("Barycentre: %.2f\n", barycentre);
}

// Calculates the difference in the objective function from last step to this step and stores the result in the fish
double obj_diff(struct fish *fish, double prev_x, double prev_y) {
	fish->f = fabs(sqrt(pow(fish->x, 2) + pow(fish->y, 2)) - sqrt(pow(prev_x, 2) + pow(prev_y, 2)));

	return fish->f;
}
