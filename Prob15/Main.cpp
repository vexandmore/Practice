#include <iostream>
#include<vector>
#include<string>
#include "Point.h"
#include "Wall.h"
using std::cout;
using std::cin;
using std::vector;
using std::string;

int main() {
	int numCases;
	cin >> numCases;
	vector<string> answers;

	for (int i = 0; i < numCases; i++) {
		Point spy, camera;
		cin >> spy >> camera;
		int numWalls;
		cin >> numWalls;
		vector<Wall> walls;

		for (int i = 0; i < numWalls; i++) {
			Wall tempWall;
			cin >> tempWall;
			walls.push_back(tempWall);
		}

		answers.push_back(Wall::lineOfSightExists(spy, camera, walls) ? "YES" : "NO");
	}

	for (string s : answers) {
		cout << s << "\n";
	}
}
