#include <iostream>
#include <stdlib.h>
#include <memory.h>

class SmallAllocator
{
private:
	char Memory[1048576];

public:
	SmallAllocator() = default;
	~SmallAllocator() = default;
	
	void *Alloc(unsigned int Size)
	{
		return (void *)malloc(Size);
	};
	
	void *ReAlloc(void *Pointer, unsigned int Size)
	{
		void	*newPointer;
	
		if (!Pointer)
			return nullptr;
		else if (!Size)
		{
			free(Pointer);
			return nullptr;
		}
		else
		{
			newPointer = (void *)malloc(Size);
			if (!newPointer)
				return nullptr;
			memmove(newPointer, Pointer, Size);
		}
		return newPointer;
	};
    
	void Free(void *Pointer)
	{
		if (Pointer)
			free(Pointer);
	};
};

int main()
{
	SmallAllocator A1;
	SmallAllocator A2;
	
	int * A1_P1 = (int *)A1.Alloc(sizeof(int));
	A1_P1 = (int *) A1.ReAlloc(A1_P1, 2 * sizeof(int));
	A1.Free(A1_P1);

	int * A2_P1 = (int *)A2.Alloc(10 * sizeof(int));
	
	for (unsigned int i = 0; i < 10; i++)
		A2_P1[i] = i;
	
	for (unsigned int i = 0; i < 10; i++)
		if (A2_P1[i] != i)
			std::cout << "ERROR 1" << std::endl;
	
	int * A2_P2 = (int *)A2.Alloc(10 * sizeof(int));
	for (unsigned int i = 0; i < 10; i++)
		A2_P2[i] = -1;
	
	for (unsigned int i = 0; i < 10; i++)
		if (A2_P1[i] != i)
			std::cout << "ERROR 2" << std::endl;
	
	for (unsigned int i = 0; i < 10; i++)
		if (A2_P2[i] != -1)
			std::cout << "ERROR 3" << std::endl;
	
	A2_P1 = (int *)A2.ReAlloc(A2_P1, 20 * sizeof(int));
	for (unsigned int i = 10; i < 20; i++)
		A2_P1[i] = i;

	for (unsigned int i = 0; i < 20; i++)
		if (A2_P1[i] != i)
			std::cout << "ERROR 4" << std::endl;
	
	for (unsigned int i = 0; i < 10; i++)
		if (A2_P2[i] != -1)
			std::cout << "ERROR 5" << std::endl;
	
	A2_P1 = (int *)A2.ReAlloc(A2_P1, 5 * sizeof(int));
	for (unsigned int i = 0; i < 5; i++)
		if (A2_P1[i] != i)
			std::cout << "ERROR 6" << std::endl;

	for (unsigned int i = 0; i < 10; i++)
		if (A2_P2[i] != -1)
			std::cout << "ERROR 7" << std::endl;
	
	A2.Free(A2_P1);
	A2.Free(A2_P2);
	return (0);
}