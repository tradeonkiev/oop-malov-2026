#pragma once

#include <string>

class Point
{
public:
    double x;
    double y;
 
    Point();
    Point(double x, double y);
 
    std::string ToString() const;
};