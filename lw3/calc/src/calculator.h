#include "function.h"
#include "variable.h"
#include <map>
#include <stdexcept>
#include <string>

class Calculator
{
public:
	void InitVariable(const std::string& name);

	void SetVariable(const std::string& name, double value);
	void SetVariable(const std::string& firstName, const std::string& secondName);

	void InitFunction(const std::string& name, const std::string& operand);
	void InitFunction(const std::string& name, const std::string& leftOperand, MathOperation operand, const std::string& rightOperand);

	double GetValue(const std::string& name) const;
	bool IdentifierExists(const std::string& name) const;
	bool IsFunction(const std::string& name) const;

	static bool IsValidIdentifier(const std::string& name);
	std::map<std::string, double> AllFunctions() const;
	std::map<std::string, double> AllVariables() const;

private:
	double EvaluateFunc(const std::string& name) const;
	double Calculate(double leftOperand, MathOperation operation, double rightOperand) const;

	std::map<std::string, Function> m_functions;
	std::map<std::string, Variable> m_variables;

	mutable std::map<std::string, double> m_cache;
	void InvalidateCache();
};