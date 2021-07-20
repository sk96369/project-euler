/* I came up with this solution completely by myself. No other people or resources on the internet
 * were consulted at any point.
 *
 * The solution is based on the following (y being the largest of the integer denominators):
 * -Every value of n has a trivial solution where x and y values are both 2xn.
 * -x has to be smaller than n.
 * 
 * How the process of finding the solutions for n works:
 * 1. Go through every integer value of x, where n < x < n*2.
 * 2. For each x:
 * 	2.1. Expand n and its numerator by x, and expand x and its numerator by n,
 * 	so their denominators are equal.
 *      2.2. Subtract the expanded (1/n) term by the expanded (1/x) term
 *      2.3. Figure out if the difference can be expressed as (1/y), by
 *      calculating the remainder of its denominator divided by its numerator
 *      2.4. If the remainder is 0, a solution exists
 */

#include <iostream>
#include <list>

int findSolutions(long n)
{
	int solutions = 0;
	long x = n*2;
	long denom;
	long num;
	while(x > n)
	{
		num = x - n;
		denom = n * x;
		if(denom%num == 0)
		{
			//The commented out line below lists every solution for n if uncommented
			//std::cout << "1/" << x << " + 1/" << denom/num << " = 1/" << n << std::endl;
			solutions++;
		}
		x-=1;
	}
	return solutions;
}


int main()
{
	//I chose to use long because using int with this solution caused problems past 65536
	long i = 1;
	int solutions = 0;
	while(solutions <= 1000)
	{
		solutions = findSolutions(i);
		std::cout << "Calculating for: " << i << ": solutions: " << solutions << std::endl;
		i++;
	}
	std::cout << i-1 << std::endl;
}
