// Parallel Fish Operations

double simulate_parallel_fish_operations(struct fish *fish) {
    double max;
    double barycentre;

    #pragma omp parallel for private(max) shared(barycentre) num_threads(NUM_THREADS)
    for (int i = 0; i < NUM_STEPS; i++) {
        max = swim(fish);
        eat(fish, max, i);
        barycentre = find_barycentre(fish);
    }

    return barycentre;
}