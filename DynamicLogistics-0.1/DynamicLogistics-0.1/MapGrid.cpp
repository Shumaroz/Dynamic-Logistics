#include "MapGrid.h"
#include <iostream>

MapGrid::MapGrid(sf::RenderWindow& window) : _window(window)
{
	_windowSize = _window.getSize().x;
	coef_x = _windowSize / width;
	coef_y = _windowSize / height;

	map.resize(height);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			//map[i].push_back(new Cell*[2]{ new Cell(Pass, sf::Vector2i(i * coef_x, j * coef_y)), new Cell(Pass, sf::Vector2i(i * coef_x, j * coef_y)) });
			map[i].push_back(new Cell(sf::Vector2i(i * coef_x, j * coef_y)));
		}
	markerShape.setSize(sf::Vector2f((float)coef_x, (float)coef_y));

	if (!markerTexture.create(_windowSize, _windowSize))
		std::cout << "BAD";

	markerTexture.display();

	//addJoints(Hub, sf::Vector2f{ (float)_windowSize / 2.f, (float)_windowSize / 2.f });
	addJoints(Hub, startPos);

	addJoints(Node, sf::Vector2f{ 650.f, 550.f });

	/*markerShape.setFillColor(sf::Color(255, 0, 0));
	markerShape.setPosition(322, 322);
	markerTexture.draw(markerShape, sf::BlendNone);*/
}

MapGrid::~MapGrid()
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			delete map[i][j];
		}
}

sf::Vector2f MapGrid::getStartPos() { return startPos; }

void MapGrid::update(float dt)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			//map[i][j]->decreaseIntensity(dt);
			if (!map[i][j]->decreaseIntensity(dt))
				updateTexture(Pass, map[i][j]->getPos());
		}
	//map[80][80]->debugParams();
}

void MapGrid::render()
{
	renderMarker();

	//for (int i = 0; i < jointShapes.size(); i++)
		//_window.draw(*jointShapes[i]);
}

void MapGrid::updateTexture(CellType type, sf::Vector2i pos)
{
	if (type == Pass)
		markerShape.setFillColor(sf::Color(229, 222, 207));
	if (type == ToHub)
		markerShape.setFillColor(sf::Color(100, 100, 100, 10));
	if (type == Hub)
		markerShape.setFillColor(sf::Color(255, 0, 0));
	if (type == Node)
		markerShape.setFillColor(sf::Color(0, 255, 0));
	markerShape.setPosition((float)pos.x + 2.f, (float)pos.y + 2.f);
	markerTexture.draw(markerShape, sf::BlendAlpha);
}

void MapGrid::renderMarker()
{
	markerTexture.display();
	_window.draw(sf::Sprite(markerTexture.getTexture()));
}

void MapGrid::addMarker(sf::Vector2f pos, CellType phase, float relevance)
{
	int x = (int)pos.x / coef_x;
	int y = (int)pos.y / coef_y;
	// Здесь все наоборот, потому что фаза агента - двигаться к узлу, а маркеры он оставляет, ведущие к хабу
	if (phase == ToNode)
		map[x][y]->changeCell(ToHub, relevance);
	else
		map[x][y]->changeCell(ToNode, relevance);

	updateTexture(map[x][y]->getType(), map[x][y]->getPos());
}

bool MapGrid::isDestination(sf::Vector2f pos, CellType phase)
{
	int x = (int)pos.x / coef_x;
	int y = (int)pos.y / coef_y;
	if ((phase == ToNode && map[x][y]->getType() == Node) || (phase == ToHub && map[x][y]->getType() == Hub))
		return true;
	else
		return false;
}

int MapGrid::dirByMarkers(sf::Vector2f pos, CellType phase)
{
	int x = (int)pos.x / coef_x;
	int y = (int)pos.y / coef_y;
	float maxIntensity = 0.f;
	int intenseDir = -1;
	int k = 0, kx = 0, ky = 0;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			/*if (phase == ToHub)
				std::cout << map[x + j][y + i]->getIntensity(phase) << " ";*/
			if (map[x + j][y + i]->getIntensity(phase) > maxIntensity && map[x + j][y + i]->getIntensity(phase) != 0.f)
			{
				maxIntensity = map[x + j][y + i]->getIntensity(phase);
				kx = x + j;
				ky = y + i;
				if (k < 4)
					intenseDir = -45 * i + 45 * j - 135;
				else if (k > 4)
					intenseDir = 45 * i - 45 * j + 45;
			}
			k++;
		}
		/*if (phase == ToHub)
			std::cout << '\n';*/
	}
	/*if (phase == ToHub)
		std::cout << '\n';*/
	/*markerShape.setFillColor(sf::Color(0, 0, 255));
	markerShape.setPosition(kx * coef_x + 2, ky * coef_y + 2);
	markerTexture.draw(markerShape, sf::BlendNone);*/
	//if ((intenseDir == -135 || intenseDir == -90) && phase == ToHub)
	//	std::cout << map[kx][ky]->getIntensity(phase) << " " << map[kx + 1][ky - 2]->getIntensity(phase) << '\n';
	return intenseDir;
}

void MapGrid::addJoints(CellType t, sf::Vector2f pos)
{
	int x = (int)pos.x / coef_x;
	int y = (int)pos.y / coef_y;
	for (int i = -2; i <= 2; i++)
		for (int j = -2; j <= 2; j++)
		{
			map[x + j][y + i]->changeCell(t, 0);
			updateTexture(t, map[x + j][y + i]->getPos());
		}

	jointShapes.push_back(new sf::CircleShape);

	jointShapes[jointShapes.size() - 1]->setRadius(10.f);
	jointShapes[jointShapes.size() - 1]->setFillColor(sf::Color(51, 51, 51));
	jointShapes[jointShapes.size() - 1]->setPosition(x * coef_x + 10.f, y * coef_y + 10.f);
}