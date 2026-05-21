#include "MyArray.h"
#include <iostream>
#include <string>

int main()
{
	MyArray<float> arr;
	arr.PushBack(2.0);
	arr.PushBack(1.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);

	MyArray<int> arr1;
	arr1.PushBack(1);
	arr1.PushBack(2);
	arr = arr1;

	// for (int _ = 0; _ < 100; _++)
	// {
	// 	arr.PushBack("p");
	// 	std::cout << arr.GetCapacity() << " | " << arr.GetSize() << std::endl;
	// }

	for (const float i : arr)
	{
		std::cout << i << std::endl;
	}
}