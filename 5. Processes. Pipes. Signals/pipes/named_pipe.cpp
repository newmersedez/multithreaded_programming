#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
	const char	*fifo_in = "/home/box/in.fifo";
	const char	*fifo_out = "/home/box/out.fifo";

	mkfifo(fifo_in, 0666);
	mkfifo(fifo_out, 0666);
	
	size_t	len = 0;
	char	buffer[4096];
	int		read_d = open(fifo_in, O_RDONLY);
	int		write_d = open(fifo_out, O_WRONLY);
	
	while ((len = read(read_d, buffer, sizeof(buffer))) > 0)
		write(write_d, buffer, len);
	close(read_d);
	close(write_d);
	
	return 0;
}