#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

#define COMMAND_BUFSIZ	16

void split(std::vector<std::string>& commands_vec,
			const std::string& command, std::string delim)
{
	size_t 				i = 0, length = command.length();
	std::stringstream	sstream;

	while (i < length)
	{
		if (delim.find(command[i]) == std::string::npos)
		{
			while (i < length && delim.find(command[i]) == std::string::npos)
				sstream << command[i++];
			commands_vec.push_back(sstream.str());
			sstream.str("");
		}
		else
			i++;
	}
}

void exec_pipe_command(std::vector<std::string> commands_vec)
{
	size_t	argc = 0;
	for (auto command : commands_vec)
	{
		std::vector<std::string>	exec_vec;
		size_t						size = 0;
		char						*exec_array[COMMAND_BUFSIZ];
	
		split(exec_vec, command, " ");
		for (size_t i = 0; i < exec_vec.size(); i++)
			exec_array[size++] = const_cast<char *>(exec_vec[i].c_str());
		exec_array[size] = NULL;

		int		fd[2];
		pid_t	child_pid;
	
		if (pipe(fd) < 0)
			exit(1);
		child_pid = fork();
		if (child_pid == 0)
		{
			//right command
			if (command != *(commands_vec.begin()))
			{
				if (dup2(fd[0], STDIN_FILENO) < 0)
				{
					perror("dup2");
					exit(1);
				}
			}
			//left command
			if (command != *(commands_vec.end() - 1))
			{
				if (dup2(fd[1], STDOUT_FILENO) < 0)
				{
					perror("dup2");
					exit(1);
				}
			}
			close(fd[0]);
			close(fd[1]);
			execvp(exec_array[0], exec_array);
			perror("execvp");
			exit(1);
		}
		else if (child_pid < 0)
		{
			perror("fork");
			exit(1);
		}
		argc++;
	}
}

int main()
{
	std::vector<std::string>	commands_vec;
	std::string					command;

	std::getline(std::cin, command);
	split(commands_vec, command, "|");
	if (commands_vec.size() > 0)
		exec_pipe_command(commands_vec);
	return (0);
}
