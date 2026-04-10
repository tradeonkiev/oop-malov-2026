#pragma once

#include "ICanvas.h"
#include <SFML/Graphics.hpp>

class Canvas : public ICanvas
{
public:
	Canvas(sf::RenderWindow& window)
		: m_window(window)
	{
	}

	void DrawLine(Point from, Point to, uint32_t lineColor) override
	{
		sf::Color color = ToSfColor(lineColor);
		std::array vertices = {
			sf::Vertex{ { static_cast<float>(from.x), static_cast<float>(from.y) }, color },
			sf::Vertex{ { static_cast<float>(to.x), static_cast<float>(to.y) }, color }
		};
		m_window.draw(vertices.data(), vertices.size(), sf::PrimitiveType::Lines);
	}

	void FillPolygon(std::vector<Point> points, uint32_t fillColor) override
	{
		sf::ConvexShape polygon(points.size());
		for (int i = 0; i < points.size(); ++i)
		{
			polygon.setPoint(i, { static_cast<float>(points[i].x), static_cast<float>(points[i].y) });
		}
		polygon.setFillColor(ToSfColor(fillColor));
		m_window.draw(polygon);
	}

	void DrawCircle(Point center, double radius, uint32_t lineColor) override
	{
		sf::CircleShape circle(static_cast<float>(radius));
		circle.setPosition({ static_cast<float>(center.x - radius), static_cast<float>(center.y - radius) });
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineColor(ToSfColor(lineColor));
		circle.setOutlineThickness(5);
		m_window.draw(circle);
	}

	void FillCircle(Point center, double radius, uint32_t fillColor) override
	{
		sf::CircleShape circle(static_cast<float>(radius));
		circle.setPosition({ static_cast<float>(center.x - radius), static_cast<float>(center.y - radius) });
		circle.setFillColor(ToSfColor(fillColor));
		m_window.draw(circle);
	}

private:
	sf::RenderWindow& m_window;

	static sf::Color ToSfColor(uint32_t color)
	{
		uint8_t r = (color >> 16) & 0xFF;
		uint8_t g = (color >> 8) & 0xFF;
		uint8_t b = color & 0xFF;
		return sf::Color(r, g, b);
	}
};