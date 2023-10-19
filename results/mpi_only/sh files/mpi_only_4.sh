#!/bin/sh 
#SBATCH --account=courses0101
#SBATCH --partition=debug
#SBATCH --ntasks=4
#SBATCH --ntasks-per-node=1
#SBATCH --time=01:00:00
#SBATCH --mem-per-cpu=32G
#module load  openmpi/4.0.5

srun ./mpi_only_4
