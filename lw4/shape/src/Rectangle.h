#pragma once

#include "ISolidShape.h"
#include "Point.h"
#include <string>

class Rectangle : public ISolidShape
{
public:
	Rectangle(Point leftTop, double width, double height, uint32_t outlineColor, uint32_t fillColor);

	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	uint32_t GetOutlineColor() override;
	uint32_t GetFillColor() override;
	std::string GetInfo() override;

	void Draw(ICanvas& canvas) override;

	Point GetLeftTop();
	Point GetRightBottom();
	double GetWidth();
	double GetHeight();

private:
	Point m_leftTop;
	double m_width;
	double m_height;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};