#include "decode.h"
#include <map>
#include <string>

static const std::map<std::string, std::string> k_html_entities = {
    { "&quot;", "\"" },
    { "&apos;", "'" },
    { "&amp;",  "&" },
    { "&lt;",   "<" },
    { "&gt;",   ">" },
};

std::string HtmlDecode(std::string const& html)
{
    std::string result;
    result.reserve(html.size());
    size_t i = 0;

    while (i < html.size())
    {
        if (html[i] == '&')
        {
            bool matched = false;
            for (auto const& [entity, replacement] : k_html_entities)
            {
                if (html.compare(i, entity.size(), entity) == 0)
                {
                    result += replacement;
                    i += entity.size();
                    matched = true;
                    break;
                }
            }
            if (!matched)
            {
                result += '&';
                ++i;
            }
        }
        else
        {
            result += html[i];
            ++i;
        }
    }
    return result;
}