#include "ft_ping.h"

extern args_t args;
extern loop_t loop;

void print_info(void) { printf("PING %s (%s): 56 data bytes\n", args.hostname, loop.ipstr); }

void print_response(void *res, short seq, int p_siz) {
	struct iphdr *ip = (struct iphdr *)res;

	double time = (double)loop.stats.last;

	// TODO:  64 bytes from 157.240.226.35: icmp_seq=3 ttl=54 time=-983.001 ms
	printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3lf ms\n", p_siz, loop.ipstr, seq, ip->ttl, time);
}

void print_statistics(void) {
	printf("--- %s ping statistics ---\n", args.hostname);
	printf("%d packets transmitted, %d packets received, %d%% packet loss\n", loop.stats.send, loop.stats.recv,
		   100 - ((100 * loop.stats.recv) / loop.stats.send));
	printf("round-trip min/avg/max/stdddev = %.3lf/%.3lf/%.3lf/%.3lf ms\n", (double)loop.stats.min,
		   (double)loop.stats.avg, (double)loop.stats.max, 0.0);
}
