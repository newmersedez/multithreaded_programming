#include <iostream>
#include <vector>
#include <stdlib.h>

void merge(std::vector<int>& vec, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  
    /* create temp vecays */
    std::vector<int>	L(n1);
	std::vector<int>	R(n2);
  
    /* Copy data to temp vecays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = vec[l + i];
    for (j = 0; j < n2; j++)
        R[j] = vec[m + 1 + j];
  
    /* Merge the temp vecays back into vec[l..r]*/
    i = 0; // Initial index of first subvecay
    j = 0; // Initial index of second subvecay
    k = l; // Initial index of merged subvecay
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vec[k] = L[i];
            i++;
        }
        else {
            vec[k] = R[j];
            j++;
        }
        k++;
    }
  
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        vec[k] = L[i];
        i++;
        k++;
    }
  
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        vec[k] = R[j];
        j++;
        k++;
    }
}
  
/* l is for left index and r is right index of the
sub-vecay of vec to be sorted */
void mergeSort(std::vector<int>& vec, int l, int r)
{
    if (l >= r)
		return ;
	// Same as (l+r)/2, but avoids overflow for
	// large l and h
	int m = (l + r) / 2;

	// Sort first and second halves
	mergeSort(vec, l, m);
	mergeSort(vec, m + 1, r);
	merge(vec, l, m, r);
}

void fillVec(std::vector<int>& vec, size_t size)
{
	int	temp;

	for (size_t i = 0; i < size; i++)
	{
		std::cin >> temp;
		vec.push_back(temp);
	}
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

	fillVec(vec, 6);
	mergeSort(vec, 0, 5);
	printVec(vec);
	return 0;
}