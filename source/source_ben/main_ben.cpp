#include "../../include/Ben_AFK.h"

static uint8_t	g_auth = 0;

char	*ft_crypt(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
		i++;
	i--;
	while (i >= 0)
	{
		str[i] += 5;
		i--;
	}
	return (str);
}

int	create_client(char *addr, uint16_t port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

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
	sin.sin_port = htons(port);
	if (!strcmp("localhost", addr))
		sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	else
		sin.sin_addr.s_addr = inet_addr(addr);
	if ((connect(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
	{
		perror("connect");
		exit(errno);
	}
	return (sock);
}

static uint8_t	authentification_pass(void)
{
	char			bu[4096];
	uint8_t			attempt;
	struct termios	term[2];

	attempt = 1;
	while (attempt <= 3)
	{
		memset(bu, 0, sizeof(bu));
		write(1, "pass : ", 7);
		tcgetattr(STDIN_FILENO, &OLD);
		NEW = OLD;
		NEW.c_lflag &= (unsigned long)~(ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &NEW);
		read(STDIN_FILENO, bu, sizeof(bu));
		tcsetattr(STDIN_FILENO, TCSANOW, &OLD);
		if (!strcmp("toor\n", bu) && printf(GREEN"\nWelcome root !\n"END))
			return (1);
		++attempt;
		printf("\n");
		sleep(2);
		printf(RED"Wrong password\n"END);
	}
	return (0);
}

static uint8_t	authentification(void)
{
	char	buff[4096];

	memset(buff, 0, sizeof(buff));
	write(1, "Username : ", 11);
	read(STDIN_FILENO, buff, sizeof(buff));
	if (!strcmp("root\n", buff))
	{
		if (authentification_pass() == 1)
			return (1);
		printf(RED"Login failure\n%slogged as anonymous\n\
		Welcome anonymous\n"END, GREEN);
	}
	else if (!strncmp(buff, "anonymous", 9))
		printf(GREEN"Welcome anonymous !\n"END);
	else
		printf(GREEN"login incorrect, logged as anonymous\n"END);
	return (0);
}

int	main()
{
	int			sock;
	char		buff[BUFFSIZE] = {0};
	ssize_t		ret_read = 0;

	sock = create_client((char *)"localhost", 4242);
	g_auth = authentification();

	while (1)
	{
		if ((ret_read = read(0, buff, BUFFSIZE)) == -1)
		{
			perror("read");
			return (errno);
		}
		buff[ret_read -1] = '\0';
		if (g_auth == 1 && strcmp("quit", buff))
		{
			memcpy(buff, ft_crypt(buff), strlen(buff));
			strcpy(&buff[strlen("0xrabougue")], buff);
			memcpy(buff, "0xrabougue", 10);
		}
		if (send(sock, buff, BUFFSIZE, 0) == -1)
		{
			perror("send");
			return (errno);
		}
		if (!strcmp(buff, "quit"))
			return (0);
		memset(&buff, 0, BUFFSIZE);
	}

}
