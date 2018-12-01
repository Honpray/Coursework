#include "bb.h"

int main(int argc, char** argv) {
	int sockfd, len, n, addr_len, optval;
	char* test_repy = "Msg rcved", buf[BUFFER_SIZE];
	struct sockaddr_in sevr_addr, cli_addr, uc_addr_svr, mc_addr_svr;
	
	memset(&sevr_addr, 0, sizeof sevr_addr);
	/*memset(&uc_addr_svr, 0, sizeof uc_addr_svr);*/
	/*memset(&mc_addr_svr, 0, sizeof mc_addr_svr);*/

	sevr_addr.sin_family = AF_INET;
	sevr_addr.sin_port = htons(SEVR_PORT);
	sevr_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	/*sockfd = socket(AF_INET, SOCK_DGRAM, 0);*/
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		return 1;
	}

	optval = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));

	if (bind(sockfd, (SA *)&sevr_addr, sizeof sevr_addr) == -1) {
		perror("bind");
		return 1;
	}

	while (1) {
		addr_len = sizeof cli_addr;
		if ((len = recvfrom(sockfd, buf, BUFFER_SIZE, 0, (SA *)&cli_addr, &addr_len)) == -1) {
			perror("recvfrom");
			return 1;
		}
		/*n = sendto(sockfd, test_repy, strlen(test_repy), 0, (SA *)&cli_addr, sizeof cli_addr);*/
		printf("%d received\n", len);
	}

	return 0;
}
