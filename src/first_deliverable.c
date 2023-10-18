#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include "fish.h"
#include "utilities.h"

// Populates the fish array and writes their data to a file
void pre_scatter(struct fish *fish)
{
	FILE *fp;
	
	generate_fish(fish);

	// Write fish data to a file
	fp = fopen("out1.txt", "w+");
	fprintf(fp, "#\tx\ty\tw\tf\n");
	for (int i = 0; i < NUM_FISH; i++)
		fprintf(fp, "%d\t%.2f\t%.2f\t%.2f\t%.2f\n", i, fish[i].x, fish[i].y, 
		  fish[i].w, fish[i].f);
}

// Writes fish data to a file and frees the fish array
void post_scatter(struct fish *fish)
{
	FILE *fp;

	// Write fish data to a file
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
	struct fish *all_fish;
	struct fish *worker_fish;
	
	// MPI code initialisation
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	const int num_bytes = (NUM_FISH / NUM_PROCESSES) * sizeof(struct fish);

	if (rank == 0) {
		all_fish = malloc(NUM_FISH * sizeof(struct fish));
		pre_scatter(all_fish);
	}
	
    worker_fish = malloc(num_bytes);
	
	MPI_Scatter(all_fish, num_bytes, MPI_BYTE, worker_fish, num_bytes, MPI_BYTE, 0, MPI_COMM_WORLD);
	for (int i = 0; i < 10; i++) {
		printf("%f\n",worker_fish[i].x);
	}
	MPI_Gather(worker_fish, num_bytes, MPI_BYTE, all_fish, num_bytes, MPI_BYTE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        post_scatter(all_fish);
    }

    free(worker_fish);

    MPI_Finalize();

	return 0;
}
