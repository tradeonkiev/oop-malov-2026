#pragma once

#include "ISolidShape.h"
#include "Point.h"
#include <string>

class Circle : public ISolidShape
{
public:
	Circle(Point center, double radius, uint32_t outlineColor, uint32_t fillColor);

	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	uint32_t GetOutlineColor() override;
	uint32_t GetFillColor() override;
	std::string GetInfo() override;

	void Draw(ICanvas& canvas) override;

	Point GetCenter();
	double GetRadius();

private:
	Point m_center;
	double m_radius;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};