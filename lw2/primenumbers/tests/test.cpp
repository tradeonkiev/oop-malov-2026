#include "primenumbers.h"
#include <gtest/gtest.h>

TEST(GeneratePrimes, BelowTwo)
{
	EXPECT_TRUE(GeneratePrimeNumbersSet(0).empty());
	EXPECT_TRUE(GeneratePrimeNumbersSet(1).empty());
	EXPECT_TRUE(GeneratePrimeNumbersSet(-5).empty());
}

TEST(GeneratePrimes, ExactlyTwo)
{
	auto primes = GeneratePrimeNumbersSet(2);
	EXPECT_EQ(primes.size(), 1);
	EXPECT_TRUE(primes.count(2));
}

TEST(GeneratePrimes, UpToTen)
{
	auto primes = GeneratePrimeNumbersSet(10);
	std::set<int> expected = { 2, 3, 5, 7 };
	EXPECT_EQ(primes, expected);
}

TEST(GeneratePrimes, UpToThirty)
{
	auto primes = GeneratePrimeNumbersSet(30);
	std::set<int> expected = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
	EXPECT_EQ(primes, expected);
}

TEST(GeneratePrimes, BoundaryIsPrime)
{
	auto primes = GeneratePrimeNumbersSet(13);
	EXPECT_TRUE(primes.count(13));
}

TEST(GeneratePrimes, BoundaryIsComposite)
{
	auto primes = GeneratePrimeNumbersSet(12);
	EXPECT_FALSE(primes.count(12));
}

TEST(GeneratePrimes, NoEvenExceptTwo)
{
	auto primes = GeneratePrimeNumbersSet(100);
	for (int p : primes)
	{
		if (p != 2)
		{
			EXPECT_NE(p % 2, 0) << p << " чётное, но попало в простые";
		}
	}
}

TEST(GeneratePrimes, CountUpToHundred)
{
	auto primes = GeneratePrimeNumbersSet(100);
	EXPECT_EQ(primes.size(), 25);
}

TEST(GeneratePrimes, LargeUpperBound)
{
	auto primes = GeneratePrimeNumbersSet(100000);
	EXPECT_EQ(primes.size(), 9592);
	EXPECT_TRUE(primes.count(99991));
}

TEST(GeneratePrimes, MaxUpperBound)
{
	auto primes = GeneratePrimeNumbersSet(100000000);
	EXPECT_EQ(primes.size(), 5761455);
	EXPECT_TRUE(primes.count(99991));
}