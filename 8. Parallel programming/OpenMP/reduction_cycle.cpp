#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	int	sum = 0;

	#pragma omp parallel for reduction(+:sum)	// parallel for cycle
	for (size_t i = 0; i < 100000; i++)			// reduction for correct sum: splitting parts summed up at the end
	{
		sum = sum + i;
	}
	return 0;
}

/*
NOTE

!!!#pragma omp for is incorrect!!!
Correct variants:
	a)	#pragma omp parallel for
	b)	#pragma omp parallel
		{
			#pragma omp for
			{
				...
			}
		}
*/

