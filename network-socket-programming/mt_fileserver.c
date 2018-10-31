#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> 		//addrinfo structure
#include <errno.h> 		//errno
#include <string.h> 	//memset()
#include <unistd.h> 	//close()
#include <pthread.h> 

#define BUFFER_SIZE 1000
#define BACKLOG 50

pthread_mutex_t mutex;
pthread_t thread;

typedef struct data{
	int currentCon;
	int completedCon;
	int commandRcv;
}D;

D statData = {0, 0, 0};

void* func(void* arg) {
	int recvLen, sendLen;
	char recvFromClient[BUFFER_SIZE], tmp[BUFFER_SIZE], sendBack[BUFFER_SIZE];
	int ss = *((int*) arg);
	
	pthread_t tId = pthread_self();

	printf("*** thread %lu: started ***\n", tId);

	pthread_mutex_lock(&mutex);
	statData.currentCon++;
	pthread_mutex_unlock(&mutex);
	
	while (1) {
		recvLen = recv(ss, recvFromClient, BUFFER_SIZE, 0); 
		if (recvLen < 0) {
			perror("recv");
		}
		
		//process received input
		char *recvProcessed = strtok(recvFromClient, "\n");
		pthread_mutex_lock(&mutex);
		
		printf("*** thread %lu: %s ***\n", tId, recvProcessed);
		
		statData.commandRcv++;

		pthread_mutex_unlock(&mutex);
		if (!strcmp(recvProcessed, "exit")){
			break;
		} else if (!strcmp(recvProcessed, "stats")) {
			sprintf(sendBack, "concurrent connections: %d\ncompleted connections: %d\nnumber of commands received across all clients: %d\n", statData.currentCon, statData.completedCon, statData.commandRcv);
		} else {
			strcat(recvProcessed, " 2>&1");
			FILE *fd;
			if ((fd = popen(recvFromClient, "r")) == NULL){
				perror("popen");
			}
			//recursive writing to the response buffer
			while (fgets(tmp, BUFFER_SIZE, fd)){
				strcat(sendBack, tmp);
			}
			fclose(fd);
		}
				
		//append len to the beginning
		sendLen = strlen(sendBack);
		char sendPrefix[BUFFER_SIZE];
		sprintf(sendPrefix, "%d\n", sendLen);
		strcat(sendPrefix, sendBack);

		if (send(ss, sendPrefix, strlen(sendPrefix), 0) == -1) 
			perror("send");
		
		memset(tmp, 0, sizeof tmp);
		memset(sendBack, 0, sizeof sendBack);
		memset(sendPrefix, 0, sizeof sendPrefix);
		memset(recvFromClient, 0, sizeof recvFromClient);

		printf("--- response %d Byte(s) sent ---\n", sendLen);
		
	}
	printf("*** thread %lu: exited ***\n", tId);

	pthread_mutex_lock(&mutex);
	statData.completedCon++;
	statData.currentCon--;
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

int main(int argc, char** argv){

	if (argc != 1 && argc != 2) {
		fprintf(stderr, "usage: %s [svrport]\n", argv[0]);
		return 1;
	}
	
	printf("CMPE 207 HW3 mtrfmsvr Hanbing Leng 354\n");

	char *serverPort;
	serverPort = (argc == 1) ? "9091" : argv[1];

	int status, s, ss;
	struct addrinfo hints, *res, *p;
	struct sockaddr_in clientAddr;
	char buffer[BUFFER_SIZE];
	char ipstr[INET_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (status = getaddrinfo(NULL, serverPort, &hints, &res) != 0) {
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
	
	pthread_attr_t attr;
	int rc;
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_mutex_init(&mutex, NULL);

	while (1) {
		socklen_t addrlen = sizeof clientAddr;
		ss = accept(s, (struct sockaddr*)&clientAddr, &addrlen);
		if (ss == -1) {
			if (errno = EINTR) 
				continue;
			perror("accept");
			continue;
		}
		
		inet_ntop(AF_INET, &clientAddr.sin_addr, ipstr, INET_ADDRSTRLEN);
		
		printf("=== connection from %s ===\n", ipstr);

		if ((rc = (pthread_create(&thread, &attr, func, (void*)&ss))) != 0){
			perror("pthread_create");
			return 1;
		}		
	}

	pthread_mutex_destroy(&mutex);
	pthread_attr_destroy(&attr);
  pthread_exit(NULL);
	return 0;
}
