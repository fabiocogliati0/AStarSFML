#include <SFML\Graphics.hpp>

#include "AStar.h"
#include "NodeState.h"

const int iWindowSizeX = 600;
const int iWindowSizeY = 600;
sf::RectangleShape* rectangles;


void createBlocksNodes(const int numX, const int numY, AStar& algorithm)
{
	//Creates Blocks
	bool* blockMap = new bool[numX * numY];
	for (int i = 0; i < numX*numY; ++i)
	{
		blockMap[i] = false;
	}

	//muro a riga 1
	blockMap[0 * numY + 1] = true;
	blockMap[1 * numY + 1] = true;
	blockMap[2 * numY + 1] = true;
	blockMap[3 * numY + 1] = true;
	blockMap[4 * numY + 1] = true;
	blockMap[5 * numY + 1] = true;
	blockMap[6 * numY + 1] = true;
	blockMap[7 * numY + 1] = true;
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
}

void update(AStar& algorithm)
{
	if (!algorithm.SearchFinished())
	{
		algorithm.Update();
	}

}

void createRectangles(const int numX, const int numY)
{
	rectangles = new sf::RectangleShape[numX*numY];

	sf::Vector2f quadSize(static_cast<float>(iWindowSizeX) / numX, static_cast<float>(iWindowSizeY) / numY);

	for (int i = 0; i < numX; ++i)
	{
		for (int j = 0; j < numY; ++j)
		{
			const int pos = i*numY + j;
			sf::Vector2f position(i*quadSize.x, j*quadSize.y);
			rectangles[pos] = sf::RectangleShape(quadSize);
			rectangles[pos].setPosition(position);
			rectangles[pos].setOutlineColor(sf::Color::White);
			rectangles[pos].setOutlineThickness(1.0f);

		}
	}
}

sf::Color getNodeColor(const NodeState& state)
{
	switch (state)
	{
	case Start:
		return sf::Color::Cyan;
	case End:
		return sf::Color::Magenta;
	case Open:
		return sf::Color::Green;
	case Closed:
		return sf::Color::Blue;
	case Block:
		return sf::Color::Red;
	default:
		return sf::Color::Black;
	}
}

sf::Color getPathNodeColor(const NodeState& state)
{
	switch (state)
	{
	case Start:
		return sf::Color::Yellow;
	case End:
		return sf::Color::Yellow;
	case Path:
		return sf::Color::Yellow;
	case Block:
		return sf::Color::Red;
	default:
		return sf::Color::Black;
	}
}

void drawRectangles(const int numX, const int numY, AStar& algorithm, sf::RenderWindow& window, bool lastDraw)
{
	for (int i = 0; i < numX; ++i)
	{
		for (int j = 0; j < numY; ++j)
		{
			sf::Color fillColor;
			NodeState nodeState = algorithm.getNodeState(i, j);

			if (lastDraw)
			{
				fillColor = getPathNodeColor(nodeState);
			}
			else
			{
				fillColor = getNodeColor(nodeState);
			}

			rectangles[i*numY + j].setFillColor(fillColor);

			window.draw(rectangles[i*numY + j]);
		}
	}
}


int main()
{

	sf::RenderWindow window(sf::VideoMode(iWindowSizeX, iWindowSizeY), "AStar");
	window.setFramerateLimit(60);

	AStar algorithm;

	const int numX = algorithm.getXMax();
	const int numY = algorithm.getYMax();
	
	createBlocksNodes(numX, numY, algorithm);
	algorithm.Init();
	createRectangles(numX,numY);

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

		drawRectangles(numX, numY, algorithm, window, algorithm.SearchFinished());

		window.display();

	}

	algorithm.Clean();

	return 0;
}