#pragma once
#include <vector>
#include <string>
#include <istream>
#include <ostream>
#include <memory>

/*
* Represents a point on the map
*/
class Point {
public:
	int row, col;
	char type;
	std::vector<Point*> connectedPoints{};
	Point* previous = nullptr;
	int distanceFromStart = 1000000;
public:
	Point(int row, int col, char type);

	void connectTo(std::vector<Point*> otherPoints);
	int distance(Point* other);
	bool operator< (const Point& other) const;
	bool operator== (const Point& other) const;
	bool operator!= (const Point& other) const;
	friend std::ostream& operator<< (std::ostream& os, const Point& node);
	class LessThan {
	public:
		bool operator() (Point* const lh, Point* const rh) const;
	};
};