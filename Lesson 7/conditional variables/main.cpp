#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <fstream>
#include <pthread.h>

void *pthread_cond_var(void *arg)
{
	pthread_cond_t	cond = PTHREAD_COND_INITIALIZER;
	pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_cond_wait(&cond, &mutex);
	sleep(2);
	return NULL;
}

void *pthread_barrier(void *arg)
{
	pthread_barrier_t br;
	pthread_barrierattr_t attr;

	pthread_barrier_init(&br, &attr, 1);
	sleep(2);
	pthread_barrier_wait(&br);
	return NULL;
}

int main()
{
	std::ofstream stream;

	stream.open("main.pid");
	stream << getpid();
	stream.close();

	pthread_t	thread1;
	pthread_create(&thread1, NULL, pthread_cond_var, NULL);
	pthread_detach(thread1);

	pthread_t	thread2;
	pthread_create(&thread2, NULL, pthread_barrier, NULL);
	pthread_detach(thread2);
	return 0;
}