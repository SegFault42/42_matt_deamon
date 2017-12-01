#include "MattDaemon.h"

extern	Tintin_reporter	*ptr;

bool	setup_deamon(t_connexion *connexion)
{
	umask(0);
	if (setsid() == -1)
	{
		perror("setsid()");
		ptr->write_log("setsid() failure", "\033[1;31mERROR\033[0m");
		return (false);
	}
	chdir("/");

	for (int i = 0; i < MAX_CLIENT; i++)
		connexion->client_socket[i] = 0;

	//create a master socket
	if( (connexion->master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
	{
		perror("socket()");
		ptr->write_log("socket() failure", "\033[1;31mERROR\033[0m");
		return (false); 
	}

	//set master socket to allow multiple connections , 
	//this is just a good habit, it will work without this 
	if ( setsockopt(connexion->master_socket, SOL_SOCKET, SO_REUSEADDR,
		(char *)&connexion->opt, sizeof(connexion->opt)) < 0)
	{
		perror("setsockopt()");
		ptr->write_log("setsockopt() failure", "\033[1;31mERROR\033[0m");
		return (false); 
	}

	//type of socket created 
	connexion->address.sin_family = AF_INET;
	connexion->address.sin_addr.s_addr = INADDR_ANY;
	connexion->address.sin_port = htons(4242);

	//bind the socket to localhost port 8888 
	if (bind(connexion->master_socket, (struct sockaddr *)&connexion->address,
		sizeof(connexion->address))<0)
	{
		perror("bind()");
		ptr->write_log("bind() failure", "\033[1;31mERROR\033[0m");
		return (false);
	}
	return (true);
}

static void	signal_handler(int sig)
{
	ptr->write_sig_error(sig);
	ptr->~Tintin_reporter();
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
	tintin->write_log("Deamon created pid : " + std::to_string(getpid()), "\033[1;32mINFO\033[0m");
	for (int i = 1; i <= 64; ++i)
		signal(i, signal_handler);
}

void	daemon(Tintin_reporter *tintin, char arg)
{
	int			new_socket, activity, i , valread , sd;
	int			max_sd;
	int			nb_user = 0;
	char		buffer[4097];  //data buffer of 1K 
	fd_set		readfds;
	t_connexion	connexion = {0};

	create_deamon(tintin);
	if (setup_deamon(&connexion) == false)
		return ;

	if (listen(connexion.master_socket, 3) < 0)  
	{
		tintin->write_log("listen() failure", "\033[1;31mERROR\033[0m");
		return ;
	}

	connexion.addrlen = sizeof(connexion.address);

	while(true)
	{
		FD_ZERO(&readfds);
		FD_SET(connexion.master_socket, &readfds);
		max_sd = connexion.master_socket;

		for ( i = 0 ; i < MAX_CLIENT; i++)
		{
			sd = connexion.client_socket[i];
			if(sd > 0)
				FD_SET( sd , &readfds);
			if(sd > max_sd)
				max_sd = sd;
		}
		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
		if ((activity < 0) && (errno!=EINTR))
			printf("select error");

		if (FD_ISSET(connexion.master_socket, &readfds))
		{
			if ((new_socket = accept(connexion.master_socket,
							(struct sockaddr *)&connexion.address, (socklen_t*)&connexion.addrlen))<0)
			{
				tintin->write_log("accept() failure", "\033[1;31mERROR\033[0m");
				return ;
			}
			if (nb_user >= 3)
			{
				tintin->write_log("Connexion limit reached", "\033[1;31mERROR\033[0m");
				close(new_socket);
			}
			else
			{
				for (i = 0; i < MAX_CLIENT; i++)
				{
					if(connexion.client_socket[i] == 0 )
					{
						connexion.client_socket[i] = new_socket;
						tintin->write_log("New client, id : " + std::to_string(i + 1), "\033[1;32mINFO\033[0m");
						break;
					}
				}
				nb_user++;
			}
		}

		for (i = 0; i < MAX_CLIENT; i++)
		{
			sd = connexion.client_socket[i];
			if (FD_ISSET( sd , &readfds))
			{
				if ((valread = read( sd , buffer, 4096)) == 0)
				{
					getpeername(sd , (struct sockaddr*)&connexion.address , (socklen_t*)&connexion.addrlen);
					tintin->write_log("User " + std::to_string(i + 1) + " request quit", "\033[1;35mLOG\033[0m");
					close(sd);
					connexion.client_socket[i] = 0;
					nb_user--;
				}
				else
				{
					buffer[valread -1] = '\0';
					if (!strcmp(buffer, "quit"))
					{
						tintin->write_log("Client " + std::to_string(i + 1) + " request quit", "\033[1;35mLOG\033[0m");
						close( sd );
						connexion.client_socket[i] = 0;
						nb_user--;
					}
					else
					{
						if (!strncmp(buffer, "0xrabougue", 10))
							strcpy(buffer, ft_decrypt(&buffer[10]));
						tintin->write_log(buffer, "\033[1;35mLOG\033[0m");
					}
				}
			}
			for (int j = 0; j <= 2; j++)
			{
				if (connexion.client_socket[j] != 0)
					break;
				else if (j == 2)
				{
					tintin->write_log("All client disconnected.", "\033[1;32mINFO\033[0m");
					return ;
				}
			}
		}
	}
}

