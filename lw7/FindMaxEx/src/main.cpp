#include "FindMaxEx.h"
#include <iostream>
#include <string>
#include <vector>

class Person
{
public:
	std::string surname;
	std::string name;
	double weight;
	double height;
};

std::ostream& operator<<(std::ostream& os, Person const& a)
{
	return os << a.surname << " | " << a.name << " | " << a.height << "cm |  kg" << a.weight;
}
int main()
{
	std::vector<Person> people = {
		{ "ivanov", "ivan", 185.0, 82.5 },
		{ "smirnov", "sergey", 178.0, 95.0 },
		{ "kozlov", "kozel", 185.0, 95.0 },
		{ "petrov", "petr", 175.0, 95.0 },
		{ "pavlov", "pavel", 189.0, 95.5 },
		{ "vladimirov", "vladimir", 189.0, 95.5 },
	};
	Person answer;

	if (FindMaxEx(people, answer,
			[](Person const& a, Person const& b) {
				return a.surname.size() + a.name.size() < b.surname.size() + b.name.size();
			}))
	{
		std::cout << "longest surname + name: " << answer << "\n";
	}
}