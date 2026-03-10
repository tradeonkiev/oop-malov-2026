#include "primenumbers.h"
#include <iostream>
#include <set>
#include <vector>

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::set<int> primes;
	if (upperBound < 2)
		return primes;

	std::vector<bool> isPrime(upperBound + 1, true);
	isPrime[0] = false;
	isPrime[1] = false;

	for (int j = 4; j <= upperBound; j += 2)
		isPrime[j] = false;

	for (int i = 3; i * i <= upperBound; i += 2)
	{
		if (isPrime[i])
		{
			for (int j = i * i; j <= upperBound; j += i)
				isPrime[j] = false;
		}
	}

	for (int i = 2; i <= upperBound; ++i)
	{
		if (isPrime[i])
			primes.insert(primes.end(), i);
	}

	return primes;
}

std::optional<int> ParseUpperBound(const std::string& str)
{
	try
	{
		int value = std::stoi(str);
		if (value < 1 || value > 100000000)
			return std::nullopt;
		return value;
	}
	catch (...)
	{
		return std::nullopt;
	}
}

void PrintPrimes(const std::set<int>& primes, std::ostream& output)
{
	for (int prime : primes)
		output << prime << "\n";
}
