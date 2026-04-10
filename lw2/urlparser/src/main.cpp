#include "urlparser.h"
#include <iostream>

int main()
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        try
        {
            UrlInfo info(line);
            info.Print(std::cout);
        }
        catch (const std::exception& e)
        {
            std::cout << "ERROR" << std::endl;
            return 0;
        }
    }
    return 0;
}