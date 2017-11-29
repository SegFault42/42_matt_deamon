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
	chdir("/");
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
	const char	*sig_list[] = {NULL, "HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT",
	"BUS", "FPE", "KILL", "USR1", "SEGV", "USR2", "PIPE", "ALRM", "TERM", "STKFLT",
	"CHLD", "CONT", "STOP", "TSTP", "TTIN", "TTOU", "URG", "XCPU", "XFSZ", "VTALRM",
	"PROF", "WINCH", "POLL", "PWR", "SYS", "???", "???", "???", "???", "???",
	"???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???",
	"???", "???", "???", "???", "???", "???", "???", "???", "???", "???", "???",
	"???", "???", "???", "???", "???", "???", "???"};

	fd = open("/var/log/matt_daemon/matt_daemon.log", O_RDWR | O_APPEND);

	dprintf(fd,
			"[%d/%d/%d-%d:%d:%02d] [ \033[1;31mSIGNAL\033[0m ] - Signal handler (\033[1;31mSIG%s\033[0m)\n",
			now->tm_mday,
			now->tm_mon + 1,
			now->tm_year + 1900,
			now->tm_hour,
			now->tm_min,
			now->tm_sec,
			sig_list[sig]);
	dprintf(fd,
			"[%d/%d/%d-%d:%d:%d] [ \033[1;32mINFO\033[0m ] - Matt_daemon: Quitting.\n",
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

void	create_deamon(Tintin_reporter *tintin)
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
	tintin->write_log("Deamon created", "\033[1;32mINFO\033[0m");
	for (int i = 1; i <= 64; ++i)
		signal(i, signal_handler);
}

void	daemon(Tintin_reporter *tintin)
{
	int					socket = 0;
	int					child_pid;
	int					sock;
	uint32_t			client_socket_len;
	char				buff[4096] = {0};
	struct sockaddr_in	sin;
	ssize_t				ret_recv;

	create_deamon(tintin);
	socket = setup_deamon();

	if (socket == -1)
		return ;

	sock = accept(socket, (struct sockaddr *)&sin, &client_socket_len);
	while ((ret_recv = recv(sock, buff, sizeof(buff), 0)) > 0)
	{
		buff[ret_recv -1] = '\0';
		if (!strcmp(buff, "quit"))
		{
			tintin->write_log("User request quit", "\033[1;35mLOG\033[0m");
			return ;
		}
		tintin->write_log(buff, "\033[1;35mLOG\033[0m");
		memset(buff, 0, sizeof(buff));
	}
	close(socket);
	close(sock);
}
