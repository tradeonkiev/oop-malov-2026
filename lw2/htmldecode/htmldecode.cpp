#include <iostream>
#include <string>

std::string HtmlDecode(std::string const &html);

int main()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		std::cout << HtmlDecode(line) << '\n';
	}
	
	return 0;
}

std::string HtmlDecode(std::string const &html)
{
	std::string result;
	result.reserve(html.size());

	size_t i = 0;
	while (i < html.size())
	{
		if (html[i] == '&')
		{
			if (html.compare(i, 6, "&quot;") == 0)
			{
				result += '"';
				i += 6;
			}
			else if (html.compare(i, 6, "&apos;") == 0)
			{
				result += '\'';
				i += 6;
			}
			else if (html.compare(i, 4, "&lt;") == 0)
			{
				result += '<';
				i += 4;
			}
			else if (html.compare(i, 4, "&gt;") == 0)
			{
				result += '>';
				i += 4;
			}
			else if (html.compare(i, 5, "&amp;") == 0)
			{
				result += '&';
				i += 5;
			}
			else
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