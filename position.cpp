#include <SFML/System/Vector2.hpp>

#include "position.hpp"

Position::Position(float x, float y) {
	this->x = x;
	this->y = y;
}

bool Position::operator==(Position other) {
	return this->x == other.x && this->y == other.y;
}

void Position::operator+=(Position other) {
	this->x += other.x;
	this->y += other.y;
}

void Position::operator-=(Position other) {
	this->x -= other.x;
	this->y -= other.y;
}

Position::operator sf::Vector2f() {
	return sf::Vector2f(this->x, this->y);
}
