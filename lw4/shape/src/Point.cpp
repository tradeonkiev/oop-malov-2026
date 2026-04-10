#include "Point.h"
#include <iomanip>
#include <sstream>

Point::Point()
	: x(0)
	, y(0)
{
}

Point::Point(double x, double y)
	: x(x)
	, y(y)
{
}

std::string Point::ToString() const
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << "(" << x << ", " << y << ")";
	return oss.str();
}