#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "fish.h"
#include "utilities.h"

// Helper function for eat step
void eat_step(struct fish *fish, double max, int start, int end) {
    for (int i = start; i < end; i++) {
        if (fish[i].w < 2 * INITIAL_WEIGHT) {
            fish[i].w += fish[i].f / max;
            if (fish[i].w > 2 * INITIAL_WEIGHT) {
                fish[i].w = 2 * INITIAL_WEIGHT;
            }
        }
    }
}

// Helper function for swim step
double swim_step(struct fish *fish, int start, int end) {
    double max_local = 0;
    double prev_x, prev_y, new;

    for (int i = start; i < end; i++) {
        if (fish[i].w < 2 * INITIAL_WEIGHT) {
            prev_x = fish[i].x;
            prev_y = fish[i].y;
            fish[i].x += ((rand() / (double)RAND_MAX) - 0.5) * 0.2;
            fish[i].y += ((rand() / (double)RAND_MAX) - 0.5) * 0.2;

            new = obj_diff(&fish[i], prev_x, prev_y);

            if (new > max_local) {
                max_local = new;
            }
        }
    }

    return max_local;
}

// Calculates the new weight for the fish
void eat(struct fish *fish, double max, int step) {
    if (!step) {
        #pragma omp parallel for
        for (int i = 0; i < NUM_FISH; i++) {
            fish[i].w += (rand() / (double)RAND_MAX) * INITIAL_WEIGHT * 0.01;
        }
    } else {
        #pragma omp parallel
        {
            double max_local = max; // Initialize max_local with the passed max value.
            #pragma omp single
            {
                for (int i = 0; i < NUM_FISH; i++) {
                    #pragma omp task
                    {
                        if (fish[i].w < 2 * INITIAL_WEIGHT) {
                            fish[i].w += fish[i].f / max_local;
                            if (fish[i].w > 2 * INITIAL_WEIGHT) {
                                fish[i].w = 2 * INITIAL_WEIGHT;
                            }
                        }
                    }
                }
            }
        }
    }
}

// Updates the locations of fish if they are below 2w, also determines the maximum change in f across fish for use in eat()
double swim(struct fish *fish) {
    double max = 0;
    double max_local = 0;

    #pragma omp parallel
    {
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        int chunk_size = NUM_FISH / num_threads;
        int start = thread_id * chunk_size;
        int end = (thread_id == num_threads - 1) ? NUM_FISH : start + chunk_size;

        max_local = swim_step(fish, start, end);

        #pragma omp critical
        {
            if (max_local > max) {
                max = max_local;
            }
        }
    }

    return max;
}

// Calculates the barycentre of the fish
double find_barycentre(struct fish *fish) {
    double numerator = 0;
    double denominator = 0;
    double distance;

    #pragma omp parallel for reduction(+:numerator) reduction(+:denominator) private(distance)
    for (int i = 0; i < NUM_FISH; i++) {
        distance = sqrt(pow(fish[i].x, 2) + pow(fish[i].y, 2));
        numerator +=  distance * fish[i].w;
        denominator += distance;
    }

    return numerator / denominator;
}
