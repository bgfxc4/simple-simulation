#include <iostream>

#include "ball.hpp"
#include "bouncer.hpp"

void Ball::simulate(sf::RenderWindow& window, std::vector<Bouncer>& bouncers) {
	vel += gravity;
	pos += vel;
	checkForBorderCollision(window);
	checkForBouncerCollision(bouncers, window);
}

void Ball::draw(sf::RenderWindow& window) {
	sf::CircleShape circle(radius);
	circle.setFillColor(sf::Color(150, 50, 250));
	circle.setPosition(pos.x - radius, pos.y - radius);
	window.draw(circle);
}

void Ball::checkForBorderCollision(sf::RenderWindow& window) {
	if (pos.x + radius >= window.getSize().x) {
		// if collided, move right for the distance the ball clipped into the wall
		float clipped = (pos.x + radius) - window.getSize().x;
		pos.x = (window.getSize().x - radius) - (clipped * wallBounceCoefficient);

		vel.x = (vel.x < 1) ? 0 : -wallBounceCoefficient * vel.x;
	} else if (pos.x < 0) {
		float clipped = -pos.x;
		pos.x = clipped * wallBounceCoefficient;
		vel.x = (vel.x > -1) ? 0 : -wallBounceCoefficient * vel.x;
	}

	if (pos.y + radius >= window.getSize().y) {
		// if collided, move up for the distance the ball clipped into the wall
		float clipped = (pos.y + radius) - window.getSize().y;
		pos.y = (window.getSize().y - radius) - (clipped * wallBounceCoefficient);

		vel.y = (vel.y < 1) ? 0 : -wallBounceCoefficient * vel.y;
	} else if (pos.y < 0) {
		float clipped = -pos.y; 
		pos.y = clipped * wallBounceCoefficient;

		vel.y = (vel.y > -1) ? 0 : -wallBounceCoefficient * vel.y;
	}
}

void Ball::checkForBouncerCollision(std::vector<Bouncer>& bouncers, sf::RenderWindow& window) {
	for (Bouncer& b : bouncers) {
		if (b.checkBallCollision(this)) {
			std::cout << "ball collision" << std::endl;
			window.setFramerateLimit(1);
		} else {
			window.setFramerateLimit(60);
		}
	}
}
