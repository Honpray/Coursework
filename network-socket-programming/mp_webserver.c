#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> 		//addrinfo structure
#include <errno.h> 		//errno
#include <string.h> 	//memset()
#include <unistd.h> 	//close()
#include <signal.h>

#define PORT "http"
#define BACKLOG 100 		//queue length
#define BUFFERSIZE 11000

//reaper function
void sigchld_handler(int s) {
	int saved_errno = errno; //errno may be overwriten by waitpid()
	while (waitpid(-1, NULL, WNOHANG) > 0);
	errno = saved_errno;
}

int main(void) {
	int s, status, new_s, http_response_len, recv_len;
	char ipstr[INET_ADDRSTRLEN];
	struct addrinfo hints, *res, *p;
	struct sockaddr_in client_addr;
	socklen_t addrlen;
	struct sigaction sa;
	char response_buffer[BUFFERSIZE], recv_buffer[BUFFERSIZE];

	printf("CMPE 207 HW2 mpwebsvr Hanbing Leng 354\n");

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (status = getaddrinfo(NULL, PORT, &hints, &res) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 1;
	}

	for (p = res; p != NULL; p = p->ai_next) {
		if ((s = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("socket");
			continue;
		}

		if (bind(s, p->ai_addr, p->ai_addrlen) == -1) {
			close(s);
			perror("bind");
			continue;
		}
		break;
	}

	freeaddrinfo(res);

	if (p == NULL) {
		fprintf(stderr, "failed to bind");
		return 1;
	}

	if (listen(s, BACKLOG) == -1) {
		perror("listen");
		return 1;
	}
	
	

	sa.sa_handler = sigchld_handler;
	sigemptyset(&sa.sa_mask); //initializes signalmask to empty

	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("sigaction");
		return 1;
	}
	
	printf("waiting for connections...\n");

	while (1) {
		addrlen = sizeof client_addr;
		new_s = accept(s, (struct sockaddr*)&client_addr, &addrlen);
		if (new_s == -1) {
			if (errno = EINTR) 
				continue;
			perror("accept");
			continue;
		}
		
		inet_ntop(AF_INET, &client_addr, ipstr, INET_ADDRSTRLEN);
		
		printf("connection from %s\n", ipstr);

		if (!fork()) { //child process
			close(s);
			
			int server_pid = (int)getpid();
			
			struct sockaddr_in peeraddr;
			socklen_t peeraddr_len;
			peeraddr_len = sizeof peeraddr;
			char peerip[INET_ADDRSTRLEN];
			int peerport;

			getpeername(new_s, (struct sockaddr*)&peeraddr, &peeraddr_len);
			inet_ntop(AF_INET, &peeraddr.sin_addr, peerip, INET_ADDRSTRLEN); // peeraddr.sin_addr
			peerport = ntohs(peeraddr.sin_port);
			
			printf("server-pid=%d, client-ip=%s, client-port=%d\n", server_pid, peerip, peerport);
			
			if ((recv_len = recv(new_s, recv_buffer, BUFFERSIZE, 0)) < 0) {
				perror("recv");
				return 1;
			}
			//no recursive read needed?

			http_response_len = sprintf(response_buffer, "HTTP/1.1 200 OK\r\nClientID: %s\nClientPort: %d\n\r\n<!DOCTYPE html>\n<html><body><blockquote>\n%s\n</blockquote></body></html>\n", peerip, peerport, recv_buffer);

			if (send(new_s, response_buffer, http_response_len, 0) == -1) 
				perror("send");
			
			sleep(30);	
			
			close(new_s);
			
			return 0;
		}
		close(new_s);
	}
	return 0;
}
