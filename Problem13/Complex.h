#pragma once
#include<istream>;
#include<ostream>;
#include <string>;

class Complex {
private:
	double a, i;
	std::string stringA, stringI;
public:
	Complex();
	Complex(double a, double i);
	double magnitude() const;
	Complex squared() const;
	friend Complex operator+(const Complex& c1, const Complex& c2);
	friend std::istream& operator>>(std::istream& is, Complex& complex);
	friend std::ostream& operator<<(std::ostream& os, const Complex& complex);
};