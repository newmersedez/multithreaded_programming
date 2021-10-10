#include <iostream>
#include <string.h>

class StringPointer
{
private:
    std::string    *ptr;

public:
    StringPointer(std::string *Pointer)
		: ptr(Pointer)
    {}

	~StringPointer()
	{}

    std::string *operator->()
    {
		if (!ptr)
			ptr = new std::string("");
        return ptr;
    }
    
    operator std::string*()
    {
		if (!ptr)
			ptr = new std::string("");
        return ptr;
    }
};

int main()
{
	std::string s1 = "Hello, world!";

	StringPointer sp1(&s1);
	StringPointer sp2(nullptr);

	std::cout << sp1->length() << std::endl;
	std::cout << *sp1 << std::endl;
	std::cout << sp2->length() << std::endl;
	std::cout << *sp2 << std::endl;
	return 0;
}