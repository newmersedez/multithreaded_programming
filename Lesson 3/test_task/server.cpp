#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	int					masterSocket;
	struct sockaddr_in	sockAddr;

	masterSocket = socket(AF_INET, SOCK_STREAM, 0);
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(12345);
	sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);	// 0.0.0.0
	bind(masterSocket, (struct sockaddr *)&sockAddr, sizeof(sockAddr));
	listen(masterSocket, SOMAXCONN);
	while (true)
	{
		int 	slaveSocket = accept(masterSocket, 0, 0);
		int		buffer_recv[10] = {0};
		char	buffer_send[10] = "MSG RECV";

		recv(slaveSocket, buffer_recv, 9, MSG_NOSIGNAL);
		printf("From client = %s\n", (char *)buffer_recv);
		send(slaveSocket, buffer_send, 9, MSG_NOSIGNAL);
		shutdown(slaveSocket, SHUT_RDWR);
		close(slaveSocket);
	}
	return 0;
}