#include"Wall.h"
#include"Point.h"
#include<vector>
#include<iostream>

Wall::Wall() : Wall(Point(0,0), Point(0,0)){
}
Wall::Wall(Point start, Point end) 
	: start(start), end(end), slope(0), yint(0) {
	if (start.x == end.x) {
		vertical = true;
	}
	else {
		vertical = false;
		slope = (start.y - end.y) / (start.x - end.x);
		yint = start.y - slope * start.x;
	}
}

bool Wall::lineOfSightExists(const Point& a, const Point& b, const std::vector<Wall>& walls) {
	Wall wallSpyToCam(a, b);
	for (const Wall& wall : walls) {
		if (wall.intersect(wallSpyToCam))
			return false;
	}
	return true;
}

bool Wall::intersect(const Wall& other) const {
	if (isVertical() && other.isVertical()) {
		//check if any of the endpoints are in another line
		return isInBoundingBox(other.start) || isInBoundingBox(other.end)
			|| other.isInBoundingBox(start) || other.isInBoundingBox(end);
	}
	else if (isVertical()) {
		Point intersection;
		intersection.x = start.x;
		intersection.y = other.slope * intersection.x + other.yint;
		return isInBoundingBox(intersection) && other.isInBoundingBox(intersection);
	}
	else if (other.isVertical()) {
		Point intersection;
		intersection.x = other.start.x;
		intersection.y = slope * intersection.x + yint;
		return isInBoundingBox(intersection) && other.isInBoundingBox(intersection);
	}
	else {
		//find the point where the lines intersect
		Point p;
		p.x = (other.yint - yint) / (slope - other.slope);
		p.y = slope * p.x + yint;
		//check if the point is on both line segments
		if (isInBoundingBox(p) && other.isInBoundingBox(p)) {
			return true;
		}
		else {
			return false;
		}

	}
}
bool Wall::isVertical() const {
	return vertical;
}
bool Wall::isInBoundingBox(const Point& p) const {
		if (p.y <= end.y && p.y >= start.y && p.x >= start.x && p.x <= end.x
			|| p.y >= end.y && p.y <= start.y && p.x <= start.x && p.x >= end.x) {
			return true;
		}
		else {
			return false;
		}
}

std::istream& operator>> (std::istream& is, Wall& w) {
	is >> w.start.x >> w.start.y >> w.end.x >> w.end.y;
	w.vertical = w.start.x == w.end.x;//set vertical, since we're changing the points
	w.slope = (w.start.y - w.end.y) / (w.start.x - w.end.x);
	w.yint = w.start.y - w.slope * w.start.x;
	return is;
}
