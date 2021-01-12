#include "Map.h"

size_t Map::Point::distance(Map::Point other) {
	if (row == other.row) {
		return other.col > col ? other.col - col : col - other.col;
	}
	else {
		return other.row > row ? other.row - row : row - other.row;
	}
}

Map::Point::Point(size_t row, size_t col) : row(row), col(col) {
}

bool Map::Point::operator< (const Map::Point& other) const {
	//consider row as the 'most significant bits'
	if (row < other.row)
		return true;
	else if (row > other.row)
		return false;
	else return col < other.col;
}

std::ostream& operator<<(std::ostream& os, const Map::Point& node) {
	os << "row: " << node.row << " col: " << node.col;
	return os;
}