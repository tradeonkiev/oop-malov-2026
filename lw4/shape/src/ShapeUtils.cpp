#include "ShapeUtils.h"
#include "Circle.h"
#include "LineSegment.h"
#include "Rectangle.h"
#include "Triangle.h"
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <stdexcept>

using Color = uint32_t;

Color ParseColor(const std::string& colorStr)
{
	Color color;
	std::istringstream iss(colorStr);
	iss >> std::hex >> color;
	return color;
}

std::string ColorToString(Color color)
{
	std::ostringstream oss;
	oss << std::hex << std::setfill('0') << std::setw(6) << color;
	return oss.str();
}

std::unique_ptr<IShape> ParseShape(const std::string& line)
{
	std::istringstream iss(line);
	std::string type;
	iss >> type;
	if (type == "line")
	{
		double x1, y1, x2, y2;
		std::string colorStr;
		if (!(iss >> x1 >> y1 >> x2 >> y2 >> colorStr))
			return nullptr;
		return std::make_unique<LineSegment>(Point(x1, y1), Point(x2, y2), ParseColor(colorStr));
	}
	else if (type == "triangle")
	{
		double x1, y1, x2, y2, x3, y3;
		std::string outlineStr, fillStr;
		if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> outlineStr >> fillStr))
			return nullptr;
		return std::make_unique<Triangle>(Point(x1, y1), Point(x2, y2), Point(x3, y3), ParseColor(outlineStr), ParseColor(fillStr));
	}
	else if (type == "rectangle")
	{
		double x, y, w, h;
		std::string outlineStr, fillStr;
		if (!(iss >> x >> y >> w >> h >> outlineStr >> fillStr))
			return nullptr;
		return std::make_unique<Rectangle>(Point(x, y), w, h, ParseColor(outlineStr), ParseColor(fillStr));
	}
	else if (type == "circle")
	{
		double cx, cy, r;
		std::string outlineStr, fillStr;
		if (!(iss >> cx >> cy >> r >> outlineStr >> fillStr))
			return nullptr;
		return std::make_unique<Circle>(Point(cx, cy), r, ParseColor(outlineStr), ParseColor(fillStr));
	}

	return nullptr;
}

std::vector<std::unique_ptr<IShape>> ReadShapes(std::istream& input)
{
	std::vector<std::unique_ptr<IShape>> shapes;
	std::string line;
	while (std::getline(input, line))
	{
		if (line.empty())
			break;

		auto shape = ParseShape(line);
		if (shape)
			shapes.push_back(std::move(shape));
	}
	return shapes;
}

IShape* FindMaxAreaShape(std::vector<std::unique_ptr<IShape>>& shapes)
{
	if (shapes.empty())
		return nullptr;
	auto it = std::max_element(shapes.begin(), shapes.end(),
		[](const auto& a, const auto& b) {
			return a->GetArea() < b->GetArea();
		});
	return it->get();
}

IShape* FindMinPerimeterShape(std::vector<std::unique_ptr<IShape>>& shapes)
{
	if (shapes.empty())
		return nullptr;
	auto it = std::min_element(shapes.begin(), shapes.end(),
		[](const auto& a, const auto& b) {
			return a->GetPerimeter() < b->GetPerimeter();
		});
	return it->get();
}

// TODO: вынеси в класс + виртуальный
void PrintShapeInfo(std::ostream& output, IShape* shape)
{
	if (!shape)
	{
		output << "No shape" << std::endl;
		return;
	}

	output << shape->GetInfo() << std::endl;
}
