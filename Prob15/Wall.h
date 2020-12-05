#pragma once
#include"Point.h"
#include<vector>

class Wall {
private:
	bool vertical;
	//used as a helper method to verify if the intersection point is on the line
	//exact match isn't used because floating point rounding could put the point slightly off the line (at least that was my fear)
	bool isInBoundingBox(const Point& p) const;
public:
	Point start, end;
	double slope, yint;
	Wall();
	Wall(Point start, Point end);
	bool intersect(const Wall& other) const;
	//vertical lines must be treated differently
	bool isVertical() const;
	//most important method: used to tell if the spy and camera have line of sight to each other
	static bool lineOfSightExists(const Point& a, const Point& b, const std::vector<Wall>& walls);
	//used to get wall from cin
	friend std::istream& operator>> (std::istream& is, Wall& w);
};
