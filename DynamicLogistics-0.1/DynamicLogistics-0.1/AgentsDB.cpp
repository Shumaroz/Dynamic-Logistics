#include "AgentsDB.h"

AgentsDB::AgentsDB(sf::RenderWindow& window) : _window(window)
{
	mapGrid = new MapGrid(window);
}

AgentsDB::~AgentsDB()
{
	delete mapGrid;
}

void AgentsDB::createAgents(int count)
{
	for (int i = 0; i < count; i++)
	{
		agentsVec.push_back(new Agent(_window));
	}
}

void AgentsDB::deleteAgents()
{
	for (int i = 0; i < agentsVec.size(); i++)
		delete agentsVec[i];
	agentsVec.clear();
}

void AgentsDB::update(float dt)
{
	mapGrid->update(dt);
	for (int i = 0; i < agentsVec.size(); i++)
	{
		agentsVec[i]->update(dt, *mapGrid);
	}
}

void AgentsDB::render()
{
	mapGrid->render();
	for (int i = 0; i < agentsVec.size(); i++)
		agentsVec[i]->render();
}