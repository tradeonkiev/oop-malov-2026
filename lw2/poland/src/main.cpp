#include "poland.h"
#include <iostream>
#include <string>

int main()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		try
		{
			std::cout << EvaluateFromString(line) << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << "ERROR" << std::endl;
			return 0;
		}
	}
	return 0;
}