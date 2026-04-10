#include "Rectangle.h"
#include <iomanip>
#include <sstream>
#include <string>

Rectangle::Rectangle(Point leftTop, double width, double height, uint32_t outlineColor, uint32_t fillColor)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double Rectangle::GetArea()
{
	return m_width * m_height;
}

double Rectangle::GetPerimeter()
{
	return 2.0 * (m_width + m_height);
}

std::string Rectangle::ToString()
{
	std::ostringstream oss;

	oss << std::fixed << std::setprecision(2)
		<< "Rectangle: (left top) pos " << m_leftTop.ToString()
		<< ", w = " << m_width << ", h = " << m_height
		<< ", s = " << GetArea() << ", p = " << GetPerimeter();

	return oss.str();
}

std::string Rectangle::GetInfo()
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

void Rectangle::Draw(ICanvas& canvas)
{
	Point topRight(m_leftTop.x + m_width, m_leftTop.y);
	Point bottomRight(m_leftTop.x + m_width, m_leftTop.y + m_height);
	Point bottomLeft(m_leftTop.x, m_leftTop.y + m_height);

	canvas.FillPolygon({ m_leftTop, topRight, bottomRight, bottomLeft }, m_fillColor);
	canvas.DrawLine(m_leftTop, topRight, m_outlineColor);
	canvas.DrawLine(topRight, bottomRight, m_outlineColor);
	canvas.DrawLine(bottomRight, bottomLeft, m_outlineColor);
	canvas.DrawLine(bottomLeft, m_leftTop, m_outlineColor);
}

uint32_t Rectangle::GetOutlineColor()
{
	return m_outlineColor;
}

uint32_t Rectangle::GetFillColor()
{
	return m_fillColor;
}

Point Rectangle::GetLeftTop()
{
	return m_leftTop;
}

Point Rectangle::GetRightBottom()
{
	return Point(m_leftTop.x + m_width, m_leftTop.y + m_height);
}

double Rectangle::GetWidth()
{
	return m_width;
}

double Rectangle::GetHeight()
{
	return m_height;
}