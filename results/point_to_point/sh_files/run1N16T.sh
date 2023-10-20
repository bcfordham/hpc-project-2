#!/bin/sh 
#SBATCH --account=courses0101
#SBATCH --partition=debug
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:15:00
#SBATCH --job-name=1N16T
#SBATCH --output=1N16T.out
#SBATCH --mem-per-cpu=32G
#module load  openmpi/4.0.5

export OMP_NUM_THREADS=16

srun ./1N
