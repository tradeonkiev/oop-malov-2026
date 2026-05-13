#include "OwnIterator.h"
#include "Strong.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

int main()
{
	// std::string::iterator
	Strong container("01234567");
	auto it = container.begin();
	std::string k = "12345Э";
	auto it2 = k.begin();
	++it2;
	std::cout << *it2 << std::endl;
	class a
	{
		bool k;
		bool z;
		// int l;
	};

	// std::cout << sizeof(a) << std::endl;

	// ++it;
	// --it;
	++it++;

	std::cout << *it << std::endl;

	// std::sort(container.begin(), container.end());
	// std::cout << container << std::endl;
}
