#pragma once

#include "IVehicle.h"
#include "MakesOfCar.h"

template <typename Passenger>
class ICar : public IVehicle<Passenger>
{
public:
	virtual MakeOfTheCar GetMakeOfTheCar() const = 0;
};
