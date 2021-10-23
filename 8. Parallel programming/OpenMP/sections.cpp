#include <iostream>

int main(int argc, char *argv)
{
	#pragma omp sections			// like pthreads in c
	{
		#pragma omp section
		{
			/* code 1 */
		}
		#pragma omp section
		{
			/* other code 2 */
		}
	}
	return 0;
}
