#include "calculator.h"
#include "parser.h"
#include <string>

int main()
{
	Calculator calc;
	Parser parser(calc);
	std::string line;

	while (std::getline(std::cin, line))
	{
		try
		{
			parser.ProcessCommandFromLine(line);
		}
		catch (...)
		{
		}
	}

	return 0;
}