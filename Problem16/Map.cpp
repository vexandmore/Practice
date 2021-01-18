#include "Map.h"
#include "Point.h"
#include <vector>
#include <string>
#include <istream>
#include <iostream>
#include <set>
#include <map>
#include <utility>
#include <algorithm>
#include <utility>
using std::string;
using std::vector;
using std::size_t;
using std::set;
using std::map;
using std::shared_ptr;
using std::make_shared;

Map::Map() {
}

std::istream& operator>> (std::istream& is, Map& map) {
	map.map.clear();
	int width, height;
	is >> width >> height;
	string throwaway;
	std::getline(is, throwaway);//remove extraneous whitespace
	for (int i = 0; i < height; i++) {
		map.map.emplace_back("");
		std::getline(is, map.map[i], '\n');
	}
	return is;
}

shared_ptr<Point> Map::getPoint(int row, int col, char c) const {
	Map::Spoint sp = Spoint(row, col);
	if (internedPoints.count(sp) != 0) {
		return internedPoints[sp];
	}
	else {
		shared_ptr<Point> newPoint = make_shared<Point>(row, col, c);
		internedPoints.insert(std::make_pair(sp, newPoint));
		return newPoint;
	}
}

set<shared_ptr<Point>, Point::LessThan> Map::getPoints() const {
	auto start = getStart();
	set<shared_ptr<Point>, Point::LessThan> points;
	points.insert(start);
	getPointsR(points, start);
	return points;
}

void Map::getPointsR(set<shared_ptr<Point>, Point::LessThan>& points, shared_ptr<Point> start) const {
	vector<shared_ptr<Point>> newPoints = getAdjacentPoints(start);
	start->connectTo(newPoints);
	for (auto newPoint : newPoints) {
		if (points.count(newPoint) == 0) {
			//newPoint->connectTo(start);
			points.insert(newPoint);
			getPointsR(points, newPoint);
		}
	}
}

vector<shared_ptr<Point>> Map::getAdjacentPoints(shared_ptr<Point> start) const {
	vector<shared_ptr<Point>> adjacentPoints;
	//if at an exit, don't check (since we could go off the map)
	if (start->type == 'X')
		return adjacentPoints;
	//add point above
	int candidateRow = start->row - 1;
	if (candidateRow >= 0) {
		char candidateChar = map[candidateRow][start->col];
		if (candidateChar != '#') {
			adjacentPoints.push_back(getPoint(candidateRow, start->col, candidateChar));
		}
	}
	//add point below
	candidateRow = start->row + 1;
	if (candidateRow < map.size()) {
		char candidateChar = map[candidateRow][start->col];
		if (candidateChar != '#') {
			adjacentPoints.push_back(getPoint(candidateRow, start->col, candidateChar));
		}
	}
	//add point at right
	int candidateCol = start->col + 1;
	if (candidateCol < map[start->row].length()) {
		char candidateChar = map[start->row][candidateCol];
		if (candidateChar != '#') {
			adjacentPoints.push_back(getPoint(start->row, candidateCol, candidateChar));
		}
	}
	//add point at left
	candidateCol = start->col - 1;
	if (candidateCol >= 0) {
		char candidateChar = map[start->row][candidateCol];
		if (candidateChar != '#') {
			adjacentPoints.push_back(getPoint(start->row, candidateCol, candidateChar));
		}
	}
	return adjacentPoints;
}

shared_ptr<Point> Map::getStart() const {
	for (int i = 0; i < map.size(); i++) {
		std::size_t position = map[i].find('o');
		if (position != string::npos) {
			return getPoint(i, position, 'o');
		}
	}
	throw "cannot find start";
}
/*
void Map::printShortestPath() {
	Point start = findStart('o');
	PointDetails points = findNodes(start);
	set<DPoint> unvisitedPoints;//these sets are ordered by distance from center, then row, then col
	set<Dpoint> visitedPoints;
	for (const Point& point : points.points) {
		if (point == start) {
			unvisitedPoints.insert(DPoint(point, 0));
		}
		else {
			unvisitedPoints.insert(DPoint(point));
		}
	}
	//main loop
	while (unvisitedPoints.size() != 0) {
		//get lowest distance point
		DPoint currentPoint = *unvisitedPoints.begin();
		unvisitedPoints.erase(currentPoint);
		//get points it's connected to and update their distanceFromCenter
		vector<Point> connectedPoints = points.connections[currentPoint.point];
		for (const Point& point : connectedPoints) {
			DPoint connectedDPoint = std::find_if(unvisitedPoints.begin(), unvisitedPoints.end(), [point](DPoint dp) {
				return point == dp.point;
				});
			unvisitedPoints.erase(connectedDPoint);
			if (currentPoint.distanceFromStart + currentPoint.point.distance(connectedDPoint.point) < connectedDPoint.distanceFromStart) {
				connectedDPoint.distanceFromStart = currentPoint.distanceFromStart + currentPoint.point.distance(connectedDPoint.point);
				connectedDPoint.previous = currentPoint.point;
				currentPoint.next = connectedDPoint.point;
				unvisitedPoints.insert(connectedDPoint);
			}
		}
		visitedPoints.
		visitedPoints.insert(currentPoint);
	}

}


PointDetails Map::findNodes(Map::Point start) {
	PointDetails points;
	points.points.insert(start);
	findNodesR(points, start);
	return points;
}

void Map::findNodesR(PointDetails& points, Map::Point start) {
	//add start to connections if not already there
	if (points.connections.count(start) == 0) {
		points.connections.insert(std::make_pair(start, vector<Map::Point>{}));
	}

	vector<Map::Point> newNodes = findConnectedNodes(start);
	for (const auto& node : newNodes) {
		if (points.points.count(node) == 0) {
			//if point is new,
			//add to points and have start connect to it
			points.points.insert(node);
			points.connections[start].push_back(node);//add new node to connections. We know that start is in the map
			//connect this point to start
			if (points.connections.count(node) == 0) {
				points.connections.insert(std::make_pair(node, vector<Map::Point>{}));
			}
			points.connections[node].push_back(start);
			//recurse
			findNodesR(points, node);
		}
	}

}

vector<Map::Point> Map::findConnectedNodes(Map::Point start) {
	vector<Map::Point> nodes;

	if (map[start.row][start.col] == 'X' || map[start.row][start.col] == '#') {
		//exits and walls could lead off the array or off the map by accident
		return nodes;
	}
	else {
		//add top if exists
		int candidateRow = start.row - 1;
		if (candidateRow >= 0) {
			char currentChar = map[candidateRow][start.col];
			switch (currentChar) {
			case 'X':
			case 'o':
			case ' ':
				nodes.push_back(Map::Point(candidateRow, start.col));
			}
		}
		//add bottom if exists
		candidateRow = start.row + 1;
		if (candidateRow < map.size()) {
			char currentChar = map[candidateRow][start.col];
			switch (currentChar) {
			case 'X':
			case 'o':
			case ' ':
				nodes.push_back(Map::Point(candidateRow, start.col));
			}
		}
		//add right if exists
		int candidateCol = start.col + 1;
		if (candidateCol < map[start.row].size()) {
			char currentChar = map[start.row][candidateCol];
			switch (currentChar) {
			case 'X':
			case 'o':
			case ' ':
				nodes.push_back(Map::Point(start.row, candidateCol));
			}
		}
		//add left if it exists
		candidateCol = start.col - 1;
		if (candidateCol >= 0) {
			char currentChar = map[start.row][candidateCol];
			switch (currentChar) {
			case 'X':
			case 'o':
			case ' ':
				nodes.push_back(Map::Point(start.row, candidateCol));
			}
		}
		return nodes;
	}
}*/