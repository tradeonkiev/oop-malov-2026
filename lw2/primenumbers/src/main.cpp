#include "primenumbers.h"
#include "iostream"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <upperBound>" << std::endl;
        return 1;
    }

    int upperBound = std::atoi(argv[1]);

    if (upperBound < 1 || upperBound > 100000000)
    {
        std::cerr << "Error: upperBound must be between 1 and 100000000" << std::endl;
        return 1;
    }

    std::set<int> primes = GeneratePrimeNumbersSet(upperBound);

    for (int prime : primes)
    {
        std::cout << prime << std::endl;
    }

    return 0;
}
