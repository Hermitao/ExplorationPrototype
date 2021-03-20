#pragma once
#include <SFML/Graphics.hpp>

class Dust
{
public:
	sf::Vector2f size{};
	sf::Vector2f position{};
	sf::Vector2f velocity{};

	sf::RectangleShape rectangle;

	Dust(sf::Vector2f position = {0.0f, 0.0f});
	void update();
	void draw();
};

