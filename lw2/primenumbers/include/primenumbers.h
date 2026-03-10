#pragma once
#include <iostream>
#include <set>
#include <vector>
#include <optional>

std::set<int> GeneratePrimeNumbersSet(int upperBound);
std::optional<int> ParseUpperBound(const std::string& str);
void PrintPrimes(const std::set<int>& primes, std::ostream& output);
