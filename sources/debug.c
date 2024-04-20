#include "ft_ping.h"

extern args_t args;

static void print_bits(size_t const size, void const *const ptr) {
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

void debug_args(void) {
	printf("Debug ------------------------------------------------------\n\n");
	printf("Options flag: ");
	print_bits(sizeof(int), &args.opt.n);

	printf("------------------------------------------------------------\n");
	printf("Options arguments:\n");
	printf("\tPreload: %d\n", args.preload);
	printf("\tTimeout: %d\n", args.timeout);
	printf("\tLinger: %d\n", args.linger);
	printf("\tPattern: %s\n", args.pattern);
	printf("\tSize: %d\n", args.size);
	printf("\tTOS: %d\n", args.tos);
	printf("\tTTL: %d\n", args.ttl);
	printf("\tTimestamp: %s\n", args.timestamp);

	printf("------------------------------------------------------------\n");
	printf("Hostname: %s\n", args.hostname);
}
