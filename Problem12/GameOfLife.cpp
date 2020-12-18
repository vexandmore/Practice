#include<vector>;
#include <istream>;
#include <ostream>;
#include<string>;
#include "GameOfLife.h";
using std::vector;

void GameOfLife::advance(int numGenerations) {
	vector<vector<bool>> nextPosition;//contains 10 vector<bool> initialized to false
	for (int i = 0; i < boardSize; i++) {
		vector<bool> temp;
		for (int j = 0; j < boardSize; j++) {
			temp.push_back(false);
		}
		nextPosition.push_back(temp);
	}

	for (int i = 0; i < numGenerations; i++) {
		for (int row = 0; row < boardSize; row++) {
			for (int col = 0; col < boardSize; col++) {
				int neighbours = numNeighbours(row, col);
				if (board[row][col]) {
					//if live cell
					if (neighbours == 2 || neighbours == 3)
						nextPosition[row][col] = true;
					else if (neighbours == 1 || neighbours == 0 || neighbours >= 4)
						nextPosition[row][col] == false;
				}
				else {
					if (neighbours == 3)
						nextPosition[row][col] = true;
				}
			}
		}
		this->board = nextPosition;
		for (int f = 0; f < boardSize; f++) {
			for (int t = 0; t < boardSize; t++) {
				nextPosition[f][t] = false;
			}
		}
	}
}

GameOfLife::GameOfLife() {
	for (int i = 0; i < boardSize; i++) {
		vector<bool> temp;
		board.push_back(temp);
	}
}

std::istream& operator>> (std::istream& is, GameOfLife& gol) {
	for (int i = 0; i < GameOfLife::boardSize; i++) {
		gol.board[i].clear();
		std::string line;
		is >> line;
		for (std::string::const_iterator it = line.begin(); it < line.end(); it++) {
			gol.board[i].push_back(*it == '1');
		}
	}
	return is;
}

std::ostream& operator<< (std::ostream& os, const GameOfLife& gol) {
	for (auto line : gol.board) {
		for (auto character : line) {
			os << character;
		}
		os << "\n";
	}
	return os;
}


int GameOfLife::numNeighbours(int row, int col) {
	int numNeighbours = 0;
	//add top row
	if (row == 0) {
	}
	else {
		numNeighbours += board[row-1][col];//add top center
		//cond add top left
		if (col == 0) {
		}
		else {
			numNeighbours += board[row-1][col-1];
		}
		//cond add top right
		if (col == boardSize - 1) {
		}
		else {
			numNeighbours += board[row-1][col+1];
		}
	}
	//add center left and right
	if (col != 0) {
		numNeighbours += board[row][col - 1];
	}
	if (col != boardSize - 1) {
		numNeighbours += board[row][col + 1];
	}
	//add bottom
	if (row != boardSize - 1) {
		numNeighbours += board[row+1][col];
		if (col != 0) {
			numNeighbours += board[row + 1][col - 1];
		}
		if (col != boardSize - 1) {
			numNeighbours += board[row + 1][col + 1];
		}
	}
	return numNeighbours;
}