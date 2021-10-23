#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>

void merge(std::vector<int>& vec, int left, int mid, int right)
{
	int	i, j, k;
	int	size_left = mid - left + 1;
	int	size_right = right - mid;

	std::vector<int>	vec_left(size_left);
	std::vector<int>	vec_right(size_right);

	for (i = 0; i < size_left; i++)
		vec_left[i] = vec[left + i];
	for (j = 0; j < size_right; j++)
		vec_right[j] = vec[mid + j + 1];
	i = 0;
	j = 0;
	k = left;
	while (i < size_left && j < size_right)
	{
		if (vec_left[i] <= vec_right[j])
			vec[k++] = vec_left[i++];
		else
			vec[k++] = vec_right[j++];
	}
	while (i < size_left)
		vec[k++] = vec_left[i++];
	while (j < size_right)
		vec[k++] = vec_right[j++];
}

void mergeSort(std::vector<int>& vec, int left, int right)
{
	int	mid;

	if (left >= right)
		return ;
	mid = (left + right) / 2;
	mergeSort(vec, left, mid);
	mergeSort(vec, mid + 1, right);	
	merge(vec, left, mid, right);
}

void fillVec(std::vector<int>& vec, std::string filename)
{
	int	temp;
	std::ifstream	stream;

	stream.open(filename);
	while (stream >> temp)
		vec.push_back(temp);
	stream.close();
}

void printVec(const std::vector<int>& vec)
{
	for (const auto& obj: vec)
		std::cout << obj << " ";
	std::cout << std::endl;
}

int main(int argc, char *argv[])
{
	std::vector<int>	vec;

	fillVec(vec, "dataset_12656_4.txt");
	mergeSort(vec, 0, vec.size() - 1);
	printVec(vec);
	return 0;
}