#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::string ToLower(const std::string &s)
{
	std::string result = s;
	std::transform(result.begin(), result.end(), result.begin(),
				   [](unsigned char c)
				   { return std::tolower(c); });
	return result;
}

void LoadDictionary(const std::string &filename, std::map<std::string, std::string> &dict)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		return;
	}

	std::string word, translation;
	while (std::getline(file, word) && std::getline(file, translation))
	{
		if (!word.empty() && !translation.empty())
		{
			dict[ToLower(word)] = translation;
		}
	}
}

void SaveDictionary(const std::string &filename, const std::map<std::string, std::string> &dict)
{
	std::ofstream file(filename);
	if (!file.is_open())
	{
		std::cout << "Failed to open file for writing." << std::endl;
		return;
	}

	for (const auto &[key, value] : dict)
	{
		file << key << "\n"
			 << value << "\n";
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: dicter <dictionary-file>" << std::endl;
		return 1;
	}

	std::string filename = argv[1];
	std::map<std::string, std::string> dict;
	LoadDictionary(filename, dict);

	bool modified = false;
	std::string line;

	while (std::getline(std::cin, line))
	{
		if (line == "...")
		{
			break;
		}

		std::string key = ToLower(line);

		auto it = dict.find(key);
		if (it != dict.end())
		{
			std::cout << it->second << std::endl;
			continue;
		}

		std::vector<std::string> reverseMatches;
		for (const auto &[dictKey, dictValue] : dict)
		{
			if (dictValue == line)
			{
				reverseMatches.push_back(dictKey);
			}
		}

		if (!reverseMatches.empty())
		{
			for (size_t i = 0; i < reverseMatches.size(); ++i)
			{
				if (i > 0)
				{
					std::cout << ", ";
				}
				std::cout << reverseMatches[i];
			}
			std::cout << std::endl;
			continue;
		}

		std::cout << "Unknown word \"" << line << "\". Enter translation or empty line to skip:" << std::endl;
		std::string translation;
		if (std::getline(std::cin, translation) && !translation.empty())
		{
			dict[key] = translation;
			modified = true;
			std::cout << "Word \"" << line << "\" saved as \"" << key << "\" -> \"" << translation << "\"." << std::endl;
		}
		else
		{
			std::cout << "Word \"" << line << "\" ignored." << std::endl;
		}
	}

	if (modified)
	{
		std::cout << "Dictionary was modified. Save changes? (Y/N): ";
		std::string answer;
		if (std::getline(std::cin, answer) && (answer == "Y" || answer == "y"))
		{
			SaveDictionary(filename, dict);
			std::cout << "Changes saved." << std::endl;
		}
		else
		{
			std::cout << "Changes discarded." << std::endl;
		}
	}

	std::cout << "Goodbye." << std::endl;
	return 0;
}
