#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "fish.h"
#include "utilities.h"

// Calculates the new weight for the fish
void eat(struct fish *fish, double max, int step) {
    if (!step) {
        #pragma omp parallel
        {
            #pragma omp single
            {
                for (int i = 0; i < NUM_FISH; i++) {
                    #pragma omp task
                    {
                        fish[i].w += (rand() / (double)RAND_MAX) * INITIAL_WEIGHT * 0.01; // TODO: potentially tweak this random value that stands in for the objective function stuff
                    }
                }
            }
        }
        return;
    }

    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 0; i < NUM_FISH; i++) {
                #pragma omp task
                {
                    if (fish[i].w < 2 * INITIAL_WEIGHT) {
                        fish[i].w += fish[i].f / max;

                        if (fish[i].w > 2 * INITIAL_WEIGHT)
                            fish[i].w = 2 * INITIAL_WEIGHT;
                    }
                }
            }
        }
    }
}

// Updates the locations of fish if they are below 2w, also determines the maximum change in f across fish for use in eat()
double swim(struct fish *fish) {
    double prev_x;
    double prev_y;
    double max = 0;
    double new;

    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 0; i < NUM_FISH; i++) {
                #pragma omp task
                {
                    if (fish[i].w < 2 * INITIAL_WEIGHT) {
                        prev_x = fish[i].x;
                        prev_y = fish[i].y;
                        fish[i].x += ((rand() / (double)RAND_MAX) - 0.5) * 0.2;
                        fish[i].y += ((rand() / (double)RAND_MAX) - 0.5) * 0.2;

                        double new_val = obj_diff(&fish[i], prev_x, prev_y);

                        #pragma omp critical
                        {
                            if (new_val > max) {
                                max = new_val;
                            }
                        }
                    }
                }
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

    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 0; i < NUM_FISH; i++) {
                #pragma omp task
                {
                    distance = sqrt(pow(fish[i].x, 2) + pow(fish[i].y, 2));
                    double partial_numerator = distance * fish[i].w;
                    double partial_denominator = distance;

                    #pragma omp critical
                    {
                        numerator += partial_numerator;
                        denominator += partial_denominator;
                    }
                }
            }
        }
    }

    return numerator / denominator;
}
