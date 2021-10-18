#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	int		status;
	char	buffer[32];
	FILE	*fd;
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		fd = fopen("LOCATE YOUR PATH", "w");
		fprintf(fd, "%d", getpid());
		fclose(fd);
		signal(SIGTERM, SIG_DFL);
		signal(SIGABRT, SIG_IGN);
		pause();
	}
	else
	{
		fd = fopen("LOCATE YOUR PATH", "w");
		fprintf(fd, "%d", getpid());
		fclose(fd);	
		signal(SIGTERM, SIG_IGN);
		signal(SIGABRT, SIG_IGN);
		waitpid(child_pid, &status, 0);
		pause();
	}
}