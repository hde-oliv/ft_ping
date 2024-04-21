#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include "ft_ping.h"

extern args_t args;
extern loop_t loop;

#define SECOND 1000000

int setup_socket(void) {
	int err;

	loop.hints.ai_family   = AF_UNSPEC;
	loop.hints.ai_socktype = SOCK_RAW;
	loop.hints.ai_flags	   = AI_PASSIVE;
	loop.hints.ai_protocol = IPPROTO_ICMP;

	err = getaddrinfo(args.hostname, NULL, &loop.hints, &loop.result);
	if (err) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
		return 1;
	}

	for (loop.rp = loop.result; loop.rp != NULL; loop.rp = loop.rp->ai_next) {
		if (loop.rp->ai_family == AF_INET) {
			inet_ntop(loop.rp->ai_family, &(((struct sockaddr_in *)loop.rp->ai_addr)->sin_addr), loop.ipstr,
					  sizeof(loop.ipstr));

			loop.sockfd = socket(loop.rp->ai_family, loop.rp->ai_socktype, loop.rp->ai_protocol);

			if (loop.sockfd == -1) {
				perror("socket");
				return 1;
			}

			break;
		}
	}

	if (loop.rp == NULL) {
		fprintf(stderr, "could not connect with any address\n");
		return 1;
	}

	return 0;
}

int send_packets(void) {
	int			 PACKET_SIZE = 64;
	char		 packet[PACKET_SIZE];
	struct icmp *header = (struct icmp *)packet;

	for (int i = 0;; i++) {
		setup_packet(header, packet, PACKET_SIZE, i);

		if (sendto(loop.sockfd, packet, PACKET_SIZE, 0, loop.rp->ai_addr, loop.rp->ai_addrlen) < 0) {
			perror("sendto");
			close(loop.sockfd);
			return 1;
		}

		char	buf[PACKET_SIZE + 20];	// NOTE: +20 Because of ivp4 header
		ssize_t r = recvfrom(loop.sockfd, buf, PACKET_SIZE + 20, 0, NULL, NULL);

		if (r < 0) {
			perror("recvfrom");
			close(loop.sockfd);
			return 1;
		}

		if (validate_packet(packet, buf, PACKET_SIZE)) {
			fprintf(stderr, "invalid incoming packet\n");
			return 1;
		}

		printf("%d bytes from %s: icmp_seq=%d ttl=? time=?\n", PACKET_SIZE, loop.ipstr, i);

		usleep(SECOND);
	}

	return 0;
}

static void clear_loop(void) { freeaddrinfo(loop.result); }

int run_loop(void) {
	if (setup_socket()) {
		return 1;
	}

	//  debug_loop();

	if (send_packets()) {
		return 1;
	}

	clear_loop();
	return 0;
}
