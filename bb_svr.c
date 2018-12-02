#include "bb.h"

void do_readwrite(evutil_socket_t fd, short events, void *arg);
// unicast recvfrom and sendto callback function

/*void do_mcast(evutil_socket_t fd, short events, void *arg);*/
// multicast sendto callback funtion

int main(int argc, char** argv) {
	int optval;
	evutil_socket_t sockfd[2]; // [0] for receiving & sending, [2] for multicast sending 
	struct sockaddr_in sevr_addr, cli_addr;
	/*struct ip_mreq mreq;*/
	struct event_base *base;
	struct event *ev_readwrite, *ev_mcast;

	base = event_base_new();
	if (!base)
    	return 1;
	
	memset(&sevr_addr, 0, sizeof sevr_addr);
	memset(&cli_addr, 0, sizeof cli_addr);
	sevr_addr.sin_family = AF_INET;
	sevr_addr.sin_port = htons(SEVR_PORT);
	sevr_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	for (int i = 0; i < 2; i++) {
		evutil_make_socket_nonblocking(sockfd[i]);
		if ((sockfd[i] = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
			perror("socket");
			return 1;
		}
	}
	
	optval = 1;
	setsockopt(sockfd[0], SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));
	setsockopt(sockfd[0], SOL_SOCKET, SO_REUSEPORT, (const void *)&optval , sizeof(int));
	if (bind(sockfd[0], (SA *)&sevr_addr, sizeof sevr_addr) == -1) {
		perror("bind");
		return 1;
	}
	
	ev_readwrite = event_new(base, sockfd[0], EV_READ | EV_PERSIST, do_readwrite, &cli_addr);
	/*ev_mcast = event_new(base, sockfd[1], EV_WRITE | EV_PERSIST, do_mcast, NULL);*/

	event_add(ev_readwrite, NULL);
	/*event_add(ev_mcast, NULL);*/

	event_base_dispatch(base);
	
	return 0;
}

void do_readwrite(evutil_socket_t fd, short events, void *arg) {
	int recv_bytes, send_bytes;
	socklen_t addr_len;
	char recv_buf[BUFFER_SIZE], *send_buf = "server reply!";
	struct sockaddr_in ucast_addr = *((struct sockaddr_in *)arg);
	addr_len = sizeof ucast_addr;
	if ((recv_bytes = recvfrom(fd, recv_buf, sizeof recv_buf, 0, (SA *)&ucast_addr, &addr_len)) == -1) {
		perror("recv_bytes");
		return;
	}
	printf("recved %d bytes: %s ", recv_bytes, recv_buf);
	
	// @todo: command parsing and reply here
	
	if ((send_bytes = sendto(fd, send_buf, strlen(send_buf) + 1, 0, (SA *)&ucast_addr, sizeof ucast_addr)) == -1) {
		perror("sendto");
		return;
	}
	printf("server sent %d\n", send_bytes);
}

/*void do_mcast(evutil_socket_t fd, short events, void *arg);*/
// multicast sendto callback funtion



	/*while (1) {*/
		/*addr_len = sizeof cli_addr;*/
		/*if ((len = recvfrom(sockfd, buf, BUFFER_SIZE, 0, (SA *)&cli_addr, &addr_len)) == -1) {*/
			/*perror("recvfrom");*/
			/*return 1;*/
		/*}*/
		/*[>n = sendto(sockfd, test_repy, strlen(test_repy), 0, (SA *)&cli_addr, sizeof cli_addr);<]*/
		/*printf("%d received\n", len);*/
	/*}*/

