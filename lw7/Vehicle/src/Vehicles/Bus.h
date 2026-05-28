#pragma once

#include "IBus.h"
#include "IPerson.h"
#include "VehicleImpl.h"

class Bus : public VehicleImpl<IBus, IPerson>
{
public:
	Bus() = delete;

	Bus(size_t placeCount)
		: VehicleImpl<IBus, IPerson>(placeCount)
	{
	}
};
