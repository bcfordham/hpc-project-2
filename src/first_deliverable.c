#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "fish.h"
#include "utilities.h"

int main() {
	FILE *fp1;
	struct fish *fish = malloc(NUM_FISH * sizeof(struct fish));

	double start = omp_get_wtime();
	
	generate_fish(fish);

	fp1 = fopen("out1.txt", "w+");
	fprintf(fp1, "#\tx\ty\tw\tf\n");
	for (int i = 0; i < NUM_FISH; i++)
		fprintf(fp1, "%d\t%.2f\t%.2f\t%.2f\t%.2f\n", i, fish[i].x, fish[i].y, fish[i].w, fish[i].f);

	double end = omp_get_wtime();
	double time_taken = end - start;
	
	//print_all_fish(fish, barycentre);
	printf("num of fish: %d\n", NUM_FISH);
	printf("Time taken: %.10f\n", time_taken);
	free(fish);

	return 0;
}
