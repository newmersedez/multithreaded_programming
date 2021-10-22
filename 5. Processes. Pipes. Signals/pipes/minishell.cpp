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

static void split(std::vector<std::string>& commands_vec,
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

static void exec_pipe_command(std::vector<std::string> commands_vec)
{
	int		fd[2], fdd = 0, status;
	pid_t	child_pid;

	for (const auto& command: commands_vec)
	{
        std::vector<std::string>    exec_vec;
		size_t                      size = 0;
		char                        *exec_array[COMMAND_BUFSIZ];

		split(exec_vec, command, " ");
		for (size_t i = 0; i < exec_vec.size(); i++)
			exec_array[size++] = const_cast<char *>(exec_vec[i].c_str());
		exec_array[size] = NULL;
		
		if (pipe(fd) < 0)
			{ perror("pipe"), exit(EXIT_FAILURE); }
		child_pid = fork();
		if (child_pid < 0)
			{ perror("fork"), exit(EXIT_FAILURE); }
		else if (child_pid == 0)
		{
			if (dup2(fdd, 0) < 0)
				{ perror("dup2"), exit(EXIT_FAILURE); }
			if (command != commands_vec.back())
			{
				if (dup2(fd[1], 1) < 0)
					{ perror("dup2"), exit(EXIT_FAILURE); }
			}
			close(fd[0]);
			execvp(exec_array[0], exec_array);
			perror("execvp");
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(child_pid, &status, 0);
			close(fd[1]);
			fdd = fd[0];
		}
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