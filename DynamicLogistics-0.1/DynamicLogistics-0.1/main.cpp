#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <time.h>
#include "AgentsDB.h"

class FPS
{
public:
	FPS() : mFrame(0), mFps(0) {}
	const unsigned int getFPS() const { return mFps; }

private:
	unsigned int mFrame;
	unsigned int mFps;
	sf::Clock mClock;

public:
	void update()
	{
		if (mClock.getElapsedTime().asSeconds() >= 1.f)
		{
			mFps = mFrame;
			mFrame = 0;
			mClock.restart();
		}

		++mFrame;
	}
};

int main()
{
	const float dt = 0.016f;
	FPS fps;
	const int windowSize = 800;
	int agentCount = 200;
	sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Dynamic Logistics");
	window.setFramerateLimit(60);
	srand(time(NULL));
	
	AgentsDB* agents = new AgentsDB(window);

	agents->createAgents(agentCount);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(229, 222, 207));
		
		agents->update(dt);
		agents->render();

		//fps.update();
		//std::cout << fps.getFPS() << " ";
		
		window.display();
	}

	agents->deleteAgents();

	delete agents;

	return 0;
}