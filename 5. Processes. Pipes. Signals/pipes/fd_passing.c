#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>

ssize_t	sock_fd_write(int sock, void *buf, ssize_t buflen, int fd)
{
	ssize_t 		size;
	struct iovec	iov;
	struct msghdr	msg;
	struct cmsghdr	*cmsg;
	union
	{
		struct cmsghdr cmsghdr;
		char control[CMSG_SPACE(sizeof(int))];
	}	cmsgu;

	iov.iov_base = buf;
	iov.iov_len = buflen;
	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	if (fd!=-1)
	{
		msg.msg_control = cmsgu.control;
		msg.msg_controllen = sizeof(cmsgu.control);
		cmsg = CMSG_FIRSTHDR(&msg);
		cmsg->cmsg_len = CMSG_LEN(sizeof(int));
		cmsg->cmsg_level = SOL_SOCKET;
		cmsg->cmsg_type = SCM_RIGHTS;
		printf("passing fd %d\n", fd);
		*((int *) CMSG_DATA(cmsg)) = fd;
	}
	else
	{
		msg.msg_control = NULL;
		msg.msg_controllen = 0;
		printf("not passing fd\n");
	}
  	size = sendmsg(sock, &msg, 0);
 	if (size < 0)
  		perror("sendmsg");
	return (size);
};

ssize_t	sock_fd_read(int sock, void *buf, ssize_t buflen, int *fd)
{
	ssize_t	size;
  	
	if (fd)
	{
		struct iovec iov;
		struct msghdr msg;
		struct cmsghdr *cmsg;
		union
		{
			struct cmsghdr cmsghdr;
			char control[CMSG_SPACE(sizeof(int))];
		}	cmsgu;

		iov.iov_base = buf;
		iov.iov_len = buflen;
		msg.msg_name = NULL;
		msg.msg_namelen = 0;
		msg.msg_iov = &iov;
		msg.msg_iovlen = 1;
		size = recvmsg(sock, &msg, 0);
		cmsg = CMSG_FIRSTHDR(&msg);
		if (cmsg && cmsg->cmsg_len == CMSG_LEN(sizeof(int)))
		{
			if (cmsg->cmsg_level != SOL_SOCKET)
			{
				fprintf(stdout,"invalid cmsg_level %d\n", cmsg->cmsg_level);
				exit(1);
			}
			if (cmsg->cmsg_type != SCM_RIGHTS)
			{
				fprintf(stderr,"invalid cmsg_type %d\n", cmsg->cmsg_type);
				exit(1);
			}
			*fd = *((int *) CMSG_DATA(cmsg));
			printf("received fd %d\n", *fd);
		}
		else
			*fd =- 1;
  	}
	else
	{
    	size = read(sock, buf, buflen);
    	if (size < 0)
		{
      		perror("read");
    		exit(1);
    	}
  	}
	return (size);
};

int main()
{
	int		socketPairResult;
	int		s[2];
	int		fd1 = 1;
	char	b[] = "0\n";
	char	buf[512];
  
	socketPairResult = socketpair(AF_UNIX, SOCK_STREAM, 0, s);
	sock_fd_write(s[0], b, 3, 1);
	sock_fd_read(s[1], &buf, 512, &fd1);
	printf("fd = %d\n", fd1);
	return (0);
} 