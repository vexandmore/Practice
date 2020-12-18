#include "GameOfLife.h";
#include <iostream>;
#include <vector>;
using std::cout;
using std::cin;
using std::vector;

int main() {
	int numCases;
	cin >> numCases;
	vector<GameOfLife> games;

	for (int i = 0; i < numCases; i++) {
		int numGenerations;
		cin >> numGenerations;
		GameOfLife game;
		cin >> game;
		game.advance(numGenerations);
		games.push_back(game);
	}

	for (vector<GameOfLife>::const_iterator it = games.begin(); it < games.end(); it++) {
		cout << *it << "\n";
	}
}