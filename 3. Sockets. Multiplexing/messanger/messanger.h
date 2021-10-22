#ifndef MESSANGER_H
# define MESSANGER_H

# include <set>
# include <iostream>
# include <string.h>
# include <algorithm>
# include <ostream>

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <sys/socket.h>

# define PORT					12345
# define IPv4_SIZE				15
# define MESSAGE_SIZE			256
# define BUFFER_SIZE			MESSAGE_SIZE + IPv4_SIZE + 1 

# define GOOD					"Success exit"
# define IP_ERROR				"Incorrect ip address"
# define SOCKET_CREATE_ERROR	"Failed to create socket"
# define SOCKET_CONNECT_ERROR	"Failed to connect socket"
# define SOCKET_BIND_ERROR		"Failed to bind socket"
# define SOCKET_LISTEN_ERROR	"Failed to listen socket"
# define SOCKET_ACCEPT_ERROR	"Failed to accept socket"
# define SOCKET_SEND_ERROR		"Failed to send buffer"
# define SOCKET_RECV_ERROR		"Failed to recieve buffer"

void	terminate(std::ostream& stream, std::string message, int code);

#endif