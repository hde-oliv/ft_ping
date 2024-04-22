#include "ft_ping.h"

extern args_t args;
extern loop_t loop;

void setup_socket(void) {
	int err;

	loop.hints.ai_family   = AF_UNSPEC;
	loop.hints.ai_socktype = SOCK_RAW;
	loop.hints.ai_flags	   = AI_PASSIVE;
	loop.hints.ai_protocol = IPPROTO_ICMP;

	err = getaddrinfo(args.hostname, NULL, &loop.hints, &loop.result);
	if (err) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
		panic(NULL);
	}

	for (loop.rp = loop.result; loop.rp != NULL; loop.rp = loop.rp->ai_next) {
		if (loop.rp->ai_family == AF_INET) {
			inet_ntop(loop.rp->ai_family, &(((struct sockaddr_in *)loop.rp->ai_addr)->sin_addr), loop.ipstr,
					  sizeof(loop.ipstr));

			loop.sockfd = socket(loop.rp->ai_family, loop.rp->ai_socktype, loop.rp->ai_protocol);

			if (loop.sockfd == -1) panic("socket");
			break;
		}
	}

	if (loop.rp == NULL) {
		fprintf(stderr, "could not connect with any address\n");
		panic(NULL);
	}
}
