#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>

#include "ball.hpp"
#include "bouncer.hpp"

std::vector<Ball> balls;
std::vector<Bouncer> bouncers;

void draw(sf::RenderWindow& window) {
	for (Ball& b : balls) {
		b.simulate(window, bouncers);
		b.draw(window);
	}

	for (Bouncer& b : bouncers) {
		b.draw(window);
	}
}

int main() {
	balls.push_back(Ball());
	bouncers.push_back(Bouncer(Position(70, 200), 100, 15, 45));

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
