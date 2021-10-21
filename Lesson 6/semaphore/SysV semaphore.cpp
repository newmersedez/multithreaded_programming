#include <iostream>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>

#define SEMNUM 16
#define KEYPATH "/home/dmitry/Work/multithreaded_programming/Lesson 6/semaphore/sem.temp"

union semnum
{
	int				val;
	struct semid_ds	*buf;
	unsigned short	*array;
};

int main()
{
	int				semid;
	key_t			key;
	union semnum	arg;

	key = ftok(KEYPATH, 1);
	if ((semid = semget(key, SEMNUM, IPC_CREAT | 0777)) == -1)
		exit(EXIT_FAILURE);
	for (int i = 0; i < SEMNUM; i++)
	{
		arg.val = i;
		semctl(semid, i, SETVAL, arg);
	}
	return 0;
}
