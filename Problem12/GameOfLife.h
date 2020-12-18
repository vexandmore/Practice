#pragma once
#include<vector>;
#include <istream>;
#include <ostream>;
class GameOfLife {
public:
	const static int boardSize = 10;
	GameOfLife();
	friend std::istream& operator>> (std::istream& is, GameOfLife& gol);
	friend std::ostream& operator<< (std::ostream& os, const GameOfLife& gol);
	void advance(int numberGenerations);
private:
	std::vector<std::vector<bool>> board;
	int numNeighbours(int x, int y);
	static std::vector<std::vector<bool>> getEmptyVector();
	static void resetVector(std::vector<std::vector<bool>>& vec);
};