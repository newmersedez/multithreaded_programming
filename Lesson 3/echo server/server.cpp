#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sstream>

static void get_message(int fd)
{
	int					slaveSocket;
	char				buffer[BUFSIZ] = {0};
	size_t				recvCount;
	std::stringstream	sStream;

	while (true)
	{
		if ((slaveSocket = accept(fd, 0, 0)) == -1)
		{
			std::cerr << "Failed to accept socket" << std::endl;
			exit(EXIT_FAILURE);
		}
		if ((recvCount = recv(slaveSocket, buffer, BUFSIZ - 1, MSG_NOSIGNAL)) > 0)
		{
			send(slaveSocket, buffer, recvCount, MSG_NOSIGNAL);
			sStream << buffer;
		}
		shutdown(slaveSocket, SHUT_RDWR);
		close(slaveSocket);
		std::cout << sStream.str() << std::endl;
	}
}

static void echo_server(int domain, int type, int protocol,
				const char *addr, uint16_t port)
{
	int					masterSocket;
	struct sockaddr_in	sockAddr;

	sockAddr.sin_family = domain;
	sockAddr.sin_port = htons(port);
	sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (inet_pton(domain, addr, &sockAddr.sin_addr) == -1)
	{
		std::cerr << "inet_pton error" << std::endl;
		exit(EXIT_FAILURE);
	}
	if ((masterSocket = socket(domain, type, protocol)) == -1)
	{
		std::cerr << "Failed to create IPv4 TCP socket" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (bind(masterSocket, (const sockaddr *)&sockAddr, sizeof(sockAddr)) == -1)
	{
		std::cerr << "Failed to bind socket" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (listen(masterSocket, SOMAXCONN) == -1)
	{
		std::cerr << "Failed to listen socket" << std::endl;
		exit(EXIT_FAILURE);
	}
	get_message(masterSocket);
	shutdown(masterSocket, SHUT_RDWR);
	close(masterSocket);
}

int main()
{
	echo_server(AF_INET, SOCK_STREAM, IPPROTO_TCP, "127.0.0.1",	7777);
	return 0;
}