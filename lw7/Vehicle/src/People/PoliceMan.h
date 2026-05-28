#pragma once
#include "IPoliceMan.h"
#include "PersonImpl.h"
#include <string>

class PoliceMan : public PersonImpl<IPoliceMan>
{
public:
	PoliceMan() = delete;

	PoliceMan(const std::string& name, const std::string& departmentName)
		: PersonImpl<IPoliceMan>(name)
		, m_departmentName(departmentName)
	{
	}

	std::string GetDepartmentName() const override
	{
		return m_departmentName;
	}

private:
	std::string m_departmentName;
};
