#pragma once

#include <SFML/Graphics.hpp>

class Cell
{
private:
	int Size;
	sf::Color Color;
	sf::RectangleShape Shape;

	sf::Color EmptyColor;
	sf::RectangleShape EmptyShape;
};