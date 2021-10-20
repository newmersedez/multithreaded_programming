#include <iostream>
#include <unistd.h>
#include <signal.h>

void operate(int sig_num)
{
	raise(SIGUSR1);
	std::cout << "Signal " << sig_num << " is detected" << std::endl;
}

void	operate2(int sig_num)
{
	std::cout << "SIGUSR1 is catched " << sig_num << std::endl;
}

int main()
{
	struct sigaction	sa;
	struct sigaction	sa2;

	sa.sa_handler = operate;
	sa2.sa_handler = operate2;
	sigaction(SIGINT, &sa, 0);
	sigaction(SIGUSR1, &sa2, 0);
	pause();
	return 0;
}