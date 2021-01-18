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

void Map::printShortestPath(std::ostream& os) {
	auto unvisited = getPoints();
	set<shared_ptr<Point>, Point::LessTLDistance> endPoints;
	while (unvisited.size() > 0) {
		auto currentPoint = *unvisited.begin();
		unvisited.erase(currentPoint);
		for (auto point : currentPoint->connectedPoints) {
			if (unvisited.count(point) != 0 &&
				currentPoint->distanceFromStart + currentPoint->straightDistance(point) < point->distanceFromStart) {
				unvisited.erase(point);
				point->distanceFromStart = currentPoint->distanceFromStart + currentPoint->straightDistance(point);
				point->previous = currentPoint;
				unvisited.insert(point);
			}
			if (currentPoint->type == 'X') {
				endPoints.insert(currentPoint);
			}
		}
	}
	os << "Shortest path:\n";
	auto exit = *endPoints.begin();
	vector<string> annotatedMap = map;
	auto previous = exit->previous;
	while (previous->type == ' ') {
		annotatedMap[previous->row][previous->col] = '.';
		previous = previous->previous;
	}
	for (const string& line : annotatedMap) {
		os << line << '\n';
	}
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