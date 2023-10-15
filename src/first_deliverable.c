#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <mpi.h>
#include "fish.h"
#include "utilities.h"

// NUM_FISH needs to be divisible by NUM_PROCESSES to send the correct number of 
// fish to worker processes
#define NUM_PROCESSES 4

// Function only executed by the master process
void pre_scatter(struct fish *fish)
{
	FILE *fp;
	
	generate_fish(fish);

	// Write fish data to an output file
	fp = fopen("out1.txt", "w+");
	fprintf(fp, "#\tx\ty\tw\tf\n");
	for (int i = 0; i < NUM_FISH; i++)
		fprintf(fp, "%d\t%.2f\t%.2f\t%.2f\t%.2f\n", i, fish[i].x, fish[i].y, 
		  fish[i].w, fish[i].f);
}

void post_scatter(struct fish *fish)
{
	FILE *fp;

	// Write fish data to an output file
	fp = fopen("out2.txt", "w+");
	fprintf(fp, "#\tx\ty\tw\tf\n");
	for (int i = 0; i < NUM_FISH; i++)
		fprintf(fp, "%d\t%.2f\t%.2f\t%.2f\t%.2f\n", i, fish[i].x, fish[i].y, 
		  fish[i].w, fish[i].f);

	free(fish);
}

int main(int argc, char *argv[])
{
	int rank, size;
	double start, end, time_taken;
	struct fish *all_fish;
	struct fish *worker_fish;

	start = omp_get_wtime();
	
	const int num_bytes = (NUM_FISH / NUM_PROCESSES) * sizeof(struct fish);

	// MPI code initialisation
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {
		all_fish = malloc(NUM_FISH * sizeof(struct fish));
		pre_scatter(all_fish);
	}
	
	worker_fish = malloc(num_bytes);

	MPI_Scatter(all_fish, num_bytes, MPI_BYTE, worker_fish, num_bytes, 
			 MPI_BYTE, 0, MPI_COMM_WORLD);

	MPI_Gather(worker_fish, num_bytes, MPI_BYTE, all_fish, 
			num_bytes, MPI_BYTE, 0, MPI_COMM_WORLD);

	if (rank == 0)
		post_scatter(all_fish);

	free(worker_fish);

	MPI_Finalize();

	end = omp_get_wtime();
	time_taken = end - start;
	
	printf("num of fish: %d\n", NUM_FISH);
	printf("Time taken: %.10f\n", time_taken);

	return 0;
}
