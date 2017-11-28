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

static int	deamon_exist()
{
	struct stat	st;
	int			ret_stat = 0;

	ret_stat = stat("/var/lock/matt_daemon.lock", &st);
	if (ret_stat == -1)
		return (false);
	return (true);
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

	daemon(&tintin);
}
