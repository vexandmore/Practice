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

	PointDetails nodes;
	nodes = map.findNodes(map.findStart('o'));
	for (const Map::Point& node : nodes.points) {
		cout << node << "\n";
		cout << "connected to: ";
		for (const Map::Point& connectedPoint : nodes.connections[node]) {
			cout << connectedPoint << " ";
		}
		cout << "\n";
	}
}