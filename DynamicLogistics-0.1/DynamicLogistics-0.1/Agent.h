#pragma once

/*#ifndef AGENT_H
#define AGENT_H*/
#include <SFML/Graphics.hpp>
#include "framework.h"
#include "CellTypes.h"
#include "MapGrid.h"

class Agent
{
private:
	sf::RenderWindow& _window;
	sf::CircleShape agentShape;
	sf::Vector2f desiredDirection;
	sf::Vector2f velocity;
	sf::Vector2f position;

	CellType phase;
	float relevanceTime = 50.f;

	int _windowSize;
	float wanderStrength = 0.15f;
	float steerStrength = 1.f;
	float moveSpeed = 70.f;
	//float cooldown = 0.f;

public:
	Agent(sf::RenderWindow& window);
	~Agent();
	void update(float dt, MapGrid& mapGrid);
	void checkMarkers();
	void render();
	sf::Vector2f wallHitDir();
	sf::Vector2f getPos();
};