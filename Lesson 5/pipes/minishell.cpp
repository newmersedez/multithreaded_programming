// execlp("/bin/sh", "sh", "-c", command.c_str(), NULL);
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
	int		fd[2], status;
	pid_t	cpid;

	for (const auto& command: commands_vec)
	{
		std::vector<std::string>	exec_vec;
		size_t						size = 0;
		char						*exec_array[COMMAND_BUFSIZ];

		split(exec_vec, command, " ");
		for (size_t i = 0; i < exec_vec.size(); i++)
			exec_array[size++] = const_cast<char *>(exec_vec[i].c_str());
		exec_array[size] = NULL;
		
		cpid = fork();
		if (cpid == 0)
		{
			// left command
			if (command != commands_vec.back())
			{
				// close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				execvp(exec_array[0], exec_array);
			}
			// right command
			if (command != commands_vec.front())
			{
				// close(fd[1]);
				dup2(fd[0], STDIN_FILENO);
				execvp(exec_array[0], exec_array);
			}
		}
		close(fd[0]);
		close(fd[1]);
		waitpid(-1, &status, 1);
	}

	// // left pipe command
	// cpid = fork();
	// if (cpid == 0)
	// {
	// 	close(fd[0]);
	// 	dup2(fd[1], STDOUT_FILENO);
	// 	execlp("/bin/sh", "sh", "-c", commands_vec[0].c_str(), NULL);
	// }
	// // right pipe command
	// cpid = fork();
	// if (cpid == 0)
	// {
	// 	close(fd[1]);
	// 	dup2(fd[0], STDIN_FILENO);
	// 	execlp("/bin/sh", "sh", "-c", commands_vec[1].c_str(), NULL);
	// }
	// close(fd[0]);
	// close(fd[1]);
	// waitpid(-1, &status, 0);
	// waitpid(-1, &status, 0);
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