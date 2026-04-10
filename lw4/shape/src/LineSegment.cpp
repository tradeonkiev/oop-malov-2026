#include "LineSegment.h"
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

LineSegment::LineSegment(Point start, Point end, uint32_t outlineColor)
{
	m_start = start;
	m_end = end;
	m_outlineColor = outlineColor;
}

double LineSegment::GetArea()
{
	return 0.0;
}

double LineSegment::GetPerimeter()
{
	double dx = m_start.x - m_end.x;
	double dy = m_start.y - m_end.y;
	return std::sqrt(dx * dx + dy * dy);
}

std::string LineSegment::ToString()
{
	std::ostringstream oss;
	oss << "Line Segment: " << m_start.ToString() << " - " << m_end.ToString()
		<< ", l = " << std::fixed << std::setprecision(2) << GetPerimeter();
	return oss.str();
}

std::string LineSegment::GetInfo()
{
	std::ostringstream oss;
	oss << ToString() << std::endl
		<< std::fixed << std::setprecision(2)
		<< "  s: " << GetArea() << std::endl
		<< "  p: " << GetPerimeter() << std::endl
		<< "  Outline: #" << std::hex << std::setfill('0') << std::setw(6) << GetOutlineColor() << std::endl;
	return oss.str();
}

void LineSegment::Draw(ICanvas& canvas)
{
	canvas.DrawLine(m_start, m_end, m_outlineColor);
}

uint32_t LineSegment::GetOutlineColor()
{
	return m_outlineColor;
}

Point LineSegment::GetStartPoint()
{
	return m_start;
}

Point LineSegment::GetEndPoint()
{
	return m_end;
}