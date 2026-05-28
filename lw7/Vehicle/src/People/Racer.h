#pragma once

#include "IRacer.h"
#include "PersonImpl.h"

#include <cstddef>
#include <string>

class Racer : public PersonImpl<IRacer>
{
public:
	Racer() = delete;

	Racer(const std::string& name, size_t awardsCount)
		: PersonImpl<IRacer>(name)
		, m_awardsCount(awardsCount)
	{
	}

	size_t GetAwardsCount() const override
	{
		return m_awardsCount;
	}

private:
	size_t m_awardsCount;
};
