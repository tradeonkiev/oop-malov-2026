#pragma once
#include "IPerson.h"
#include <cstddef>

class IRacer : public IPerson
{
public:
	virtual size_t GetAwardsCount() const = 0;
};
