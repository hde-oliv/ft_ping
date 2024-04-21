#pragma once

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <uchar.h>
#include <unistd.h>

typedef enum e_flags {
	F_e	   = 0b0000000000000001,
	F_v	   = 0b0000000000000010,
	F_q	   = 0b0000000000000100,
	F_f	   = 0b0000000000001000,
	F_l	   = 0b0000000000010000,
	F_n	   = 0b0000000000100000,
	F_w	   = 0b0000000001000000,
	F_W	   = 0b0000000010000000,
	F_p	   = 0b0000000100000000,
	F_r	   = 0b0000001000000000,
	F_s	   = 0b0000010000000000,
	F_T	   = 0b0000100000000000,
	F_ttl  = 0b0001000000000000,
	F_ip_t = 0b0010000000000000,
} flags_e;

struct s_flag {
	int e : 1;
	int v : 1;
	int q : 1;
	int f : 1;
	int l : 1;
	int n : 1;
	int w : 1;
	int W : 1;
	int p : 1;
	int r : 1;
	int s : 1;
	int T : 1;
	int t : 1;
	int i : 1;
};

typedef union u_flag {
	struct s_flag s;
	int			  n;
} flag_t;

typedef struct s_args {
	flag_t opt;
	int	   preload;	   // -l
	int	   timeout;	   // -w
	int	   linger;	   // -W
	char  *pattern;	   // -p | 16 byte hex
	int	   size;	   // -s
	int	   tos;		   // -T
	int	   ttl;		   // --ttl
	char  *timestamp;  // --ip-timestamp | "tsonly" and "tsaddr"
	char  *hostname;
} args_t;

typedef struct s_loop {
	struct addrinfo *result;
	struct addrinfo *rp;
	struct addrinfo	 hints;
	int				 sockfd;
	char			 ipstr[INET6_ADDRSTRLEN];
} loop_t;

// Parse
int parse_args(int argc, char **argv);

// Debug
void debug_args(void);
void debug_loop(void);
void print_bits(size_t size, void *ptr);

// Run
int run_loop(void);
