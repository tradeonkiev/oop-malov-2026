#include "pch.h"

const int SIZE = 3;

void PrintUsage()
{
	std::cout << "Usage: revert.exe [-h] [<matrix-file>]" << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "  -h             Show this help message" << std::endl;
	std::cout << "  <matrix-file>  File matrix (tab-separated)" << std::endl;
	std::cout << "  (no args)      Read matrix from input" << std::endl;
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
				std::cout << "Invalid matrix value" << std::endl;
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

double Determinant(const double matrix[SIZE][SIZE])
{
	return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
		- matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
		+ matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
}

void InvertMatrix(const double matrix[SIZE][SIZE], double result[SIZE][SIZE])
{
	double det = Determinant(matrix);

	result[0][0] = (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) / det;
	result[0][1] = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) / det;
	result[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) / det;

	result[1][0] = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) / det;
	result[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) / det;
	result[1][2] = (matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2]) / det;

	result[2][0] = (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]) / det;
	result[2][1] = (matrix[0][1] * matrix[2][0] - matrix[0][0] * matrix[2][1]) / det;
	result[2][2] = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) / det;
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

int main(int argc, char* argv[])
{
	double matrix[SIZE][SIZE];
	double inverse[SIZE][SIZE];

	if (argc > 2)
	{
		std::cout << "Invalid arguments" << std::endl;
		return 1;
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
			std::cout << "Cant open file '" << arg << "'" << std::endl;
			return 1;
		}

		if (!ReadMatrix(file, matrix))
		{
			return 1;
		}
	}
	else
	{
		if (!ReadMatrix(std::cin, matrix))
		{
			return 1;
		}
	}

	double det = Determinant(matrix);
	std::cout << det << std::endl;
	
	if (!det)
	{
		std::cout << "Non-invertible" << std::endl;
		return 1;
	}

	InvertMatrix(matrix, inverse);
	PrintMatrix(inverse);

	return 0;
}
