#include "Car.h"
#include "CarController.h"
#include <iostream>

int main()
{
	Car car;
	RunCarController(car, std::cin, std::cout);
}