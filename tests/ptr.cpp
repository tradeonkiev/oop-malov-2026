#include "Strong.h"
#include <cstring>
#include <iostream>

int main()
{
	Strong string = "maksim";
	Strong damir = "damir";
	string = damir;
	std::cout << string.GetStringData() << std::endl;
	std::cout << string.GetLength() << " " << string.GetCapacity() << std::endl;
}
