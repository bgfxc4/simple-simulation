#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

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
};

class Ball {
	public:
	Position vel = Position(0, 0);
	Position pos = Position(100, 0);

	Position gravity = Position(0, 0.2f);
	
	void simulate() {
		vel += gravity;
		pos += vel;
		std::cout << gravity.y << std::endl;
	}

	void draw(sf::RenderWindow& window) {
		sf::CircleShape circle(10);
		circle.setFillColor(sf::Color(150, 50, 250));
		circle.setPosition(pos.x, pos.y);
		window.draw(circle);
	}
};

std::vector<Ball> balls;

void draw(sf::RenderWindow& window) {
	for (Ball& b : balls) {
		b.simulate();
		b.draw(window);
	}
}

int main() {
	balls.push_back(Ball());

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
