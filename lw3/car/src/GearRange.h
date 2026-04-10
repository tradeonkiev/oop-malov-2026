#pragma once
#include <array>

struct GearRange
{
	int gear;
	int minSpeed;
	int maxSpeed;
};

const std::array<GearRange, 7> kGearRanges = { {
	{ -1, 0, 20 },
	{ 0, 0, 150 },
	{ 1, 0, 30 },
	{ 2, 20, 50 },
	{ 3, 30, 60 },
	{ 4, 40, 90 },
	{ 5, 50, 150 },
} };

const int kMinGear = -1;
const int kMaxGear = 5;

const GearRange& GetGearRange(int gear)
{
	return kGearRanges[gear + 1];
}

const bool IsSpeedInGearRange(int gear, int speed)
{
	const GearRange& range = GetGearRange(gear);
	return speed >= range.minSpeed && speed <= range.maxSpeed;
}