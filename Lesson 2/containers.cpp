#include<iostream>
#include<map>
#include<string>
#include<sstream>
#include<regex>

std::string derivative(std::string polynomial)
{
	std::regex			m("[+]?([-]?[0-9]*)[\\*]?(x?)[\\^]?([0-9]*)");
	std::smatch			sm;
	std::map<int, int>	pow_k;
	std::ostringstream	result;

	while(regex_search(polynomial, sm, m) && polynomial.size() > 0)
	{
		int	k = atoi(std::string(sm[1]).c_str());
		int	pow = atoi(std::string(sm[3]).c_str());
		
		if (std::string(sm[2]) == "x") 
		{
			if (pow == 0)
				pow = 1;
			if (k == 0)
				k = 1;
			if (std::string(sm[1]) == "-")
				k = -1;
		}
		pow_k[pow] += k;
		polynomial = sm.suffix();
	}
	auto begin = pow_k.rbegin();
	auto end = pow_k.rend();
	auto gets = [](int pow, int k)
	{
		std::ostringstream	member;
		
		member << k * pow;
		if (pow > 1)
			member << "*x";
		if (pow > 2)
			member << '^' << pow-1;
		return member.str();
	};
	if (begin != end)
	{
		result << gets(begin->first, begin->second);
		++begin;
	}
	for(; begin != end; ++begin)
	{
		if (begin->first == 0)
			continue;
		if (begin->second > 0)
			result << '+';
	    result << gets(begin->first, begin->second);
	}
	return result.str();
}

int main()
{
	std::string	polynomial;

	getline(std::cin, polynomial);
	std::cout << derivative(polynomial) << std::endl;
	return 0;
}
