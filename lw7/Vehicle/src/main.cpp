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
	
	auto johnG = std::make_shared<PoliceMan>("джон гарик", "департамент северо-западной полиции");
	auto dimB = std::make_shared<PoliceMan>("джим бигдик", "департамент северо-восточной полиции");
	auto raja = std::make_shared<Person>("ганди раджи");

	PoliceCar policeCar(5, MakeOfTheCar::FORD);
	policeCar.AddPassenger(johnG);
	policeCar.AddPassenger(dimB);
	// policeCar.AddPassenger(rajaGandhi);

	PrintPoliceCarPassengers(policeCar);

	policeCar.RemovePassenger(1);

	auto michaelS = std::make_shared<Racer>("михаил шумахер", 7);

	Taxi taxi(2, MakeOfTheCar::TOYOTA);
	taxi.AddPassenger(raja);
	taxi.AddPassenger(michaelS);
	taxi.RemovePassenger(0);
	taxi.AddPassenger(johnG);

	PrintTaxiPassengers(taxi);

	try
	{
		taxi.AddPassenger(raja);
		taxi.AddPassenger(raja);
	}
	catch (std::logic_error const& e)
	{
		std::cout << "Raja Gandhi cannot return to the taxi: " << e.what() << "\n";
	}
}
