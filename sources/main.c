#include "ft_ping.h"

args_t args;
loop_t loop;

int main(int argc, char *argv[]) {
	bzero(&args, sizeof(args_t));
	bzero(&loop, sizeof(loop_t));

	if (argc == 1) {
		fprintf(stderr, "error: destination address required\n");
		return EXIT_FAILURE;
	}

	if (parse_args(argc, argv)) {
		fprintf(stderr, "error: parsing arguments\n");
		return EXIT_FAILURE;
	}

	debug_args();

	if (run_loop()) {
		fprintf(stderr, "error: running loop\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
