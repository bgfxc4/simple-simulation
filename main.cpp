#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>

class Position {
	public:
	float x = 0;
	float y = 0;

	Position(float x, float y) {
		this->x = x;
		this->y = y;
	}

	bool operator==(Position other) {
		return this->x == other.x && this->y == other.y;
	}

	void operator+=(Position other) {
		this->x += other.x;
		this->y += other.y;
	}
	
	void operator-=(Position other) {
		this->x -= other.x;
		this->y -= other.y;
	}

	operator sf::Vector2f() {
		return sf::Vector2f(this->x, this->y);
	}
};

class Bouncer {
	public:
	Position pos = Position(0, 0);
	int width = 0;
	int height = 0;
	int rotation = 0;

	Bouncer(Position pos, int width, int height, int rotation) {
		this->pos = pos;
		this->width = width;
		this->height = height;
		this->rotation = rotation;
	}

	void draw(sf::RenderWindow& window) {
		sf::ConvexShape convex(4);
		convex.setFillColor(sf::Color(50, 50, 50));
		convex.setPoint(0, rotateRectPoint(pos, 45));
		convex.setPoint(1, rotateRectPoint(Position(pos.x + width, pos.y), 45));
		convex.setPoint(2, rotateRectPoint(Position(pos.x + width, pos.y + height), 45));
		convex.setPoint(3, rotateRectPoint(Position(pos.x, pos.y + height), 45));

		window.draw(convex);
	}

	Position rotateRectPoint(Position point, int angle) {
		int tempX = point.x - pos.x;
		int tempY = point.y - pos.y;
		float rX = pos.x + (tempX * cos(angle * 3.14159f / 180.0f)) - (tempY * sin(angle * 3.14159f / 180.0f));
		float rY = pos.y + (tempX * sin(angle * 3.14159f / 180.0f)) + (tempY * cos(angle * 3.14159f / 180.0f));
		return Position(rX, rY);
	}

	std::vector<Position> getCorners() {
		std::vector<Position> res;
		res.push_back(rotateRectPoint(pos, rotation));
		res.push_back(rotateRectPoint(Position(pos.x + width, pos.y), rotation));
		res.push_back(rotateRectPoint(Position(pos.x + width, pos.y + height), rotation));
		res.push_back(rotateRectPoint(Position(pos.x, pos.y + height), rotation));
		return res;
	}
};

class Ball {
	public:
	float radius = 10;
	float wallBounceCoefficient = 0.9f;

	Position vel = Position(6, 0);
	Position pos = Position(100, 0);

	Position gravity = Position(0, 1.0f);
	
	void simulate(sf::RenderWindow& window) {
		vel += gravity;
		pos += vel;
		checkForBorderCollision(window);
		checkForBouncerCollision();
	}

	void draw(sf::RenderWindow& window) {
		sf::CircleShape circle(radius);
		circle.setFillColor(sf::Color(150, 50, 250));
		circle.setPosition(pos.x, pos.y);
		window.draw(circle);
	}

	private:
	void checkForBorderCollision(sf::RenderWindow& window) {
		if (pos.x + 2*radius >= window.getSize().x) {
			// if collided, move right for the distance the ball clipped into the wall
			float clipped = (pos.x + 2*radius) - window.getSize().x;
			pos.x = (window.getSize().x - 2*radius) - (clipped * wallBounceCoefficient);

			vel.x = (vel.x < 1) ? 0 : -wallBounceCoefficient * vel.x;
		} else if (pos.x < 0) {
			float clipped = -pos.x;
			pos.x = clipped * wallBounceCoefficient;
			vel.x = (vel.x > -1) ? 0 : -wallBounceCoefficient * vel.x;
		}

		if (pos.y +  2*radius >= window.getSize().y) {
			// if collided, move up for the distance the ball clipped into the wall
			float clipped = (pos.y + 2*radius) - window.getSize().y;
			pos.y = (window.getSize().y -  2 * radius) - (clipped * wallBounceCoefficient);

			vel.y = (vel.y < 1) ? 0 : -wallBounceCoefficient * vel.y;
		} else if (pos.y < 0) {
			float clipped = -pos.y; 
			pos.y = clipped * wallBounceCoefficient;

			vel.y = (vel.y > -1) ? 0 : -wallBounceCoefficient * vel.y;
		}
	}

	void checkForBouncerCollision() {
	}
};

std::vector<Ball> balls;
std::vector<Bouncer> bouncers;

void draw(sf::RenderWindow& window) {
	for (Ball& b : balls) {
		b.simulate(window);
		b.draw(window);
	}

	for (Bouncer& b : bouncers) {
		b.draw(window);
	}
}

int main() {
	balls.push_back(Ball());
	bouncers.push_back(Bouncer(Position(70, 200), 100, 15, 0));

	sf::RenderWindow window(sf::VideoMode(800, 600), "simple simulation");
	window.setFramerateLimit(60);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		draw(window);

		window.display();
	}
}
