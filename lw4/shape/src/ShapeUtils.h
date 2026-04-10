#pragma once
#include "IShape.h"
#include "ISolidShape.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

uint32_t ParseColor(const std::string& colorStr);
std::string ColorToString(uint32_t color);

std::unique_ptr<IShape> ParseShape(const std::string& line);
std::vector<std::unique_ptr<IShape>> ReadShapes(std::istream& input);

IShape* FindMaxAreaShape(std::vector<std::unique_ptr<IShape>>& shapes);
IShape* FindMinPerimeterShape(std::vector<std::unique_ptr<IShape>>& shapes);

void PrintShapeInfo(std::ostream& output, IShape* shape);