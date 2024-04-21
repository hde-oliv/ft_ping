#include <arpa/inet.h>
#include <netinet/in.h>

#include "ft_ping.h"

extern args_t args;
extern loop_t loop;

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
		return 1;
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

		/* err = connect(loop.sockfd, loop.rp->ai_addr, loop.rp->ai_addrlen); */

		if (err) {
			fprintf(stderr, "connection: %s\n", strerror(err));
			close(loop.sockfd);
			return 1;
		}
		break;
	}

	if (loop.rp == NULL) {
		fprintf(stderr, "could not connect with any address\n");
		return 1;
	}

	return 0;
}

unsigned short get_cksum(unsigned short *b, int len) {
	unsigned sum;

	for (sum = 0; len > 1; len -= 2) {
		sum += *b++;
	}

	if (len == 1) {
		sum += *(unsigned char *)b;
	}

	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	return ~sum;
}

int send_packets(void) {
	int			 PACKET_SIZE = 64;
	char		 packet[PACKET_SIZE];
	struct icmp *header = (struct icmp *)packet;

	for (int i = 0;; i++) {
		bzero(packet, PACKET_SIZE);

		header->icmp_type  = ICMP_ECHO;
		header->icmp_code  = 0;
		header->icmp_id	   = getpid();
		header->icmp_seq   = (i >> 8) | (i << 8);
		header->icmp_cksum = get_cksum((unsigned short *)packet, PACKET_SIZE);

		if (sendto(loop.sockfd, packet, PACKET_SIZE, 0, loop.rp->ai_addr, loop.rp->ai_addrlen) < 0) {
			perror("sendto");
			close(loop.sockfd);
			return 1;
		}

		char	buf[PACKET_SIZE];
		ssize_t r = recvfrom(loop.sockfd, buf, PACKET_SIZE, 0, NULL, NULL);
		if (r < 0) {
			perror("recvfrom");
			close(loop.sockfd);
			return 1;
		}
	}

	return 0;
}

int run_loop(void) {
	if (setup_connection()) {
		return 1;
	}

	debug_loop();

	if (send_packets()) {
		return 1;
	}

	clear();
	return 0;
}
