#include "MattDaemon.h"

static bool	check_root(void)
{
	if (getuid() != 0)
	{
		std::cout << "Permission denied. Are you root ?" << std::endl;
		return (false);
	}
	return (true);
}

static void	prompt(int sig)
{
	if (sig == SIGINT)
		quit();
}

int	main(void)
{
	if (check_root() == false)
		return (false);
	if (deamon_exist() == true)
	{
		std::cerr << "Another instance of MattDaemon is already running" << std::endl;
		return (0);
	}

	Tintin_reporter	tintin; // create object



	create_deamon();
	daemon(&tintin);
}
