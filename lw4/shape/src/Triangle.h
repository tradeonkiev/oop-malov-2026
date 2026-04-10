#pragma once
#include "ISolidShape.h"
#include "Point.h"
#include <string>

class Triangle : public ISolidShape
{
public:
	Triangle(Point v1, Point v2, Point v3, uint32_t outlineColor, uint32_t fillColor);

	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	uint32_t GetOutlineColor() override;
	uint32_t GetFillColor() override;
	std::string GetInfo() override;

	void Draw(ICanvas& canvas) override;

	Point GetVertex1();
	Point GetVertex2();
	Point GetVertex3();

private:
	Point m_vertex1, m_vertex2, m_vertex3;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;

	static double SideLength(const Point& a, const Point& b);
};