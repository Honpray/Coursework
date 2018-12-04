#include "bb.h"
#include "pygsheets.h"

static struct event *ev_readwrite, *ev_mcast;
static struct timeval tv;

struct mc_arg {
	char *msg;
	struct sockaddr_in dest_addr;
};

static struct mc_arg *mcast_arg = NULL;

void do_readwrite(evutil_socket_t fd, short events, void *arg);
// unicast recvfrom and sendto callback function

void do_mcast(evutil_socket_t fd, short events, void *arg);
// multicast sendto callback funtion

int main(int argc, char** argv) {
	int optval;
	evutil_socket_t sockfd[2]; // [0] for receiving & sending, [1] for multicast sending 
	struct sockaddr_in sevr_addr, cli_addr;
	/*struct ip_mreq mreq;*/
	struct event_base *base;
	/*struct event *ev_readwrite, *ev_mcast;*/
	mcast_arg = malloc(sizeof(struct mc_arg));
	mcast_arg->msg = "Server multicasting";
	/*Py_Initialize();*/
	/*printf("%s\n", p_get_cell("B2"));*/

	base = event_base_new();
	if (!base)
    	return 1;
	
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	memset(&sevr_addr, 0, sizeof sevr_addr);
	memset(&cli_addr, 0, sizeof cli_addr);
	sevr_addr.sin_family = AF_INET;
	sevr_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	sevr_addr.sin_port = htons(SEVR_PORT);
	mcast_arg->dest_addr.sin_family = AF_INET;
	mcast_arg->dest_addr.sin_port = htons(MC_PORT);
	inet_pton(AF_INET, MC_ADDR, &(mcast_arg->dest_addr).sin_addr);

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
	ev_mcast = event_new(base, sockfd[1], EV_READ, do_mcast, mcast_arg);
	


	event_add(ev_readwrite, NULL);
	event_add(ev_mcast, &tv);

	event_base_dispatch(base);
	
	/*Py_Finalize();*/
	return 0;
}

void do_readwrite(evutil_socket_t fd, short events, void *arg) {
	int recv_bytes, send_bytes;
	socklen_t addr_len;
	char recv_buf[BUFFER_SIZE], *send_buf, *cmd, *target, content[BUFFER_SIZE];
	struct sockaddr_in ucast_addr = *((struct sockaddr_in *)arg);
	addr_len = sizeof ucast_addr;

	send_buf = "Server is on!";
	if ((recv_bytes = recvfrom(fd, recv_buf, sizeof recv_buf, 0, (SA *)&ucast_addr, &addr_len)) == -1) {
		perror("recv_bytes");
		return;
	}
	recv_buf[recv_bytes] = 0;
	printf("\e[3mrecved %2d bytes\e[0m \033[32;1m%s\033[0m from ", recv_bytes, recv_buf);
	
	// print client ip info
	char str[INET_ADDRSTRLEN];
	int clientPort = ntohs(ucast_addr.sin_port);
	inet_ntop(AF_INET, &ucast_addr.sin_addr, str, INET_ADDRSTRLEN);
	printf("%s:%d \n", str, clientPort);

	// parse the command
	cmd = strtok(recv_buf, " ");
	if (cmd != NULL) {
		target = strtok(NULL, " ");
		/*printf("target: %s\n", target);*/
	}
 if (cmd != NULL && target != NULL) {
		int pos =  strlen(cmd) + strlen(target) + 2;
		int len = recv_bytes - pos;

		memcpy(content, &recv_buf[pos], len);
		content[len] = '\0';
		/*printf("content: %s\n", content);*/
	}
	
	
	// fork here
	
	/*sleep(1);*/
	// send back general message 
	if ((send_bytes = sendto(fd, send_buf, strlen(send_buf) + 1, 0, (SA *)&ucast_addr, sizeof ucast_addr)) == -1) {
		perror("sendto");
		return;
	}
	/*printf("server sent %d \n", send_bytes);*/
	
	// *** post ***
	if (cmd != NULL && !strcmp(cmd, "post")) {
		mcast_arg->msg = content;
		event_active(ev_mcast, EV_READ, 0);
	}
	
}

void do_mcast(evutil_socket_t fd, short events, void *arg) {
	int send_bytes;
	/*struct sockaddr_in mcast_addr = *((struct sockaddr_in *)arg);*/
	struct mc_arg mcast_arg_cb = *((struct mc_arg *)arg);
	char *send_buf = mcast_arg_cb.msg;
	/*printf("%s", send_buf);*/

	if ((send_bytes = sendto(fd, send_buf, strlen(send_buf) + 1, 0, (SA *)&(mcast_arg_cb.dest_addr), sizeof(struct sockaddr_in) )) == -1) {
		perror("sendto");
		return;
	}
	printf("%smcast msg sent!%s\n", COLOR_RED, COLOR_NORMAL);
	event_del(ev_mcast);
}
