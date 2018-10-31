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

	printf("%s\n\n", "CMPE 207 HW2 webclient-post Hanbing Leng 354");

	int status, s, len, hostname_len;
	struct addrinfo hints, *res, *p;
	char buffer[BUFFERSIZE]; //allocate memory for char*
	/*char hostname[100], servicename[100];*/

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET; //ipv4
	hints.ai_socktype = SOCK_STREAM;

	if ((status = getaddrinfo(host, "http", &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 1;
	}

	for (p = res ; p != NULL; p = p->ai_next){
		if ((s = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
			/*fprintf(stderr, "cannot create socket\n");*/
			perror("socket");
			continue;
	}

		if ((connect(s, p->ai_addr, p->ai_addrlen)) < 0) {
			/*fprintf(stderr, "connect() failed\n");*/
			perror("connect");
			continue;
		}
		break;
	}

	if (p == NULL) {
		fprintf(stderr, "failed to connect\n");
		return 2;
	}
	
	/*if (gethostname(hostname, sizeof hostname) < 0) {*/
		/*fprintf(stderr, "gethostname() failed\n");*/
		/*return 1;*/
	/*}*/

	/*printf("My hostname: %s\n", hostname);*/
 	
	/********************identify Client IP address and Port number*********************/
	struct sockaddr_storage localaddr;
	socklen_t localaddr_len;
	/*localaddr_len = sizeof localaddr_len;*/
	localaddr_len = sizeof localaddr;
	char localip[INET6_ADDRSTRLEN];
	int port;

	getsockname(s, (struct sockaddr*)&localaddr, &localaddr_len);
	if (localaddr.ss_family == AF_INET) {
		struct sockaddr_in *sk = (struct sockaddr_in *)&localaddr;
		port = ntohs(sk->sin_port);
		inet_ntop(AF_INET, &sk->sin_addr, localip, sizeof localip);
	} else {
		struct sockaddr_in6 *sk = (struct sockaddr_in6 *)&localaddr;
		port = ntohs(sk->sin6_port);
		inet_ntop(AF_INET6, &sk->sin6_addr, localip, sizeof localip);
	}
	/*printf("Local IP: %s\n", localip);*/
	/*printf("Local port: %d\n", port);*/
	/********************identify Client IP address and Port number END******************/
	
	/* getnameinfo(res->ai_addr, res->ai_addrlen, hostname, sizeof hostname, servicename, sizeof servicename, 0);*/
	/*printf("host: %s\n", hostname);*/
	/*printf("service: %s\n", servicename);*/

	len = sprintf(buffer, "POST /%s HTTP/1.0\r\n\r\nClientID=%s\nClientPort=%d", path, localip, port);
	printf("HTTP Post Request which is sent to server:\n%s\n\n", buffer);
	/*printf("bufferlen: %d\n", len);*/

	send(s, buffer, len, 0);
	
	printf("HTTP Post Response recieved from server:\n");

	while ((len = recv(s, buffer, BUFFERSIZE, 0)) > 0)
		printf("%s", buffer);
	
	freeaddrinfo(res);
	
	shutdown(s, 2);

	return 0;
}
