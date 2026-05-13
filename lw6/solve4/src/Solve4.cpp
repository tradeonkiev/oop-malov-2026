#include "Solve4.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numbers>
#include <stdexcept>

struct Coefficients
{
	double p;
	double q;
	double r;
};

Coefficients CalcCoefs(double a, double b, double c, double d, double e);
Coefficients CalcCoefsCubicResolvent(double a, double b, double c);
EquationRoot4 SolveBiquadratic(double a_, double c_, double bShift);
double CalcResolventY(double a_, double b_, double c_);
EquationRoot4 ExtractRoots(double a_, double b_, double y, double bShift);

EquationRoot4 Solve4(double a, double b, double c, double d, double e)
{
	if (std::abs(a) < 1e-12)
		throw std::invalid_argument("Coefficient at x^4 must not be zero");

	auto [a_, b_, c_] = CalcCoefs(a, b, c, d, e);
	double bShift = -b / (4 * a);

	EquationRoot4 result;
	if (std::abs(b_) < 1e-12)
		result = SolveBiquadratic(a_, c_, bShift);
	else
	{
		double y = CalcResolventY(a_, b_, c_);
		result = ExtractRoots(a_, b_, y, bShift);
	}

	if (result.numRoots == 0)
		throw std::domain_error("Equation has no real roots");

	std::sort(result.roots, result.roots + result.numRoots);
	return result;
}

Coefficients CalcCoefs(double a, double b, double c, double d, double e)
{
	Coefficients res;
	res.p = -3.0 * std::pow(b, 2) / 8.0 / std::pow(a, 2) + c / a;
	res.q = std::pow(b, 3) / 8.0 / std::pow(a, 3) - b * c / 2.0 / std::pow(a, 2) + d / a;
	res.r = -3.0 * std::pow(b, 4) / 256.0 / std::pow(a, 4) + std::pow(b, 2) * c / 16.0 / std::pow(a, 3) - b * d / 4.0 / std::pow(a, 2) + e / a;
	return res;
}

EquationRoot4 SolveBiquadratic(double a_, double c_, double bShift)
{
	EquationRoot4 result{};
	int n = 0;
	double x1, x2;

	double disc = std::pow(a_, 2) - 4 * c_;
	if (disc < 0)
	{
		result.numRoots = 0;
		return result;
	}

	for (int sign : { -1, 1 })
	{
		double inner = (-a_ + sign * std::sqrt(disc)) * 0.5;
		if (inner < 0)
		{
			continue;
		}
		x1 = bShift - std::sqrt(inner);
		x2 = bShift + std::sqrt(inner);
		if (!std::isnan(x1))
		{
			result.roots[n++] = x1;
		}

		if (!std::isnan(x2))
		{
			result.roots[n++] = x2;
		}
	}

	result.numRoots = n;
	return result;
}

double CalcResolventY(double a_, double b_, double c_)
{
	auto [P, Q, R] = CalcCoefsCubicResolvent(a_, b_, c_);
	double u = std::cbrt(R);
	double y = -5.0 / 6.0 * a_ + u;
	if (std::abs(u) > 1e-12)
		y -= P / (3.0 * u);
	else
		y -= std::cbrt(Q);
	return y;
}

Coefficients CalcCoefsCubicResolvent(double a, double b, double c)
{
	Coefficients res;
	res.p = -a * a / 12.0 - c;
	res.q = -a * a * a / 108.0 + a * c / 3.0 - b * b / 8.0;
	res.r = -res.q / 2 + std::sqrt(std::pow(res.q, 2) / 4 + std::pow(res.p, 3) / 27);
	return res;
}

EquationRoot4 ExtractRoots(double a_, double b_, double y, double bShift)
{
	EquationRoot4 result{};
	int n = 0;
	double x1, x2;

	double w_sq = a_ + 2 * y;
	if (w_sq < 0)
		return {};
	double w = std::sqrt(w_sq);

	for (int sign : { -1, 1 })
	{
		double inner = -(3 * a_ + 2 * y + sign * 2 * b_ / w);
		if (inner < 0)
			continue;
		x1 = bShift + 0.5 * (sign * w - std::sqrt(inner));
		x2 = bShift + 0.5 * (sign * w + std::sqrt(inner));
		if (!std::isnan(x1))
		{
			result.roots[n++] = x1;
		}

		if (!std::isnan(x2))
		{
			result.roots[n++] = x2;
		}
	}

	result.numRoots = n;
	return result;
}
