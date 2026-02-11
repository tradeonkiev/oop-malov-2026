#include "pch.h"

const int MAX_SIZE = 100;

const int DR[] = { -1, 1, 0, 0 };
const int DC[] = { 0, 0, -1, 1 };

struct Point
{
	int row;
	int col;
};

bool ReadMaze(std::istream& input, std::vector<std::string>& maze)
{
	std::string line;
	while (std::getline(input, line))
	{
		if (!line.empty() && line.back() == '\r')
		{
			line.pop_back();
		}
		maze.push_back(line);
	}
	return true;
}

bool ValidateMaze(const std::vector<std::string>& maze, int& width, int& height, Point& start, Point& end)
{
	height = static_cast<int>(maze.size());
	width = 0;

	for (int i = 0; i < height; i++)
	{
		int len = static_cast<int>(maze[i].size());
		if (len > width)
		{
			width = len;
		}
	}

	if (height > MAX_SIZE || width > MAX_SIZE)
	{
		return false;
	}

	int countA = 0;
	int countB = 0;
	start = { -1, -1 };
	end = { -1, -1 };

	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < static_cast<int>(maze[r].size()); c++)
		{
			char ch = maze[r][c];
			if (ch == 'A')
			{
				countA++;
				start = { r, c };
			}
			else if (ch == 'B')
			{
				countB++;
				end = { r, c };
			}
			else if (ch != '#' && ch != ' ')
			{
				return false;
			}
		}
	}

	if (countA != 1 || countB != 1)
	{
		return false;
	}

	return true;
}

bool FindShortestPath(std::vector<std::string>& maze, int width, int height, Point start, Point end)
{
	std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
	std::vector<std::vector<Point>> parent(height, std::vector<Point>(width, { -1, -1 }));

	std::queue<Point> q;
	q.push(start);
	visited[start.row][start.col] = true;

	bool found = false;

	while (!q.empty())
	{
		Point cur = q.front();
		q.pop();

		if (cur.row == end.row && cur.col == end.col)
		{
			found = true;
			break;
		}

		for (int d = 0; d < 4; d++)
		{
			int nr = cur.row + DR[d];
			int nc = cur.col + DC[d];

			if (nr >= 0 && nr < height && nc >= 0 && nc < static_cast<int>(maze[nr].size()))
			{
				if (!visited[nr][nc] && maze[nr][nc] != '#')
				{
					visited[nr][nc] = true;
					parent[nr][nc] = cur;
					q.push({ nr, nc });
				}
			}
		}
	}

	if (found)
	{
		Point cur = end;
		while (cur.row != start.row || cur.col != start.col)
		{
			if (maze[cur.row][cur.col] != 'A' && maze[cur.row][cur.col] != 'B')
			{
				maze[cur.row][cur.col] = '.';
			}
			Point prev = parent[cur.row][cur.col];
			cur = prev;
		}
	}

	return found;
}

void WriteMaze(std::ostream& output, const std::vector<std::string>& maze)
{
	for (const auto& line : maze)
	{
		output << line << "\n";
	}
}

int main(int argc, char* argv[])
{
	bool fileMode = (argc == 3);

	if (argc != 1 && argc != 3)
	{
		std::cout << "ERROR" << std::endl;
		return 1;
	}

	std::vector<std::string> maze;

	if (fileMode)
	{
		std::ifstream fin(argv[1]);
		if (!fin.is_open())
		{
			std::cout << "ERROR" << std::endl;
			return 1;
		}
		ReadMaze(fin, maze);
	}
	else
	{
		ReadMaze(std::cin, maze);
	}

	int width = 0;
	int height = 0;
	Point start, end;

	if (!ValidateMaze(maze, width, height, start, end))
	{
		std::cout << "ERROR" << std::endl;
		return fileMode ? 1 : 0;
	}

	FindShortestPath(maze, width, height, start, end);

	if (fileMode)
	{
		std::ofstream fout(argv[2]);
		if (!fout.is_open())
		{
			std::cout << "ERROR" << std::endl;
			return 1;
		}
		WriteMaze(fout, maze);
	}
	else
	{
		WriteMaze(std::cout, maze);
	}

	return 0;
}
