#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "fish.h"
#include "simulation.h"

#define NUM_FISH 1000000
#define SQUARE_SIZE 200
#define INITIAL_WEIGHT 45
#define NUM_STEPS 100
#define NUM_THREADS 4

int main() {
	double barycentre;
	struct fish *fish = malloc(NUM_FISH * sizeof(struct fish));

	double start = omp_get_wtime();
	
	generate_fish(fish);

	// Declare which simulation you would like to use
	// barycentre = simulate1(fish);

	double end = omp_get_wtime();
	double time_taken = end - start;
	
	print_all_fish(fish, barycentre);
	printf("Time taken: %.10f\n", time_taken);

	free(fish);

	return 0;
}
