#include "ft_ping.h"

args_t args;
loop_t loop;

int main(int argc, char *argv[]) {
	bzero(&args, sizeof(args_t));
	bzero(&loop, sizeof(loop_t));

	if (argc == 1) {
		fprintf(stderr, "error: destination address required\n");
		return 1;
	}

	if (parse_args(argc, argv)) {
		fprintf(stderr, "error: parsing arguments\n");
		return 1;
	}

	// debug_args();

	if (run_loop()) {
		fprintf(stderr, "error: running loop\n");
		return 1;
	}

	return 0;
}
