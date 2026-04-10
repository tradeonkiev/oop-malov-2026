#pragma once
#include <cmath>

class Variable
{
public:
	Variable()
		: m_value(std::nan("")){};
	explicit Variable(double value)
		: m_value(value){}; 

	double Value() const;
	void SetValue(double value);

private:
	double m_value;
};