#include "Point.h"
#include <limits>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <exception>
using std::vector;
using std::shared_ptr;

Point::Point(int row, int col, char type): row(row), col(col), type(type) {
	if (type == 'o') {
		distanceFromStart = 0;
	}
}

void Point::connectTo(vector<shared_ptr<Point>> otherPoints) {
	for (shared_ptr<Point> point : otherPoints) {
		if (std::count(connectedPoints.begin(), connectedPoints.end(), point) == 0) {
			connectedPoints.push_back(point);
		}
		if (std::count(point->connectedPoints.begin(), point->connectedPoints.end(), shared_from_this()) == 0) {
			point->connectedPoints.push_back(shared_from_this());
		}
	}
}

int Point::straightDistance(shared_ptr<Point> other) {
	if (row == other->row) {
		return std::abs(col - other->col);
	}
	else if (col == other->col) {
		return std::abs(row - other->row);
	}
	else {
		throw new std::exception("points must be in line");
	}
}

bool Point::operator< (const Point& other) const {
	return std::tie(distanceFromStart, row, col) < std::tie(other.distanceFromStart, other.row, other.col);
}
bool Point::operator== (const Point& other) const {
	if (distanceFromStart == other.distanceFromStart) {
		return true;
	}
	else if (row == other.row) {
		return true;
	}
	else if (col == other.col) {
		return true;
	}
	else {
		return false;
	}
}
bool Point::operator!=(const Point& other) const {
	return !(*this == other);
}

std::ostream& operator<< (std::ostream& os, const Point& node) {
	os << "Type: " << node.type << " Row: " << node.row << " Col: " << node.col;
	return os;
}

bool Point::LessThan::operator() (const shared_ptr<Point>& const lh, const shared_ptr<Point>& const rh) const {
	return lh->operator<(*rh);
}
bool Point::LessTLDistance::operator() (const shared_ptr<Point>& const lh, const shared_ptr<Point>& const rh) const {
	if (lh->distanceFromStart != rh->distanceFromStart) {
		return lh->distanceFromStart < rh->distanceFromStart;
	}
	else {
		double distanceFromTLlh = std::sqrt(lh->col * lh->col + lh->row * lh->row);
		double distanceFromTLrh = std::sqrt(rh->col * rh->col + rh->row * rh->row);
		return distanceFromTLlh < distanceFromTLrh;
	}
}


/*bool operator== (const std::shared_ptr<Point>& lhs, const std::shared_ptr<Point>& rhs) {
	return *lhs < *rhs;
}*/