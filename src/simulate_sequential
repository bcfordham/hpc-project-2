// Squential Simulation

double simulate_sequential(struct fish *fish) {
	double max;
	double barycentre;

	for (int i = 0; i < NUM_STEPS; i++) {
		max = swim(fish);
		eat(fish, max, i);
		barycentre = find_barycentre(fish);
	}

	return barycentre;
}
