#pragma once
#include<iostream>

class Point {
public:
	double x, y;
	Point(double x, double y);
	Point();
	//used to grab a point from cin
	friend std::istream &operator>> (std::istream &is, Point &pt);
};
