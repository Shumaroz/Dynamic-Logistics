#pragma once

/*#ifndef MAPGRID_H
#define MAPGRID_H*/
#include <SFML/Graphics.hpp>
#include "framework.h"
#include <vector>
#include "Cell.h"
#include "CellTypes.h"

class MapGrid
{
private:
	const int pass = 0, marker = 1;
	const int height = 200, width = 200;
	sf::RenderWindow& _window;
	std::vector<std::vector<Cell*>> map;
	sf::RectangleShape markerShape;
	sf::RenderTexture markerTexture;

	std::vector <sf::CircleShape*> jointShapes;
	//std::vector<sf::RectangleShape*> markerShapeVec;

	int _windowSize, coef_x, coef_y;

public:
	MapGrid(sf::RenderWindow& window);
	~MapGrid();
	void update(float dt);
	void render();
	void updateTexture(CellType type, sf::Vector2i pos);
	void renderMarker();
	void renderJoints();

	void addMarker(sf::Vector2f pos, CellType phase, float relevance);
	bool isDestination(sf::Vector2f pos, CellType phase);
	int dirByMarkers(sf::Vector2f pos, CellType phase);

	void addJoints(CellType t, sf::Vector2f pos);
};