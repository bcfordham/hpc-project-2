#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "timer.h"
#include <omp.h>


#define NUM_FISH 1000000
#define SQUARE_SIZE 200
#define INITIAL_WEIGHT 45
#define NUM_STEPS 100

struct fish {
	double x;
	double y;
	double w;
	double f;
};

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

// Calculates the new weight for the fish
void eat(struct fish *fish, double max, int step) {
	if (!step) {
		for (int i = 0; i < NUM_FISH; i++)
			fish[i].w += (rand() / (double)RAND_MAX) * INITIAL_WEIGHT * 0.01;	// TODO: potentially tweak this random value that stands in for the objective function stuff

		return;
	}

	for (int i = 0; i < NUM_FISH; i++) {
		if (fish[i].w < 2 * INITIAL_WEIGHT) {
			fish[i].w += fish[i].f / max;

			if(fish[i].w > 2 * INITIAL_WEIGHT)
				fish[i].w = 2 * INITIAL_WEIGHT;
		}
	}
}

// Calculates the difference in the objective function from last step to this step and stores the result in the fish
double obj_diff(struct fish *fish, double prev_x, double prev_y) {
	fish->f = fabs(sqrt(pow(fish->x, 2) + pow(fish->y, 2)) - sqrt(pow(prev_x, 2) + pow(prev_y, 2)));

	return fish->f;
}

// Updates the locations of fish if they are below 2w, also determines the maximum change in f across fish for use in eat()
double swim(struct fish *fish) {
	double prev_x;
	double prev_y;
	double max = 0;
	double new;

	for (int i = 0; i < NUM_FISH; i++) {
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
double find_barycentre(struct fish *fish) {
	double numerator = 0;
	double denominator = 0;
	double distance ;

	for (int i = 0; i < NUM_FISH; i++) {
		distance = sqrt(pow(fish[i].x, 2) + pow(fish[i].y, 2));
		numerator +=  distance * fish[i].w;
		denominator += distance;
	}

	return numerator / denominator;
}

// Simulates the eating, swimming and collective action of the fish
// double simulate(struct fish *fish) {
// 	double max;
// 	double barycentre;

// 	for (int i = 0; i < NUM_STEPS; i++) {
// 		max = swim(fish);
// 		eat(fish, max, i);
// 		barycentre = find_barycentre(fish);
// 	}

// 	return barycentre;
// }

double simulate(struct fish *fish) {
    double max;
    double barycentre;

    #pragma omp parallel for private(max) shared(barycentre) num_threads(NUM_THREADS)
    for (int i = 0; i < NUM_STEPS; i++) {
        max = swim(fish);
        eat(fish, max, i);
        barycentre = find_barycentre(fish);
    }

    return barycentre;
}


int main() {
	double barycentre;
	struct timer *timer = malloc(sizeof(struct timer));
	struct fish *fish = malloc(NUM_FISH * sizeof(struct fish));


	// Set the number of threads you want to use
    int NUM_THREADS = 4; // adjust this for experimentation of report

	// substitute for OpenMP
	double start = omp_get_wtime();
	// start_timer(timer);
	generate_fish(fish);
	barycentre = simulate(fish);

	double end = omp_get_wtime();
	double time_taken= end-start;
	// end_timer(timer);
	print_all_fish(fish, barycentre);
	printf("Time taken: %.10f\n", time_taken);

	free(fish);

	return 0;
}
