// #include "pch.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>

const int SIZE = 3;

void PrintUsage();
bool ReadMatrix(std::istream& input, double matrix[SIZE][SIZE]);
double Determinant(const double matrix[SIZE][SIZE]);
double Minor(const double matrix[SIZE][SIZE], int row, int col);
void InvertMatrix(const double matrix[SIZE][SIZE], double result[SIZE][SIZE]);
void PrintMatrix(const double matrix[SIZE][SIZE]);

int main(int argc, char* argv[])
{
	double matrix[SIZE][SIZE];
	double inverse[SIZE][SIZE];

	if (argc > 2)
	{
		std::cout << "Invalid arguments" << std::endl;
		return 0;
	}

	if (argc == 2)
	{
		std::string arg = static_cast<std::string>(argv[1]);
		if (arg == "-h")
		{
			PrintUsage();
			return 0;
		}

		std::ifstream file(arg);
		if (!file.is_open())
		{
			std::cout << "Cant open file \"" << arg << "\"" << std::endl;
			return 1;
		}

		if (!ReadMatrix(file, matrix))
		{
			return 0;
		}
	}
	else
	{
		if (!ReadMatrix(std::cin, matrix))
		{
			return 0;
		}
	}

	double det = Determinant(matrix);

	if (std::abs(det) < 1e-9) det = 0.0;

	if (!det)
	{
		std::cout << "Non-invertible" << std::endl;
		return 0;
	}

	InvertMatrix(matrix, inverse);
	PrintMatrix(inverse);

	return 0;
}

void PrintUsage()
{
	std::cout << "Usage: revert.exe [-h] [<matrix-file>]" << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "  -h            Show this help message" << std::endl;
	std::cout << "  <matrix-file> File matrix (tab-separated)" << std::endl;
	std::cout << "  (no args)     Read matrix from input" << std::endl;
}

bool ReadMatrix(std::istream& input, double matrix[SIZE][SIZE])
{
	std::string line;

	for (int i = 0; i < SIZE; i++)
	{
		if (!std::getline(input, line))
		{
			std::cout << "Invalid matrix format" << std::endl;
			return false;
		}

		std::istringstream linestream(line);
		std::string token;
		int colCount = 0;

		while (std::getline(linestream, token, '\t'))
		{
			if (colCount >= SIZE)
			{
				std::cout << "Invalid matrix format" << std::endl;
				return false;
			}

			std::istringstream tokenStream(token);
			double value;
			char ch;

			if (!(tokenStream >> value) || (tokenStream >> ch))
			{
				std::cout << "Invalid matrix" << std::endl;
				return false;
			}

			matrix[i][colCount] = value;
			colCount++;
		}

		if (colCount != SIZE)
		{
			std::cout << "Invalid matrix format" << std::endl;
			return false;
		}
	}

	while (std::getline(input, line))
	{
		if (!line.empty())
		{
			std::cout << "Invalid matrix format" << std::endl;
			return false;
		}
	}

	return true;
}

void PrintMatrix(const double matrix[SIZE][SIZE])
{
	std::cout << std::fixed << std::setprecision(3);
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (j > 0)
			{
				std::cout << "\t";
			}
			std::cout << matrix[i][j];
		}
		std::cout << std::endl;
	}
}

void InvertMatrix(const double matrix[SIZE][SIZE], double result[SIZE][SIZE])
{
	double det = Determinant(matrix);

	int power = 1;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			result[i][j] = power * Minor(matrix, j, i) / det;
			if (std::abs(result[i][j]) < 1e-9) result[i][j] = 0.0;
			power *= -1;
		}
	}
}

double Determinant(const double matrix[SIZE][SIZE])
{
	return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
		- matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
		+ matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
}

double Minor(const double matrix[SIZE][SIZE], int row, int col)
{
	double minorMatrix[SIZE - 1][SIZE - 1];

	int x = 0, y = 0;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (i != row && j != col)
			{
				minorMatrix[x][y] = matrix[i][j];
				if (++y >= SIZE - 1)
				{
					++x;
					y = 0;
				}
			}
		}
	}

	return minorMatrix[0][0] * minorMatrix[1][1] - minorMatrix[0][1] * minorMatrix[1][0];
}
