#include "udpchat.h"

int main(int argc, char** argv){

	int status, sockfd, recvBytes, sentBytes, connected;
	struct addrinfo hints, *res, *p;
	struct sockaddr_in clientAddr, otherClientAddr;
	char clientIp[INET_ADDRSTRLEN], recvBuf[BUFFER_SIZE];
	socklen_t addrLen;
	int clientPort;

	addrLen = sizeof clientAddr;

	fd_set readfds, writefds;


	if (argc != 1 && argc != 2) {
		fprintf(stderr, "usage: %s [svrport]\n", argv[0]);
		return 1;
	}
	
	printf("CMPE 207 HW4 udpchatsvr Hanbing Leng 354\n");

	char *serverPort;
	
	serverPort = (argc == 1) ? "9091" : argv[1];
	

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;

	if ((status = getaddrinfo(NULL, serverPort, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 1;
	}

	for (p = res; p != NULL; p = p->ai_next){
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("socket");
			continue;
		}
		
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			perror("bind");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "failed to connect\n");
		return 1;
	}

	freeaddrinfo(res);

	connected = 0;
	
	while(1) {
		//use copy
		FD_ZERO(&readfds);
		FD_SET(sockfd, &readfds);
		FD_SET(STDIN_FILENO, &readfds);
		

		/*FD_ZERO(&writefds);*/
		/*FD_SET(sockfd, &writefds);*/
	
		select(sockfd + 1, &readfds, NULL, NULL, 0);

		if (FD_ISSET(sockfd, &readfds) && !connected) {
				if ((recvBytes = recvfrom(sockfd, recvBuf, BUFFER_SIZE - 1, 0, (struct sockaddr*)&clientAddr, &addrLen)) == -1) {
					perror("recvfrom");
					return 1;
				} 

				connected = 1;
				clientPort = ntohs(clientAddr.sin_port);

				recvBuf[recvBytes] = '\0';
				printTime();	
				printf(", <%s:%d>: %s", inet_ntop(AF_INET, &clientAddr.sin_addr, clientIp, INET_ADDRSTRLEN), ntohs(clientAddr.sin_port), recvBuf);
				FD_CLR(sockfd, &readfds);	
			}
			
		else if (FD_ISSET(sockfd, &readfds) && connected) {
				if ((recvBytes = recvfrom(sockfd, recvBuf, BUFFER_SIZE - 1, 0, (struct sockaddr*)&otherClientAddr, &addrLen)) == -1) {
					perror("recvfrom");
					return 1;
				}

				if (clientPort == ntohs(otherClientAddr.sin_port)) {
recvBuf[recvBytes] = '\0';
				printTime();	
				printf(", <%s:%d>: %s", inet_ntop(AF_INET, &clientAddr.sin_addr, clientIp, INET_ADDRSTRLEN), ntohs(clientAddr.sin_port), recvBuf);

				} 
				else {
					char busymsg[20] = "<<Server Busy>>\n";

					if ((sentBytes = sendto(sockfd, busymsg, strlen(busymsg), 0, (struct sockaddr*)&otherClientAddr, addrLen)) == -1) {
					fprintf(stderr, "Error %d: ", errno);
					perror("sendto");
					return 1;

					}
				
				}
			}
		if (FD_ISSET(STDIN_FILENO, &readfds)) {
			char testmsg[BUFFER_SIZE];
		
			fgets(testmsg, BUFFER_SIZE, stdin);
			
			if ((sentBytes = sendto(sockfd, testmsg, strlen(testmsg), 0, (struct sockaddr*)&clientAddr, addrLen)) == -1) {
				fprintf(stderr, "Error %d: ", errno);
				perror("sendto");
				return 1;
			}

			/*printf("Sent %d Bytes\n", sentBytes);*/
			FD_CLR(STDIN_FILENO, &readfds);
		}

	} //end while

		

	close(sockfd);

	return 0;
}
