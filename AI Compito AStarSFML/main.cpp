#include <SFML\Graphics.hpp>

#include "AStar.h"
#include "NodeState.h"

const int iWindowSizeX = 600;
const int iWindowSizeY = 600;


void update(AStar& algorithm)
{
	if (!algorithm.SearchFinished())
	{
		algorithm.Update();
	}

}

int main()
{

	AStar algorithm;
	algorithm.Init();

	sf::RenderWindow window(sf::VideoMode(iWindowSizeX, iWindowSizeY), "AStar");
	window.setFramerateLimit(60);

	int numX = algorithm.getXMax();
	int numY = algorithm.getYMax();

	sf::RectangleShape* rectancles = new sf::RectangleShape[numX*numY];

	sf::Vector2f quadSize(static_cast<float>(iWindowSizeX) / numX, static_cast<float>(iWindowSizeY) / numY);;

	for (int i = 0; i < numX; ++i)
	{
		for (int j = 0; j < numY; ++j)
		{
			const int pos = i*numY + j;
			sf::Vector2f position(i*quadSize.x, j*quadSize.y);
			rectancles[pos] = sf::RectangleShape(quadSize);
			rectancles[pos].setPosition(position);
			rectancles[pos].setOutlineColor(sf::Color::White);
			rectancles[pos].setOutlineThickness(1.0f);

		}
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.key.code == sf::Keyboard::N)
				update(algorithm);
		}

		window.clear();

		for (int i = 0; i < numX; ++i)
		{
			for (int j = 0; j < numY; ++j)
			{
				rectancles[i*numY + j].setFillColor(algorithm.getNodeColor(i, j));
				window.draw(rectancles[i*numY + j]);
			}
		}

		window.display();

	}

	algorithm.Clean();

	return 0;
}