#pragma once
#include "Point.h"
#include<vector>
#include <string>
#include <istream>
#include <limits>
#include <set>
#include <ostream>
#include <map>
#include <tuple>

class PointDetails;
class Dpoint;

/*
* Represents a map, from which a shortest path will be found
*/
class Map {
public:
	Map();
	friend std::istream& operator>>(std::istream& is, Map& map);
	void printShortestPath();

public:
	class Spoint {
	public:
		int row, col;
		Spoint(int row, int col) : row(row), col(col) {
		}
		bool operator< (const Spoint& rh) const {
			return std::tie(row, col) < std::tie(rh.row, rh.col);
		}
	};
	
	std::vector<std::string> map;
	mutable std::map<Spoint, Point*> internedPoints{};

	Point* getStart() const;
	std::set<Point*, Point::LessThan> getPoints() const;
	void getPointsR(std::set<Point*, Point::LessThan>& points, Point* start) const;
	std::vector<Point*> getAdjacentPoints(Point* start) const;

	Point* getPoint(int row, int col, char c) const;
};