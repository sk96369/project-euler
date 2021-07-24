#include <list>
#include <iostream>
#include <fstream>
#include <vector>

using ull_int = unsigned long long int;

struct largevector
{

	ull_int size;
	std::size_t subvectorsize;
	int subvectorcount;
	std::vector<std::vector<ull_int>> vectors;

	largevector(ull_int s) : size(s)
	{
		ull_int n = s;
		std::vector<int> v;
		subvectorsize = v.max_size()/2;
		do
		{
			std::cout << "TEST1 " << v.max_size() << " " << subvectorsize << " " << v.max_size() - subvectorsize << "\n";
			std::vector<ull_int> newvector(subvectorsize, true);
			std::cout << "TEST2\n";
			vectors.push_back(newvector);
			if(n > subvectorsize)
				n -= subvectorsize;
			else
				n = 0;
			subvectorcount++;
			std::cout << "TEST\n";
		}
		while(n > subvectorsize);
	}


	ull_int operator [](ull_int i) const
	{
		return vectors[i/subvectorsize][i-((i/subvectorsize)*subvectorsize)];
	}

	ull_int & operator [](ull_int i)
	{
		return vectors[i/subvectorsize][i-((i/subvectorsize)*subvectorsize)];
	}
};

struct pelem
{
	ull_int v;
	bool r;

	pelem(ull_int i) : v(i), r(0) {}
};

//Generate prime numbers up to n, from largest to smallest
std::list<ull_int>& generateprimesdesc(ull_int n)
{

	largevector isprime(n);

	std::list<ull_int>* primes;
	isprime[0] = false;
	isprime[1] = false;
	for(ull_int i = 2;i<n;i++)
	{
		//Add i to the list of primes, if it is not flagged as a non-prime
		if(isprime[i])
		{
			primes->push_front(i);
		}
		
		ull_int j = i;
		while(j + i < n)
		{
//			std::cout << "TEST: " << j << std::endl;

			j+=i;
			isprime[j] = false;
		}
	}
	return *primes;
}


//Generate prime numbers up to n, from smallest to largest
std::list<ull_int> generateprimes(ull_int n)
{

	std::vector<ull_int> isprime(n, true);
	std::list<ull_int> primes;
	std::vector<ull_int> smallestp(n);
	isprime[0] = false;
	isprime[1] = false;
	for(ull_int i = 2;i<n;i++)
	{
		//Add i to the list of primes, if it is not flagged as a non-prime
		if(isprime[i])
		{
			primes.push_back(i);
			smallestp.push_back(i);
		}
		
		ull_int j = i;
		while(j + i < n)
		{
//			std::cout << "TEST: " << j << std::endl;

			j+=i;
			isprime[j] = false;
		}
	}
	return primes;
}
