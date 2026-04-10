#pragma once
#include "bank.h"
#include "person.h"
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

class Town
{
public:
	explicit Town(Bank& bank);

	Person& AddPerson(const std::string& name, Money pockerMoney);
	Person& GetPerson(const std::string& name);
	void StepAll();

    const std::vector<Person*>& Everyone() const;

private:
	Bank& bank_;
	std::map<std::string, Person> people_;
	std::vector<Person*> order_;
};
