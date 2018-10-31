#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> 		//addrinfo structure
#include <errno.h> 		//errno
#include <string.h> 	//memset()
#include <unistd.h> 	//close()

#define BUFFER_SIZE 1000

int main(int argc, char** argv){
	if (argc != 2 && argc != 3) {
		fprintf(stderr, "usage: %s <servername> [svrport]\n", argv[0]);
		return 1;
	}
	
	printf("CMPE 207 HW3 rfmclient Hanbing Leng 354\n");

	char *serverName, *serverPort;
	
	serverName = argv[1];
	serverPort = (argc == 2) ? "9091" : argv[2];
	
	int status, s, len;
	struct addrinfo hints, *res, *p;
	char cmdInput[BUFFER_SIZE], cmdOutput[BUFFER_SIZE];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if ((status = getaddrinfo(serverName, serverPort, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 1;
	}

	for (p = res ; p != NULL; p = p->ai_next) {
		if ((s = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
			perror("socket");
			continue;
		}
		if ((connect(s, p->ai_addr, p->ai_addrlen)) < 0) {
			perror("connect");
			continue;
		}
		break;
	}

	if (p == NULL) {
		fprintf(stderr, "failed to connect\n");
		return 2;
	}

	freeaddrinfo(res);
	
	while (1) {
		char tmp[BUFFER_SIZE], rLen[10];	
		int lenReceived = 0, lenTotal = 1000000;
		size_t inputSize = BUFFER_SIZE;
	
		//read input from command line
		fgets(cmdInput, BUFFER_SIZE, stdin);
		if(!strcmp(cmdInput, "\n")) 
		{
			memset(cmdInput, 0, sizeof cmdInput);
			continue;
		}

		send(s, cmdInput, strlen(cmdInput), 0);
		if(!strcmp(cmdInput, "exit\n")) break;

		//output received from server
		while (lenReceived < lenTotal && (len = recv(s, tmp, BUFFER_SIZE, 0)) > 0 ){
			if (lenReceived == 0) {
				lenTotal = atoi(tmp);
				/*printf("lenTotal: %d\n", lenTotal);*/
			} 
			strcat(cmdOutput, tmp);
			
			lenReceived += strlen(tmp);
			/*printf("lenReceived: %d\n", lenReceived);*/
			memset(tmp, 0, sizeof tmp);
		}

		char* outputProcessed = strpbrk(cmdOutput, "\n");
		memmove(outputProcessed, outputProcessed + 1, strlen(outputProcessed));
		puts(outputProcessed);
		puts("--- client receive finished ---");
		memset(cmdOutput, 0, sizeof cmdOutput);
	}
	
	puts("=== client exiting ===");
	close(s);

	return 0;
}
