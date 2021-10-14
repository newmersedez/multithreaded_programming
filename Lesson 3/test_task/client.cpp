#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	int					masterSocket;
	struct sockaddr_in	sockAddr;
	char				buffer[5] = "PING";

	masterSocket = socket(AF_INET, SOCK_STREAM, 0);
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(12345);
	sockAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);	// 127.0.0.1
	connect(masterSocket, (const sockaddr *)&(sockAddr), sizeof(sockAddr));
	send(masterSocket, buffer, 4, MSG_NOSIGNAL);
	recv(masterSocket, buffer, 4, MSG_NOSIGNAL);
	shutdown(masterSocket, SHUT_RDWR);
	close(masterSocket);
	printf("%s\n", buffer);
	return 0;
}