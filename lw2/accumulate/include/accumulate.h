#pragma once
#include <sstream>
#include <vector>

std::vector<double> ReadArray(std::istream& input);
double CalcPositiveAverage(const std::vector<double>& arr);
void PrintArray(const std::vector<double>& arr, std::ostream& output);
