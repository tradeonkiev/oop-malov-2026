#include "Vehicle.h"

#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <type_traits>

TEST(PersonTest, PersonReturnsName)
{
	Person person("Gandhi");

	ASSERT_EQ(person.GetName(), "Gandhi");
}

TEST(PersonTest, PoliceManReturnsNameAndDepartment)
{
	PoliceMan policeMan("Smith", "NW Dep");

	ASSERT_EQ(policeMan.GetName(), "Smith");
	ASSERT_EQ(policeMan.GetDepartmentName(), "NW Dep");
}

TEST(PersonTest, RacerReturnsNameAndAwardsCount)
{
	Racer racer("Sergey", 7);

	ASSERT_EQ(racer.GetName(), "Sergey");
	ASSERT_EQ(racer.GetAwardsCount(), 7);
}

TEST(VehicleTest, EmptyVehicleKnowsItsCapacity)
{
	Taxi taxi(2, MakeOfTheCar::TOYOTA);

	ASSERT_TRUE(taxi.IsEmpty());
	ASSERT_FALSE(taxi.IsFull());
	ASSERT_EQ(taxi.GetPlaceCount(), 2);
	ASSERT_EQ(taxi.GetPassengerCount(), 0);
}

TEST(VehicleTest, VehicleStoresPassengersInInsertionOrder)
{
	Taxi taxi(2, MakeOfTheCar::TOYOTA);
	auto driver = std::make_shared<Person>("Gandhi");
	auto racer = std::make_shared<Racer>("Sergey", 7);

	taxi.AddPassenger(driver);
	taxi.AddPassenger(racer);

	ASSERT_FALSE(taxi.IsEmpty());
	ASSERT_TRUE(taxi.IsFull());
	ASSERT_EQ(taxi.GetPassengerCount(), 2);
	ASSERT_EQ(taxi.GetPassenger(0).GetName(), "Gandhi");
	ASSERT_EQ(taxi.GetPassenger(1).GetName(), "Sergey");
}

TEST(VehicleTest, FullVehicleRejectsNewPassengerWithLogicError)
{
	Taxi taxi(1, MakeOfTheCar::TOYOTA);
	taxi.AddPassenger(std::make_shared<Person>("Gandhi"));

	ASSERT_THROW(taxi.AddPassenger(std::make_shared<PoliceMan>("Clark", "SE dep")), std::logic_error);
}

TEST(VehicleTest, GettingOrRemovingPassengerByInvalidIndexThrowsOutOfRange)
{
	Taxi taxi(1, MakeOfTheCar::TOYOTA);

	ASSERT_THROW(taxi.GetPassenger(0), std::out_of_range);
	ASSERT_THROW(taxi.RemovePassenger(0), std::out_of_range);
}

TEST(VehicleTest, RemovePassengerDeletesRequestedPassenger)
{
	PoliceCar policeCar(5, MakeOfTheCar::FORD);
	policeCar.AddPassenger(std::make_shared<PoliceMan>("J Smith", "NW Dep"));
	policeCar.AddPassenger(std::make_shared<PoliceMan>("J Clark", "SE Dep"));

	policeCar.RemovePassenger(0);

	ASSERT_EQ(policeCar.GetPassengerCount(), 1);
	ASSERT_EQ(policeCar.GetPassenger(0).GetName(), "J Clark");
}

TEST(VehicleTest, RemoveAllPassengersClearsVehicle)
{
	Bus bus(3);
	bus.AddPassenger(std::make_shared<Person>("Gandhi"));
	bus.AddPassenger(std::make_shared<PoliceMan>("J Clark", "SE Dep"));

	bus.RemoveAllPassengers();

	ASSERT_TRUE(bus.IsEmpty());
	ASSERT_EQ(bus.GetPassengerCount(), 0u);
}

TEST(CarTest, CarStoresMake)
{
	RacingCar racingCar(1, MakeOfTheCar::FERRARI);

	ASSERT_EQ(racingCar.GetMakeOfTheCar(), MakeOfTheCar::FERRARI);
	ASSERT_EQ(MakeOfTheCarToString(racingCar.GetMakeOfTheCar()), "Ferrari");
}
