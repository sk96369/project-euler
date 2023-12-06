#include <iostream>
#include <list>

void cutlist(int n, std::list<int> &l)
{
	std::list<int>::iterator ptr = l.begin();
	while(ptr != l.end())
	{
		if(*ptr > n)
			ptr = l.erase(ptr);
		else
			ptr++;
	}
}

int findcombination(int n, const std::list<int> &kncopy)
{
	int biggest = 0;
	int m = 0;
	int recursion = -1;
	bool end = 0;
	std::list<int> routelengths;
	std::list<int>::const_iterator ptr;
	std::list<int>::iterator rptr;
	for(ptr = kncopy.begin();!end && ptr != kncopy.end();ptr++)
	{
		m = 0;
		biggest = *ptr;
//		std::cout << "              kn: " << biggest << std::endl;
		if(biggest == n)
		{
//			std::cout << "   Chose number: " << biggest << std::endl;
			m++;
			return m;
		}
		if(biggest < n)
		{
			m++;
			recursion = findcombination(n - biggest, kncopy);
			if(recursion != -1)
			{
//				std::cout << "     Pushing new subroute - kn: " << biggest << " - length: " << m+recursion << std::endl;
				routelengths.push_back(m + recursion);
				end = 1;
			}
		}
	}
	recursion = 9999999;
	for(rptr = routelengths.begin();rptr != routelengths.end();rptr++)
	{
		if(recursion > *rptr)
		{
			recursion = *rptr;
		}
	}
	return recursion;
}

int findshortest(int n, std::list<int> &kn)
{
	int x = kn.front();
	//The number of multiplication operations
	int m = 0;
	int mcopy = 0;
	int recursion = -1;
	int prev = 1;
	int help = 0;
	std::list<int> kncopy;
	std::list<int>::iterator ptr;
	std::list<int> routelengths;
/*	for(ptr = kn.begin();ptr != kn.end();ptr++)
	{
		kncopy.push_front(*ptr);
	}*/
	if(n == 1)
		return 0;
	int i = 1;
	while(i<n)
	{
		mcopy = m;
		x=i;
		while(x * 2 <= n)
		{
			x *= 2;
			kn.push_front(x);
			mcopy++;
//			std::cout << "   kn + kn = " << x << " route length: " << mcopy << std::endl;
		}
		if(x == n)
		{
//			std::cout << "Pushing back new route: " << mcopy << std::endl;
			routelengths.push_back(mcopy);
		}
		else
		{
//			std::cout << "Finding new combination to reach " << n << " from: " << x << std::endl;
/*			for(auto a = kn.begin();a != kn.end();a++)
			{
				std::cout << "   known number: " << *a << std::endl;
			}
			*/
			recursion = findcombination(n-x, kn);
			if(recursion != -1)
			{
//				std::cout << "Pushing back new route: " << recursion + mcopy << std::endl;
				routelengths.push_back(recursion + mcopy);
			}
			//If n can't be reached with a multiplication of x by a power of 2, add the sum of
			//the largest known numbers to the list of known numbers and call this function again
			/*
			ptr = kn.begin();
			x = *ptr;
			ptr++;
			x += *ptr;
			m++;
			kn.push_front(x);
			recursion = findshortest(n, kn);
			m+=recursion;
			if(recursion == -1)
			{
				kn.pop_front();
				kncopy = getsublist(n - kn.front(), kn);
				m+=findshortest(n - kn.front(), kncopy);
				return m;
			}*/
		}
		m++;
		help = i;
		i += prev;
		prev = help;
		cutlist(prev, kn);
		kn.push_front(i);
	
	}
	recursion = 999999;
	for(ptr = routelengths.begin();ptr != routelengths.end();ptr++)
	{
		if(*ptr < recursion)
			recursion = *ptr;
	}
	return recursion;
}

int main()
{
	int sum = 0;
	int shortest;
	for(int i = 1;i <= 200;i++)
	{
		std::list<int> kn;
		kn.push_front(1);
		std::cout << "\nFinding shortest way to: " << i << std::endl;
		shortest=findshortest(i, kn);
		sum+=shortest;
		std::cout << "Shortest way: " << shortest << " - New sum: " << sum << std::endl;
	}
	std::cout << sum << std::endl;
	return 0;
}

