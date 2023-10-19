#define SQUARE_SIZE 200
#define INITIAL_WEIGHT 45
/* NUM_FISH needs to be divisible by NUM_PROCESSES to send the correct number 
 of fish to worker processes */
#define NUM_FISH 100
#define NUM_STEPS 100
#define NUM_PROCESSES 4

struct fish {
	double x;
	double y;
	double w;
	double f;
};

void eat(struct fish *fish, double max, int step);
double swim(struct fish *fish);
void find_barycentre(struct fish *fish, double *numerator, double *denominator);
