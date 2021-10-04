#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "position.hpp"

class Bouncer;

class Ball {
	public:
	float radius = 10;
	float wallBounceCoefficient = 1.0f;

	Position vel = Position(40, 20.0f);
	Position pos = Position(100, 0);

	Position gravity = Position(0, 1.0f);
	
	void simulate(sf::RenderWindow& window, std::vector<Bouncer>& bouncers);
	void draw(sf::RenderWindow& window);

	private:
	void checkForBorderCollision(sf::RenderWindow& window);
	void checkForBouncerCollision(std::vector<Bouncer>& bouncers, sf::RenderWindow& window);
};
