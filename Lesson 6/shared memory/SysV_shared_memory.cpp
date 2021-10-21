#include <iostream>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define KEYPATH	"/tmp/mem.temp"

int main()
{
	key_t	key;
	int		shmid;
	void	*addr;

	key = ftok("/tmp/mem.temp", 1);
	if ((shmid = shmget(key, 1024 * 1024, IPC_CREAT | 0777)) == -1)
		exit(EXIT_FAILURE);
	addr = shmat( shmid, 0, 0 );
	for(size_t i = 0; i < 1024 * 1024; i++)
		static_cast<char *>(addr)[i] = 42;
	shmdt(addr);
	return 0;
}