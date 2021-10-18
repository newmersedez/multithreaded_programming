#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <array>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

# define FILE_PATH	"/home/dmitry/Work/multithreaded_programming/Lesson 5/pipes/minishell/result.out"

static void parse_args(std::vector<std::string>& command_vec,
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

static void	operate_single_command(const std::string& command)
{
	int							fout;
	char						*exec_args[1024];
	size_t						size = 0;
	std::vector<std::string>	commands_vec;

	parse_args(commands_vec, command, " ");
	for (int i = 0; i < commands_vec.size(); i++)
		exec_args[size++] = strdup(commands_vec[i].c_str());
	exec_args[size] = NULL;
	if ((fout = open(FILE_PATH, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
		exit(EXIT_FAILURE);
	close(STDOUT_FILENO);
	dup2(fout, STDOUT_FILENO);
	execv("/bin:/usr/bin", exec_args);
	close(fout);
}

static void	operate_multiple_commands(std::vector<std::string>& commands_vec)
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
	parse_args(command_vec, command_line, " | ");
	for (const auto& obj: command_vec)
		std::cout << "\"" << obj << "\"" << std::endl;
	// if (command_vec.size() == 1)
	// 	operate_single_command(command_vec[0]);
	// else
	// 	operate_multiple_commands(command_vec);
	return 0;
}