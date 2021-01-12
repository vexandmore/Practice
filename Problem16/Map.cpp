#include "Map.h"
#include<vector>
#include <string>
#include <istream>
#include<iostream>
#include <set>
#include <map>
#include <utility>
using std::string;
using std::vector;
using std::size_t;
using std::set;
using std::map;

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

void Map::printShortestPath() {
	PointDetails points = findNodes(findStart('o'));

}

Map::Point Map::findStart(char matchingChar) {
	size_t row, searchCol, col;
	for (row = 0; row < map.size(); row++) {
		for (searchCol = 0; searchCol < map[row].size(); ) {
			col = map[row].find(matchingChar, searchCol);
			if (col == string::npos) {
				break;
			}
			else {
				searchCol = col + 1;
				return Map::Point(row, col);
			}
		}
	}
	return Map::Point(1000, 1000);
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
}