#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "position.hpp"

class Ball;

class Bouncer {
	public:
	Position pos = Position(0, 0);
	int width = 0;
	int height = 0;
	int rotation = 0;

	Bouncer(Position pos, int width, int height, int rotation);
	void draw(sf::RenderWindow& window);
	bool checkBallCollision(Ball* ball);
	bool checkPointInPolygon(Position point);

	private:
	bool isPointOnSegment(Position p, Position q, Position r);
	int orientationOfPoints(Position p, Position q, Position r);
	bool checkIfIntersect(Position p1, Position q1, Position p2, Position q2);
	float distanceBetweenPoints(Position a, Position b);
	float distanceBetweenPointAndLine(Position l1, Position l2, Position p);

	Position rotateRectPoint(Position point, int angle);
	std::vector<Position> getCorners(); 
};

