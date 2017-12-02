#include "../../include/MattDaemon.h"

Tintin_reporter	*ptr;

static void SendEmail(void)
{
	CkMailMan	mailman;
	CkEmail		email;
	char		entry[50];

	bool success = mailman.UnlockComponent("30-day trial");
	if (success != true)
	{
		std::cout << mailman.lastErrorText() << "\r\n";
		return;
	}
	mailman.put_SmtpHost("smtp.gmail.com");
	fgets(entry, 50, stdin);
	mailman.put_SmtpUsername("ramzi90000@gmail.com");
	mailman.put_SmtpPassword("izdxvufraise%901");
	email.put_Subject("This is a test");
	email.put_Body("This is a test");
	email.put_From("Matt_daemon log");
	success = email.AddTo("SegFault42", "SegFault42@protonmail.com");
	success = mailman.SendEmail(email);
	if (success != true)
	{
		std::cout << mailman.lastErrorText() << "\r\n";
		return;
	}
	success = mailman.CloseSmtpConnection();
	if (success != true)
		std::cout << "Connection to SMTP server not closed cleanly." << "\r\n";
	std::cout << "Mail Sent!" << "\r\n";
}

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
		//if (argv[i][0] == '-' && argv[i][1] == 'd' && strlen(argv[i]) == 2)
			//*arg |= 2;
		//if (argv[i][0] == '-' && argv[i][1] == 'e' && strlen(argv[i]) == 2)
			//*arg |= 4;
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

	if (daemon(&tintin, arg) == true && arg == 1)
		SendEmail();
}
