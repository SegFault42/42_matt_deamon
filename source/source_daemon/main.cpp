#include "../../include/MattDaemon.h"

Tintin_reporter	*ptr;

char	*ft_decrypt(char *str)
{
	int i = 0;

	if	(str == NULL)
		return (NULL);
	while (str[i] != '\0')
		i++;
	i--;
	while (i >= 0)
	{
		str[i] -= 5;
		i--;
	}
	return (str);
}

static bool	check_root(void)
{
	if (getuid() != 0)
	{
		std::cout << "Permission denied. Are you root ?" << std::endl;
		return (false);
	}
	return (true);
}

static void	get_arg(int argc, char **argv, char *arg)
{
	for (int i = 0; i < argc; i++)
	{
		if (argv[i][0] == '-' && argv[i][1] == 'm' && strlen(argv[i]) == 2)
			*arg |= 1;
	}
}

int	main(int argc, char **argv)
{
	if (check_root() == false)
		return (false);

	Tintin_reporter	tintin; // create object
	char			arg = 0;;

	get_arg(argc -1, &argv[1], &arg);
	ptr = &tintin;

	if (daemon(&tintin) == true && arg == 1)
		tintin.send_mail();;
	(void)argc;
}
