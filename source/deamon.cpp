#include "MattDaemon.h"

//int	setup_deamon(void)
//{
//int					sock;
//struct protoent		*proto;
//struct sockaddr_in	sin;

//umask(0);
//if (setsid() == -1)
//{
//perror("setsid()");
//exit(errno);
//}
//chdir("/");
////close(STDIN_FILENO);
////close(STDOUT_FILENO);
////close(STDERR_FILENO);

//if ((proto = getprotobyname("tcp")) == NULL)
//{
//perror("getprotobyname");
//exit(errno);
//}
//if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
//{
//perror("socket");
//exit(errno);
//}
//sin.sin_family = AF_INET;
//sin.sin_port = htons(4242);
//sin.sin_addr.s_addr = htonl(INADDR_ANY);
//if ((bind(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
//{
//perror("bind");
//return (-1);
//}
//if ((listen(sock, 2)) == -1)
//{
//perror("listen");
//return (-1);
//}
//return (sock);
//}

static void	signal_handler(int sig)
{
	int			fd = 0;
	time_t		t = time(0);
	struct tm	*now = localtime(&t);
	const char	*sig_list[] = {NULL, "HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT",
		"BUS", "FPE", "KILL", "USR1", "SEGV", "USR2", "PIPE", "ALRM", "TERM", "STKFLT",
		"CHLD", "CONT", "STOP", "TSTP", "TTIN", "TTOU", "URG", "XCPU", "XFSZ", "VTALRM",
		"PROF", "WINCH", "POLL", "PWR", "SYS", "WAITING", "LWP", "RTMIN", "RTMIN+1",
		"RTMIN+2", "RTMIN+3", "RTMIN+4", "RTMIN+5", "RTMIN+6", "RTMIN+7", "RTMIN+8",
		"RTMIN+9", "RTMIN+10", "RTMIN+11", "RTMIN+12", "RTMIN+13", "RTMIN+14",
		"RTMIN+15", "RTMAX-14", "RTMAX-13", "RTMAX-12", "RTMAX-11", "RTMAX-10",
		"RTMAX-9", "RTMAX-8", "RTMAX-7", "RTMAX-6", "RTMAX-5", "RTMAX-4", "RTMAX-3",
		"RTMAX-2", "RTMAX-1", "RTMAX"};

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
	int opt = true;  
	int master_socket , addrlen , new_socket , client_socket[3] , 
		max_clients = 3 , activity, i , valread , sd;  
	int max_sd;  
	int nb_user = 0;
	struct sockaddr_in address;  

	char buffer[1025];  //data buffer of 1K 

	//set of socket descriptors 
	fd_set readfds;  


	create_deamon(tintin);
	umask(0);
	if (setsid() == -1)
	{
		perror("setsid()");
		exit(errno);
	}
	chdir("/");
	for (i = 0; i < max_clients; i++)  
	{  
		client_socket[i] = 0;  
	}  

	//create a master socket 
	if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
	{  
		perror("socket failed");  
		exit(EXIT_FAILURE);  
	}  

	//set master socket to allow multiple connections , 
	//this is just a good habit, it will work without this 
	if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
				sizeof(opt)) < 0 )  
	{  
		perror("setsockopt");  
		exit(EXIT_FAILURE);  
	}  

	//type of socket created 
	address.sin_family = AF_INET;  
	address.sin_addr.s_addr = INADDR_ANY;  
	address.sin_port = htons( 4242 );  

	//bind the socket to localhost port 8888 
	if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
	{  
		perror("bind failed");  
		exit(EXIT_FAILURE);  
	}  
	printf("Listener on port %d \n", 4242);  

	//try to specify maximum of 3 pending connections for the master socket 
	if (listen(master_socket, 3) < 0)  
	{  
		perror("listen");  
		exit(EXIT_FAILURE);  
	}  

	//accept the incoming connection 
	addrlen = sizeof(address);  
	puts("Waiting for connections ...");  

	while(true)  
	{  
		//clear the socket set 
		FD_ZERO(&readfds);  

		//add master socket to set 
		FD_SET(master_socket, &readfds);  
		max_sd = master_socket;  

		//add child sockets to set 
		for ( i = 0 ; i < max_clients ; i++)  
		{  
			//socket descriptor 
			sd = client_socket[i];  

			//if valid socket descriptor then add to read list 
			if(sd > 0)  
				FD_SET( sd , &readfds);  

			//highest file descriptor number, need it for the select function 
			if(sd > max_sd)  
				max_sd = sd;  
		}  

		//wait for an activity on one of the sockets , timeout is NULL , 
		//so wait indefinitely 
		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  

		if ((activity < 0) && (errno!=EINTR))  
		{  
			printf("select error");  
		}  

		//If something happened on the master socket , 
		//then its an incoming connection 
		if (FD_ISSET(master_socket, &readfds))  
		{  
			if ((new_socket = accept(master_socket, 
							(struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
			{  
				perror("accept");  
				exit(EXIT_FAILURE);  
			}  
			if (nb_user >= 3)
			{
				printf("Connexion limit reached\n");
				close(new_socket);
			}
			else
			{
				//inform user of socket number - used in send and receive commands 
				printf("New connection , socket fd is %d , ip is : %s , port : %d \n" ,\
				new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  



				puts("Welcome message sent successfully");  

				//add new socket to array of sockets 
				for (i = 0; i < max_clients; i++)  
				{  
					//if position is empty 
					if( client_socket[i] == 0 )  
					{  
						client_socket[i] = new_socket;  
						printf("Adding to list of sockets as %d\n" , i);
						break;  
					} 
				}  
				nb_user++;
			}
		}  

		//else its some IO operation on some other socket
		for (i = 0; i < max_clients; i++)  
		{  
			sd = client_socket[i];  

			if (FD_ISSET( sd , &readfds))  
			{  
				//Check if it was for closing , and also read the 
				//incoming message 
				if ((valread = read( sd , buffer, 1024)) == 0)  
				{  
					//Somebody disconnected , get his details and print 
					getpeername(sd , (struct sockaddr*)&address , \
							(socklen_t*)&addrlen);  
					printf("Host disconnected , ip %s , port %d \n" , 
							inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
					tintin->write_log("User request quit", "\033[1;35mLOG\033[0m");
					//Close the socket and mark as 0 in list for reuse 
					close( sd );  
					client_socket[i] = 0;  
					nb_user--;
				}  

				//Echo back the message that came in 
				else
				{  
					//set the string terminating NULL byte on the end 
					//of the data read 
					buffer[valread -1] = '\0';
					if (!strcmp(buffer, "quit"))
					{
						tintin->write_log("User request quit", "\033[1;35mLOG\033[0m");
						close( sd );  
						client_socket[i] = 0;  
						nb_user--;
					}
					tintin->write_log(buffer, "\033[1;35mLOG\033[0m");
				}  
			} 
			if (client_socket[0] == 0 && client_socket[1] == 0 && client_socket[2] == 0)
				return ; 
		}  
	}  

}

