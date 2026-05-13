#include "Solve4.h"
#include <iostream>

int main()
{
	std::cout << "Input values of a, b, c, d, e" << std::endl;
	double a, b, c, d, e;

	while (std::cin >> a >> b >> c >> d >> e)
	{
		try
		{
			EquationRoot4 solution = Solve4(a, b, c, d, e);
			for (int i = 0; i < solution.numRoots; i++)
			{
				std::cout << "x" << i << ": " << solution.roots[i] << std::endl;
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
}