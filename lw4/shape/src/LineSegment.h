#pragma once

#include "IShape.h"
#include "Point.h"
#include <cstdint>
#include <string>

class LineSegment : public IShape
{
public:
	LineSegment(Point start, Point end, uint32_t outlineColor);
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	uint32_t GetOutlineColor() override;
	std::string GetInfo() override;

	void Draw(ICanvas& canvas) override;

	Point GetStartPoint();
	Point GetEndPoint();

private:
	Point m_start;
	Point m_end;

	uint32_t m_outlineColor;
};
