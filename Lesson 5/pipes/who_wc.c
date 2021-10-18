#include <stdio.h>
#include <unistd.h>

// who ---(stdout)---> [fd[1] ---> fd[0]] ---(stdin)---> wc -l

void	who_wc()
{
	int	fd[2];

	pipe(fd);
	if (fork() == 0)
	{
		close(STDOUT_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		execlp("who", "who", NULL);
	}
	else
	{
		close(STDIN_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("wc", "wc", "-l", NULL);
	}
}

int main(int argc, char *argv[])
{
	who_wc();	
	return (0);
}