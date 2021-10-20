#include <iostream>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <memory.h>
#include <unistd.h>

#define KEYFILE_PATH	"/home/dmitry/Work/multithreaded_programming/Lesson 6/message queue/msg.temp"
#define OUTPUTFILE_PATH	"/home/dmitry/Work/multithreaded_programming/Lesson 6/message queue/message.txt"

struct message
{
	long mtype;
	char mtext[80];
};

int main()
{
	struct message	msg;
	key_t			key;
	size_t			recv_size, write_len;
	int				keyd, outputd, msgid;

	if ((keyd = creat(KEYFILE_PATH, 0666)) == -1)
		exit(EXIT_FAILURE);
	if ((key = ftok(KEYFILE_PATH, 1)) == -1)
		exit(EXIT_FAILURE);
	if ((msgid = msgget(key, IPC_CREAT | 0666)) == -1)
		exit(EXIT_FAILURE);
	if ((recv_size = msgrcv(msgid, &msg, 80, 0, 0)) == -1)
		exit(EXIT_FAILURE);
	if (msgctl(msgid, IPC_RMID, NULL) == -1)	
		exit(EXIT_FAILURE);
	if ((outputd= open(OUTPUTFILE_PATH, O_CREAT | O_WRONLY | O_TRUNC)) == -1)
		exit(EXIT_FAILURE);
	if ((write_len = write(outputd, msg.mtext, recv_size)) < recv_size)
		exit(EXIT_FAILURE);
	return 0;
}