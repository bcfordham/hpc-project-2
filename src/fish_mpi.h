#define SQUARE_SIZE 200
#define INITIAL_WEIGHT 45
#define NUM_FISH 100


struct fish {
	double x;
	double y;
	double w;
	double f;
};

double parallel_swim(struct fish *fish, int local_num_fish);
void parallel_eat(struct fish *fish, int local_num_fish, double max, int step);
double parallel_find_barycentre(struct fish *fish, int local_num_fish);
