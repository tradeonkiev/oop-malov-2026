#pragma once

#include "IRacer.h"
#include "IRacingCar.h"
#include "CarImpl.h"

class RacingCar : public CarImpl<IRacingCar, IRacer>
{
public:
	RacingCar() = delete;

	RacingCar(size_t placeCount, MakeOfTheCar make)
		: CarImpl<IRacingCar, IRacer>(placeCount, make)
	{
	}
};
