#include <iostream>

int main(int argc, char *argv)
{
	#pragma omp task	// like detached thread, but also can be joinable
	{

	}
	#pragma omp taskwait
	return 0;
}
