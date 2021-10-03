#include <vector>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <algorithm>
#include <iostream>

#include "bouncer.hpp"
#include "ball.hpp"

Bouncer::Bouncer(Position pos, int width, int height, int rotation) {
	this->pos = pos;
	this->width = width;
	this->height = height;
	this->rotation = rotation;
}

void Bouncer::draw(sf::RenderWindow& window) {
	std::vector<Position> corners = getCorners();
	sf::ConvexShape convex(corners.size());
	convex.setFillColor(sf::Color(50, 50, 50));
	for (int i = 0; i < corners.size(); i++) {
		convex.setPoint(i, corners[i]);
	}

	window.draw(convex);
}

bool Bouncer::checkBallCollision(Ball* ball) {
	std::vector<Position> corners = getCorners();
	float dMax = 0;
	float dMin = 999999;
	for (Position p : corners) {
		float dist = sqrt(pow((ball->pos.x - p.x), 2) + pow((ball->pos.y - p.y), 2));
		dMax = std::max(dist, dMax);
		dMin = std::min(dist, dMin);
	}

	bool pointInPolygon = checkPointInPolygon(ball->pos);

	if (ball->radius > dMax) 
		return true; // ball encloses polygon
	if (dMin < ball->radius && ball->radius < dMax)
		return true; // ball intersects polygon
	if (ball->radius < dMin && pointInPolygon)
		return true; // ball is in polygon
	if (ball->radius < dMin && !pointInPolygon)
		return false; // ball is outside polygon

	return false;
	
}

bool Bouncer::checkPointInPolygon(Position p) {
	std::vector<Position> polygon = getCorners();
	int n = polygon.size();

	Position extreme = Position(10000, p.y);

	int count = 0, i = 0;
	do {
		int next = (i+1)%n;

		if (checkIfIntersect(polygon[i], polygon[next], p, extreme)) {
			if (orientationOfPoints(polygon[i], p, polygon[next]) == 0)
				return isPointOnSegment(polygon[i], p, polygon[next]);

			count++;
		}
		i = next;
	} while (i != 0);

	return (count % 2 == 1);
}

// checks if point q is on segmant pr for three collinear points p, q, r
bool Bouncer::isPointOnSegment(Position p, Position q, Position r) {
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		return true;
	return false;
}

// given three ordered points, returns 0 if collinear, 1 if clockwise and 2 if counterclockwise
int Bouncer::orientationOfPoints(Position p, Position q, Position r) {
	int val = (q.y - p.y) * (r.x - q.x) -
			(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0; // collinear
	return (val > 0)? 1: 2; // clock or counterclock wise
}

// checks if p1q1 and p2q1 intersect
bool Bouncer::checkIfIntersect(Position p1, Position q1, Position p2, Position q2) {
	// Find the four orientations
	int o1 = orientationOfPoints(p1, q1, p2);
	int o2 = orientationOfPoints(p1, q1, q2);
	int o3 = orientationOfPoints(p2, q2, p1);
	int o4 = orientationOfPoints(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1
	if (o1 == 0 && isPointOnSegment(p1, p2, q1)) return true;

	// p1, q1 and p2 are collinear and q2 lies on segment p1q1
	if (o2 == 0 && isPointOnSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2
	if (o3 == 0 && isPointOnSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2
	if (o4 == 0 && isPointOnSegment(p2, q1, q2)) return true;

	return false;
}

Position Bouncer::rotateRectPoint(Position point, int angle) {
	int tempX = point.x - pos.x;
	int tempY = point.y - pos.y;
	float rX = pos.x + (tempX * cos(angle * 3.14159f / 180.0f)) - (tempY * sin(angle * 3.14159f / 180.0f));
	float rY = pos.y + (tempX * sin(angle * 3.14159f / 180.0f)) + (tempY * cos(angle * 3.14159f / 180.0f));
	return Position(rX, rY);
}

std::vector<Position> Bouncer::getCorners() {
	std::vector<Position> res;
	res.push_back(rotateRectPoint(pos, rotation));
	res.push_back(rotateRectPoint(Position(pos.x + width, pos.y), rotation));
	res.push_back(rotateRectPoint(Position(pos.x + width, pos.y + height), rotation));
	res.push_back(rotateRectPoint(Position(pos.x, pos.y + height), rotation));
	return res;
}
