#include "calculator.h"
#include "parser.h"
#include <cmath>
#include <gtest/gtest.h>
#include <sstream>

class CalculatorTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		out = new std::ostringstream();
		calc = new Calculator();
		pars = new Parser(*calc, *out);
	}

	void TearDown() override
	{
		delete pars;
		delete calc;
		delete out;
	}

	std::ostringstream* out;
	Calculator* calc;
	Parser* pars;
};

TEST_F(CalculatorTest, DeclareAndGetVariable)
{
	calc->InitVariable("x");
	EXPECT_TRUE(std::isnan(calc->GetValue("x")));

	calc->SetVariable("x", 42.0);
	EXPECT_DOUBLE_EQ(calc->GetValue("x"), 42.0);
}

TEST_F(CalculatorTest, FunctionTracksVariable)
{
	calc->SetVariable("x", 5.0);
	calc->InitFunction("f", "x");
	EXPECT_DOUBLE_EQ(calc->GetValue("f"), 5.0);

	calc->SetVariable("x", 10.0);
	EXPECT_DOUBLE_EQ(calc->GetValue("f"), 10.0);
}

TEST_F(CalculatorTest, BinaryOperations)
{

	calc->SetVariable("a", 10.0);
	calc->SetVariable("b", 3.0);
	calc->InitFunction("sum", "a", MathOperation::Add, "b");
	calc->InitFunction("div", "a", MathOperation::Div, "b");
	EXPECT_DOUBLE_EQ(calc->GetValue("sum"), 13.0);
	EXPECT_NEAR(calc->GetValue("div"), 3.33, 0.01);
}

TEST_F(CalculatorTest, Errors)
{

	EXPECT_THROW(calc->InitVariable("123"), std::invalid_argument);

	calc->InitVariable("x");
	EXPECT_THROW(calc->InitVariable("x"), std::runtime_error);
	EXPECT_THROW(calc->InitFunction("f", "unknown"), std::runtime_error);
}

TEST_F(CalculatorTest, Example1)
{
	pars->ProcessCommandFromLine("var x");
	pars->ProcessCommandFromLine("print x");
	pars->ProcessCommandFromLine("let x=42");
	pars->ProcessCommandFromLine("print x");

	EXPECT_EQ(out->str(), "nan\n42.00\n");
};

TEST_F(CalculatorTest, Example2)
{
	pars->ProcessCommandFromLine("var x");
	pars->ProcessCommandFromLine("var y");
	pars->ProcessCommandFromLine("fn XPlusY=x+y");
	pars->ProcessCommandFromLine("print XPlusY");
	pars->ProcessCommandFromLine("let x=3");
	pars->ProcessCommandFromLine("let y=4");
	pars->ProcessCommandFromLine("print XPlusY");
	pars->ProcessCommandFromLine("let x=10");
	pars->ProcessCommandFromLine("print XPlusY");
	pars->ProcessCommandFromLine("let z=3.5");
	pars->ProcessCommandFromLine("fn XPlusYDivZ=XPlusY/z");
	pars->ProcessCommandFromLine("printfns");

	EXPECT_EQ(out->str(), "nan\n7.00\n14.00\nXPlusY:14.00\nXPlusYDivZ:4.00\n");
}

TEST_F(CalculatorTest, FnLet)
{
	pars->ProcessCommandFromLine("let v=42");
	pars->ProcessCommandFromLine("let variable=v");
	pars->ProcessCommandFromLine("fn function=v");
	pars->ProcessCommandFromLine("let v=43");
	pars->ProcessCommandFromLine("print variable");
	pars->ProcessCommandFromLine("print function");

	EXPECT_EQ(out->str(), "42.00\n43.00\n");
}

TEST_F(CalculatorTest, BigNumbers)
{
	pars->ProcessCommandFromLine("let v=999999999");
	pars->ProcessCommandFromLine("let h=999999999");
	pars->ProcessCommandFromLine("fn sum=v+h");
	pars->ProcessCommandFromLine("print sum");

	pars->ProcessCommandFromLine("let v=-999999999");
	pars->ProcessCommandFromLine("let h=-999999999");
	pars->ProcessCommandFromLine("fn sum1=v+h");
	pars->ProcessCommandFromLine("print sum1");

	EXPECT_EQ(out->str(), "1999999998.00\n-1999999998.00\n");
}

TEST_F(CalculatorTest, Fibonacci)
{
	pars->ProcessCommandFromLine("let v0=0");
	pars->ProcessCommandFromLine("let v1=1");
	pars->ProcessCommandFromLine("fn fib0=v0");
	pars->ProcessCommandFromLine("fn fib1=v1");
	pars->ProcessCommandFromLine("fn fib2=fib1+fib0");
	pars->ProcessCommandFromLine("fn fib3=fib2+fib1");
	pars->ProcessCommandFromLine("fn fib4=fib3+fib2");
	pars->ProcessCommandFromLine("fn fib5=fib4+fib3");
	pars->ProcessCommandFromLine("fn fib6=fib5+fib4");
	pars->ProcessCommandFromLine("printfns");

	std::string expected = "fib0:0.00\nfib1:1.00\nfib2:1.00\nfib3:2.00\nfib4:3.00\nfib5:5.00\nfib6:8.00\n";
	EXPECT_EQ(out->str(), expected);
}

TEST_F(CalculatorTest, ErrorMessages)
{
	pars->ProcessCommandFromLine("foo bar");
	pars->ProcessCommandFromLine("var 123abc");
	pars->ProcessCommandFromLine("print x");

	EXPECT_EQ(out->str(), "Unknown command\nInvalid usage\nName does not exist\n");
}

TEST_F(CalculatorTest, Fib50)
{
	calc->SetVariable("v0", 0.0);
	calc->SetVariable("v1", 1.0);
	calc->InitFunction("fib0", "v0");
	calc->InitFunction("fib1", "v1");

	std::string prev2 = "fib0";
	std::string prev1 = "fib1";
	for (int i = 2; i <= 50; i++)
	{
		std::string name = "fib" + std::to_string(i);
		calc->InitFunction(name, prev1, MathOperation::Add, prev2);
		prev2 = prev1;
		prev1 = name;
	}

	EXPECT_DOUBLE_EQ(calc->GetValue("fib50"), 12586269025.0);
}

TEST_F(CalculatorTest, Fib50ResetVar)
{

	calc->SetVariable("v0", 0.0);
	calc->SetVariable("v1", 1.0);
	calc->InitFunction("fib0", "v0");
	calc->InitFunction("fib1", "v1");

	std::string prev2 = "fib0";
	std::string prev1 = "fib1";
	for (int i = 2; i <= 50; i++)
	{
		std::string name = "fib" + std::to_string(i);
		calc->InitFunction(name, prev1, MathOperation::Add, prev2);
		prev2 = prev1;
		prev1 = name;
	}

	EXPECT_DOUBLE_EQ(calc->GetValue("fib50"), 12586269025.0);

	calc->SetVariable("v0", 1.0);
	EXPECT_DOUBLE_EQ(calc->GetValue("fib50"), 20365011074.0);
}


// let a = 10
// let b = 20
// fn fn1 = a + b
// let a = fn1
// print fn1