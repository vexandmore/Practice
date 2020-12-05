#include "Point.h"

Point::Point(double x, double y) : x(x), y(y) {
}
Point::Point() : x(0), y(0) {}
std::istream& operator>> (std::istream& is, Point& pt) {
	is >> pt.x >> pt.y;
	return is;
}
