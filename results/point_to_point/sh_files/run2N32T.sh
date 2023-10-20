#!/bin/sh 
#SBATCH --account=courses0101
#SBATCH --partition=debug
#SBATCH --ntasks=2
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:15:00
#SBATCH --job-name=2N32T
#SBATCH --output=2N32T.out
#SBATCH --mem-per-cpu=32G
#module load  openmpi/4.0.5

export OMP_NUM_THREADS=32

srun ./2N
