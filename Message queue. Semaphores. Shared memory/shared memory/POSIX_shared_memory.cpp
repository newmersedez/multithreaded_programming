#include <iostream>

#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <fcntl.h>

int	main()
{
	int		shmfd;
	void	*addr;

	shmfd = shm_open("/test.shm",  O_CREAT | O_RDWR | O_TRUNC, 0666);
	ftruncate(shmfd, 1024 * 1024);
	addr = mmap(0, 1024 * 1024, PROT_WRITE, MAP_SHARED, shmfd, 0);
	for( int i = 0; i < 1024*1024; i++ )
		static_cast<char *>(addr)[i] = 13;
	munmap(addr, 1024 * 1024);
	close(shmfd);
	return 0;
}
