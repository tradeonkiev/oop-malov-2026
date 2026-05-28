#include "Vehicle.h"

#include <iostream>
#include <memory>
#include <stdexcept>

void PrintPoliceCarPassengers(IPoliceCar const& policeCar)
{
	std::cout << "Police car (" << MakeOfTheCarToString(policeCar.GetMakeOfTheCar())
			  << ") passengers:\n";

	for (size_t i = 0; i < policeCar.GetPassengerCount(); ++i)
	{
		auto const& policeMan = policeCar.GetPassenger(i);
		std::cout << "- " << policeMan.GetName()
				  << ", " << policeMan.GetDepartmentName() << "\n";
	}
}

void PrintTaxiPassengers(ITaxi const& taxi)
{
	std::cout << "Taxi (" << MakeOfTheCarToString(taxi.GetMakeOfTheCar())
			  << ") passengers:\n";

	for (size_t i = 0; i < taxi.GetPassengerCount(); ++i)
	{
		std::cout << "- " << taxi.GetPassenger(i).GetName() << "\n";
	}
}

int main()
{
	auto johnSmith = std::make_shared<PoliceMan>("John Smith", "North-West Police Department");
	auto jimClark = std::make_shared<PoliceMan>("Jim Clark", "South-East Police Department");
	auto rajaGandhi = std::make_shared<Person>("Raja Gandhi");

	PoliceCar policeCar(5, MakeOfTheCar::FORD);
	policeCar.AddPassenger(johnSmith);
	policeCar.AddPassenger(jimClark);
	// policeCar.AddPassenger(rajaGandhi);

	PrintPoliceCarPassengers(policeCar);

	policeCar.RemovePassenger(1);

	auto michaelSchumacher = std::make_shared<Racer>("Michael Schumacher", 7);

	Taxi taxi(2, MakeOfTheCar::TOYOTA);
	taxi.AddPassenger(rajaGandhi);
	taxi.AddPassenger(michaelSchumacher);

	taxi.RemovePassenger(0);
	taxi.AddPassenger(jimClark);

	PrintTaxiPassengers(taxi);

	try
	{
		taxi.AddPassenger(rajaGandhi);
	}
	catch (std::logic_error const& e)
	{
		std::cout << "Raja Gandhi cannot return to the taxi: " << e.what() << "\n";
	}
}
