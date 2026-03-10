#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>

using Dictionary = std::map<std::string, std::vector<std::string>>;

std::string ToLower(const std::string& s);
std::string JoinStrings(const std::vector<std::string>& vec, const std::string& separator);
void LoadDictionary(std::istream& input, Dictionary& dict);
void SaveDictionary(std::ostream& output, const Dictionary& dict);
std::string LookupWord(const Dictionary& dict, const std::string& word);
std::string ReverseLookup(const Dictionary& dict, const std::string& word);