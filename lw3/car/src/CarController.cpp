#include "CarController.h"
#include <sstream>
#include <string>

std::string DirectionToString(Direction dir)
{
	switch (dir)
	{
	case Direction::Standing:
		return "standing still";
	case Direction::Forward:
		return "forward";
	case Direction::Backward:
		return "backward";
	}
	return "standing still";
}

bool TryParseInt(const std::string& str, int& result)
{
	if (str.empty())
	{
		return false;
	}

	try
	{
		size_t pos = 0;
		result = std::stoi(str, &pos);
		return pos == str.size();
	}
	catch (...)
	{
		return false;
	}
}

void PrintInfo(Car& car, std::ostream& output)
{
	output << "Engine: " << (car.IsTurnedOn() ? "on" : "off") << std::endl;
	output << "Direction: " << DirectionToString(car.GetDirection()) << std::endl;
	output << "Speed: " << car.GetSpeed() << std::endl;
	output << "Gear: " << car.GetGear() << std::endl;
}

void HandleSetGear(Car& car, const std::string& arg, std::ostream& output)
{
	int gear;
	if (!TryParseInt(arg, gear))
	{
		output << "Invalid command argument" << std::endl;
		return;
	}
	try
	{
		car.SetGear(gear);
	}
	catch (const std::exception& e)
	{
		output << e.what() << std::endl;
	}
}

void HandleSetSpeed(Car& car, const std::string& arg, std::ostream& output)
{
	int speed;
	if (!TryParseInt(arg, speed))
	{
		output << "Invalid command argument" << std::endl;
		return;
	}
	try
	{
		car.SetSpeed(speed);
	}
	catch (const std::exception& e)
	{
		output << e.what() << std::endl;
	}
}

bool TryReadSingleArg(std::istringstream& iss, std::string& arg, std::ostream& output)
{
	if (!(iss >> arg))
	{
		output << "Invalid command argument" << std::endl;
		return false;
	}
	std::string extra;
	if (iss >> extra)
	{
		output << "Invalid command argument" << std::endl;
		return false;
	}
	return true;
}

void HandleCommand(Car& car, const std::string& line, std::ostream& output)
{
	std::istringstream iss(line);
	std::string command;
	iss >> command;

	if (command.empty())
	{
		return;
	}

	if (command == "Info")
	{
		PrintInfo(car, output);
	}
	else if (command == "EngineOn")
	{
		car.TurnOnEngine();
	}
	else if (command == "EngineOff")
	{
		try
		{
			car.TurnOffEngine();
		}
		catch (const std::exception& e)
		{
			output << e.what() << std::endl;
		}
	}
	else if (command == "SetGear")
	{
		std::string arg;
		if (TryReadSingleArg(iss, arg, output))
		{
			HandleSetGear(car, arg, output);
		}
	}
	else if (command == "SetSpeed")
	{
		std::string arg;
		if (TryReadSingleArg(iss, arg, output))
		{
			HandleSetSpeed(car, arg, output);
		}
	}
	else
	{
		output << "Unknown command" << std::endl;
	}
}

void RunCarController(Car& car, std::istream& input, std::ostream& output)
{
	std::string line;
	while (std::getline(input, line))
	{
		HandleCommand(car, line, output);
	}
}
