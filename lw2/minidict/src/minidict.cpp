#include "minidict.h"
#include <algorithm>
#include <sstream>

std::string ToLower(const std::string& s)
{
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

std::string JoinStrings(const std::vector<std::string>& vec, const std::string& separator)
{
    std::string result;
    for (int i = 0; i < vec.size(); ++i)
    {
        if (i > 0)
            result += separator;
        result += vec[i];
    }
    return result;
}

void LoadDictionary(std::istream& input, Dictionary& dict)
{
    std::string word, translation;
    while (std::getline(input, word) && std::getline(input, translation))
    {
        if (!word.empty() && !translation.empty())
        {
            std::string key = ToLower(word);
            auto& translations = dict[key];
            if (std::find(translations.begin(), translations.end(), translation) == translations.end())
                translations.push_back(translation);
        }
    }
}

void SaveDictionary(std::ostream& output, const Dictionary& dict)
{
    for (const auto& [key, translations] : dict)
    {
        for (const auto& translation : translations)
        {
            output << key << "\n" << translation << "\n";
        }
    }
}

std::string LookupWord(const Dictionary& dict, const std::string& word)
{
    std::string key = ToLower(word);
    auto it = dict.find(key);
    if (it != dict.end() && !it->second.empty())
        return JoinStrings(it->second, ", ");
    return "";
}

std::string ReverseLookup(const Dictionary& dict, const std::string& word)
{
    std::vector<std::string> matches;
    for (const auto& [key, translations] : dict)
    {
        for (const auto& translation : translations)
        {
            if (ToLower(translation) == ToLower(word))
            {
                if (std::find(matches.begin(), matches.end(), key) == matches.end())
                    matches.push_back(key);
            }
        }
    }
    return JoinStrings(matches, ", ");
}