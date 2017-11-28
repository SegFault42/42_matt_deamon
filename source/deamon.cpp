#include "MattDaemon.h"



int	setup_deamon(void)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	umask(0);
	if (setsid() == -1)
	{
		perror("setsid()");
		exit(errno);
	}
	//close(STDIN_FILENO);
	//close(STDOUT_FILENO);
	//close(STDERR_FILENO);

	if ((proto = getprotobyname("tcp")) == NULL)
	{
		perror("getprotobyname");
		exit(errno);
	}
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
	{
		perror("socket");
		exit(errno);
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons(4242);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if ((bind(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
	{
		perror("bind");
		return (-1);
	}
	if ((listen(sock, 2)) == -1)
	{
		perror("listen");
		return (-1);
	}
	return (sock);
}

static void	signal_handler(int sig)
{
	int			fd = 0;
	time_t		t = time(0);
	struct tm	*now = localtime(&t);

	fd = open("/var/log/matt_daemon/matt_daemon.log", O_RDWR | O_APPEND);
	dprintf(fd,
			"[%d/%d/%d-%d:%d:%d] [ SIGNAL ] - Signal handler\n",
			now->tm_mday,
			now->tm_mon + 1,
			now->tm_year + 1900,
			now->tm_hour,
			now->tm_min,
			now->tm_sec);
	dprintf(fd,
			"[%d/%d/%d-%d:%d:%d] [ INFO ] - Matt_daemon: Quitting.\n",
			now->tm_mday,
			now->tm_mon + 1,
			now->tm_year + 1900,
			now->tm_hour,
			now->tm_min,
			now->tm_sec);
	close(fd);
	remove("/var/lock/matt_daemon.lock");
	exit(0);
}

void	create_deamon()
{
	pid_t	ps_deamon = 0;

	ps_deamon = fork();
	if (ps_deamon == -1)
	{
		perror("fork failed");
		exit(errno);
	}
	else if (ps_deamon > 0)
	{
		std::cout << "fork ok" << std::endl << "pid = " << ps_deamon << std::endl;
		exit(0);
	}
	signal(SIGTERM, signal_handler);
}

void	quit(void)
{
	int	fd;

	fd = open("/var/log/matt_daemon/matt_daemon.log", O_RDWR | O_APPEND);
	if (fd != -1)
	{
		dprintf(fd, "\033[31mMatt_daemon: Quitting.\033[0m");
		close(fd);
	}
	else
		perror("open()");

	if (remove("/var/lock/matt_daemon.lock") == -1)
		perror("remove()");
	//close(socket);
	//close(sock);
	exit(0);
}

int	create_log_file(void)
{
	int	fd;

	if (mkdir("/var/log/matt_daemon", 0755) == -1 && errno != 17)
	{
		perror("mkdir");
		exit (errno);
	}
	fd = open("/var/log/matt_daemon/matt_daemon.log", O_RDWR | O_CREAT | O_APPEND, 0755);
	if (fd == -1)
	{
		perror("open");
		exit (errno);
	}
	return (fd);
}

void	daemon(Tintin_reporter *tintin)
{
	int					socket = 0;
	int					child_pid;
	int					sock;
	uint32_t			client_socket_len;
	char				buff[4096] = {0};
	int					fd = 0;
	struct sockaddr_in	sin;
	ssize_t				ret_recv;

	create_deamon();
	socket = setup_deamon();
	std::cout << "socket = " << socket << std::endl;
	if (socket == -1)
		return ;
	//create_lock_file();

	fd = create_log_file();
	sock = accept(socket, (struct sockaddr *)&sin, &client_socket_len);
	while (1)
	{
		ret_recv = recv(sock, buff, sizeof(buff), 0);
		buff[ret_recv -1] = '\0';
		if (!strcmp(buff, "quit") || !ret_recv)
			return ;
		tintin->write_log(buff);
		memset(buff, 0, sizeof(buff));
	}
}
