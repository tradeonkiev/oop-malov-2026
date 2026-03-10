#include "accumulate.h"
#include <algorithm>
#include <iostream>

int main()
{
	try
	{
		std::vector<double> arr = ReadArray(std::cin);
		double avg = CalcPositiveAverage(arr);

		std::transform(arr.begin(), arr.end(), arr.begin(), [avg](double x) {
			return x + avg;
		});

		std::sort(arr.begin(), arr.end());
		PrintArray(arr, std::cout);
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << "Ошибка: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}