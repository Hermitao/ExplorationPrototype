#pragma once
#include "FastNoiseLite.h"
#include "dust.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <list>


class Game
{
public:
	static float gravity;
	static float timeScale;
	static float dustSize;
	int screenWidth;
	int screenHeight;

	sf::Clock bootTime{};
	sf::Clock deltaClock{};
	static float time;
	static float deltaTime;

	sf::RenderWindow& window;
	sf::Font font;
	sf::Text text;

	FastNoiseLite noise;
	std::list<sf::CircleShape> hexagons = {};
	std::list<sf::Text> heightTexts = {};
	sf::Color oceanColors[7]    = {};
	sf::Color grassColors[7]	= {};
	sf::Color sandColors[3]		= {};
	sf::Color hillColors[3]		= {};

	Game(sf::RenderWindow& window);
	void clear();
	void events();
	void update();
	void draw();
	void generateMap();
};