#include <iostream>
#include <fstream>
#include <unistd.h>
#include <pthread.h>

void *thread_func(void *arg)
{
	sleep(30);
	return NULL;
}

int main()
{
	std::ofstream	stream;

	stream.open("main.pid");
	stream << getpid();
	stream.close();
	
	pthread_t	thread;
	pthread_create(&thread, 0, thread_func, 0);
	pthread_join(thread, 0);

	return 0;
}