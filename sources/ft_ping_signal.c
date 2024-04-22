#include "ft_ping.h"

void signal_handler(int sig) {
	(void)sig;
	clear();
	print_statistics();
	exit(0);
}

int signal_setup(void) {
	struct sigaction sa = { 0 };

	sa.sa_handler = signal_handler;
	if (sigaction(SIGINT, &sa, NULL)) {
		return 1;
	}
	if (sigaction(SIGQUIT, &sa, NULL)) {
		return 1;
	}
	if (sigaction(SIGUSR1, &sa, NULL)) {
		return 1;
	}
	return 0;
}
