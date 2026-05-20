#include "StringList.h"
#include <iostream>

int main()
{
	StringList list;
	list.PushFront("1");
	list.PushFront("2");
	list.PushFront("3");
	list.PushFront("4");
	StringList list1(std::move(list));

	std::cout << list1.Front() << " | " << list1.Back() << std::endl;
	for (auto str : list)
	{
		std::cout << str << std::endl;
	}

	for (auto str : list1)
	{
		std::cout << str << std::endl;
	}
}
