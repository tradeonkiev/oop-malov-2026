#include "Car.h"
#include <functional>
#include <gtest/gtest.h>

void ExpectThrowMsg(std::function<void()> func, const char* expectedMsg)
{
	try
	{
		func();
		FAIL() << "Expected exception: " << expectedMsg;
	}
	catch (const std::exception& e)
	{
		EXPECT_STREQ(e.what(), expectedMsg);
	}
}

TEST(EngineTest, DoubleTurnOn)
{
	Car car;
	car.TurnOnEngine();
	car.TurnOnEngine();
	EXPECT_TRUE(car.IsTurnedOn());
}

TEST(EngineTest, TurnOnTurnOff)
{
	Car car;
	car.TurnOnEngine();
	car.TurnOffEngine();
	EXPECT_FALSE(car.IsTurnedOn());
}

TEST(EngineTest, TurnOffWhenAlreadyOff)
{
	Car car;
	EXPECT_NO_THROW(car.TurnOffEngine());
}

TEST(EngineTest, CannotTurnOffWhileMoving)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);
	ExpectThrowMsg([&car] { car.TurnOffEngine(); }, "Car must be stopped and in neutral gear");
}


TEST(InitialStateTest, InfoEngineOn)
{
	Car car;
	car.TurnOnEngine();
	EXPECT_TRUE(car.IsTurnedOn());
	EXPECT_EQ(car.GetSpeed(), 0);
	EXPECT_EQ(car.GetGear(), 0);
	EXPECT_EQ(car.GetDirection(), Direction::Standing);
}

TEST(GearTest, SetFirstFromNeutral)
{
	Car car;
	car.TurnOnEngine();
	EXPECT_NO_THROW(car.SetGear(1));
	EXPECT_EQ(car.GetGear(), 1);
}

TEST(GearTest, SetReverseFromNeutral)
{
	Car car;
	car.TurnOnEngine();
	EXPECT_NO_THROW(car.SetGear(-1));
	EXPECT_EQ(car.GetGear(), -1);
}

TEST(GearTest, CannotSetWhenEngineOff)
{
	Car car;
	ExpectThrowMsg([&car] { car.SetGear(1); }, "Cannot set gear while engine is off");
}

TEST(GearTest, CanSetNeutralWhenEngineOff)
{
	Car car;
	EXPECT_NO_THROW(car.SetGear(0));
}

TEST(GearTest, InvalidGearUnderBound)
{
	Car car;
	car.TurnOnEngine();
	ExpectThrowMsg([&car] { car.SetGear(-2); }, "Invalid gear");
}

TEST(GearTest, InvalidGearUpperBound)
{
	Car car;
	car.TurnOnEngine();
	ExpectThrowMsg([&car] { car.SetGear(6); }, "Invalid gear");
}

TEST(GearTest, CannotReverseWhileMovingForward)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);
	ExpectThrowMsg([&car] { car.SetGear(-1); }, "Cannot reverse while moving");
}

TEST(GearTest, CannotSetForwardWhileMovingBackward)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);
	car.SetGear(0);
	ExpectThrowMsg([&car] { car.SetGear(1); }, "Unsuitable current speed");
}

TEST(GearTest, UnsuitableSpeed)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(19);
	ExpectThrowMsg([&car] { car.SetGear(2); }, "Unsuitable current speed");
}

TEST(GearTest, SetSecondAtSpeed20)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	EXPECT_NO_THROW(car.SetGear(2));
	EXPECT_EQ(car.GetGear(), 2);
}

TEST(GearTest, SetToSameGear)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	EXPECT_NO_THROW(car.SetGear(1));
}

TEST(GearTest, InvalidGearPriorityOverEngineOff)
{
	Car car;
	ExpectThrowMsg([&car] { car.SetGear(6); }, "Invalid gear");
}

TEST(SpeedTest, SetOnFirstGear)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	EXPECT_NO_THROW(car.SetSpeed(15));
	EXPECT_EQ(car.GetSpeed(), 15);
}

TEST(SpeedTest, CannotSetNegative)
{
	Car car;
	car.TurnOnEngine();
	ExpectThrowMsg([&car] { car.SetSpeed(-1); }, "Speed cannot be negative");
}

TEST(SpeedTest, CannotSetWhenEngineOff)
{
	Car car;
	ExpectThrowMsg([&car] { car.SetSpeed(10); }, "Cannot set speed while engine is off");
}

TEST(SpeedTest, CannotAccelerateOnNeutral)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(0);
	ExpectThrowMsg([&car] { car.SetSpeed(25); }, "Cannot accelerate on neutral");
}

TEST(SpeedTest, CanDecelerateOnNeutral)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(0);
	EXPECT_NO_THROW(car.SetSpeed(10));
	EXPECT_EQ(car.GetSpeed(), 10);
}

TEST(SpeedTest, OutOfGearRange)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	ExpectThrowMsg([&] { car.SetSpeed(31); }, "Speed is out of gear range");
}

TEST(SpeedTest, ZeroAlwaysValid)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(15);
	EXPECT_NO_THROW(car.SetSpeed(0));
	EXPECT_EQ(car.GetSpeed(), 0);
}

TEST(SpeedTest, NegativePriorityOverEngineOff)
{
	Car car;
	ExpectThrowMsg([&car] { car.SetSpeed(-5); }, "Speed cannot be negative");
}

TEST(DirectionTest, ForwardOnFirstGear)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);
	EXPECT_EQ(car.GetDirection(), Direction::Forward);
}

TEST(DirectionTest, BackwardOnReverse)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);
	EXPECT_EQ(car.GetDirection(), Direction::Backward);
}

TEST(DirectionTest, StandingAtZeroSpeed)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);
	car.SetSpeed(0);
	EXPECT_EQ(car.GetDirection(), Direction::Standing);
}

TEST(DirectionTest, PreservedForwardOnNeutral)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(0);
	EXPECT_EQ(car.GetDirection(), Direction::Forward);
}

TEST(DirectionTest, PreservedBackwardOnNeutral)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);
	car.SetGear(0);
	EXPECT_EQ(car.GetDirection(), Direction::Backward);
}

TEST(ScenarioTest, FullForwardDrive)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);
	car.SetSpeed(50);
	car.SetGear(3);
	car.SetSpeed(60);
	car.SetGear(4);
	car.SetSpeed(90);
	car.SetGear(5);
	car.SetSpeed(150);
	EXPECT_EQ(car.GetSpeed(), 150);
	EXPECT_EQ(car.GetGear(), 5);
}

TEST(ScenarioTest, ReverseToNeutralToStop)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(15);
	car.SetGear(0);
	EXPECT_EQ(car.GetDirection(), Direction::Backward);
	EXPECT_EQ(car.GetGear(), 0);

	EXPECT_THROW(car.SetGear(1), std::runtime_error);

	car.SetSpeed(0);
	EXPECT_EQ(car.GetDirection(), Direction::Standing);
	EXPECT_NO_THROW(car.SetGear(1));
}

TEST(ScenarioTest, CannotReverseOnNeutralMovingBackward)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(10);
	car.SetGear(0);
	ExpectThrowMsg([&car] { car.SetGear(-1); }, "Cannot reverse while moving");
}

TEST(ScenarioTest, StopAndTurnOff)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(0);
	car.SetSpeed(0);
	EXPECT_NO_THROW(car.TurnOffEngine());
	EXPECT_FALSE(car.IsTurnedOn());
}

TEST(ScenarioTest, MaxSpeedOnReverse)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(-1);
	EXPECT_NO_THROW(car.SetSpeed(20));
	ExpectThrowMsg([&car] { car.SetSpeed(21); }, "Speed is out of gear range");
}

TEST(ScenarioTest, GearBoundaryCheck)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(20);
	car.SetGear(2);
	EXPECT_EQ(car.GetGear(), 2);
	car.SetSpeed(50);
	car.SetGear(3);
	EXPECT_EQ(car.GetGear(), 3);
}