#include "dust.h"
#include "game.h"

#include <SFML/Graphics.hpp>

Dust::Dust(sf::Vector2f position) : position(position)
{
	size = sf::Vector2f(Game::dustSize, Game::dustSize);
	rectangle.setSize(size);
	rectangle.setPosition(position.x - (size.x / 2.0f), position.y - (size.y / 2.0f));
	rectangle.setFillColor(sf::Color::Color(rand() % 255, rand() % 255, rand() % 255, 255));
}

void Dust::update()
{
	velocity += sf::Vector2f(0.0f, Game::gravity) * Game::deltaTime;
	position += velocity * Game::deltaTime;

	int remainderX = (int)position.x % (int)Game::dustSize;
	int remainderY = (int)position.y % (int)Game::dustSize;
	sf::Vector2i snappedPosition{};
	snappedPosition.x = (float)((int)position.x + (int)Game::dustSize - remainderX);
	snappedPosition.y = (float)((int)position.y + (int)Game::dustSize - remainderY);
	rectangle.setPosition((float)snappedPosition.x - (size.x / 2.0f), (float)snappedPosition.y - (size.y / 2.0f));
}

void Dust::draw()
{
		
}