#include "pch.h"

std::string ReplaceString(
	const std::string& subject,
	const std::string& searchString, 
	const std::string& replacementString)
{
	if (searchString.empty()) 
		return subject;

	int pos = 0;
	std::string result;

	while (pos < subject.length())
	{
		int foundPos = subject.find(searchString, pos);

		if (foundPos == -1)
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

int main(int argc, char* argv[])
{
	if (argc == 5)
	{
		// replace.exe <input> <output> <search> <replace>
		std::ifstream inputFile(argv[1]);
		if (!inputFile.is_open())
		{
			std::cerr << "ERROR" << std::endl;
			return 1;
		}

		std::ofstream outputFile(argv[2]);
		if (!outputFile.is_open())
		{
			std::cerr << "ERROR" << std::endl;
			return 1;
		}

		std::string search = argv[3];
		std::string replace = argv[4];

		CopyStreamWithReplacement(inputFile, outputFile, search, replace);
		outputFile.flush();

		return 0;
	}
	else if (std::string(argv[1]) == "-h")
	{
		std::cout << "Usage:\n"
			<< "  File mode:  replace.exe <input file> <output file> <search string> <replace string>\n"
			<< "  Stdin mode: run without arguments, enter search string, replacement string, then text"
			<< std::endl;
		return 0;
	}
	else if (argc == 1)
	{
		std::string searchString;
		std::string replacementString;

		std::getline(std::cin, searchString);
		std::getline(std::cin, replacementString);

		CopyStreamWithReplacement(std::cin, std::cout, searchString, replacementString);
		return 0;
	}
	else
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}
}
