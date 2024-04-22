#include "ft_ping.h"

extern loop_t loop;

void update_time(void *s, void *e) {
	struct timespec *start = s;
	struct timespec *end   = e;

	double sts	= ((start->tv_sec * 1000) + (start->tv_nsec / 1000000.0));
	double ets	= ((end->tv_sec * 1000) + (end->tv_nsec / 1000000.0));
	double time = ets - sts;

	loop.stats.last = time;

	// NOTE: First run
	if (loop.stats.max == 0) {
		loop.stats.max = time;
	}
	if (loop.stats.min == 0) {
		loop.stats.min = time;
	}
	if (loop.stats.avg == 0) {
		loop.stats.avg = time;
	}

	// NOTE: Subsequent runs
	if (loop.stats.max < time) {
		loop.stats.max = time;
	}
	if (loop.stats.min > time) {
		loop.stats.min = time;
	}

	loop.stats.avg = ((loop.stats.avg + time) / 2);
	loop.stats.sq += time * time;
	loop.stats.tl += time;
	loop.stats.runs++;
}
