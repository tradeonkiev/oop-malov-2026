#include "Car.h"
#include "GearRange.h"
#include <stdexcept>

bool Car::IsTurnedOn()
{
	return m_engineOn;
}

Direction Car::GetDirection()
{
	return m_movementDirection;
}

int Car::GetSpeed()
{
	return m_speed;
}

int Car::GetGear()
{
	return m_gear;
}

void Car::TurnOnEngine()
{
	m_engineOn = true;
}

void Car::TurnOffEngine()
{
	if (!m_engineOn)
		return;
	else if (m_gear != 0 || m_speed != 0)
	{
		throw std::runtime_error("Car must be stopped and in neutral gear");
	}
	else
	{
		m_engineOn = false;
	}
}

void Car::SetGear(int gear)
{

	if (gear > kMaxGear || gear < kMinGear)
	{
		throw std::runtime_error("Invalid gear");
	}

	if (!m_engineOn && gear)
	{
		throw std::runtime_error("Cannot set gear while engine is off");
	}

	if (gear == m_gear)
	{
		return;
	}

	if (!gear)
	{
		m_gear = 0;
		return;
	}

	if (gear == -1 && m_speed != 0)
	{
		throw std::runtime_error("Cannot reverse while moving");
	}

	if ((m_speed > 0 && m_movementDirection == Direction::Backward) || !IsSpeedInGearRange(gear, m_speed))
	{
		throw std::runtime_error("Unsuitable current speed");
	}

	m_gear = gear;
	if (m_gear)
	{
		m_movementDirection = (m_gear == -1) ? Direction::Backward : Direction::Forward;
	}
}

void Car::SetSpeed(int speed)
{
	if (speed < 0)
	{
		throw std::runtime_error("Speed cannot be negative");
	}
	if (!m_engineOn)
	{
		throw std::runtime_error("Cannot set speed while engine is off");
	}
	if (!m_gear && speed > m_speed)
	{
		throw std::runtime_error("Cannot accelerate on neutral");
	}
	if (!IsSpeedInGearRange(m_gear, speed))
	{
		throw std::runtime_error("Speed is out of gear range");
	}

	if (!speed)
		m_movementDirection = Direction::Standing;
	m_speed = speed;
}
