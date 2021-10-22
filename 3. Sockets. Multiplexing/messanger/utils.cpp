#include "messanger.h"

void	terminate(std::ostream& stream, std::string message, int code)
{
	stream << message << std::endl;
	exit(code);
}