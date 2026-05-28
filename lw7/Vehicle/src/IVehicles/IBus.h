#pragma once
#include "IPerson.h"
#include "IVehicle.h"

class IBus : public IVehicle<IPerson>
{
};
