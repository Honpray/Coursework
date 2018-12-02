#include "bb.h"

#define CLI_DEBUG

void do_read(evutil_socket_t fd, short events, void *arg);
// multicast & unicast recvfrom callback function

void do_write(evutil_socket_t fd, short events, void *arg);
// unicast sendto callback funtion


int main(int argc, char **argv) {
	int optval;
	evutil_socket_t sockfd[2]; // [0] for reading, [1] for writing
	char *sevr_addr;
	struct sockaddr_in uc_addr, mc_addr;
	struct ip_mreq mreq;
	struct event_base *base;
	struct event *ev_read, *ev_write;

	base = event_base_new();
	if (!base)
    	return 1;
	
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
	uc_addr.sin_port = htons(SEVR_PORT);
	inet_pton(AF_INET, sevr_addr, &uc_addr.sin_addr);
	mc_addr.sin_family = AF_INET;
	mc_addr.sin_port = htons(SEVR_PORT);
	mc_addr.sin_addr.s_addr = INADDR_ANY;

	for (int i = 0; i < 2; i++) {
		evutil_make_socket_nonblocking(sockfd[i]);
		if ((sockfd[i] = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
			perror("socket");
			return 1;
		}
	}
	
	optval = 1;
	setsockopt(sockfd[1], SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));
	if (bind(sockfd[1], (SA *)&mc_addr, sizeof mc_addr) != 0) {
		perror("bind");
		return 1;
	}
	
	mreq.imr_multiaddr.s_addr = inet_addr("MC_GROUP");
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);

	if (setsockopt(sockfd[1], IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof mreq) < 0) {
		perror("setsockopt");
		return 1;
	}

	ev_read= event_new(base, sockfd[0], EV_READ | EV_PERSIST, do_read, &mc_addr);
	ev_write = event_new(base, sockfd[1], EV_WRITE | EV_PERSIST, do_write, NULL);

	event_add(ev_read, NULL);
	event_add(ev_write, NULL);

	event_base_dispatch(base);
	
	return 0;
}
	
void do_read(evutil_socket_t fd, short events, void *arg) {
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

void do_write(evutil_socket_t fd, short events, void *arg) {
	int sent_bytes;
	char *input;
	struct sockaddr_in ucast_addr = *((struct sockaddr_in *)arg);
	input = readline("> ");
	if ((sent_bytes = sendto(fd, input, strlen(input) + 1, 0, (SA *)&ucast_addr, sizeof ucast_addr)) == -1) {
		perror("sendto");
		return;
	}
	printf("%d\n", sent_bytes);

	// @todo: parse input as different command
}
