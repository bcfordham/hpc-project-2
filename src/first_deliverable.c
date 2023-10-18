#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include "fish_mpi.h"
#include "utilities_mpi.h"

#define NUM_PROCESSES 4
#define NUM_STEPS 100

<<<<<<< HEAD
// NUM_FISH needs to be divisible by NUM_PROCESSES to send the correct number of 
// fish to worker processes
=======
/* NUM_FISH needs to be divisible by NUM_PROCESSES to send the correct number 
 of fish to worker processes */
#define NUM_PROCESSES 4
>>>>>>> origin/master

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
        generate_fish(all_fish);
    }
	
    worker_fish = malloc(num_bytes);
	
	MPI_Scatter(all_fish, num_bytes, MPI_BYTE, worker_fish, num_bytes, MPI_BYTE, 0, MPI_COMM_WORLD);
    double local_numerator, local_denominator, local_max;
	double global_numerator, global_denominator, global_max;
    for (int i = 0; i < NUM_STEPS; i++) {
		local_max = parallel_swim(worker_fish);
		
		MPI_Allreduce(&local_max, &global_max, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
		MPI_Bcast(&global_max, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		parallel_eat(worker_fish, max, i);
		barycentre = parallel_find_barycentre(worker_fish, &local_numerator, &local_denominator);

		MPI_Allreduce(&local_numerator, &global_numerator, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    	MPI_Allreduce(&local_denominator, &global_denominator, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        // global deno / global numer

		barycentre = &global_numerator / &global_numerator;
	}

	MPI_Gather(worker_fish, num_bytes, MPI_BYTE, all_fish, num_bytes, MPI_BYTE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Only the master process had allocated memory for all_fish
        free(all_fish);
    }
    free(worker_fish);
    MPI_Finalize();

	return 0;
}
