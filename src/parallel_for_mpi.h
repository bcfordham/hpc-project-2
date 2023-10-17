#include "fish_mpi.h"  // Ensure this includes the definition of the 'struct fish'
void parallel_eat(struct fish *fish, int local_num_fish, double max, int step);
double parallel_swim(struct fish *fish, int local_num_fish);
double parallel_find_barycentre(struct fish *fish, int local_num_fish);
