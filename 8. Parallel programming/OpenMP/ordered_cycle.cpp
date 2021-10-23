#include <iostream>

int main(int argc, char *argv[])
{
	#pragma omp parallel for ordered
	for (int i = 0; i < 100; i++)
	{
		std::cout << "Cycle ";
		#pragma omp ordered
		{
			std::cout << i << std::endl;
		}
	}
	return 0;
}