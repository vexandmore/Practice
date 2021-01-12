#pragma once
#include<vector>
#include <string>
#include <istream>
#include <limits>
#include <set>
#include <ostream>

class Map {
public:
	Map();
	friend std::istream& operator>>(std::istream& is, Map& map);
	//void printShortestPath();

	class Node {
	public:
		enum class Type {
			start,
			intermediate,
			exit
		};

		std::size_t row, col;
		Node* previous = nullptr;
		Node* next = nullptr;
		std::vector<Node*> connectedNodes{};
		int distanceFromStart = std::numeric_limits<int>::max();
		Node::Type type;
		std::size_t distance(Node other);

	public:
		Node(std::size_t row, std::size_t col, Type type);
		Node(std::size_t row, std::size_t col, char character);

		bool operator< (const Node& other) const;
		friend std::ostream& operator<< (std::ostream& os, const Node& node);
	};

public:
	std::vector<std::string> map;

	std::vector<Node> findConnectedNodes(Node start);
	std::vector<Map::Node> findStart(char matchingChar);
	std::set<Map::Node> findNodes(Map::Node start);
	void findNodesR(std::set<Map::Node>& knownNodes, Map::Node start);
};