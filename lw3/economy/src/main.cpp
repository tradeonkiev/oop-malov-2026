#include "economy.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[])
{
    int numIterations = 0;

    if (argc >= 2)
    {
        numIterations = std::atoi(argv[1]);
    }
    else
    {
        std::cout << "Enter number of iterations: ";
        std::cin >> numIterations;
    }

    if (numIterations <= 0)
    {
        std::cerr << "Invalid number of iterations\n";
        return 1;
    }

    RunEconomy(numIterations);

    return 0;
}