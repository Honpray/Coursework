#include "bb.h"
#include "rtt.h"

#define CLI_DEBUG

int main(int argc, char** argv) {
	int sockfd, status;
	char *input, *sevraddr;
	struct addrinfo hints, *res, *p;

#ifdef CLI_DEBUG
	sevraddr = "localhost";
#else
	if (argc != 2) {
		fprintf(stderr, "usage: bb-cli <IPaddress>\n");
		return 1;
	}
	sevraddr = argv[1];
#endif

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	
	if ((status = getaddrinfo(sevraddr, SEVR_PORT_STR, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 1;
	}
		
	for (p = res; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("socket");
			continue;
		}
		break;
	}

	if (p == NULL) {
		fprintf(stderr, "failed to connect\n");
		return 1;
	}
	
	freeaddrinfo(res);
	
	while (1) {
		input = readline("> ");
		printf("%s\n", input);

		// @todo: client processing loop here



	}
	
	return 0;
}
