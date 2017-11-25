#ifndef MATTDAEMON_H
#define MATTDAEMON_H

#include <iostream>

# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void	daemon(void);
int		deamon_exist();
void	create_deamon();
int	setup_deamon(void);

#endif
