#include "ft_ping.h"

extern loop_t loop;

void clear(void) {
	close(loop.sockfd);
	freeaddrinfo(loop.result);
}
