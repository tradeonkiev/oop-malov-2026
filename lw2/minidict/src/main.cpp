#include "minidict.h"
#include "inputhandler.h"
#include <algorithm>
#include <fstream>
#include <iostream>


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