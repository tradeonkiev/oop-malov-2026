#include "parser.h"
#include <cmath>
#include <iomanip>

std::string Parser::Trim(const std::string& s)
{
	int start = s.find_first_not_of(" \t");
	if (start == std::string::npos)
		return "";
	int end = s.find_last_not_of(" \t");
	return s.substr(start, end - start + 1);
}

MathOperation Parser::CharToOperation(char ch)
{
	switch (ch)
	{
	case '+':
		return MathOperation::Add;
	case '-':
		return MathOperation::Sub;
	case '*':
		return MathOperation::Mul;
	case '/':
		return MathOperation::Div;
	default:
		return MathOperation::None;
	}
}

void Parser::PrintValue(double value)
{
	if (std::isnan(value))
	{
		m_out << "nan" << std::endl;
	}
	else
	{
		m_out << std::fixed << std::setprecision(2) << value << std::endl;
	}
}

// TODO: rename + try -
void Parser::ProcessCommandFromLine(const std::string& line)
{
	std::string trimmed = Trim(line);
	if (trimmed.empty())
		return;

	int spacePos = trimmed.find(' ');
	std::string command;
	std::string args;

	if (spacePos != std::string::npos)
	{
		command = trimmed.substr(0, spacePos);
		args = Trim(trimmed.substr(spacePos + 1));
	}
	else
	{
		command = trimmed;
		args = "";
	}

	if (command == "var")
		HandleVar(args);
	else if (command == "let")
		HandleLet(args);
	else if (command == "fn")
		HandleFn(args);
	else if (command == "print")
		HandlePrint(args);
	else if (command == "printvars")
		HandlePrintVars();
	else if (command == "printfns")
		HandlePrintFns();
	else
		m_out << "Unknown command" << std::endl;
}

void Parser::HandleVar(const std::string& args)
{
	if (args.empty())
	{
		m_out << "Invalid usage" << std::endl;
		return;
	}
	try
	{
		m_calc.InitVariable(args);
	}
	catch (const std::exception& e)
	{
		m_out << e.what() << std::endl;
	}
}

void Parser::HandleLet(const std::string& args)
{
	if (args.empty())
	{
		m_out << "Invalid usage" << std::endl;
		return;
	}

	std::string compact;
	for (char ch : args)
	{
		if (ch != ' ' && ch != '\t')
			compact += ch;
	}

	int eqPosition = compact.find('=');
	if (eqPosition == std::string::npos || eqPosition == 0 || eqPosition == compact.size() - 1)
	{
		m_out << "Invalid usage" << std::endl;
		return;
	}

	std::string name = compact.substr(0, eqPosition);
	std::string rawValue = compact.substr(eqPosition + 1);

	if (!Calculator::IsValidIdentifier(name))
	{
		m_out << "Invalid usage" << std::endl;
		return;
	}

	try
	{
		size_t pos = 0;
		double value = std::stod(rawValue, &pos);
		if (pos == rawValue.size())
		{
			try
			{
				m_calc.SetVariable(name, value);
			}
			catch (const std::exception& e)
			{
				m_out << e.what() << std::endl;
			}
			return;
		}

		m_out << "Invalid usage" << std::endl;
		return;
	}
	catch (...)
	{
	}

	if (Calculator::IsValidIdentifier(rawValue))
	{
		try
		{
			m_calc.SetVariable(name, rawValue);
		}
		catch (const std::exception& e)
		{
			m_out << e.what() << std::endl;
		}
		return;
	}

	m_out << "Invalid usage" << std::endl;
}

void Parser::HandleFn(const std::string& args)
{
	if (args.empty())
	{
		m_out << "Invalid usage" << std::endl;
		return;
	}

	std::string compact;
	for (char ch : args)
	{
		if (ch != ' ' && ch != '\t')
			compact += ch;
	}

	int eqPosition = compact.find('=');
	if (eqPosition == std::string::npos || eqPosition == 0 || eqPosition == compact.size() - 1)
	{
		m_out << "Invalid usage" << std::endl;
		return;
	}

	std::string name = compact.substr(0, eqPosition);
	std::string expression = compact.substr(eqPosition + 1);

	if (!Calculator::IsValidIdentifier(name))
	{
		m_out << "Invalid usage" << std::endl;
		return;
	}

	size_t operationPosition = std::string::npos;
	for (int i = 0; i < expression.size(); ++i)
	{
		if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/')
		{
			operationPosition = i;
			break;
		}
	}

	if (operationPosition == std::string::npos)
	{
		if (!Calculator::IsValidIdentifier(expression))
		{
			m_out << "Invalid usage" << std::endl;
			return;
		}
		try
		{
			m_calc.InitFunction(name, expression);
		}
		catch (const std::exception& e)
		{
			m_out << e.what() << std::endl;
		}
	}
	else
	{
		std::string left = expression.substr(0, operationPosition);
		char rawOperation = expression[operationPosition];
		std::string right = expression.substr(operationPosition + 1);

		if (!Calculator::IsValidIdentifier(left) || !Calculator::IsValidIdentifier(right))
		{
			m_out << "Invalid usage" << std::endl;
			return;
		}

		MathOperation operation = CharToOperation(rawOperation);
		try
		{
			m_calc.InitFunction(name, left, operation, right);
		}
		catch (const std::exception& e)
		{
			m_out << e.what() << std::endl;
		}
	}
}

void Parser::HandlePrint(const std::string& args)
{
	if (args.empty())
	{
		m_out << "Invalid usage" << std::endl;
		return;
	}

	if (!m_calc.IdentifierExists(args))
	{
		m_out << "Name does not exist" << std::endl;
		return;
	}
	PrintValue(m_calc.GetValue(args));
}

void Parser::HandlePrintVars()
{
	auto vars = m_calc.AllVariables();
	for (const auto& [key, value] : vars)
	{
		m_out << key << ":";
		if (std::isnan(value))
			m_out << "nan";
		else
			m_out << std::fixed << std::setprecision(2) << value;
		m_out << std::endl;
	}
}

void Parser::HandlePrintFns()
{
	auto fns = m_calc.AllFunctions();
	for (const auto& [key, value] : fns)
	{
		m_out << key << ":";
		if (std::isnan(value))
			m_out << "nan";
		else
			m_out << std::fixed << std::setprecision(2) << value;
		m_out << std::endl;
	}
}
