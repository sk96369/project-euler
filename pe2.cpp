#include <iostream>
#include <list>
#include <iterator>

using ull_int = unsigned long long int;

int main()
{
	std::list<int>::iterator ptr;
	std::list<int> fib;
	fib.push_back(1);
	fib.push_back(1);
	ull_int sum = 0;
	ptr = fib.begin();
	while(*ptr < 4000001)
	{
		fib.push_back(*ptr+fib.back());
		ptr++;
	}
	for(auto ptr = fib.begin();ptr != fib.end();ptr++)
	{
		std::cout << *ptr << std::endl;
		if(*ptr % 2 == 0)
		{
			if(*ptr < 4000001)
				sum+=*ptr;
		}
	}
	std::cout << sum << std::endl;
	return 0;
}
