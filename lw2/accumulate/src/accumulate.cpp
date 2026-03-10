#include "accumulate.h"
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <sstream>
#include <string>

std::vector<double> ReadArray(std::istream& input)
{
	std::vector<double> arr;
	std::string line;
	std::getline(input, line);
	std::istringstream iss(line);

	double val;
	std::string token;
	while (iss >> token)
	{
		std::istringstream check(token);
		if (check >> val && check.eof())
			arr.push_back(val);
		else
			throw std::invalid_argument("\"" + token + "\" �� �������� ������");
	}
	return arr;
}

double CalcPositiveAverage(const std::vector<double>& arr)
{
	double sum = std::accumulate(arr.begin(), arr.end(), 0.0,
		[](double acc, double x) { return x > 0 ? acc + x : acc; });

	int count = std::count_if(arr.begin(), arr.end(),
		[](double x) { return x > 0; });

	return (count > 0) ? sum / count : 0.0;
}

void PrintArray(const std::vector<double>& arr, std::ostream& output)
{
	if (arr.empty())
		return;

	for (size_t i = 0; i < arr.size(); ++i)
	{
		if (i > 0)
			output << " ";
		output << std::fixed << std::setprecision(3) << arr[i];
	}
	output << std::endl;
}
