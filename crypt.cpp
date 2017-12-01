#include <iostream>

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

int	main(int argc, char **argv)
{
	if (argv[1])
		std::cout << ft_crypt(argv[1]) << std::endl;
}
