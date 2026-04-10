#include "function.h"
#include <string>

const std::string& Function::LeftOperand() const
{
	return m_leftOperand;
}

const std::string& Function::RightOperand() const
{
	return m_rightOperand;
}

MathOperation Function::Operation() const
{
	return m_operation;
}