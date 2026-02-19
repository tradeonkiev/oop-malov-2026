#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

const int MAX_SIZE = 100;

struct Point
{
	int row, col;
};

using Grid = std::vector<std::string>;

Grid ReadGrid(std::istream& input);
void WriteGrid(std::ostream& output, const Grid& grid);
void FloodFill(Grid& grid, int startRow, int startCol);
void FillAllMarkers(Grid& grid);
void DisplayHelpNotation(std::ostream& output);
int ProcessFileMode(char* arguments[]);
int ProcessStdinMode();

int main(int argc, char* argv[])
{
	if (argc == 3)
	{
		return ProcessFileMode(argv);
	}
	else if (argc == 1)
	{
		return ProcessStdinMode();
	}
	else if (argc == 2 && std::string(argv[1]) == "-h")
	{
		DisplayHelpNotation(std::cout);
		return 0;
	}
	else
	{
		std::cout << "ERROR" << std::endl;
		return 1;
	}
}

int ProcessFileMode(char* arguments[])
{
	std::ifstream inputFile(arguments[1]);
	if (!inputFile.is_open())
	{
		std::cout << "ERROR" << std::endl;
		return 1;
	}

	Grid grid = ReadGrid(inputFile);
	if (grid.empty())
	{
		std::cout << "ERROR" << std::endl;
		return 1;
	}

	FillAllMarkers(grid);

	std::ofstream outputFile(arguments[2]);
	if (!outputFile.is_open())
	{
		std::cout << "ERROR" << std::endl;
		return 1;
	}

	WriteGrid(outputFile, grid);
	outputFile.flush();

	return 0;
}

int ProcessStdinMode()
{
	Grid grid = ReadGrid(std::cin);
	if (grid.empty())
	{
		std::cout << "ERROR" << std::endl;
		return 0;
	}

	FillAllMarkers(grid);
	WriteGrid(std::cout, grid);

	return 0;
}

Grid ReadGrid(std::istream& input)
{
	Grid grid;
	std::string line;

	while (grid.size() < MAX_SIZE && std::getline(input, line))
	{
		if (line.length() > MAX_SIZE)
		{
			line.resize(MAX_SIZE);
		}
		grid.push_back(line);
	}

	while (grid.size() < MAX_SIZE)
	{
		grid.push_back(std::string(MAX_SIZE, ' '));
	}

	for (std::string& row : grid)
	{
		if (row.length() < MAX_SIZE)
		{
			row.resize(MAX_SIZE, ' ');
		}
	}

	return grid;
}

void WriteGrid(std::ostream& output, const Grid& grid)
{
	int lastRow = grid.size() - 1;
	while (lastRow >= 0 && grid[lastRow].find_first_not_of(' ') == std::string::npos)
	{
		lastRow--;
	}

	for (int i = 0; i <= lastRow; i++)
	{
		size_t end = grid[i].find_last_not_of(' ');
		if (end != std::string::npos)
		{
			output << grid[i].substr(0, end + 1) << "\n";
		}
		else
		{
			output << "\n";
		}
	}
}

void FloodFill(Grid& grid, int startRow, int startCol)
{
	int rows = grid.size();
	std::vector<std::vector<bool>> visited(rows, std::vector<bool>(MAX_SIZE, false));
	std::queue<Point> queue;

	queue.push({ startRow, startCol });
	visited[startRow][startCol] = true;

	int dr[] = { -1, 1, 0, 0 };
	int dc[] = { 0, 0, -1, 1 };

	while (!queue.empty())
	{
		Point current = queue.front();
		queue.pop();

		int r = current.row;
		int c = current.col;

		if (grid[r][c] == ' ')
		{
			grid[r][c] = '.';
		}

		for (int i = 0; i < 4; i++)
		{
			int nr = r + dr[i];
			int nc = c + dc[i];

			if (nr < 0 || nr >= rows || nc < 0 || nc >= MAX_SIZE)
			{
				continue;
			}
			if (visited[nr][nc])
			{
				continue;
			}

			if (grid[nr][nc] == ' ' || grid[nr][nc] == 'O')
			{
				visited[nr][nc] = true;
				queue.push({ nr, nc });
			}
		}
	}
}

void FillAllMarkers(Grid& grid)
{
	for (int r = 0; r < grid.size(); r++)
	{
		for (int c = 0; c < grid[r].length(); c++)
		{
			if (grid[r][c] == 'O')
			{
				FloodFill(grid, r, c);
			}
		}
	}
}


void DisplayHelpNotation(std::ostream& output)
{
	output << "Usage:\n"
		   << "  File mode:  fill.exe <input file> <output file>\n"
		   << "  Stdin mode: run without arguments, enter image, then EOF"
		   << std::endl;
}



