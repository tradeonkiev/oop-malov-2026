#include "Canvas.h"
#include "ShapeUtils.h"
#include <iostream>

int main()
{
	auto shapes = ReadShapes(std::cin);

	if (shapes.empty())
	{
		std::cout << "No shapes were entered." << std::endl;
		return 0;
	}

	IShape* maxArea = FindMaxAreaShape(shapes);
	IShape* minPerimeter = FindMinPerimeterShape(shapes);

	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Shape");
	window.clear(sf::Color::White);

	Canvas canvas(window);
	for (const auto& shape : shapes)
	{
		shape->Draw(canvas);
	}

	window.display();

	while (window.isOpen())
	{
		if (auto event = window.pollEvent(); event && event->is<sf::Event::Closed>())
		{
			window.close();
		}
	}

	std::cout << "Shape with the largest area:" << std::endl;
	PrintShapeInfo(std::cout, maxArea);
	std::cout << std::endl;
	std::cout << "Shape with the smallest perimeter:" << std::endl;
	PrintShapeInfo(std::cout, minPerimeter);

	return 0;
}