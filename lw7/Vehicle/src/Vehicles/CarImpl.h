#pragma once

#include "MakesOfCar.h"
#include "VehicleImpl.h"

template <typename Interface, typename Passenger>
class CarImpl : public VehicleImpl<Interface, Passenger>
{
public:
	CarImpl() = delete;

	CarImpl(size_t placeCount, MakeOfTheCar brand)
		: VehicleImpl<Interface, Passenger>(placeCount)
		, m_make(brand)
	{
	}

	MakeOfTheCar GetMakeOfTheCar() const override
	{
		return m_make;
	}

private:
	MakeOfTheCar m_make;
};
