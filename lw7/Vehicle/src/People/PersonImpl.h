#pragma once
#include <string>

template <typename IPerson>
class PersonImpl : public IPerson
{
public:
	PersonImpl() = delete;

	PersonImpl(const std::string& name)
		: m_name(name)
	{
	}

	std::string GetName() const override
	{
		return m_name;
	}

private:
	std::string m_name;
};
