#include <iostream>
#include <omp.h>

int main(int argc, char *argv[])
{
	int	n = 0;

	#pragma omp parallel num_threads(2)
	{
		#pragma omp atomic
			n++;
	}
	std::cout << n << std::endl;
	return 0;
}
