#include "Date.h"
#include <iostream>

int main()
{
	Date date1, date2;
	std::cin >> date1;
	std::cin >> date2;

	std::cout << date1 << ": " << date1 + 2 << std::endl;
	std::cout << date2 << ": " << date2++ << " -> " << ++date2 << std::endl;
	std::cout << date1 - date2 << std::endl;
	std::cout << date1 + date2 << std::endl;
}
