#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> 		//addrinfo structure
#include <errno.h> 		//errno
#include <string.h> 	//memset()
#include <unistd.h> 	//close()
#include <time.h>

#define BUFFERSIZE 512

void printCurrentTime() {
	time_t current_time;
	current_time = time(NULL);
	printf("UTC %s", asctime(gmtime(&current_time)));
}

int main(int argc, char** argv){
	
	if (argc != 4) {
		fprintf(stderr, "%s%s%s\n", "usage: ", argv[0], " <host> <port> <msg>");
		return 1;
	}

	int status, s, len;
	struct addrinfo hints, *res;
	
	char *msg = argv[3], buffer[BUFFERSIZE]; 
	//allocate memory for char*; typeof msg = char *, type of argv[3] = char *, incompatible pointer type
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET; //no ipv6:7 exists
	hints.ai_socktype = SOCK_DGRAM;

	if ((status = getaddrinfo(argv[1], argv[2], &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 2;
	}

	if ((s = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
		fprintf(stderr, "cannot create socket\n");
		return 3;
	}
	
	if (sendto(s, msg, strlen(msg), 0, res->ai_addr, res->ai_addrlen) < 0) {
		fprintf(stderr, "Error %d: ", errno);
		perror("sendto() failed");
		return 4;
	}

	if ((len = recvfrom(s, buffer, BUFFERSIZE, 0, res->ai_addr, &res->ai_addrlen)) < 0) {
		fprintf(stderr, "recvfrom() failed");
		return 5;
	}

	printCurrentTime();
	printf("%d Bytes received: ", len);
	printf("%s\n", buffer);

	freeaddrinfo(res);
	
	close(s);

	return 0;
}
