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
	PoliceMan policeMan("J Smith", "NW Dep");

	ASSERT_EQ(policeMan.GetName(), "J Smith");
	ASSERT_EQ(policeMan.GetDepartmentName(), "NW Dep");
}

TEST(PersonTest, RacerReturnsNameAndAwardsCount)
{
	Racer racer("Michael Schumacher", 7);

	ASSERT_EQ(racer.GetName(), "Michael Schumacher");
	ASSERT_EQ(racer.GetAwardsCount(), 7u);
}

TEST(VehicleTest, EmptyVehicleKnowsItsCapacity)
{
	Taxi taxi(2, MakeOfTheCar::TOYOTA);

	ASSERT_TRUE(taxi.IsEmpty());
	ASSERT_FALSE(taxi.IsFull());
	ASSERT_EQ(taxi.GetPlaceCount(), 2u);
	ASSERT_EQ(taxi.GetPassengerCount(), 0u);
}

TEST(VehicleTest, VehicleStoresPassengersInInsertionOrder)
{
	Taxi taxi(2, MakeOfTheCar::TOYOTA);
	auto driver = std::make_shared<Person>("Raja Gandhi");
	auto racer = std::make_shared<Racer>("Michael Schumacher", 7);

	taxi.AddPassenger(driver);
	taxi.AddPassenger(racer);

	ASSERT_FALSE(taxi.IsEmpty());
	ASSERT_TRUE(taxi.IsFull());
	ASSERT_EQ(taxi.GetPassengerCount(), 2u);
	ASSERT_EQ(taxi.GetPassenger(0).GetName(), "Raja Gandhi");
	ASSERT_EQ(taxi.GetPassenger(1).GetName(), "Michael Schumacher");
}

TEST(VehicleTest, FullVehicleRejectsNewPassengerWithLogicError)
{
	Taxi taxi(1, MakeOfTheCar::TOYOTA);
	taxi.AddPassenger(std::make_shared<Person>("Raja Gandhi"));

	ASSERT_THROW(taxi.AddPassenger(std::make_shared<PoliceMan>(
					 "Jim Clark", "South-East Police Department")),
		std::logic_error);
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

	ASSERT_EQ(policeCar.GetPassengerCount(), 1u);
	ASSERT_EQ(policeCar.GetPassenger(0).GetName(), "J Clark");
}

TEST(VehicleTest, RemoveAllPassengersClearsVehicle)
{
	Bus bus(3);
	bus.AddPassenger(std::make_shared<Person>("Raja Gandhi"));
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

TEST(TypeSafetyTest, TaxiAndBusAcceptAnyPerson)
{
	static_assert(std::is_invocable_v<decltype(&Taxi::AddPassenger), Taxi*,
		std::shared_ptr<IPerson>>);
	static_assert(std::is_invocable_v<decltype(&Bus::AddPassenger), Bus*,
		std::shared_ptr<IPerson>>);
}

TEST(TypeSafetyTest, SpecialCarsAcceptOnlySpecialPassengers)
{
	static_assert(std::is_invocable_v<decltype(&PoliceCar::AddPassenger),
		PoliceCar*, std::shared_ptr<IPoliceMan>>);
	static_assert(std::is_invocable_v<decltype(&RacingCar::AddPassenger),
		RacingCar*, std::shared_ptr<IRacer>>);
	static_assert(!std::is_invocable_v<decltype(&PoliceCar::AddPassenger),
		PoliceCar*, std::shared_ptr<IPerson>>);
	static_assert(!std::is_invocable_v<decltype(&RacingCar::AddPassenger),
		RacingCar*, std::shared_ptr<IPerson>>);
}
