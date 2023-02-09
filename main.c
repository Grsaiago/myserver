#include "myserver.h"
void	create_proxy(int sig, siginfo_t *s_info, void *context);
int		set_minitalk(struct sigaction *sa);
void	minitalk(int sig, siginfo_t *s_info, void *context);

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &create_proxy;
	sigaction(SIGUSR1, &sa, NULL);
	printf("Server PID: %d\n", getpid());
	while (42)
		pause();
	return (0);
}

void	create_proxy(int sig, siginfo_t *s_info, void *context)
{
	struct sigaction	sa;
	pid_t				client_pid;
	pid_t				pid;

	client_pid = s_info->si_pid;
	pid = fork();
	if (pid == 0)
	{
		printf("[PROXY pid %d] > request received from pid: %d\n", getpid(), client_pid);
		set_minitalk(&sa);
		kill(client_pid, SIGUSR1);
		while (42)
			pause();
		return ;
	}
	return ;
}

int	set_minitalk(struct sigaction *sa)
{
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = &minitalk;
	sigaction(SIGUSR1, sa, NULL);
	return (0);
}

void	minitalk(int sig, siginfo_t *s_info, void *context)
{
	static uint8_t		index = 0;
	static uint8_t		i = 0;
	static char			c = 0;
	static char			name[8];

	c <<= 1;
	if (sig == SIGUSR2)
		c |= 1;
	i++;
	if (i == 8)
	{
		name[index] = c;
		i = 0;
		c = 0;
		index++;
		kill(s_info->si_pid, SIGUSR1);
	}
	kill(s_info->si_pid, SIGUSR1);
}
