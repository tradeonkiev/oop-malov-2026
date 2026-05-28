#pragma once

#include "IPerson.h"
#include "ITaxi.h"
#include "CarImpl.h"

class Taxi : public CarImpl<ITaxi, IPerson>
{
public:
	Taxi() = delete;

	Taxi(size_t placeCount, MakeOfTheCar make)
		: CarImpl<ITaxi, IPerson>(placeCount, make)
	{
	}
};
