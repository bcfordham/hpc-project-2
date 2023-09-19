#include "fish.h"

// Squential Simulation

double simulate_sequential(struct fish *fish, int num_steps) {
	double max;
	double barycentre;

	for (int i = 0; i < num_steps; i++) {
		max = swim(fish);
		eat(fish, max, i);
		barycentre = find_barycentre(fish);
	}

	return barycentre;
}
