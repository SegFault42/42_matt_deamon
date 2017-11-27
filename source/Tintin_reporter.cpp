#include "MattDaemon.h"

//Methode
void	Tintin_reporter::write_log(std::string log) const
{
	int			fd = 0;
	time_t		t = time(0);
	struct tm	*now = localtime(&t);

	fd = open("/var/log/matt_daemon/matt_daemon.log",
				O_RDWR | O_CREAT | O_APPEND,
				0755);

	if (fd == -1)
	{
		perror("write_log failure");
		exit(errno);
	}

	dprintf(fd,
			"[%d/%d/%d-%d:%d:%d] [ INFO ] - %s.\n",
			now->tm_mday,
			now->tm_mon + 1,
			now->tm_year + 1900,
			now->tm_hour,
			now->tm_min,
			now->tm_sec,
			log.c_str());

	close(fd);
}

void	Tintin_reporter::create_lock_file(void) const
{
	int	fd;

	fd = open("/var/lock/matt_daemon.lock", O_CREAT, 0755);
	if (fd == -1)
	{
		perror("lockfile failure");
		exit(errno);
	}
	flock(fd, LOCK_EX);
	close(fd);
	write_log("Matt_daemon: Started");
}

void	Tintin_reporter::delete_lock_file(void) const
{
	int	fd;

	fd = open("/var/lock/matt_daemon.lock", O_RDONLY);
	if (fd == -1)
	{
		perror("delete_lock_file failure");
		exit(errno);
	}
	remove("/var/lock/matt_daemon.lock");
	flock(fd, LOCK_UN);
	close(fd);
	write_log("Matt_daemon: Quitting");
}

//Constructeur
Tintin_reporter::Tintin_reporter()
{
	create_lock_file();
}

//Destructeur
Tintin_reporter::~Tintin_reporter()
{
	delete_lock_file();
}
