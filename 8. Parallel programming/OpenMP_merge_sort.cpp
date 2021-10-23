#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

void mergeSort(std::vector<int>& vec, int left, int right)
{
	if (left < right)
	{
		if (right - left >= 32)
		{
			int mid = (left + right) / 2; 
			#pragma omp taskgroup
    		{
				#pragma omp task shared(vec) untied if(right - left >= (1<<14))
					mergeSort(vec, left, mid);
				#pragma omp task shared(vec) untied if(right - left >= (1<<14))
					mergeSort(vec, mid + 1, right);
				#pragma omp taskyield
			}
			std::inplace_merge(vec.begin() + left, vec.begin() + mid + 1, vec.begin() + right + 1);
		}
		else
			std::sort(vec.begin() + left, vec.begin() + right + 1);
	}
}

void mergeSort(std::vector<int>& vec) 
{
	#pragma omp parallel
		#pragma omp single
			mergeSort(vec, 0, vec.size() - 1); 
}

int main(int argc, char *argv[])
{
	int					temp;
	std::vector<int>	vec;

	for (int i = 0; i < 6; i++)
	{
		std::cin >> temp;
		vec.push_back(temp);
	}
	mergeSort(vec);
	for (const auto& obj: vec)
		std::cout << obj << " ";
	std::cout << std::endl;
	return 0;
}
