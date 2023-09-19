#!/bin/sh
#SBATCH --account=courses0101
#SBATCH --partition=debug
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=4
#SBATCH --cpus-per-task=4
#SBATCH --time=00:01:00

export OMP_NUM_THREADS=32

gcc -o all_simulation main.c simulate_parallel_step_tasks.c simulate_parallel_fish_operations.c simulate_parallel_fish_tasks.c simulate_parallel_master_taskloop.c simulate_parallel_step_and_fish.c simulate_sequential.c -fopenmp


srun ./all_simulation