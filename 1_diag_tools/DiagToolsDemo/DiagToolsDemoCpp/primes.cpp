
#include "stdafx.h"

#include <vector>

// ref
// http://blogs.msdn.com/b/vcblog/archive/2013/06/27/using-the-2013-cpu-sampling-profiler-to-understand-c-compiler-optimizations.aspx

bool is_prime(int n);
bool is_base(int n);
bool has_factors(int n);
bool is_factor(int n, int i);
void add_prime(int n, std::vector<int> &primes);

std::vector<int> get_primes(int max)
{
	std::vector<int> primes;
	for (int n = 0; n < max; n++)
	{
		if (is_prime(n)) {
			add_prime(n, primes);
		}
	}
	return primes;
}

bool is_prime(int n)
{
	if (is_base(n))
		return false;
	if (has_factors(n))
		return false;
	return true;
}

bool is_base(int n)
{
	if (n < 2)
		return true;
	return false;
}

bool has_factors(int n)
{
	for (int i = 2; i < n; ++i)
	{
		if (is_factor(n, i))
			return true;
	}
	return false;
}

bool is_factor(int n, int i) {
	if ((n % i) == 0)
		return true;
	return false;
}

void add_prime(int n, std::vector<int> &primes)
{
	primes.push_back(n);
}