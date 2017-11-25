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
		exit(errno);
	}
	if ((listen(sock, 2)) == -1)
	{
		perror("listen");
		exit(errno);
	}
	return (sock);
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
}

int	deamon_exist()
{
	struct stat	st;
	int			fd = 0;

	if (stat("/var/lock/matt_daemon.lock", &st) == -1)
	{
		if (errno == 2)
		{
			fd = open("/var/lock/matt_daemon.lock", O_CREAT);
			if (fd == -1)
			{
				perror("open()");
				exit(errno);
			}
			close(fd);
			return (false);
		}
		else
		{
			perror("stat()");
			exit(errno);
		}
	}
	return (true);
}


void	daemon(void)
{
	int	socket = 0;
	int	child_pid;
	int	sock;
	uint32_t			client_socket_len;
	struct sockaddr_in	sin;
	char	buff[4096] = {0};
	int	fd = 0;

	socket = setup_deamon();

	fd = open("/tmp/matt_daemon.log", O_RDWR | O_CREAT | O_APPEND, 0755);
	if (fd == -1)
	{
		perror("open");
		exit (errno);
	}
	sock = accept(socket, (struct sockaddr *)&sin, &client_socket_len);
	while (1)
	{
		while (recv(sock, buff, sizeof(buff), 0) > 0)
			dprintf(fd, "%s", buff);
		memset(buff, 0, sizeof(buff));
	}
}
