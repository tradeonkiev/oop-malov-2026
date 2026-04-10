#pragma once
#include <string>

enum class Direction
{
	Standing,
	Forward,
	Backward
};

class Car
{
public:
	bool IsTurnedOn();
	Direction GetDirection();
	int GetSpeed();
	int GetGear();

	void TurnOnEngine();
	void TurnOffEngine();
	void SetGear(int gear);
	void SetSpeed(int speed);

private:
	bool m_engineOn = false;
	int m_gear = 0;
	int m_speed = 0;
	Direction m_movementDirection = Direction::Standing;
};