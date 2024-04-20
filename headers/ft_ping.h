#pragma once

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

typedef enum e_flags {
	F_e,
	F_v,
	F_q,
	F_f,
	F_l,
	F_n,
	F_w,
	F_W,
	F_p,
	F_r,
	F_s,
	F_T,
	F_ttl,
	F_ip_t,
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

// Parse
int parse_args(int argc, char **argv);

// Debug
void debug_args(void);
