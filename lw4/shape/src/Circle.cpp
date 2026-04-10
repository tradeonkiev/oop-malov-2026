#include "Circle.h"
#include <cmath>
#include <iomanip>
#include <sstream>

Circle::Circle(Point center, double radius, uint32_t outlineColor, uint32_t fillColor)
	: m_center(center)
	, m_radius(fabs(radius))
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double Circle::GetArea()
{
	return M_PI * m_radius * m_radius;
}

double Circle::GetPerimeter()
{
	return 2.0 * M_PI * m_radius;
}

std::string Circle::ToString()
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2)
		<< "Circle: pos " << m_center.ToString()
		<< ", r = " << m_radius
		<< ", s = " << GetArea()
		<< ", p = " << GetPerimeter();
	return oss.str();
}

std::string Circle::GetInfo()
{
	std::ostringstream oss;

	oss << ToString() << std::endl
		<< std::fixed << std::setprecision(2)
		<< "  s: " << GetArea() << std::endl
		<< "  p: " << GetPerimeter() << std::endl
		<< "  Outline: #" << std::hex << std::setfill('0') << std::setw(6) << GetOutlineColor() << std::endl
		<< "  Fill: #" << std::hex << std::setfill('0') << std::setw(6) << GetFillColor() << std::endl;

	return oss.str();
}

void Circle::Draw(ICanvas& canvas)
{
	canvas.FillCircle(m_center, m_radius, m_fillColor);
	canvas.DrawCircle(m_center, m_radius, m_outlineColor);
}

uint32_t Circle::GetOutlineColor()
{
	return m_outlineColor;
}

uint32_t Circle::GetFillColor()
{
	return m_fillColor;
}

Point Circle::GetCenter()
{
	return m_center;
}

double Circle::GetRadius()
{
	return m_radius;
}