#pragma once
#include <string>

enum class MakeOfTheCar
{
	BMW,
	MITSUBISHI,
	FORD,
	MERCEDES,
	TOYOTA,
	KIA,
	FERRARI,
	PORSCHE,
	LEXUS,
	NISSAN,
	INFINITI,
};

inline std::string MakeOfTheCarToString(MakeOfTheCar make)
{
	switch (make)
	{
	case MakeOfTheCar::BMW:
		return "BMW";
	case MakeOfTheCar::MITSUBISHI:
		return "Mitsubishi";
	case MakeOfTheCar::FORD:
		return "Ford";
	case MakeOfTheCar::MERCEDES:
		return "Mercedes";
	case MakeOfTheCar::TOYOTA:
		return "Toyota";
	case MakeOfTheCar::KIA:
		return "Kia";
	case MakeOfTheCar::FERRARI:
		return "Ferrari";
	case MakeOfTheCar::PORSCHE:
		return "Porsche";
	case MakeOfTheCar::LEXUS:
		return "Lexus";
	case MakeOfTheCar::NISSAN:
		return "Nissan";
	case MakeOfTheCar::INFINITI:
		return "Infiniti";
	default:
		return "Unknown";
	}
}
