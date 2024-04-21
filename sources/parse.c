#include <math.h>
#include <stdlib.h>

#include "ft_ping.h"

extern args_t args;

static int match_flag(char *f) {
	char *lookup[] = {
		"", "-v", "-q", "-f", "-l", "-n", "-w", "-W", "-p", "-r", "-s", "-T", "--ttl", "--ip-timestamp", NULL,
	};

	for (int i = 0; lookup[i] != NULL; i++) {
		if (!strncmp(lookup[i], f, strlen(f))) {
			return (int)pow(2, i);	// NOTE: terrible solution
		}
	}

	return 0;
}

static int parse_pattern(char *arg) {
	args.pattern = arg;	 // TODO: parse
	return 0;
}

static int parse_timestamp(char *arg) {
	args.timestamp = arg;  // TODO: parse
	return 0;
}

static int parse_flag_arg(int f, char *fl, char *arg) {
	switch (f) {
		case F_l:
			args.preload = strtol(arg, NULL, 10);
			break;
		case F_w:
			args.timeout = strtol(arg, NULL, 10);
			break;
		case F_W:
			args.linger = strtol(arg, NULL, 10);
			break;
		case F_p:
			return parse_pattern(arg);
			break;
		case F_s:
			args.size = strtol(arg, NULL, 10);
			break;
		case F_T:
			args.tos = strtol(arg, NULL, 10);
			break;
		case F_ttl:
			args.ttl = strtol(arg, NULL, 10);
			break;
		case F_ip_t:
			return parse_timestamp(arg);
			break;
		default:
			fprintf(stderr, "error: parsing %s option arg\n", fl);
			return 1;
			break;
	}

	if (errno) {
		fprintf(stderr, "error: parsing %s option arg, %s\n", fl, strerror(errno));
		return 1;
	}

	return 0;
}

// TODO: Refactor
int parse_args(int argc, char **argv) {
	for (int i = 1; (i < argc); i++) {
		if (i == (argc - 1)) {
			args.hostname = argv[i];
			continue;
		}

		char *tmp = argv[i];

		int f = match_flag(tmp);
		args.opt.n |= f;

		if (args.opt.n & F_e) {
			fprintf(stderr, "error: invalid flag %s\n", tmp);
			return 1;
		}

		if (f != F_v && f != F_q && f != F_f && f != F_n && f != F_r) {
			i++;  // NOTE: incrementing here

			if (i >= argc) {
				fprintf(stderr, "error: missing arg for flag %s\n", tmp);
			}

			if (parse_flag_arg(f, tmp, argv[i])) {
				return 1;
			}
		}
	}

	if (args.hostname == NULL) {
		fprintf(stderr, "error: destination address required\n");
		return 1;
	}

	return 0;
}
