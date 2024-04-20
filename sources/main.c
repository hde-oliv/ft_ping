#include "ft_ping.h"

args_t args;

int main(int argc, char *argv[]) {
	bzero(&args, sizeof(args_t));

	if (argc == 1) {
		fprintf(stderr, "error: destination address required\n");
		return EXIT_FAILURE;
	}

	if (parse_args(argc, argv)) {
		fprintf(stderr, "error: parsing arguments\n");
		return EXIT_FAILURE;
	}

	debug_args();

	return EXIT_SUCCESS;
}
