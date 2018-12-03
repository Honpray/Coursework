#include "bb.h"

/*#define CLI_DEBUG*/

void do_uread(evutil_socket_t fd, short events, void *arg);
//unicast recvfrom callback function

void do_mread(evutil_socket_t fd, short events, void *arg);
// multicast recvfrom callback function

void do_writeread(evutil_socket_t fd, short events, void *arg);
// unicast sendto callback funtion

int main(int argc, char **argv) {
	int optval;
	evutil_socket_t sockfd[2]; // [0] for mread, [1] for write and read
	char *sevr_addr;
	struct sockaddr_in uc_addr, mc_addr, any_addr;
	struct ip_mreq mreq;
	struct event_base *base;
	struct event *ev_uread, *ev_mread, *ev_writeread;
	struct timeval tv;
	base = event_base_new();
	if (!base)
    	return 1;
	
	tv.tv_sec = 1;
	tv.tv_usec = 0;
#ifdef CLI_DEBUG
	sevr_addr = "127.0.0.1";
#else
	if (argc != 2) {
		fprintf(stderr, "usage: bb-cli <IPaddress>\n");
		return 1;
	}
	sevr_addr = argv[1];
#endif
	
	memset(&uc_addr, 0, sizeof uc_addr);
	memset(&mc_addr, 0, sizeof mc_addr);
	uc_addr.sin_family = AF_INET;
	inet_pton(AF_INET, sevr_addr, &uc_addr.sin_addr);
	uc_addr.sin_port = htons(SEVR_PORT);
	mc_addr.sin_family = AF_INET;
	mc_addr.sin_addr.s_addr = INADDR_ANY; // accept from any network
	mc_addr.sin_port = htons(MC_PORT);

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
	if (bind(sockfd[0], (SA *)&mc_addr, sizeof mc_addr) != 0) {
		perror("bind");
		return 1;
	}
	setsockopt(sockfd[1], SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));
	setsockopt(sockfd[1], SOL_SOCKET, SO_REUSEPORT, (const void *)&optval , sizeof(int));
	if (bind(sockfd[1], (SA *)&mc_addr, sizeof mc_addr) != 0) {
		perror("bind");
		return 1;
	}
	
	mreq.imr_multiaddr.s_addr = inet_addr(MC_ADDR);
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);

	if (setsockopt(sockfd[0], IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof mreq) < 0) {
		perror("setsockopt");
		return 1;
	}

	ev_uread = event_new(base, sockfd[1], EV_READ | EV_PERSIST, do_uread, NULL);
	ev_mread = event_new(base, sockfd[0], EV_READ | EV_PERSIST, do_mread, &mc_addr);
	ev_writeread = event_new(base, STDIN_FILENO, EV_READ | EV_PERSIST, do_writeread, &uc_addr);
	/*ev_writeread = event_new(base, sockfd[1], EV_WRITE | EV_PERSIST, do_writeread, &uc_addr);*/

	/*event_add(ev_uread, NULL);*/
	event_add(ev_mread, NULL);
	event_add(ev_writeread, &tv);

	event_base_dispatch(base);
	
	return 0;
}

void do_uread(evutil_socket_t fd, short events, void *arg) {
	puts("!");
	int recv_bytes;
	/*socklen_t addr_len;*/
	char recv_buf[BUFFER_SIZE];
	/*struct sockaddr_in ucast_addr = *((struct sockaddr_in *)arg);*/
	/*addr_len = sizeof ucast_addr;*/
	if ((recv_bytes = recvfrom(fd, recv_buf, sizeof recv_buf, 0, NULL, NULL)) == -1) {
		perror("recv_bytes");
		return;
	}
	recv_buf[recv_bytes] = 0;
	printf("from server: %s", recv_buf);
}

void do_mread(evutil_socket_t fd, short events, void *arg) {
	int recv_bytes;
	socklen_t addr_len;
	char recv_buf[BUFFER_SIZE];
	struct sockaddr_in mcast_addr = *((struct sockaddr_in *)arg);
	addr_len = sizeof mcast_addr;
	if ((recv_bytes = recvfrom(fd, recv_buf, sizeof recv_buf, 0, (SA *)&mcast_addr, &addr_len)) == -1) {
		perror("recv_bytes");
		return;
	}
}

void do_writeread(evutil_socket_t fd, short events, void *arg) {
	int sfd, send_bytes, recv_bytes;
	socklen_t addr_len;
	char *input, recv_buf[BUFFER_SIZE];
	struct sockaddr_in ucast_addr = *((struct sockaddr_in *)arg);
	input = readline("> ");
	
	sfd = socket(AF_INET, SOCK_DGRAM, 0);

	if ((send_bytes = sendto(sfd, input, strlen(input) + 1, 0, (SA *)&ucast_addr, sizeof ucast_addr)) == -1) {
		perror("sendto");
		return;
	}
	printf("sent %d\n", send_bytes);

	// @todo: parse input as different command
	addr_len = sizeof ucast_addr;
	if ((recv_bytes = recvfrom(sfd, recv_buf, sizeof recv_buf, 0, (SA *)&ucast_addr, &addr_len)) == -1) {
		perror("recv_bytes");
		return;
	}
	printf("recved %d bytes: %s from server\n", recv_bytes, recv_buf);
	close(sfd);
}
