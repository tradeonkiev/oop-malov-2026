#pragma once
#include "calculator.h"
#include <iostream>
#include <string>
// TODO: split logic (contoller + parser)
class Parser
{
public:
	explicit Parser(Calculator& calc, std::ostream& out = std::cout)
		: m_calc(calc)
		, m_out(out)
	{
	}

	void ProcessCommandFromLine(const std::string& line);

private:
	void HandleVar(const std::string& args);
	void HandleLet(const std::string& args);
	void HandleFn(const std::string& args);
	void HandlePrint(const std::string& args);
	void HandlePrintVars();
	void HandlePrintFns();

	void PrintValue(double value);
	static std::string Trim(const std::string& s);
	static MathOperation CharToOperation(char ch);

	Calculator& m_calc;
	std::ostream& m_out;
};