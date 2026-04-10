#include "inputhandler.h"
#include "minidict.h"
#include <algorithm>
#include <iostream>
#include <fstream>

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
