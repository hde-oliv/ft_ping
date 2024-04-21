#include <bits/time.h>
#include <netinet/ip_icmp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "ft_ping.h"

static unsigned short get_cksum(unsigned short *b, int len) {
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

static void fill_packet(char *p, int p_size) {
	struct timespec ts;

	clock_gettime(CLOCK_REALTIME, &ts);
	memcpy(p, &ts.tv_sec, 4);
	p += 4;
	memset(p, 0, 4);
	p += 4;

	p_size = p_size - 8 - 8;

	for (int i = 0; i < p_size; i++) {
		*p++ = i;
	}
}

void setup_packet(void *p, size_t p_siz, short seq) {
	bzero(p, p_siz);

	icmp_header_t *h = (icmp_header_t *)p;

	h->type	 = ICMP_ECHO;
	h->code	 = 0;
	h->id	 = (short)getpid();
	h->seq	 = (seq >> 8) | (seq << 8);
	h->cksum = 0;

	fill_packet(&h->data, p_siz);

	h->cksum = get_cksum((unsigned short *)p, p_siz);
}

int validate_packet(void *s, void *r, short p_siz) {
	struct icmp *rp = (struct icmp *)(r + 20);	// NOTE: +20 Because of ipv4 header
	struct icmp *sp = (struct icmp *)s;

	if (rp->icmp_type != ICMP_ECHOREPLY) {
		fprintf(stderr, "invalid type %hu\n", rp->icmp_type);
		return 1;
	}
	if (rp->icmp_code != 0) {
		fprintf(stderr, "invalid code\n");
		return 1;
	}
	if (rp->icmp_id != sp->icmp_id) {
		fprintf(stderr, "invalid id\n");
		return 1;
	}
	if (rp->icmp_seq != sp->icmp_seq) {
		fprintf(stderr, "invalid seq\n");
		return 1;
	}
	if (rp->icmp_code != get_cksum((unsigned short *)rp, p_siz)) {
		fprintf(stderr, "invalid cksum\n");
		return 1;
	}

	return 0;
}
