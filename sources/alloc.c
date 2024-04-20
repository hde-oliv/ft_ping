#include "ft_ping.h"

struct icmp *alloc_icmp(int seq) {
	struct icmp *p;

	p = calloc(1, sizeof(struct icmp));

	p->icmp_type  = ICMP_ECHO;
	p->icmp_code  = 0;
	p->icmp_cksum = 0;	// TODO: need to do validation
	p->icmp_id	  = getpid();
	p->icmp_seq	  = seq;

	return p;
}

struct addrinfo *alloc_hints() {
	struct addrinfo *h;

	h = calloc(1, sizeof(struct addrinfo));

	h->ai_family   = AF_UNSPEC;
	h->ai_socktype = SOCK_RAW;
	h->ai_flags	   = AI_PASSIVE;
	h->ai_protocol = IPPROTO_ICMP;

	return h;
}
