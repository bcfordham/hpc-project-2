// Parallel Step and Fish Simulation

void simulate_parallel_step_and_fish(struct fish *fish, int num_steps) {
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        for (int step = 0; step < num_steps; step++) {
            #pragma omp parallel for
            for (int i = 0; i < NUM_FISH; i++) {
                double max = swim(&fish[i]);
                eat(&fish[i], max, step);
            }
            
            #pragma omp single
            {
                double barycentre = find_barycentre(fish);
                // You may use barycentre in some way, e.g., print or store it
            }
        }
    }
}