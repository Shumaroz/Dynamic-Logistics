#include <SFML/Graphics.hpp>
#include "Agent.h"

#include <iostream>

#define PI 3.14159265

sf::Vector2f normalize(const sf::Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}

Agent::Agent(sf::RenderWindow& window) : _window(window)
{
	_windowSize = _window.getSize().x;
	this->agentShape.setRadius(2.f);
	this->position.x = _windowSize / 2 - agentShape.getRadius();
	this->position.y = _windowSize / 2 - agentShape.getRadius();
	this->agentShape.setFillColor(sf::Color(51, 51, 51));
	this->agentShape.setPosition(position);

	phase = ToNode;
}

Agent::~Agent() 
{
	delete this;
}

void Agent::update(float dt, MapGrid& mapGrid)
{
	//if (cooldown > 0.f)
	//	cooldown -= dt;
	//else
	//{
		int markersDirection = mapGrid.dirByMarkers(position, phase);
		if (markersDirection != -1 && (rand() % 100) < 90)
		{
			//cooldown = 0.5f;
			desiredDirection.x += (float)cos(markersDirection * PI / 180);
			desiredDirection.y += (float)sin(markersDirection * PI / 180);
			//std::cout << markersDirection.x << " " << markersDirection.y << '\n';
		}
		else
		{
			desiredDirection.x += (float)cos(rand() % 360 * PI / 180) * wanderStrength;
			desiredDirection.y += (float)sin(rand() % 360 * PI / 180) * wanderStrength;
		}
		desiredDirection = normalize(desiredDirection);
	//}
	if (wallHitDir() != sf::Vector2f(0, 0))
		desiredDirection = wallHitDir();
	sf::Vector2f desiredVelocity = moveSpeed * desiredDirection;
	sf::Vector2f desiredSteeringForce = (desiredVelocity - velocity) * steerStrength;

	velocity += desiredSteeringForce * dt;

	position += dt * velocity;
	agentShape.setPosition(position);

	if (mapGrid.isDestination(position, phase))
	{
		relevanceTime = 30.f;
		velocity = -velocity;
		if (phase == ToNode)
		{
			phase = ToHub;
			this->agentShape.setFillColor(sf::Color(255, 0, 255));
		}
		else
		{
			phase = ToNode;
			this->agentShape.setFillColor(sf::Color(255, 0, 0));
		}
	}

	mapGrid.addMarker(position, phase, relevanceTime);
	if (relevanceTime > 0)
		relevanceTime -= 2*dt;
	else
		relevanceTime = 0;
}

void Agent::render()
{
	_window.draw(agentShape);
}

sf::Vector2f Agent::wallHitDir()
{
	sf::Vector2f fromWallDirection(0,0);


	if (position.y <= 30)
		fromWallDirection.y = 1;
	if (position.x >= _windowSize - 40)
		fromWallDirection.x = -1;
	if (position.y >= _windowSize - 40)
		fromWallDirection.y = -1;
	if (position.x <= 30)
		fromWallDirection.x = 1;
	
	return fromWallDirection;
}

sf::Vector2f Agent::getPos()
{
	return position;
}