#include "minidict.h"
#include <algorithm>
#include <fstream>
#include <iostream>

bool HandleNewWord(Dictionary& dict, const std::string& line, const std::string& key)
{
	std::cout << "Unknown word \"" << line << "\". Enter translation or empty line to skip:" << std::endl;
	std::string translation;
	if (std::getline(std::cin, translation) && !translation.empty())
	{
		auto& translations = dict[key];
		if (std::find(translations.begin(), translations.end(), translation) == translations.end())
			translations.push_back(translation);
		std::cout << "Word \"" << line << "\" saved as \"" << translation << "\"" << std::endl;
		return true;
	}
	std::cout << "Word \"" << line << "\" ignored" << std::endl;
	return false;
}

bool ProcessInput(Dictionary& dict)
{
	bool modified = false;
	std::string line;

	while (std::getline(std::cin, line))
	{
		if (line == "...")
			break;

		std::string result = LookupWord(dict, line);
		if (!result.empty())
		{
			std::cout << result << std::endl;
			continue;
		}

		result = ReverseLookup(dict, line);
		if (!result.empty())
		{
			std::cout << result << std::endl;
			continue;
		}

		if (HandleNewWord(dict, line, ToLower(line)))
			modified = true;
	}

	return modified;
}

void PromptSave(const std::string& filename, const Dictionary& dict, bool modified)
{
	if (modified)
	{
		std::cout << "Dictionary was modified. Save changes? (Y/N): ";
		std::string answer;
		if (std::getline(std::cin, answer) && (answer == "Y" || answer == "y"))
		{
			std::ofstream file(filename);
			if (file.is_open())
			{
				SaveDictionary(file, dict);
				std::cout << "Changes saved" << std::endl;
			}
			else
			{
				std::cout << "Failed to save" << std::endl;
			}
		}
		else
		{
			std::cout << "Changes discarded" << std::endl;
		}
	}
	std::cout << "Goodbye" << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: dicter <dictionary-file>" << std::endl;
		return 1;
	}

	std::string filename = argv[1];
	Dictionary dict;

	std::ifstream file(filename);
	if (file.is_open())
	{
		LoadDictionary(file, dict);
		file.close();
	}

	bool modified = ProcessInput(dict);
	PromptSave(filename, dict, modified);

	return 0;
}