#!/bin/bash -l
#SBATCH --account=courses0101
#SBATCH --partition=debug
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=4
#SBATCH --cpus-per-task=4
#SBATCH --time=00:20:00
#SBATCH --job-name=dynamic_10000
#SBATCH --output=dynamic_10000.out

export OMP_NUM_THREADS=4

srun ./dynamic_10000
