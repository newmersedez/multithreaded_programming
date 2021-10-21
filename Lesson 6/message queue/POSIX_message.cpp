#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <mqueue.h>
#include <memory.h>

int main()
{
	mqd_t	mqid;
	mq_attr	attr;

	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = 128;
	attr.mq_curmsgs = 0;
	mqid = mq_open("/test.mq", O_CREAT | O_RDWR, 0666, &attr);
	
	int		fd;
	size_t	size;
	char	buffer[256] = {0};

	size = mq_receive(mqid, buffer, 256, 0);
	mq_close(mqid);
	mq_unlink("/test.mq");
	fd = open("/home/box/message.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	write(fd, buffer, size);
	close(fd);
	return 0;
}