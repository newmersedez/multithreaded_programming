#include <iostream>
#include <fstream>
#include <unistd.h>
#include <pthread.h>

void *thread_mutex(void *arg)
{
	pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
	
	pthread_mutex_lock(&m);
	sleep(2);
	return (NULL);
}

void *thread_spinblock(void *arg)
{
	pthread_spinlock_t	spinlock;

	pthread_spin_lock(&spinlock);
	sleep(2);
	return (NULL);
}

void *thread_rw_read(void *arg)
{
	pthread_rwlock_t rlock = PTHREAD_RWLOCK_INITIALIZER;

	pthread_rwlock_rdlock(&rlock);
	sleep(1);
	return (NULL);
}

void *thread_rw_write(void *arg)
{
	pthread_rwlock_t wlock = PTHREAD_RWLOCK_INITIALIZER;

	pthread_rwlock_wrlock(&wlock);
	sleep(1);
	return (NULL);
}

int main()
{
	std::ofstream	stream;

	stream.open("main.pid");
	stream << getpid();
	stream.close();

	pthread_t	thread1;
	pthread_create(&thread1, 0, thread_mutex, 0);
	pthread_detach(thread1);
	
	pthread_t	thread2;
	pthread_create(&thread2, 0, thread_spinblock, 0);
	pthread_detach(thread2);

	pthread_t	thread3;
	pthread_create(&thread3, 0, thread_rw_read, 0);
	pthread_detach(thread3);
	
	pthread_t	thread4;
	pthread_create(&thread4, 0, thread_rw_write, 0);
	pthread_detach(thread4);
	return 0;
}