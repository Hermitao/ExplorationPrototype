#include "game.h"

Game::Game(sf::RenderWindow& window) : window(window)
{
	screenWidth = sf::VideoMode::getDesktopMode().width;
	screenHeight = sf::VideoMode::getDesktopMode().height;

	if (!font.loadFromFile("res/fonts/pixelated/pixelated.ttf"))
	{
		std::cout << "ERROR::Failed to load font (class)" << "\n";
	}
	text.setFont(font);

	float radius = 4.0f;
	float cosOf30 = 0.8660254f;
	float sinOf30 = 0.5f;
	float edgeDistance = cosOf30 * radius;
	float edgeHalfLength = sinOf30 * radius;

	oceanColors[0] = sf::Color(202, 221, 236, 255);
	oceanColors[1] = sf::Color(175, 203, 226, 255);
	oceanColors[2] = sf::Color(146, 184, 216, 255);
	oceanColors[3] = sf::Color(105, 159, 201, 255);
	oceanColors[4] = sf::Color(86, 146, 194, 255);
	oceanColors[5] = sf::Color(66, 132, 185, 255);
	oceanColors[6] = sf::Color(55, 111, 155, 255);

	grassColors[0] = sf::Color(125, 227, 158, 255);
	grassColors[1] = sf::Color(100, 221, 139, 255);
	grassColors[2] = sf::Color(56, 211, 106, 255);

	sandColors[0] = sf::Color(240, 225, 191);
	sandColors[1] = sf::Color(233, 211, 160);
	sandColors[2] = sf::Color(223, 190, 115);

	hillColors[0] = sf::Color(185, 192, 200);
	hillColors[1] = sf::Color(170, 179, 187);
	hillColors[2] = sf::Color(142, 153, 164);

	noise.SetFractalType(FastNoiseLite::FractalType_FBm);
	noise.SetFrequency(0.015f);
	noise.SetFractalOctaves(5);
	noise.SetFractalLacunarity(2.0f);
	noise.SetFractalGain(0.5f);
	noise.SetSeed(10);

    for (int y{ -1 }; y < screenHeight / (edgeHalfLength * 3.0f); ++y)
    {
    	for (int x{ -1 }; x < screenWidth / (edgeDistance * 2.0f); ++x)
    	{
			float heightf = noise.GetNoise((float)x, (float)y) * 128.0f;
			int height = floor(heightf);

			sf::Color tileColor;
			if (height < -110)
			{
				tileColor = oceanColors[6];
			}
			else if (height < -70)
			{
				tileColor = oceanColors[5];
			}
			else if (height < 0)
			{
				tileColor = oceanColors[4];
			}
			else if (height < 36)
			{
				tileColor = oceanColors[3];
			}
			else if (height < 39)
			{
				tileColor = oceanColors[2];
			}
			else if (height < 42)
			{
				tileColor = oceanColors[1];
			}
		    // else if (height < 35)
		    // {
		    // 	tileColor = oceanColors[0];
		    // }
			else if (height < 50)
			{
			   tileColor = sandColors[0];
			}
			else if (height < 55)
			{
			   tileColor = sandColors[1];
			}
			else if (height < 60)
			{
			   tileColor = sandColors[2];
			}
			else if (height < 80)
			{
			   tileColor = grassColors[0];
			}
			else if (height < 95)
			{
			   tileColor = grassColors[1];
			}
			else if (height < 100)
			{
			   tileColor = grassColors[2];
			}
			else if (height < 113)
			{
			   tileColor = hillColors[0];
			}
			else if (height < 115)
			{
			   tileColor = hillColors[1];
			}
			else if (height < 128)
			{
			   tileColor = hillColors[2];
			}
			else
			{
				tileColor = oceanColors[0];
			}


    		sf::CircleShape hexagon(radius, 6);
    		hexagon.setOutlineThickness(-0.5f);
    		hexagon.setFillColor(tileColor);
			hexagon.setOutlineColor(sf::Color(105, 135, 201));
			sf::Vector2f hexagonPos = sf::Vector2f((x + (y % 2) * 0.5f) * edgeDistance * 2.0f, y * (radius + edgeHalfLength));
    		hexagon.setPosition(hexagonPos);
    		hexagons.push_back(hexagon);

		    // sf::Text heightText;
		    // heightText.setFont(font);
		    // heightText.setCharacterSize(12);
		    // heightText.setFillColor(sf::Color::Color(255, 255, 255, 255));
		    // std::ostringstream heightTextInt;
		    // heightTextInt << (height);
		    // std::string heightTextString(heightTextInt.str());
		    // heightText.setString(heightTextString);
		    // heightText.setPosition(sf::Vector2f(hexagonPos.x, hexagonPos.y));
		    // heightTexts.push_back(heightText);
    	}
    }
}

void Game::clear()
{
	window.clear(sf::Color::Black);
}

void Game::update()
{
	time = bootTime.getElapsedTime().asSeconds() * 4.0f;

	// temporary
	std::string topText = "Exploration Engine - Indev\nAldebaran Project\n";
	std::ostringstream fpsTextFloat;
	fpsTextFloat << (1.0f / deltaTime);
	std::string fpsTextString(fpsTextFloat.str());
	std::string finalText = topText + fpsTextString;
	text.setString(finalText);
	text.setCharacterSize(26);
	text.setFillColor(sf::Color::Color(255, 255, 255, 255));
	text.setOutlineColor(sf::Color(4, 5, 5, 255));
	text.setOutlineThickness(2.0f);
	// ----------

	deltaTime = deltaClock.restart().asSeconds() * timeScale;
}

void Game::draw()
{
	std::list<sf::CircleShape>::iterator it;
    for (it = hexagons.begin(); it != hexagons.end(); ++it)
    {
    	window.draw(*it);
    }
	std::list<sf::Text>::iterator it2;
    for (it2 = heightTexts.begin(); it2 != heightTexts.end(); ++it2)
    {
    	window.draw(*it2);
    }

    window.draw(text);
    window.display();
}

