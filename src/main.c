#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include "fish.h"
#include "utilities.h"

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
		MPI_Allreduce(
			&local_max,
			&global_max,
			1,
			MPI_DOUBLE,
			MPI_MAX,
			MPI_COMM_WORLD
		);
		eat(worker_fish, global_max, i);
		find_barycentre(worker_fish, &local_numerator, &local_denominator);
		MPI_Reduce(&local_numerator, &global_numerator, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		MPI_Reduce(&local_denominator, &global_denominator, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	
		if (rank == 0)
			final_barycentre = global_numerator / global_denominator;
	}

	MPI_Gather(worker_fish, num_bytes, MPI_BYTE, all_fish, num_bytes, MPI_BYTE, 0, MPI_COMM_WORLD);

    if (rank == 0)
        free(all_fish);

    free(worker_fish);

    MPI_Finalize();

	return 0;
}
