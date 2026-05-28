#pragma once
#include "IPerson.h"
#include <string>

class IPoliceMan : public IPerson
{
public:
	virtual std::string GetDepartmentName() const = 0;
};
