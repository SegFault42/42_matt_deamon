#include "MattDaemon.h"

//Methode
void	Tintin_reporter::write_log(std::string log, std::string type) const
{
	time_t		t = time(0);
	struct tm	*now = localtime(&t);

	dprintf(m_fd_log,
			"[%d/%d/%d-%d:%d:%02d] [ %s ] - %s\n",
			now->tm_mday,
			now->tm_mon + 1,
			now->tm_year + 1900,
			now->tm_hour,
			now->tm_min,
			now->tm_sec,
			type.c_str(),
			log.c_str());

	//close(fd);
}
void	Tintin_reporter::create_log_file(void)
{
	if (mkdir("/var/log/matt_daemon", 0755) == -1 && errno != 17)
	{
		perror("mkdir");
		exit (errno);
	}
	m_fd_log = open("/var/log/matt_daemon/matt_daemon.log", O_RDWR | O_CREAT | O_APPEND, 0755);
	if (m_fd_log == -1)
	{
		perror("open");
		exit (errno);
	}
}

void	Tintin_reporter::create_lock_file(void)
{
	int	ret_flock = 0;

	m_fd_lock = open("/var/lock/matt_daemon.lock", O_CREAT, 0755);
	if (m_fd_lock == -1)
	{
		exit(errno);
	}
	ret_flock = flock(m_fd_lock, LOCK_EX | LOCK_NB);
	if (ret_flock == -1)
	{
		std::cout << "Another instance of Matt_daemon running." << std::endl;
		write_log("Matt_daemon: Error file locked", "\033[1;31mERROR\033[0m");
		write_log("Matt_daemon: Quitting.", "\033[1;32mINFO\033[0m");
		exit(EXIT_FAILURE);
	}
}

void	Tintin_reporter::delete_lock_file(void) const
{
	flock(m_fd_lock, LOCK_UN);
	close(m_fd_lock);
	remove("/var/lock/matt_daemon.lock");
}

//Constructeur
Tintin_reporter::Tintin_reporter()
{
	create_log_file();
	write_log("Matt_daemon: Started.", "\033[1;32mINFO\033[0m");
	create_lock_file();
}

//Destructeur
Tintin_reporter::~Tintin_reporter()
{
	delete_lock_file();
	write_log("Matt_daemon: Quitting.", "\033[1;32mINFO\033[0m");
	close(m_fd_log);
}
