#include "MattDaemon.h"

Tintin_reporter	*ptr;

static bool	check_root(void)
{
	if (getuid() != 0)
	{
		std::cout << "Permission denied. Are you root ?" << std::endl;
		return (false);
	}
	return (true);
}

int	main(void)
{
	if (check_root() == false)
		return (false);

	Tintin_reporter	tintin; // create object
	ptr = &tintin;

	daemon(&tintin);
}
