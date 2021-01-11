#include "Map.h"

size_t Map::Node::distance(Map::Node other) {
	if (row == other.row) {
		return other.col > col ? other.col - col : col - other.col;
	}
	else {
		return other.row > row ? other.row - row : row - other.row;
	}
}

Map::Node::Node(size_t row, size_t col, Node::Type type) : row(row), col(col), type(type) {
}

Map::Node::Node(size_t row, size_t col, char character) : row(row), col(col) {
	if (character == 'o')
		type = Node::Type::start;
	else if (character == 'X')
		type = Node::Type::exit;
	else
		type = Node::Type::intermediate;
}

bool Map::Node::operator< (const Map::Node& other) const {
	//consider row as the 'most significant bits'
	if (row < other.row)
		return true;
	else if (row > other.row)
		return false;
	else return col < other.col;
}

std::ostream& operator<<(std::ostream& os, const Map::Node& node) {
	os << "row: " << node.row << " col: " << node.col << " type: " << (int)node.type <<  "\n";
	return os;
}