#include "variable.h"

double Variable::Value() const
{
	return m_value;
}

void Variable::SetValue(double value)
{
	m_value = value;
}