#include "Map.h"
#include<vector>
#include <string>
#include <istream>
#include<iostream>
#include <set>
using std::string;
using std::vector;
using std::size_t;
using std::set;

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

/*void Map::printShortestPath() {
	Map::Node start = findNodesOfChar('o')[0];
	//find the next 'nodes'
	Map::Node u = findCorner(Map::up, start), r = findCorner(Map::right, start), d = findCorner(Map::down, start), l = findCorner(Map::left, start);

}*/

vector<Map::Node> Map::findStart(char matchingChar) {
	vector<Map::Node> nodes;

	size_t row, searchCol, col;
	for (row = 0; row < map.size(); row++) {
		for (searchCol = 0; searchCol < map[row].size(); ) {
			col = map[row].find(matchingChar, searchCol);
			if (col == string::npos) {
				break;
			}
			else {
				searchCol = col + 1;
				nodes.push_back(Map::Node(row, col, Map::Node::Type::start));
			}
		}
	}
	return nodes;
}

set<Map::Node> Map::findNodes(Map::Node start) {
	set<Map::Node> nodes;
	nodes.insert(start);
	findNodesR(nodes, start);
	return nodes;
}

void Map::findNodesR(std::set<Map::Node>& knownNodes, Map::Node start) {
	vector<Map::Node> newNodes = findConnectedNodes(start);

	for (const auto& node : newNodes) {
		if (knownNodes.count(node) == 0) {
			//only add and recurse if node is new
			knownNodes.insert(node);
			findNodesR(knownNodes, node);
		}
	}

}

vector<Map::Node> Map::findConnectedNodes(Map::Node start) {
	vector<Map::Node> nodes;

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
				nodes.push_back(Map::Node(candidateRow, start.col, currentChar));
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
				nodes.push_back(Map::Node(candidateRow, start.col, currentChar));
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
				nodes.push_back(Map::Node(start.row, candidateCol, currentChar));
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
				nodes.push_back(Map::Node(start.row, candidateCol, currentChar));
			}
		}
		return nodes;
	}

	/*

	//add top node
	int candidateRow = -1;
	long int searchRow;
	for (searchRow = (start.row - 1); searchRow >= 0; searchRow--) {
		char currentChar = map[searchRow][start.col];
		if (currentChar == '#')
			break;
		else if (currentChar == 'X' || currentChar == 'o') {
			candidateRow = searchRow;
			break;
		}
		else
			candidateRow = searchRow;
	}
	if (candidateRow != -1) {
		nodes.push_back(Map::Node(candidateRow, start.col, map[candidateRow][start.col]));
	}

	//add bottom node
	candidateRow = -1;
	for (searchRow = start.row + 1; searchRow < map.size(); searchRow++) {
		char currentChar = map[searchRow][start.col];
		if (currentChar == '#')
			break;
		else if (currentChar == 'X' || currentChar == 'o') {
			candidateRow = searchRow;
			break;
		}
		else
			candidateRow = searchRow;
	}
	if (candidateRow != -1) {
		nodes.push_back(Map::Node(candidateRow, start.col, map[candidateRow][start.col]));
	}

	//add right node
	long searchCol;
	int candidateCol = -1;
	for (searchCol = start.col + 1; searchCol < map[start.row].size(); searchCol++) {
		char currentChar = map[start.row][searchCol];
		if (currentChar == '#')
			break;
		else if (currentChar == 'o' || currentChar == 'X') {
			candidateCol = searchCol;
			break;
		}
		else
			candidateCol = searchCol;
	}
	if (candidateCol != -1) {
		nodes.push_back(Map::Node(start.row, candidateCol, map[start.row][candidateCol]));
	}

	//add left node
	candidateCol = -1;
	for (searchCol = start.col - 1; searchCol >= 0; searchCol--) {
		char currentChar = map[start.row][searchCol];
		if (currentChar == '#')
			break;
		else if (currentChar == 'o' || currentChar == 'X') {
			candidateCol = searchCol;
			break;
		}
		else
			candidateCol = searchCol;
	}
	if (candidateCol != -1) {
		nodes.push_back(Map::Node(start.row, candidateCol, map[start.row][candidateCol]));
	}
	return nodes;
	*/
}