#pragma once

#include "IShape.h"
#include <cstdint>

class ISolidShape : public IShape
{
public:
	virtual ~ISolidShape() = default;

	virtual uint32_t GetFillColor() = 0;
};
