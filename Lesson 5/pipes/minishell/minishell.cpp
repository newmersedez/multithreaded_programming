#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void parse_commands(std::vector<std::string>& command_vec,
							const std::string& command_line,	
							std::string delimiter)
{
	auto	start = 0UL;
	auto	end = command_line.find(delimiter, start);

	while (end != std::string::npos)
	{
		command_vec.push_back(command_line.substr(start, end - start));
		start = end + delimiter.length();
		end = command_line.find(delimiter, start);
	}
	command_vec.push_back(command_line.substr(start, end));
}

static void	operate_multiple_commands(std::vector<std::string>& commands_vec)
{
	int		fd[2];
	pid_t	child_pid;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	child_pid = fork();
	if (child_pid == 0)
	{
		close(STDOUT_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		execlp(commands_vec[0].c_str(), commands_vec[0].c_str(), NULL);
	}
	else
	{
		close(STDIN_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp(commands_vec[1].c_str(), commands_vec[1].c_str(), NULL);
	}
	close(fd[0]);
	close(fd[1]);
}

int main(int argc, char *argv[])
{
	std::vector<std::string>	command_vec;
	std::string					command_line;

	std::getline(std::cin, command_line);
	parse_commands(command_vec, command_line, " | ");
	if (command_vec.size() == 1)
		execlp(command_vec[0].c_str(), command_vec[0].c_str(), NULL);
	else
		operate_multiple_commands(command_vec);
	return 0;
}