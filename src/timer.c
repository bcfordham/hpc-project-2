#include <time.h>
#include <stdio.h>
#include "timer.h"

void start_timer(struct timer *timer) {
	timer->begin = clock();
}

void end_timer(struct timer *timer) {
	timer->end = clock();
	timer->time_spent = (timer->end - timer->begin) / (double)CLOCKS_PER_SEC;
}
