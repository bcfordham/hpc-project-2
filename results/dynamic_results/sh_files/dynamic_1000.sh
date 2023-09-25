#!/bin/bash -l
#SBATCH --account=courses0101
#SBATCH --partition=debug
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=4
#SBATCH --cpus-per-task=4
#SBATCH --time=00:20:00
#SBATCH --job-name=dynamic_1000
#SBATCH --output=dynamic_1000.out

export OMP_NUM_THREADS=4

srun ./dynamic_1000
