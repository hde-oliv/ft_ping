#include <stdio.h>

#include "ft_ping.h"

extern args_t args;
extern loop_t loop;

void print_info(void) {
	printf(RED "FT_PING ");
	printf(RESET "%s (", args.hostname);
	printf(CYAN "%s", loop.ipstr);
	printf(RESET "): " CYAN "56 " RESET "data bytes");

	if (args.opt.n & F_v) {
		printf(", id ");
		printf(CYAN "0x%04x ", getpid());
		printf(RESET "= ");
		printf(CYAN "%u", getpid());
	}

	printf("\n");
}

void print_response(void *res, short seq, int p_siz) {
	struct iphdr *ip = (struct iphdr *)res;

	double time = (double)loop.stats.last;

	printf(CYAN "%d ", p_siz);

	printf(RESET "bytes from ");
	printf(CYAN "%s", loop.ipstr);
	printf(RESET ": icmp_seq=");
	printf(CYAN "%d ", seq);
	printf(RESET "ttl=");
	printf(CYAN "%d ", ip->ttl);
	printf(RESET "time=");
	printf(CYAN "%.3lf ", time);
	printf(RESET "ms\n");
}

void print_statistics(void) {
	size_t summ =
		loop.stats.sq + (loop.stats.runs * loop.stats.avg * loop.stats.avg) - (2 * loop.stats.avg * loop.stats.tl);
	double dev = sqrt((double)summ / loop.stats.runs);

	printf(RED "--- %s ping statistics ---\n" RESET, args.hostname);
	printf(RED "%d" YELLOW " packets transmitted, " RED "%d" YELLOW " packets received, " RED "%d%%" YELLOW
			   " packet loss\n",
		   loop.stats.send, loop.stats.recv, 100 - ((100 * loop.stats.recv) / loop.stats.send));
	printf("round-trip min/avg/max/stdddev =" RED " %.3lf" YELLOW "/" RED "%.3lf" YELLOW "/" RED "%.3lf" YELLOW "/" RED
		   "%.3lf" YELLOW " ms\n",
		   (double)loop.stats.min, (double)loop.stats.avg, (double)loop.stats.max, dev);
}

void print_help(void) {
	printf("Usage: ft_ping [OPTION...] HOST ...	\n");
	printf("Send ICMP ECHO_REQUEST packets to network hosts.\n");
	printf("\n");
	printf(" Options:\n");
	printf("  -? %40s", "this help list\n");
	printf("  -v %40s", "verbose output\n");
	printf("\n");
	printf("Report bugs to <https://github.com/hde-oliv>.\n");
}
