#include <iostream>

int main(int argc, char *argv[])
{
	#pragma omp parallel
	{
		#pragma omp critical
		{
			std::cout << "output" << std::endl;
		}
	}
	return 0;
}