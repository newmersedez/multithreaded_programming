#include <iostream>
#include <omp.h>

int main(int argc, char *argv[])
{
	#pragma omp parallel
	{
		std::cout << "1" << std::endl;
		std::cout << "2" << std::endl;
		std::cout << "3" << std::endl;
		#pragma omp barrier
	}
	return 0;
}
