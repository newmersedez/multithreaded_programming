#include "messanger.h"

int main(int argc, char *argv[])
{
	int					masterSocket;
	char				buffer[BUFFER_SIZE];
	struct	sockaddr_in	sockAddr;

	if (argc != 2)
		terminate(std::cerr, IP_ERROR, EXIT_FAILURE);
	if ((masterSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		terminate(std::cerr, SOCKET_CREATE_ERROR, EXIT_FAILURE);
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(PORT);
	if (inet_pton(AF_INET, argv[1], &sockAddr.sin_addr) == -1)
		terminate(std::cerr, IP_ERROR, EXIT_FAILURE);
	if (connect(masterSocket, (struct sockaddr *)&sockAddr, sizeof(sockAddr)) == -1)
		terminate(std::cerr, SOCKET_CONNECT_ERROR, EXIT_FAILURE);
	while (true)
	{
		std::cout << "Type message (type \"Exit\" for disconnect): ";
		std::cin >> buffer;
		if (!strcmp(buffer, "Exit"))
			break ;
		strcat(buffer, ": ");
		strcat(buffer, argv[1]);
		if (send(masterSocket, buffer, BUFFER_SIZE, MSG_NOSIGNAL) == -1)
			terminate(std::cerr, SOCKET_SEND_ERROR, EXIT_FAILURE);
		if (recv(masterSocket, buffer, BUFFER_SIZE, MSG_NOSIGNAL) == -1)
			terminate(std::cerr, SOCKET_RECV_ERROR, EXIT_FAILURE);
		std::cout << buffer << std::endl;
	}
	shutdown(masterSocket, O_RDWR);
	close(masterSocket);
	return 0;
}