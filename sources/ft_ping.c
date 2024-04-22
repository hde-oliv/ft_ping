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

	if (signal_setup()) {
		fprintf(stderr, "error: signal config\n");
		return 1;
	}

	run_loop();

	return 0;
}
