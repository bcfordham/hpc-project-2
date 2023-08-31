#include <time.h>

struct timer {
	clock_t begin;
	clock_t end;
	double time_spent;
};

void start_timer(struct timer *timer);
void end_timer(struct timer *timer);
