#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"

float Game::dustSize{ 10.0f };
float Game::gravity{ 20.0f };
float Game::time{0.0f};
float Game::timeScale{ 3.0f };
float Game::deltaTime{0.0f};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), L"(╯ ͠° ͟ʖ ͡°)╯●.* Exploration Engine - Indev", sf::Style::Fullscreen);
    Game game(window);

	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            game.events();
        }

        game.clear();
        game.update();
        game.draw();
    }

    return 0;
}