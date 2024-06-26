#pragma once

#include <arpa/inet.h>
#include <asm-generic/errno.h>
#include <bits/time.h>
#include <errno.h>
#include <math.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <uchar.h>
#include <unistd.h>

#define SECOND 1000000
#define MILLION 1000000

#define CYAN "\033[0;36m"
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define RESET "\033[0m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"

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

typedef struct s_stats {
	double min;
	double max;
	double avg;
	double dev;
	double last;
	short  send;
	short  recv;
	double sq;
	double tl;
	short  runs;
} stats_t;

typedef struct s_loop {
	struct addrinfo *result;
	struct addrinfo *rp;
	struct addrinfo	 hints;
	int				 sockfd;
	char			 ipstr[INET6_ADDRSTRLEN];
	stats_t			 stats;
} loop_t;

typedef struct s_icmp {
	char  type;
	char  code;
	short cksum;
	short id;
	short seq;
	char  data;
} icmp_header_t;

// Parse
int parse_args(int argc, char **argv);

// Debug
void debug_args(void);
void debug_loop(void);
void print_bytes(int size, void *ptr);
void print_bits(int size, void *ptr);

// Loop
void run_loop(void);

// Packet
void setup_packet(void *p, size_t p_siz, short seq);
void validate_packet(void *s, void *r, short p_siz);
void send_packet(void *time, void *packet, int p_siz);
void read_packet(void *time, void *packet, int p_siz);

// Socket
void setup_socket(void);

// Panic
void panic(char *func);

// Print
void print_response(void *res, short seq, int p_siz);
void print_info(void);
void print_statistics(void);
void print_help(void);

// Clear
void clear(void);

// Time
void update_time(void *s, void *e);

// Signal
int signal_setup(void);
