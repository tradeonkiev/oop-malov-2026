#include "town.h"

Town::Town(Bank& bank)
	: bank_(bank){};

Person& Town::AddPerson(const std::string& name, Money pockerMoney)
{
	if (people_.count(name))
	{
		throw std::invalid_argument("Person '" + name + "' already exists");
	}

	auto [it, inserted] = people_.emplace(name, Person(name, bank_, pockerMoney));
	order_.push_back(&it->second);
	return it->second;
}

Person& Town::GetPerson(const std::string& name)
{
	auto it = people_.find(name);
	if (it == people_.end())
		throw std::runtime_error("Person '" + name + "' not found");
	return it->second;
}

void Town::StepAll()
{
	for (Person* character : order_)
		character->Step(*this);
}

const std::vector<Person*>& Town::Everyone() const
{
	return order_;
}