#pragma once
#include <cstddef>

// базовое транспортное средство
class IBasicVehicle
{
public:
	// сигнализирует о том, пусто ли транспортное средство
	virtual bool IsEmpty() const = 0;

	// сигнализирует о том заполнено ли транспортное средство полностью
	virtual bool IsFull() const = 0;
	
	// возвращает общее количество мест
	virtual size_t GetPlaceCount() const = 0;

	// возвращает количество пассажиров на борту
	virtual size_t GetPassengerCount() const = 0;

	// высаживает всех пассажиров
	virtual void RemoveAllPassengers() = 0;
	virtual ~IBasicVehicle() = default;
};