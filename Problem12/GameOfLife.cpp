#include<vector>;
#include <istream>;
#include <ostream>;
#include<string>;
#include "GameOfLife.h";
using std::vector;

void GameOfLife::advance(int numGenerations) {
	vector<vector<bool>> nextPosition = getEmptyVector();

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
		resetVector(nextPosition);
	}
}

GameOfLife::GameOfLife() {
	board = getEmptyVector();
}

std::istream& operator>> (std::istream& is, GameOfLife& gol) {
	//read the 10 lines and set the board to its state
	for (int row = 0; row < GameOfLife::boardSize; row++) {
		std::string line;
		is >> line;
		for (int col = 0; col < line.size() && col < GameOfLife::boardSize; col++) {
			gol.board[row][col] = line[col] == '1';
		}
	}
	return is;
}

std::ostream& operator<< (std::ostream& os, const GameOfLife& gol) {
	for (const vector<bool>& line : gol.board) {
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
	if (row != 0) {
		numNeighbours += board[row - 1][col];//add top center
		//cond add top left
		if (col != 0) {
			numNeighbours += board[row - 1][col - 1];
		}
		//cond add top right
		if (col != boardSize - 1) {
			numNeighbours += board[row - 1][col + 1];
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
vector<vector<bool>> GameOfLife::getEmptyVector() {
	vector<vector<bool>> board;
	for (int i = 0; i < boardSize; i++) {
		vector<bool> temp;
		for (int j = 0; j < boardSize; j++) {
			temp.push_back(false);
		}
		board.push_back(temp);
	}
	return board;
}
void GameOfLife::resetVector(vector<vector<bool>>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec.size(); j++) {
			vec[i][j] = false;
		}
	}
}