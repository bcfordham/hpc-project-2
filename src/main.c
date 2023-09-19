#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "fish.h"

#define NUM_FISH 1000000
#define SQUARE_SIZE 200
#define INITIAL_WEIGHT 45
#define NUM_STEPS 100
#define NUM_THREADS 4

double simulate(struct fish *fish) {
	double max;
	double barycentre;

	for (int i = 0; i < NUM_STEPS; i++) {
		max = swim(fish);
		eat(fish, max, i);
		barycentre = find_barycentre(fish);
	}

	return barycentre;
}

int main() {
	double barycentre;
	struct fish *fish = malloc(NUM_FISH * sizeof(struct fish));

	double start = omp_get_wtime();
	
	generate_fish(fish);

	barycentre = simulate(fish);

	double end = omp_get_wtime();
	double time_taken = end - start;
	
	print_all_fish(fish, barycentre);
	printf("Time taken: %.10f\n", time_taken);

	free(fish);

	return 0;
}
