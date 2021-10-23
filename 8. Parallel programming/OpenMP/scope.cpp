#include <iostream>
#include <omp.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int a = 0, b = 12;

	std::cout << "Shared:" << std::endl;
	#pragma omp parallel num_threads(4)								// this variables shared for all threads
	{
		#pragma omp parallel shared(a)
		{
			std::string	str = std::to_string(++a) + "\n";
			write(STDOUT_FILENO, str.c_str(), str.length());	// ~ 1 2 3 4
		}
	}
	std::cout << "\nPrivate:" << std::endl;
	#pragma omp parallel num_threads(4)								// variables private for every thread individually
	{
		#pragma omp parallel private(a)
		{
			a = 0;
			std::string	str = std::to_string(++a) + "\n";
			write(STDOUT_FILENO, str.c_str(), str.length() + 1);	// ~ 1 1 1 1
		}
	}
	return 0;
}