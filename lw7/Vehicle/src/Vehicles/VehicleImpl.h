#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <vector>

template <typename Interface, typename Passenger>
class VehicleImpl : public Interface
{
public:
	VehicleImpl() = delete;

	VehicleImpl(size_t placeCount)
		: m_placeCount(placeCount)
	{
	}

	bool IsEmpty() const override
	{
		return m_passengers.empty();
	}

	bool IsFull() const override
	{
		return m_passengers.size() >= m_placeCount;
	}

	size_t GetPlaceCount() const override
	{
		return m_placeCount;
	}

	size_t GetPassengerCount() const override
	{
		return m_passengers.size();
	}

	void RemoveAllPassengers() override
	{
		m_passengers.clear();
	}

	void AddPassenger(std::shared_ptr<Passenger> pPassenger) override
	{
		if (!pPassenger)
		{
			throw std::invalid_argument("Passenger must not be null");
		}
		if (IsFull())
		{
			throw std::logic_error("There are no free seats in the vehicle");
		}

		m_passengers.push_back(pPassenger);
	}

	Passenger const& GetPassenger(size_t index) const override
	{
		if (index >= m_passengers.size())
		{
			throw std::out_of_range("Passenger index is out of range");
		}

		return *m_passengers[index];
	}

	void RemovePassenger(size_t index) override
	{
		if (index >= m_passengers.size())
		{
			throw std::out_of_range("Passenger index is out of range");
		}

		m_passengers.erase(m_passengers.begin() + index);
	}

private:
	size_t m_placeCount;
	std::vector<std::shared_ptr<Passenger>> m_passengers;
};
