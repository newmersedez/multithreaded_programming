#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
	FILE	*f;
	char	buffer[32];

	if ((f = fopen("/home/box/pid", "r")) == NULL)
		exit(EXIT_FAILURE);
	sprintf(buffer, "%d", getpid());
	fprintf(f, buffer);
	fclose(f);
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	pause();
	return 0;
}