#include "calculator.h"
#include <cmath>

bool Calculator::IsValidIdentifier(const std::string& name)
{
	if (name.empty())
		return false;
	if (std::isdigit(name[0]))
		return false;
	for (char ch : name)
	{
		if (!std::isalnum(ch) && ch != '_')
			return false;
	}
	return true;
}
// TODO: map vs unordered map
void Calculator::InvalidateCache()
{
	m_cache.clear();
}
// TODО: поднимать ошибку в самой функции
void Calculator::InitVariable(const std::string& name)
{
	if (!IsValidIdentifier(name))
		throw std::invalid_argument("Invalid usage");
	if (IdentifierExists(name))
		throw std::runtime_error("Name already exists");
	m_variables.emplace(name, Variable());
}

void Calculator::SetVariable(const std::string& name, double value)
{
	if (!IsValidIdentifier(name))
		throw std::invalid_argument("Invalid usage");
	if (IsFunction(name))
		throw std::invalid_argument("Invalid usage");

	auto it = m_variables.find(name);
	if (it != m_variables.end())
	{
		it->second.SetValue(value);
	}
	else
	{
		m_variables.emplace(name, Variable(value));
	}
	InvalidateCache();
}

void Calculator::SetVariable(const std::string& name, const std::string& srcName)
{
	if (!IsValidIdentifier(name))
		throw std::invalid_argument("Invalid usage");
	if (IsFunction(name))
		throw std::invalid_argument("Invalid usage");
	if (!IdentifierExists(srcName))
		throw std::runtime_error("Name does not exist");
	double value = GetValue(srcName);
	auto it = m_variables.find(name);
	if (it != m_variables.end())
	{
		it->second.SetValue(value);
	}
	else
	{
		m_variables.emplace(name, Variable(value));
	}
	InvalidateCache();
}

void Calculator::InitFunction(const std::string& name, const std::string& operand)
{
	if (!IsValidIdentifier(name))
		throw std::invalid_argument("Invalid usage");
	if (IdentifierExists(name))
		throw std::runtime_error("Name already exists");
	if (!IdentifierExists(operand))
		throw std::runtime_error("Name does not exist");
	m_functions.emplace(name, Function(operand));
}

void Calculator::InitFunction(const std::string& name, const std::string& left,
	MathOperation op, const std::string& right)
{
	if (!IsValidIdentifier(name))
		throw std::invalid_argument("Invalid usage");
	if (IdentifierExists(name))
		throw std::runtime_error("Name already exists");
	if (!IdentifierExists(left))
		throw std::runtime_error("Name does not exist");
	if (!IdentifierExists(right))
		throw std::runtime_error("Name does not exist");
	m_functions.emplace(name, Function(left, op, right));
}

double Calculator::EvaluateFunc(const std::string& name) const
{
	auto cacheIt = m_cache.find(name);
	if (cacheIt != m_cache.end())
		return cacheIt->second;

	auto it = m_functions.find(name);
	if (it == m_functions.end())
		return std::nan("");

	const Function& func = it->second;
	double result;

	if (func.Operation() == MathOperation::None)
	{
		result = GetValue(func.LeftOperand());
	}
	else
	{
		result = Calculate(
			GetValue(func.LeftOperand()),
			func.Operation(),
			GetValue(func.RightOperand()));
	}

	m_cache[name] = result;
	return result;
}

double Calculator::Calculate(double leftOperand, MathOperation operation, double rightOperand) const
{
	if (std::isnan(leftOperand) || std::isnan(rightOperand))
		return std::nan("");

	switch (operation)
	{
	case MathOperation::Add:
		return leftOperand + rightOperand;
	case MathOperation::Sub:
		return leftOperand - rightOperand;
	case MathOperation::Mul:
		return leftOperand * rightOperand;
	case MathOperation::Div:
		if (rightOperand == 0)
			return std::nan("");
		return leftOperand / rightOperand;
	default:
		return std::nan("");
	}
}

double Calculator::GetValue(const std::string& name) const
{
	auto varIt = m_variables.find(name);
	if (varIt != m_variables.end())
		return varIt->second.Value();
	auto funcIt = m_functions.find(name);
	if (funcIt != m_functions.end())
		return EvaluateFunc(name);
	return std::nan("");
}

bool Calculator::IdentifierExists(const std::string& name) const
{
	return m_variables.count(name) || m_functions.count(name);
}

bool Calculator::IsFunction(const std::string& name) const
{
	return m_functions.count(name);
}

std::map<std::string, double> Calculator::AllVariables() const
{
	std::map<std::string, double> result;
	for (const auto& [key, value] : m_variables)
	{
		result[key] = value.Value();
	}
	return result;
}

std::map<std::string, double> Calculator::AllFunctions() const
{
	std::map<std::string, double> result;
	for (const auto& [key, value] : m_functions)
	{
		result[key] = EvaluateFunc(key);
	}
	return result;
}