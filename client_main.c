#include "myserver.h"
void	send_bit(char c, pid_t server_pid, int shift);
void	send_stream(int sig, siginfo_t *s_info, void *context);

int	main(int argc, char **argv)
{
	pid_t				pid_to_send;
	siginfo_t			s_siginfo;
	struct sigaction	sa;
	struct timespec		timeout;

	pid_to_send = atoi(argv[1]);
	timeout.tv_sec = 5;
	timeout.tv_nsec = 0;
	if (sigemptyset(&sa.sa_mask) || sigaddset(&sa.sa_mask, SIGUSR1)
			|| sigprocmask(SIG_SETMASK, &sa.sa_mask, NULL))
	{
		perror("Failed to set the mask");
		return (EXIT_FAILURE);
	}
	sa.sa_handler = SIG_IGN;
	kill(pid_to_send, SIGUSR1);
	if (sigtimedwait(&sa.sa_mask, &s_siginfo, &timeout) == -1)
		return (printf("timeout\n"));
	printf("O meu pid é %d\n", getpid());
	printf("O pid do proxy é > %d\n", s_siginfo.si_pid);
		/*
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &send_stream;
	sigaction(SIGUSR1, &sa, NULL);
	while (42)
		pause();
	*/
	/*aqui*/
	return (EXIT_SUCCESS);
}

/*
void	send_stream(int sig, siginfo_t *s_info, void *context)
{
	int	i = 0;

	while (i < 8)
	{
		send_bit()

	
		i++;
	}




}
*/

void	send_bit(char c, pid_t server_pid, int shift)
{
	if (c & (1 << shift))
		kill(server_pid, SIGUSR2);
	else
		kill(server_pid, SIGUSR1);
	return ;
}
