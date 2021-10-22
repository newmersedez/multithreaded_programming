#include <iostream>

#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define SEMNAME "/test.sem"

int main()
{
	sem_t	*semid;

	if ((semid = sem_open(SEMNAME, O_CREAT, S_IRUSR | S_IWUSR, 66)) == NULL)
	{
		exit(EXIT_FAILURE);
	}
	return 0;
}