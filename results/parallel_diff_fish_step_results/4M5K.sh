#!/bin/bash -l
#SBATCH --account=courses0101
#SBATCH --partition=debug
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=4
#SBATCH --cpus-per-task=4
#SBATCH --time=00:20:00
#SBATCH --job-name=4M5K
#SBATCH --output=4M5K.out

export OMP_NUM_THREADS=4

srun ./4M5K
