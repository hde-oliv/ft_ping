/* #include "ft_ping.h" */

/* void setup(void) { */
/* 	struct addrinfo *result, *rp; */
/* 	struct addrinfo	 hints = { 0 }; */

/* 	char *hostname = "google.com"; */

/* 	int e; */
/* 	int sockfd; */

/* 	char ipstr[INET6_ADDRSTRLEN]; */

/* 	e = getaddrinfo(hostname, NULL, &hints, &result); */

/* 	if (e != 0) { */
/* 		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(e)); */
/* 		exit(EXIT_FAILURE); */
/* 	} */

/* 	for (rp = result; rp != NULL; rp = rp->ai_next) { */
/* 		void *addr; */
/* 		char *ipver; */

/* 		// Get the pointer to the address */
/* 		if (rp->ai_family == AF_INET) {	 // IPv4 */
/* 			struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr; */
/* 			addr					 = &(ipv4->sin_addr); */
/* 			ipver					 = "IPv4"; */
/* 		} else {  // IPv6 */
/* 			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)rp->ai_addr; */
/* 			addr					  = &(ipv6->sin6_addr); */
/* 			ipver					  = "IPv6"; */
/* 		} */

/* 		// Convert the IP to a string and print it */
/* 		inet_ntop(rp->ai_family, addr, ipstr, sizeof ipstr); */
/* 		printf("%s: %s\n", ipver, ipstr); */

/* 		sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol); */

/* 		if (sockfd == -1) { */
/* 			perror("socket"); */
/* 			continue; */
/* 		} */

/* 		e = connect(sockfd, rp->ai_addr, rp->ai_addrlen); */

/* 		printf("%d\n", e); */

/* 		if (e == 0) { */
/* 			break; */
/* 		} else { */
/* 			fprintf(stderr, "connect: %d\n", e); */
/* 		} */

/* 		close(sockfd); */
/* 	} */

/* 	if (rp == NULL) { */
/* 		fprintf(stderr, "could not bind\n"); */
/* 		exit(EXIT_FAILURE); */
/* 	} */

/* 	e = sendto(sockfd, &packet, sizeof(packet), 0, rp->ai_addr, rp->ai_addrlen); */

/* 	printf("sendto: %d\n", e); */

/* 	char buf[sizeof(packet)]; */

/* 	e = recvfrom(sockfd, buf, sizeof(packet), 0, rp->ai_addr, &rp->ai_addrlen); */

/* 	printf("recvfrom: %d | %s\n", e, buf); */

/* 	freeaddrinfo(result); */
/* } */
