#define SQUARE_SIZE 200
#define INITIAL_WEIGHT 45
#define NUM_FISH 100000


struct fish {
	double x;
	double y;
	double w;
	double f;
};

void eat(struct fish *fish, double max, int step);
double swim(struct fish *fish);
double find_barycentre(struct fish *fish);
