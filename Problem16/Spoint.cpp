#include "Map.h"
Map::Spoint::Spoint(int row, int col) : row(row), col(col) {
}
bool Map::Spoint::operator< (const Spoint& rh) const {
	return std::tie(row, col) < std::tie(rh.row, rh.col);
}