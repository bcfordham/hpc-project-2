#!/bin/bash -l
#SBATCH --account=courses0101
#SBATCH --partition=debug
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=4
#SBATCH --cpus-per-task=4
#SBATCH --time=00:20:00
#SBATCH --job-name=bad_cache
#SBATCH --output=bad_cache.out

export OMP_NUM_THREADS=8

perf stat -e cache-references,cache-misses srun ./bad_cache
