#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>

#define BUFFERSIZE 11000
#define HOST_SIZE 100
#define PATH_SIZE 100
char path[PATH_SIZE];
char host[HOST_SIZE];
	
int parseUrl(char* url) {
	int success = 0;
	if (sscanf(url, "http://%99[^/]/%199[^\n]", host, path) == 2) {
		success = 1; /* http://hostname/page */

	} else if (sscanf(url, "http://%99[^/]/[^\n]", host) == 1) {
		success = 1; /* http://hostname/ */
	} else if (sscanf(url, "http://%99[^\n]", host) == 1) {
		success = 1; /* http://hostname */ 
	}
	return success;
}

int main(int argc, char** argv){
	
	if (argc != 2) {
		fprintf(stderr, "%s%s%s\n", "usage: ", argv[0], " <url>");
		return 1;
	}
	
	if (parseUrl(argv[1]) != 1) {
		fprintf(stderr, "parsing failed"); 
		return 1;
	}

	printf("%s\n", "CMPE 207 HW1 webclient Hanbing Leng 354");

	int status, s, len;
	struct addrinfo hints, *res;
	char buffer[BUFFERSIZE]; //allocate memory for char*
	/*char ipstr[INET_ADDRSTRLEN];*/
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((status = getaddrinfo(host, "http", &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 1;
	}

	/* check IP input
	for (p = res; p != NULL; p = p->ai_next) {
		void *addr;
		struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
		addr = &(ipv4->sin_addr);
		inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
		printf("%s\n", ipstr);
	}
	*/

	if ((s = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
		fprintf(stderr, "cannot create socket\n");
		return 1;
	}

	if ((connect(s, res->ai_addr, res->ai_addrlen)) < 0) {
		fprintf(stderr, "connect() failed\n");
		return 1;
	}

	len = sprintf(buffer, "GET /%s HTTP/1.0\r\n\r\n", path); //GET path
	send(s, buffer, len, 0);
	
	while ((len = recv(s, buffer, BUFFERSIZE, 0)) > 0)
		printf("%s", buffer);
	
	freeaddrinfo(res);
	
	shutdown(s, 2);

	return 0;
}
