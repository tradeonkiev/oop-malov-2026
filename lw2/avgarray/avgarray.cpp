#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <windows.h>

std::vector<double> ReadArray(std::istream& input);
double CalcPositiveAverage(const std::vector<double>& arr);
void AddValueToAll(std::vector<double>& arr, double value);
void PrintArray(const std::vector<double>& arr, std::ostream& output);

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    try
    {
        std::vector<double> arr = ReadArray(std::cin);

        double avg = CalcPositiveAverage(arr);
        AddValueToAll(arr, avg);

        std::sort(arr.begin(), arr.end());
        PrintArray(arr, std::cout);
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

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
        {
            arr.push_back(val);
        }
        else
        {
            throw std::invalid_argument("\"" + token + "\" не является числом");
        }
    }
    return arr;
}

double CalcPositiveAverage(const std::vector<double>& arr)
{
    double sum = std::accumulate(arr.begin(), arr.end(), 0.0, [](double acc, double x)
                                 { return x > 0 ? acc + x : acc; });

    long count = std::count_if(arr.begin(), arr.end(), [](double x)
                               { return x > 0; });

    return (count > 0) ? sum / count : 0.0;
}

void AddValueToAll(std::vector<double>& arr, double value)
{
    for (double& x : arr)
        x += value;
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
