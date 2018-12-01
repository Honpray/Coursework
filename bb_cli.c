#include "bb.h"

#define CLI_DEBUG

int main(int argc, char** argv) {
	int sockfd, sent_bytes, optval;
	char *input, *sevr_addr, buf[BUFFER_SIZE];
	struct sockaddr_in uc_addr, mc_addr;
	struct ip_mreq mreq;

#ifdef CLI_DEBUG
	sevr_addr = "127.0.0.1";
#else
	if (argc != 2) {
		fprintf(stderr, "usage: bb-cli <IPaddress>\n");
		return 1;
	}
	sevr_addr = argv[1];
#endif
	
	memset(&uc_addr, 0, sizeof uc_addr);
	/*memset(&mc_addr, 0, sizeof mc_addr);*/
	
	uc_addr.sin_family = AF_INET;
	uc_addr.sin_port = htons(SEVR_PORT);
	inet_pton(AF_INET, sevr_addr, &uc_addr.sin_addr);

    /*mc_addr.sin_family = AF_INET;*/
	/*mc_addr.sin_port = htons(SEVR_PORT);*/
	/*mc_addr.sin_addr.s_addr = INADDR_ANY;*/
	
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		return 1;
	}

	// if for multicast, call bind()

	while (1) {
		input = readline("> ");

		// Parse input as different command
		// Use libevent for Asyc IO here

		// unicast sendto()
		
		if ((sent_bytes = sendto(sockfd, input, strlen(input) + 1, 0, (SA *)&uc_addr, sizeof uc_addr)) == -1) {
			perror("sendto");
			return 1;
		}
		printf("%d\n", sent_bytes);
		
		// multicast recvfrom()
		
		/*optval = 1;*/
		/*setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));*/

		/*if (bind(sockfd, (SA *)&mc_addr, sizeof mc_addr) != 0) {*/
			/*perror("bind");*/
			/*return 1;*/
		/*}*/

		/*mreq.imr_multiaddr.s_addr = inet_addr("MC_GROUP");*/
		/*mreq.imr_interface.s_addr = htonl(INADDR_ANY);*/
		/*if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof mreq) < 0) {*/
			/*perror("setsockopt");*/
			/*return 1;*/
		/*}*/

	}
	
	return 0;
}
