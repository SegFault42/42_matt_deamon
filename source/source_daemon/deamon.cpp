#include "../../include/MattDaemon.h"

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

	if( (connexion->master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
	{
		perror("socket()");
		ptr->write_log("socket() failure", "\033[1;31mERROR\033[0m");
		return (false); 
	}

	if ( setsockopt(connexion->master_socket, SOL_SOCKET, SO_REUSEADDR,
		(char *)&connexion->opt, sizeof(connexion->opt)) < 0)
	{
		perror("setsockopt()");
		ptr->write_log("setsockopt() failure", "\033[1;31mERROR\033[0m");
		return (false); 
	}

	connexion->address.sin_family = AF_INET;
	connexion->address.sin_addr.s_addr = INADDR_ANY;
	connexion->address.sin_port = htons(4242);

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
		//std::cout << "fork ok" << std::endl << "pid = " << ps_deamon << std::endl;
		exit(0);
	}
	tintin->write_log("Deamon created pid : " + std::to_string(getpid()), "\033[1;32mINFO\033[0m");
	//close(STDIN_FILENO);
	//close(STDERR_FILENO);
	//close(STDOUT_FILENO);
	for (int i = 1; i <= 64; ++i)
		signal(i, signal_handler);
}

bool	daemon(Tintin_reporter *tintin)
{
	int			new_socket, activity, i , valread , sd;
	int			max_sd;
	int			nb_user = 0;
	char		buffer[BUFFSIZE + 1];
	fd_set		readfds;
	t_connexion	connexion;

	memset(&connexion, 0, sizeof(connexion));
	create_deamon(tintin);
	if (setup_deamon(&connexion) == false)
		return (false);

	if (listen(connexion.master_socket, 3) < 0)
	{
		tintin->write_log("listen() failure", "\033[1;31mERROR\033[0m");
		return (false);
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
		//if ((activity < 0) && (errno!=EINTR))
			////printf("select error");

		if (FD_ISSET(connexion.master_socket, &readfds))
		{
			if ((new_socket = accept(connexion.master_socket,
							(struct sockaddr *)&connexion.address, (socklen_t*)&connexion.addrlen))<0)
			{
				tintin->write_log("accept() failure", "\033[1;31mERROR\033[0m");
				return (false);
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
				if ((valread = recv( sd , buffer, BUFFSIZE, 0)) == 0)
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
					memset(&buffer, 0, BUFFSIZE);
				}
			}
			for (int j = 0; j <= 2; j++)
			{
				if (connexion.client_socket[j] != 0)
					break;
				else if (j == 2)
				{
					tintin->write_log("All client disconnected.", "\033[1;32mINFO\033[0m");
					return (true);
				}
			}
		}
	}
	return (true);
}

