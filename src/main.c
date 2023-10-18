#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include "fish.h"
#include "utilities.h"

int main(int argc, char *argv[])
{
	int rank, size;
	
	// MPI code initialisation
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
    double local_numerator, local_denominator, local_max;
	double global_numerator, global_denominator, global_max;
	double barycentre;
	struct fish *all_fish;
	struct fish *worker_fish;
	
	const int num_bytes = (NUM_FISH / NUM_PROCESSES) * sizeof(struct fish);

    if (rank == 0) {
        all_fish = malloc(NUM_FISH * sizeof(struct fish));
        generate_fish(all_fish);
    }
	
    worker_fish = malloc(num_bytes);
	
	MPI_Scatter(all_fish, num_bytes, MPI_BYTE, worker_fish, num_bytes, MPI_BYTE, 0, MPI_COMM_WORLD);
    
	for (int i = 0; i < NUM_STEPS; i++) {
		local_max = swim(worker_fish);

		MPI_Allreduce(&local_max, &global_max, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
		// MPI_Bcast(&global_max, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		eat(worker_fish, global_max, i);
		barycentre = find_barycentre(worker_fish, &local_numerator, &local_denominator);

		MPI_Reduce(&local_numerator, &global_numerator, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		MPI_Reduce(&local_denominator, &global_denominator, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		if (rank == 0)
			barycentre = global_numerator / global_numerator;
	}

	// MPI_Gather(worker_fish, num_bytes, MPI_BYTE, all_fish, num_bytes, MPI_BYTE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Only the master process had allocated memory for all_fish
        free(all_fish);
    }

    free(worker_fish);
    
	MPI_Finalize();

	return 0;
}
