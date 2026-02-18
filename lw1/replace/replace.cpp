#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void CopyStreamWithReplacement(std::istream& input, std::ostream& output, const std::string& searchString, const std::string& replacementString);
std::string ReplaceString(const std::string& subject, const std::string& searchString, const std::string& replacementString);
void DisplayHelpNotation(std::ostream& output);
int ProcessFileMode(char* arguments[]);
int ProcessStdinMode();

int main(int argc, char* argv[])
{
	if (argc == 5)
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
		std::cout << "Invalid argument count\n"
				  << "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}
}

int ProcessFileMode(char* arguments[])
{
	std::ifstream inputFile(arguments[1]);
	if (!inputFile.is_open())
	{
		std::cerr << "ERROR" << std::endl;
		return 1;
	}

	std::ofstream outputFile(arguments[2]);
	if (!outputFile.is_open())
	{
		std::cerr << "ERROR" << std::endl;
		return 1;
	}

	CopyStreamWithReplacement(inputFile, outputFile, arguments[3], arguments[4]);
	outputFile.flush();

	return 0;
}

int ProcessStdinMode()
{
	std::string searchString;
	std::string replacementString;

	if (!std::getline(std::cin, searchString) || !std::getline(std::cin, replacementString))
	{
		std::cout << "ERROR" << std::endl;
		return 0;
	}

	CopyStreamWithReplacement(std::cin, std::cout, searchString, replacementString);
	return 0;
}

void CopyStreamWithReplacement(
	std::istream& input,
	std::ostream& output,
	const std::string& searchString,
	const std::string& replacementString)
{
	std::string line;
	while (std::getline(input, line))
		output << ReplaceString(line, searchString, replacementString) << "\n";
}

std::string ReplaceString(
	const std::string& subject,
	const std::string& searchString,
	const std::string& replacementString)
{
	if (searchString.empty() && subject.empty()) return replacementString;
	
	if (searchString.empty()) return subject;

	size_t pos = 0;
	std::string result;

	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		if (foundPos == std::string::npos)
		{
			result.append(subject, pos, subject.length() - pos);
			break;
		}

		result.append(subject, pos, foundPos - pos);
		result.append(replacementString);
		pos = foundPos + searchString.length();
	}

	return result;
}

void DisplayHelpNotation(std::ostream& output)
{
	output << "Usage:\n"
		   << "  File mode:  replace.exe <input file> <output file> <search string> <replace string>\n"
		   << "  Stdin mode: run without arguments, enter search string, replacement string, then text"
		   << std::endl;
}

