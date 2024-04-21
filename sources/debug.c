#include "ft_ping.h"

extern args_t args;
extern loop_t loop;

void print_bits(size_t size, void *ptr) {
	unsigned char *b = (unsigned char *)ptr;
	unsigned char  byte;
	int			   i, j;

	for (i = size - 1; i >= 0; i--) {
		for (j = 7; j >= 0; j--) {
			byte = (b[i] >> j) & 1;
			printf("%u", byte);
		}
	}
	printf("\n");
}

void debug_loop(void) {
	printf("Debug loop -------------------------------------------------\n\n");
	printf("Result: %p\n", loop.result);
	printf("RP: %p\n", loop.result);
	printf("Socket fd: %d\n", loop.sockfd);
	printf("Ip address: %s\n", loop.ipstr);
	printf("------------------------------------------------------------\n\n");
}

void debug_args(void) {
	printf("Debug args -------------------------------------------------\n\n");
	printf("Options flag: ");
	print_bits(sizeof(short), &args.opt.n);
	printf("Options arguments:\n");
	printf("\tPreload: %d\n", args.preload);
	printf("\tTimeout: %d\n", args.timeout);
	printf("\tLinger: %d\n", args.linger);
	printf("\tPattern: %s\n", args.pattern);
	printf("\tSize: %d\n", args.size);
	printf("\tTOS: %d\n", args.tos);
	printf("\tTTL: %d\n", args.ttl);
	printf("\tTimestamp: %s\n", args.timestamp);
	printf("Hostname: %s\n", args.hostname);
	printf("------------------------------------------------------------\n\n");
}
