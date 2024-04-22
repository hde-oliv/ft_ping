#include "ft_ping.h"

extern args_t args;
extern loop_t loop;

void run_loop(void) {
	struct timespec start, end;
	int				PACKET_SIZE = 64;
	char			packet[PACKET_SIZE];
	char			response[PACKET_SIZE + 20];	 // NOTE: +20 Because of ivp4 header

	setup_socket();
	print_info();

	for (int i = 0;; i++) {
		setup_packet(packet, PACKET_SIZE, i);
		send_packet(&start, packet, PACKET_SIZE);
		read_packet(&end, response, PACKET_SIZE + 20);
		validate_packet(packet, response, PACKET_SIZE);
		update_time(&start, &end);
		print_response(response, i, PACKET_SIZE);
		usleep(SECOND);
	}

	clear();
	exit(0);
}
