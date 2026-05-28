#pragma once
#include "IPerson.h"
#include "PersonImpl.h"

class Person : public PersonImpl<IPerson>
{
public:
	Person() = delete;

	Person(const std::string& name)
		: PersonImpl<IPerson>(name)
	{
	}
};
