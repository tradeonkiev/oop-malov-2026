#include "Triangle.h"
#include <cmath>
#include <iomanip>
#include <sstream>

Triangle::Triangle(Point v1, Point v2, Point v3, uint32_t outlineColor, uint32_t fillColor)
	: m_vertex1(v1)
	, m_vertex2(v2)
	, m_vertex3(v3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double Triangle::SideLength(const Point& a, const Point& b)
{
	double dx = b.x - a.x;
	double dy = b.y - a.y;
	return std::sqrt(dx * dx + dy * dy);
}

double Triangle::GetArea()
{
	double dx1 = m_vertex2.x - m_vertex1.x;
	double dy1 = m_vertex2.y - m_vertex1.y;
	double dx2 = m_vertex3.x - m_vertex1.x;
	double dy2 = m_vertex3.y - m_vertex1.y;

	return std::abs(dx1 * dy2 - dx2 * dy1) * 0.5;
}

double Triangle::GetPerimeter()
{
	return SideLength(m_vertex1, m_vertex2) + SideLength(m_vertex2, m_vertex3) + SideLength(m_vertex3, m_vertex1);
}

std::string Triangle::ToString()
{
	std::ostringstream oss;
	oss << "triangle: points " << m_vertex1.ToString() << ", "
		<< m_vertex2.ToString() << ", " << m_vertex3.ToString()
		<< ", s = " << std::fixed << std::setprecision(2) << GetArea()
		<< ", p = " << GetPerimeter();
	return oss.str();
}

std::string Triangle::GetInfo()
{
	std::ostringstream oss;
	oss << ToString() << std::endl;
	oss << std::fixed << std::setprecision(2);
	oss << "  s: " << GetArea() << std::endl;
	oss << "  p: " << GetPerimeter() << std::endl;
	oss << "  Outline: #" << std::hex << std::setfill('0') << std::setw(6) << GetOutlineColor() << std::endl;
	oss << "  Fill: #" << std::hex << std::setfill('0') << std::setw(6) << GetFillColor() << std::endl;

	return oss.str();
}

void Triangle::Draw(ICanvas& canvas)
{
	canvas.FillPolygon({ m_vertex1, m_vertex2, m_vertex3 }, m_fillColor);
	canvas.DrawLine(m_vertex1, m_vertex2, m_outlineColor);
	canvas.DrawLine(m_vertex2, m_vertex3, m_outlineColor);
	canvas.DrawLine(m_vertex3, m_vertex1, m_outlineColor);
}

uint32_t Triangle::GetOutlineColor()
{
	return m_outlineColor;
}

uint32_t Triangle::GetFillColor()
{
	return m_fillColor;
}

Point Triangle::GetVertex1()
{
	return m_vertex1;
}

Point Triangle::GetVertex2()
{
	return m_vertex2;
}

Point Triangle::GetVertex3()
{
	return m_vertex3;
}