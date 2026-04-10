#pragma once
#include "minidict.h"
#include <string>

bool HandleNewWord(Dictionary& dict, const std::string& line, const std::string& key);
bool ProcessInput(Dictionary& dict);
void PromptSave(const std::string& filename, const Dictionary& dict, bool modified);