#include <stdlib.h>

#include "ft_ping.h"

extern args_t args;
extern loop_t loop;

static struct icmp *alloc_icmp(int seq) {
	struct icmp *p;

	p = calloc(1, sizeof(struct icmp));

	p->icmp_type  = ICMP_ECHO;
	p->icmp_code  = 0;
	p->icmp_cksum = 0;	// TODO: need to do validation
	p->icmp_id	  = getpid();
	p->icmp_seq	  = seq;

	return p;
}

static void clear(void) { freeaddrinfo(loop.result); }

int setup_connection(void) {
	int err;

	loop.hints.ai_family   = AF_UNSPEC;
	loop.hints.ai_socktype = SOCK_RAW;
	loop.hints.ai_flags	   = AI_PASSIVE;
	loop.hints.ai_protocol = IPPROTO_ICMP;

	err = getaddrinfo(args.hostname, NULL, &loop.hints, &loop.result);
	if (err) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
		return EXIT_FAILURE;
	}

	for (loop.rp = loop.result; loop.rp != NULL; loop.rp = loop.rp->ai_next) {
		// TODO: Refactor, must work with ipv4 only
		if (loop.rp->ai_family == AF_INET) {
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)loop.rp->ai_addr;
			void			   *addr = &(ipv4->sin_addr);

			inet_ntop(loop.rp->ai_family, addr, loop.ipstr, sizeof(loop.ipstr));
		}

		loop.sockfd = socket(loop.rp->ai_family, loop.rp->ai_socktype, loop.rp->ai_protocol);

		if (loop.sockfd == -1) {
			perror("socket");
			continue;
		}

		err = connect(loop.sockfd, loop.rp->ai_addr, loop.rp->ai_addrlen);

		if (err) {
			fprintf(stderr, "connection: %s\n", strerror(err));
			close(loop.sockfd);
			return EXIT_FAILURE;
		}
		break;
	}

	if (loop.rp == NULL) {
		fprintf(stderr, "could not connect with any address\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int send_packets() {
	int	  err;
	void *packet = alloc_icmp(1);

	err = sendto(loop.sockfd, &packet, sizeof(packet), 0, loop.rp->ai_addr, loop.rp->ai_addrlen);

	printf("sendto: %d\n", err);

	char buf[sizeof(packet)];

	err = recvfrom(loop.sockfd, buf, sizeof(packet), 0, loop.rp->ai_addr, &loop.rp->ai_addrlen);

	printf("recvfrom: %d | %s\n", err, buf);

	return EXIT_SUCCESS;
}

int run_loop(void) {
	if (setup_connection()) {
		return EXIT_FAILURE;
	}

	if (send_packets()) {
		return EXIT_FAILURE;
	}

	clear();
	return EXIT_SUCCESS;
}
