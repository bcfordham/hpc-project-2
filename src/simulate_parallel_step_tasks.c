// Parallel Step Tasks Simulation

void simulate_parallel_step_tasks(struct fish *fish, int num_steps) {
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        #pragma omp single
        {
            for (int step = 0; step < num_steps; step++) {
                #pragma omp task
                {
                    double max = swim(fish);
                    eat(fish, max, step);
                }
                #pragma omp task
                {
                    double barycentre = find_barycentre(fish);
                    // You may use barycentre in some way, e.g., print or store it
                }
                #pragma omp taskwait
            }
        }
    }
}
