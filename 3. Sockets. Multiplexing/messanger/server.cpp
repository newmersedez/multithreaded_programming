#include "messanger.h"

static int	set_nonblock(int fd)
{
	int	flags;

	#if defined (O_NONBLOCK)
		if ((flags = fcntl(fd, F_GETFL, 0)) == -1)
			flags = 0;
		return (fcntl(fd, F_SETFL, flags | O_NONBLOCK));
	#else
		flags = 1;
		return ioctl(fd, FIOBIO, &flags);
	#endif
}

int main()
{
	int					master_socket;
	std::set<int>		slave_sockets;
	struct sockaddr_in	sock_addr;

	if ((master_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		terminate(std::cerr, SOCKET_CREATE_ERROR, EXIT_FAILURE);
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(PORT);
	sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(master_socket, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) == -1)
		terminate(std::cerr, SOCKET_BIND_ERROR, EXIT_FAILURE);
	set_nonblock(master_socket);
	if (listen(master_socket, SOMAXCONN) == -1)
		terminate(std::cerr, SOCKET_LISTEN_ERROR, EXIT_FAILURE);
	while (true)
	{
		fd_set	set;
		int		max_fd;

		FD_ZERO(&set);
		FD_SET(master_socket, &set);
		for (const auto &obj: slave_sockets)
		{
			FD_SET(obj, &set);
		}
		max_fd = std::max(master_socket,
				*std::max_element(slave_sockets.begin(),
				slave_sockets.end()));
		select(max_fd + 1, &set, NULL, NULL, NULL);
		for (auto iter = slave_sockets.begin();
			iter != slave_sockets.end();
			iter++)
		{
			if (FD_ISSET(*iter, &set))
			{
				int			recv_size;
				static char	buffer[BUFFER_SIZE];

				recv_size = recv(*iter, buffer, BUFFER_SIZE, MSG_NOSIGNAL);
				if (recv_size == 0 && errno != EAGAIN)
				{
					std::cout << *iter << " socket disconnected" << std::endl;
					shutdown(*iter, SHUT_RDWR);
					close(*iter);
					iter = slave_sockets.erase(iter);
					if (slave_sockets.size() == 0)
						terminate(std::cout, GOOD, EXIT_SUCCESS);
				}
				else if (recv_size != 0)
					for (auto iter2 = slave_sockets.begin();
							iter2 != slave_sockets.end();
							iter2++)
						send(*iter2, buffer, recv_size, MSG_NOSIGNAL);
			}
		}
		if (FD_ISSET(master_socket, &set))
		{
			int	slave_socket;
		
			if ((slave_socket = accept(master_socket, 0, 0)) == -1)
				terminate(std::cerr, SOCKET_ACCEPT_ERROR, EXIT_FAILURE);
			set_nonblock(slave_socket);
			slave_sockets.insert(slave_socket);
			std::cout << slave_socket << " socket connected" << std::endl;
		}
	}
	shutdown(master_socket, SHUT_RDWR);
	close(master_socket);
	return 0;
}