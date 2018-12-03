/* Headers. */

#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netdb.h> 
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <setjmp.h>
#include <string.h>
#include <sys/uio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>

#include "rtt.h"

#define BUFFER_SIZE 1024
#define SEVR_PORT 9091
#define SEVR_PORT_STR "9091"
#define MC_ADDR "224.0.0.1"
#define MC_PORT 6666
#define MC_PORT_STR "6666"

#define SA 	struct sockaddr
