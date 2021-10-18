#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

# define FILE_PATH	"/home/dmitry/Work/multithreaded_programming/Lesson 5/pipes/minishell/result.out"

static void parse_args(std::vector<std::string>& args_vec,
							const std::string& args_line,	
							std::string delim)
{
	size_t 				i = 0;
	size_t 				length = args_line.length();
	std::stringstream	sstream;

	while (i < length)
	{
		if (delim.find(args_line[i]) == std::string::npos)
		{
			while (i < length && delim.find(args_line[i]) == std::string::npos)
				sstream << args_line[i++];
			args_vec.push_back(sstream.str());
			sstream.str("");
		}
		else
			i++;
	}
}

static void	operate_single_command(const std::string& arg)
{
	int							fout;
	char						*exec_args[1024];
	size_t						size = 0;
	std::vector<std::string>	args_vec;

	parse_args(args_vec, arg, " ");
	for (size_t i = 0; i < args_vec.size(); i++)
		exec_args[size++] = strdup(args_vec[i].c_str());
	exec_args[size] = NULL;
	if ((fout = open(FILE_PATH, O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
		exit(EXIT_FAILURE);
	close(STDOUT_FILENO);
	dup2(fout, STDOUT_FILENO);
	execvp(exec_args[0], exec_args);
	close(fout);
	while (exec_args[--size])
		free(exec_args[size]);
}

static void	operate_multiple_commands(std::vector<std::string>& args_vec)
{
	int		fd[2];
	int		fout;
	pid_t	child_pid;

	if ((fout = open(FILE_PATH, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
		exit(EXIT_FAILURE);
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	child_pid = fork();
	if (child_pid == 0)
	{
		close(fout);
		dup2(fd[1], fout);
		close(fd[1]);
		close(fd[0]);
		execlp(args_vec[0].c_str(), args_vec[0].c_str(), NULL);
	}
	else
	{
		close(STDIN_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp(args_vec[1].c_str(), args_vec[1].c_str(), NULL);
	}
	close(fd[0]);
	close(fd[1]);
}

int main(int argc, char *argv[])
{
	std::vector<std::string>	command_vec;
	std::string					command_line;

	std::getline(std::cin, command_line);
	parse_args(command_vec, command_line, "|");
	if (command_vec.size() == 1)
		operate_single_command(command_vec[0]);
	else if (command_vec.size() > 1)
		operate_multiple_commands(command_vec);
	return 0;
}