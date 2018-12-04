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

#define COLOR_RED "\033[0;31m"
#define COLOR_REDB "\033[1;31m"
#define COLOR_NORMAL "\033[0m"
#define COLOR_GREEN "\033[32;1m"
#define COLOR_GREY "\033[37;1m"
#define COLOR_YELLOW "\033[33;1m"
#define COLOR_BLUE "\033[34;1m"
#define COLOR_MAGENTA "\033[35;1m"
#define COLOR_CYAN "\033[36;1m"
#define COLOR_LCYAN "\033[0;36m"
#define COLOR_INVERSE "\033[7m"

#define TEXT_BOLD "\e[1m]"
#define TEXT_NORMAL "\e[0m]"
#define TEXT_ITALIC "\e[3m]"
#define TEXT_UNDERLINE "\e[4m]"

