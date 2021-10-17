#include <iostream>
#include <signal.h>
#include <unistd.h>

void	handler(int signum)
{
	std::cout << "AHAHAHA" << std::endl;
}

int main()
{
	struct sigaction	action;
	action.sa_handler = handler;
	sigaction(SIGINT, &action, NULL);
	pause();
	return 0;
}