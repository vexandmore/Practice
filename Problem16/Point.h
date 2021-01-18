#pragma once
#include <vector>
#include <string>
#include <istream>
#include <ostream>
#include <memory>
/*
* Represents a point on the map
*/
class Point: public std::enable_shared_from_this<Point> {
public:
	int row, col;
	char type;
	std::vector<std::shared_ptr<Point>> connectedPoints{};
	std::shared_ptr<Point> previous = nullptr;
	int distanceFromStart = 1000000;
public:
	Point(int row, int col, char type);

	void connectTo(std::vector<std::shared_ptr<Point>> otherPoints);
	int distance(Point* other);
	bool operator< (const Point& other) const;
	bool operator== (const Point& other) const;
	bool operator!= (const Point& other) const;
	friend std::ostream& operator<< (std::ostream& os, const Point& node);
	class LessThan {
	public:
		bool operator() (std::shared_ptr<Point> const lh, std::shared_ptr<Point> const rh) const;
	};
};

//bool operator== (const std::shared_ptr<Point>& lhs, const std::shared_ptr<Point>& rhs);