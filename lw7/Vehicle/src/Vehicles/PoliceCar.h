#pragma once

#include "IPoliceCar.h"
#include "IPoliceMan.h"
#include "CarImpl.h"

class PoliceCar : public CarImpl<IPoliceCar, IPoliceMan>
{
public:
	PoliceCar() = delete;

	PoliceCar(size_t placeCount, MakeOfTheCar brand)
		: CarImpl<IPoliceCar, IPoliceMan>(placeCount, brand)
	{
	}
};
