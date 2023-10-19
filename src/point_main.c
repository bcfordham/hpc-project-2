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
	double start, end;
	double local_max;
	double global_max;
	double local_numerator;
	double local_denominator;
	double global_numerator;
	double global_denominator;
	double final_barycentre;
	MPI_Status status;
	
	// MPI code initialisation
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if (size != NUM_PROCESSES) {
		printf("NUM_PROCESSES in fish.h is %d when it should be %d\n", 
			NUM_PROCESSES, size);
		exit(EXIT_FAILURE);
	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	start = MPI_Wtime();

	const int num_bytes = (NUM_FISH / NUM_PROCESSES) * sizeof(struct fish);

	if (rank == 0) {
		all_fish = malloc(NUM_FISH * sizeof(struct fish));
		generate_fish(all_fish);
	}
	
	worker_fish = malloc(num_bytes);
	
	// Equivalent to scatter but implemented point_to_point
	if (rank == 0) {
		for (int i = 1; i < NUM_PROCESSES; i++)
			MPI_Send(&all_fish[(NUM_FISH / NUM_PROCESSES) * i], num_bytes, 
				MPI_BYTE, i, i, MPI_COMM_WORLD);

		for (int i = 0; i < NUM_FISH / NUM_PROCESSES; i++)
			worker_fish[i] = all_fish[i];
	} else
		MPI_Recv(worker_fish, num_bytes, MPI_BYTE, 0, rank, 
			MPI_COMM_WORLD, &status);

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
		MPI_Reduce(&local_numerator, &global_numerator, 1, MPI_DOUBLE, 
			 MPI_SUM, 0, MPI_COMM_WORLD);
		MPI_Reduce(&local_denominator, &global_denominator, 1, MPI_DOUBLE, 
			 MPI_SUM, 0, MPI_COMM_WORLD);
		
		if (rank == 0) 
			final_barycentre = global_numerator / global_denominator;
	}

	if (rank == 0) {
		for (int i = 0; i < NUM_FISH / NUM_PROCESSES; i++)
			all_fish[i] = worker_fish[i];

		for (int i = 1; i < NUM_PROCESSES; i++)
			MPI_Recv(&all_fish[(NUM_FISH / NUM_PROCESSES) * i], num_bytes, 
				MPI_BYTE, i, 0, MPI_COMM_WORLD, &status);
	}
	else
		MPI_Send(worker_fish, num_bytes, MPI_BYTE, 0, 0, MPI_COMM_WORLD);

	if (rank == 0)
		free(all_fish);

	free(worker_fish);

	MPI_Barrier(MPI_COMM_WORLD);
	end = MPI_Wtime();

	MPI_Finalize();


	if (rank == 0) {
		printf("Runtime: %.2f seconds\n", end - start);
		printf("Config:\n");
		printf("Fish: %d\n", NUM_FISH);
		printf("Steps: %d\n", NUM_STEPS);
		printf("Processes: %d\n", NUM_PROCESSES);
		#ifdef OPENMP
		printf("Threads: %s\n", getenv("OMP_NUM_THREADS"));
		#else
		printf("Not using OpenMP\n");
		#endif
		printf("Using point-to-point communication\n");
	}

	return 0;
}
