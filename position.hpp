#pragma once
#include <SFML/System/Vector2.hpp>

class Position {
	public:
	float x = 0;
	float y = 0;

	Position(float x, float y);

	bool operator==(Position other);
	void operator+=(Position other);
	void operator-=(Position other);

	operator sf::Vector2f();
};
