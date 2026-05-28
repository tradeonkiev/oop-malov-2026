#include "Vehicle.h"

#include <iostream>
#include <memory>
#include <stdexcept>

void PrintPoliceCarPassengers(IPoliceCar const& policeCar)
{
	std::cout << "Police car " << MakeOfTheCarToString(policeCar.GetMakeOfTheCar())
			  << " passengers:\n";

	for (size_t i = 0; i < policeCar.GetPassengerCount(); ++i)
	{
		auto const& policeMan = policeCar.GetPassenger(i);
		std::cout << "* " << policeMan.GetName()
				  << "\t-\t" << policeMan.GetDepartmentName() << std::endl;
	}
}

void PrintTaxiPassengers(ITaxi const& taxi)
{
	std::cout << "Taxi " << MakeOfTheCarToString(taxi.GetMakeOfTheCar())
			  << " passengers: " << std::endl;

	for (size_t i = 0; i < taxi.GetPassengerCount(); ++i)
	{
		std::cout << "* " << taxi.GetPassenger(i).GetName() << "\n";
	}
}

int main()
{

	auto johnG = std::make_shared<PoliceMan>("john", "sw dep");
	auto dimB = std::make_shared<PoliceMan>("jim", "ne dep");
	auto raja = std::make_shared<Person>("raji");

	PoliceCar policeCar(5, MakeOfTheCar::FORD);
	policeCar.AddPassenger(johnG);
	policeCar.AddPassenger(dimB);
	// policeCar.AddPassenger(raja);

	PrintPoliceCarPassengers(policeCar);

	policeCar.RemovePassenger(1);

	auto michaelS = std::make_shared<Racer>("michael", 7);

	Taxi taxi(2, MakeOfTheCar::TOYOTA);
	taxi.AddPassenger(raja);
	taxi.AddPassenger(michaelS);
	taxi.RemovePassenger(0);
	taxi.AddPassenger(johnG);

	PrintTaxiPassengers(taxi);

	try
	{
		taxi.AddPassenger(raja);
	}
	catch (std::logic_error const& e)
	{
		std::cout << "Raja cannot return to the taxi: " << e.what() << "\n";
	}
}
