#include <signal.h>
#include <unistd.h>

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	kill(pid, SIGABRT);
	return (0);
}
