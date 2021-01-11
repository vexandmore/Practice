#include "Map.h"
#include<iostream>
using std::string;
using std::vector;
using std::size_t;
using std::set;
using std::cin;
using std::cout;

int main() {
	cout << "enter map\n";
	Map map;
	cin >> map;

	set<Map::Node> nodes;
	nodes = map.findNodes(map.findStart('o')[0]);
	for (const Map::Node& node : nodes) {
		cout << node;
	}
}