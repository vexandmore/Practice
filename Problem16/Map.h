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

/*
* Represents a map, from which a shortest path will be found
*/
class Map {
public:
	Map();
	friend std::istream& operator>>(std::istream& is, Map& map);
	void printShortestPath(std::ostream& os);

public:
	class Spoint {
	public:
		int row, col;
		Spoint(int row, int col);
		bool operator< (const Spoint& rh) const;
	};
	
	std::vector<std::string> map;
	mutable std::map<Spoint, std::shared_ptr<Point>> internedPoints{};

	std::shared_ptr<Point> getStart() const;
	std::set<std::shared_ptr<Point>, Point::LessThan> getPoints() const;
	void getPointsR(std::set<std::shared_ptr<Point>, Point::LessThan>& points, std::shared_ptr<Point> start) const;
	std::vector<std::shared_ptr<Point>> getAdjacentPoints(std::shared_ptr<Point> start) const;

	std::shared_ptr<Point> getPoint(int row, int col, char c) const;
};