#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef OPENMP
#include <omp.h>
#endif

#include "fish.h"
#include "utilities.h"

// Calculates the new weight for the fish
void eat(struct fish *fish, double max, int step) {
	#ifdef OPENMP
	#pragma omp parallel
	{
	#endif
		if (!step) {
			#ifdef OPENMP
			#pragma omp for
			#endif
			for (int i = 0; i < NUM_FISH / NUM_PROCESSES; i++)
				fish[i].w += (rand() / (double)RAND_MAX) * INITIAL_WEIGHT * 0.01;
		} else {
			#ifdef OPENMP
			#pragma omp for
			#endif
			for (int i = 0; i < NUM_FISH / NUM_PROCESSES; i++) {
				if (fish[i].w < 2 * INITIAL_WEIGHT) {
					fish[i].w += fish[i].f / max;

					if(fish[i].w > 2 * INITIAL_WEIGHT)
						fish[i].w = 2 * INITIAL_WEIGHT;
				}
			}
		}
	#ifdef OPENMP	
	}
	#endif
}

// Updates the locations of fish if they are below 2w, also determines the maximum change in f across fish for use in eat()
double swim(struct fish *fish) {
	double prev_x;
	double prev_y;
	double max = 0;
	double new;

	#ifdef OPENMP
	#pragma omp parallel for reduction(max:max) private(prev_x, prev_y, new)
	#endif
	for (int i = 0; i < NUM_FISH / NUM_PROCESSES; i++) {
		if (fish[i].w < 2 * INITIAL_WEIGHT) {
			prev_x = fish[i].x;
			prev_y = fish[i].y;
			fish[i].x += ((rand() / (double)RAND_MAX) - 0.5) * 0.2;
			fish[i].y += ((rand() / (double)RAND_MAX) - 0.5) * 0.2;

			if ((new = obj_diff(&fish[i], prev_x, prev_y)) > max)
				max = new;
		}
	}
	return max;
}

// Calculates the barycentre of the fish
void find_barycentre(struct fish *fish, double *local_numerator, double *local_denominator) {
	double distance;
	double numerator = 0;
	double denominator = 0;

	#ifdef OPENMP
	#pragma omp parallel for reduction(+:numerator) reduction(+:denominator) private(distance)
	#endif
	for (int i = 0; i < NUM_FISH / NUM_PROCESSES; i++) {
		distance = sqrt(pow(fish[i].x, 2) + pow(fish[i].y, 2));
		numerator +=  distance * fish[i].w;
		denominator += distance;
	}

	*local_numerator = numerator;
	*local_denominator = denominator;
}
