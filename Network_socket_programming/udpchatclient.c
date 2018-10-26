#include "udpchat.h"

int main(int argc, char** argv){
	
	int status, sockfd, recvLen, sentLen;
	struct addrinfo hints, *res, *p;
	char msg[BUFFER_SIZE], recvBuffer[BUFFER_SIZE], serverIp[INET_ADDRSTRLEN]; 
	
	fd_set readfds, writefds;

	if (argc != 2 && argc != 3) {
		fprintf(stderr, "usage: %s <servername> [svrport]\n", argv[0]);
		return 1;
	}
	
	printf("CMPE 207 HW4 udpchatclient Hanbing Leng 354\n");

	char *serverName, *serverPort;

	serverName = argv[1];
	serverPort = (argc == 2) ? "9091" : argv[2];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	if ((status = getaddrinfo(serverName, serverPort, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 1;
	}
	
	for (p = res; p != NULL; p = p->ai_next){
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("socket");
			continue;
		}
		
	   /* if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {*/
			/*perror("bind");*/
			/*continue;*/
		/*}*/
		break;
	}

	if (p == NULL) {
		fprintf(stderr, "failed to connect\n");
		return 1;
	}
	
	freeaddrinfo(res);
	
	while(1) {
		FD_ZERO(&readfds);
		FD_SET(sockfd, &readfds);
		FD_SET(STDIN_FILENO, &readfds);
		
		/*FD_ZERO(&writefds);*/
		/*FD_SET(sockfd, &writefds);*/
	
		select(sockfd + 1, &readfds, NULL, NULL, 0);
		
		if (FD_ISSET(sockfd, &readfds)) {
			if ((recvLen = recvfrom(sockfd, recvBuffer, BUFFER_SIZE - 1, 0, p->ai_addr, &p->ai_addrlen)) < 0) {
				fprintf(stderr, "recvfrom() failed");
				return 1;
			}
			recvBuffer[BUFFER_SIZE] = '\0';
			printTime();	
			printf(", <%s>: %s", inet_ntop(AF_INET, &(((struct sockaddr_in*)(p->ai_addr))->sin_addr), serverIp, INET_ADDRSTRLEN), recvBuffer);

			if (strcmp(recvBuffer, "<<Server Busy>>\n") == 0)
				return 0;

			/*puts("Message received from server:");*/
			FD_CLR(sockfd, &readfds);
			memset(recvBuffer, 0, sizeof recvBuffer);
		}
	
		if (FD_ISSET(STDIN_FILENO, &readfds)) {
			char testmsg[BUFFER_SIZE];
		
			fgets(testmsg, BUFFER_SIZE, stdin);

			if ((sentLen = sendto(sockfd, testmsg, strlen(testmsg), 0, p->ai_addr, p->ai_addrlen)) == -1) {
				fprintf(stderr, "Error %d: ", errno);
				perror("sendto");
				return 1;
			}

			/*printf("Sent %d Bytes\n", sentLen);*/
			
			FD_CLR(STDIN_FILENO, &readfds);
		}
	
		
	} //end while

	close(sockfd);

	return 0;
}
