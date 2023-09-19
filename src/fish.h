struct fish {
	double x;
	double y;
	double w;
	double f;
};

void generate_fish(struct fish *fish);
void print_fish(struct fish fish, int num);
void print_all_fish(struct fish *fish, double barycentre);
void eat(struct fish *fish, double max, int step);
double swim(struct fish *fish);
double find_barycentre(struct fish *fish);
