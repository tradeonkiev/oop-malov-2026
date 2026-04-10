#pragma once
#include <string>

enum MathOperation
{
	None,
	Add,
	Sub,
	Mul,
	Div
};

class Function
{
public:
	explicit Function(const std::string& opperand)
		: m_leftOperand(opperand)
		, m_operation(MathOperation::None){};
	Function(const std::string& left, MathOperation operation, const std::string& right)
		: m_leftOperand(left)
		, m_operation(operation)
		, m_rightOperand(right){};

	const std::string& LeftOperand() const;
	const std::string& RightOperand() const;
	MathOperation Operation() const;

private:
	std::string m_leftOperand;
	MathOperation m_operation;
	std::string m_rightOperand;
};
