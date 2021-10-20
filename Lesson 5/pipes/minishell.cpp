// #include <iostream>
// #include <vector>
// #include <string.h>
// #include <sstream>

// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>

// #define BUFFER_SIZE 1024
// #define CLOSE(fd) if (fd < -1) close(fd); fd = -1
// static int fifo[2][2] = {-1, -1, -1, -1}, curr_pipe = 0;

// void split(std::vector<std::string>& cmd_vec,
// 			const std::string& cmd, std::string delim)
// {
// 	size_t 				i = 0;
// 	size_t 				length = cmd.length();
// 	std::stringstream	sstream;

// 	while (i < length)
// 	{
// 		if (delim.find(cmd[i]) == std::string::npos)
// 		{
// 			while (i < length && delim.find(cmd[i]) == std::string::npos)
// 				sstream << cmd[i++];
// 			cmd_vec.push_back(sstream.str());
// 			sstream.str("");
// 		}
// 		else
// 			i++;
// 	}
// }

// void operate_pipe_command(const std::vector<std::string>& cmd_vec)
// {
// 	size_t	i = 0;

// 	while (i < cmd_vec.size))
// }

// int main()
// {
// 	int							fd[2];
// 	std::string					argv;
// 	std::vector<std::string>	argv_vec;

// 	std::getline(std::cin, argv);
// 	split(argv_vec, argv, "|");
// 	if (argv_vec.size() == 0)
// 		return 0;
// 	else 
// 		operate_pipe_command(argv_vec);
// 	return 0;
// }
