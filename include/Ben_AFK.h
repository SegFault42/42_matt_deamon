#ifndef BEN_AFK_H
#define BEN_AFK_H

#include <iostream>
#include <string>
#include <ctime>

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <termios.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/file.h>

# define BLACK	"\033[30m"
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define PURPLE	"\033[35m"
# define CYAN	"\033[36m"
# define WHITE	"\033[37m"
# define ORANGE	"\033[38;5;208m"
# define PINK	"\033[38;5;13m"
# define GREY	"\033[38;5;246m"

# define END	"\033[0m"
# define BUFFSIZE	4096 * 4
#define OLD term[0]
#define NEW term[1]

#endif
