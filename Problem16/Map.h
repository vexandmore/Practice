#pragma once
#include<vector>
#include <string>
#include <istream>
#include <limits>
#include <set>
#include <ostream>
#include <memory>
#include <map>

class PointDetails;

class Map {
public:
	Map();
	friend std::istream& operator>>(std::istream& is, Map& map);
	void printShortestPath();

	class Point {
	public:
		std::size_t row, col;
		std::size_t distance(Point other);
	public:
		Point(std::size_t row, std::size_t col);

		bool operator< (const Point& other) const;
		friend std::ostream& operator<< (std::ostream& os, const Point& node);
	};

public:
	std::vector<std::string> map;

	std::vector<Point> findConnectedNodes(Point start);
	Map::Point findStart(char matchingChar);
	PointDetails findNodes(Map::Point start);
	void findNodesR(PointDetails& points, Map::Point start);
};

class PointDetails {
public:
	std::set<Map::Point> points;
	std::map<Map::Point, std::vector<Map::Point>> connections;
	PointDetails() {
	}
};