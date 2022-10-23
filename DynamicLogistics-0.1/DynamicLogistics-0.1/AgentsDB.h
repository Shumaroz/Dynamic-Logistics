#pragma once

#include <SFML/Graphics.hpp>
#include "framework.h"
#include <vector>
#include "Agent.h"
#include "MapGrid.h"

class AgentsDB 
{
private:
	std::vector<Agent*> agentsVec;
	sf::RenderWindow& _window;
	MapGrid* mapGrid;

public:
	AgentsDB(sf::RenderWindow& window);
	~AgentsDB();
	void createAgents(int count);
	void deleteAgents();
	void update(float dt);
	void render();
};