#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include "fish.h"
#include "utilities.h"

void post_scatter(struct fish *fish)
{
	FILE *fp;

	// Write fish data to a file
	fp = fopen("out2.txt", "w+");
	fprintf(fp, "#\tx\ty\tw\tf\n");
	for (int i = 0; i < NUM_FISH; i++)
		fprintf(fp, "%d\t%.2f\t%.2f\t%.2f\t%.2f\n", i, fish[i].x, fish[i].y, 
		  fish[i].w, fish[i].f);
}

int main(int argc, char *argv[])
{
	int rank, size;
	struct fish *all_fish;
	struct fish *worker_fish;
	double local_max;
	double global_max;
	double local_numerator;
	double local_denominator;
	double global_numerator;
	double global_denominator;
	double final_barycentre;

	// MPI code initialisation
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	const int num_bytes = (NUM_FISH / NUM_PROCESSES) * sizeof(struct fish);

	if (rank == 0) {
		all_fish = malloc(NUM_FISH * sizeof(struct fish));
		generate_fish(all_fish);
	}
	
    worker_fish = malloc(num_bytes);
	
	MPI_Scatter(all_fish, num_bytes, MPI_BYTE, worker_fish, num_bytes, MPI_BYTE, 0, MPI_COMM_WORLD);
	for (int i = 0; i < NUM_STEPS; i++) {
		local_max = swim(worker_fish);
		printf("%d is running\n", i);
		MPI_Allreduce(
			&local_max,
			&global_max,
			1,
			MPI_DOUBLE,
			MPI_MAX,
			MPI_COMM_WORLD
		);
		eat(worker_fish, global_max, i);
		printf("global max is: %f\n", global_max);
		find_barycentre(worker_fish, &local_numerator, &local_denominator);
		MPI_Reduce(&local_numerator, &global_numerator, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		MPI_Reduce(&local_denominator, &global_denominator, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		
		if (rank == 0) 
			final_barycentre = global_numerator / global_denominator;
			printf("final barycentre is done: %f\n", &final_barycentre);
	}

	MPI_Gather(worker_fish, num_bytes, MPI_BYTE, all_fish, num_bytes, MPI_BYTE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
		post_scatter(all_fish);
        free(all_fish);
    }

    free(worker_fish);

    MPI_Finalize();

	return 0;
}
