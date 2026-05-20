#include "MyArray.h"
#include <string>
#include <iostream>

int main() {
    MyArray<std::string> arr;
    arr.PushBack("p");
    arr.PushBack("e");
    arr.PushBack("n");
    arr.PushBack("u");

    for (auto i: arr) {
        std::cout << i << std::endl;
    }
}