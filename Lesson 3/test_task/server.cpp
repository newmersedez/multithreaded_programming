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
		int slaveSocket = accept(masterSocket, 0, 0);
		int	buffer[5] = {0, 0, 0, 0, 0};

		recv(slaveSocket, buffer, 4, MSG_NOSIGNAL);
		send(slaveSocket, buffer, 4, MSG_NOSIGNAL);
		shutdown(slaveSocket, SHUT_RDWR);
		close(slaveSocket);
		printf("%s\n", (char *)buffer);
	}
	return 0;
}