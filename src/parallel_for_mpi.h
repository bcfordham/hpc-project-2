#include "fish.h"  // Ensure this includes the definition of the 'struct fish'
void eat(struct fish *fish, double max, int step);
double swim(struct fish *fish);
double find_barycentre(struct fish *fish, double *local_numerator, double *local_denominator);
