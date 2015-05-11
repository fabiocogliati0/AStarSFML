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

	sf::RenderWindow window(sf::VideoMode(iWindowSizeX, iWindowSizeY), "AStar");
	window.setFramerateLimit(60);

	int numX = algorithm.getXMax();
	int numY = algorithm.getYMax();

	//Creates Blocks
	bool* blockMap = new bool[numX * numY];
	for (int i = 0; i < numX*numY; ++i)
	{
		blockMap[i] = false;
	}

	//muro a riga 1
	blockMap[0 * numY + 1] = true;
	blockMap[2 * numY + 1] = true;
	blockMap[3 * numY + 1] = true;
	blockMap[4 * numY + 1] = true;
	blockMap[5 * numY + 1] = true;
	blockMap[6 * numY + 1] = true;
	blockMap[7 * numY + 1] = true;
	blockMap[8 * numY + 1] = true;
	blockMap[9 * numY + 1] = true;

	//muro a riga 3
	blockMap[1 * numY + 3] = true;
	blockMap[2 * numY + 3] = true;
	blockMap[3 * numY + 3] = true;
	blockMap[4 * numY + 3] = true;
	blockMap[5 * numY + 3] = true;
	blockMap[6 * numY + 3] = true;
	blockMap[7 * numY + 3] = true;
	blockMap[8 * numY + 3] = true;
	blockMap[9 * numY + 3] = true;

	//muro a colonna 1
	blockMap[1 * numY + 4] = true;
	blockMap[1 * numY + 5] = true;
	blockMap[1 * numY + 6] = true;

	//muro a colonna 5
	blockMap[5 * numY + 9] = true;
	blockMap[5 * numY + 8] = true;
	blockMap[5 * numY + 7] = true;
	blockMap[5 * numY + 6] = true;

	//blocco quadrato
	blockMap[6 * numY + 7] = true;
	blockMap[6 * numY + 6] = true;
	blockMap[7 * numY + 7] = true;
	blockMap[7 * numY + 6] = true;

	algorithm.SetBlockMap(blockMap);

	//init
	algorithm.Init();

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