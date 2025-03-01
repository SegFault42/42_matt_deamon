#ifndef MATTDAEMON_H
#define MATTDAEMON_H

#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <CkMailMan.h>
#include <CkEmail.h>
#include "/include/CkMailMan.h"

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/file.h>

#define	MAX_CLIENT	3
#define	BUFFSIZE	4096 * 4

class	Tintin_reporter
{
	public:

	Tintin_reporter();
	Tintin_reporter(Tintin_reporter const & src);
	void	write_log(std::string log, std::string type) const;
	void	write_sig_error(int sig) const;
	void	create_lock_file(void);
	void	create_log_file(void);
	void	delete_lock_file(void) const;
	void	send_mail();
	~Tintin_reporter();
	Tintin_reporter & operator=(Tintin_reporter const & rhs);

	private:

	int			m_fd_lock;
	int			m_fd_log;
	std::string	m_file_name;
};

typedef struct			s_connexion
{
	int					master_socket;
	int					opt;
	int					addrlen;
	struct sockaddr_in	address;
	int					client_socket[3];
}						t_connexion;

bool	daemon(Tintin_reporter *tintin);
void	create_deamon();
void	setup_deamon(void);
void	quit(void);
char	*ft_decrypt(char *str);

#endif
