#pragma once

struct EquationRoot4
{
	int numRoots;
	double roots[4];
};

EquationRoot4 Solve4(double a, double b, double c, double d, double e);