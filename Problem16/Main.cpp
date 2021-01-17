#include "Map.h"
#include<iostream>

#include<set>
using std::string;
using std::cin;
using std::cout;

int main() {
	cout << "enter map\n";
	Map map;
	cin >> map;

	std::set<Point*, Point::LessThan> points = map.getPoints();
	for (auto p : points) {
		cout << *p << '\n';
	}
}