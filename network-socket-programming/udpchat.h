#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> 		//addrinfo structure
#include <errno.h> 		//errno
#include <string.h> 	//memset()
#include <unistd.h> 	//close()
#include <arpa/inet.h>  //const char *inet_ntop
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include <sys/select.h>

#define BUFFER_SIZE 1024

void printTime() {
	time_t timer;
	char buffer[100];
	struct tm* tm_info;

	time(&timer);
	tm_info = localtime(&timer);
	
	strftime(buffer, 100, "%c", tm_info);
	printf("%s", buffer);
}
