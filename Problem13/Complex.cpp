#include "Complex.h";
#include<cmath>;
#include<istream>;
using std::istream;

Complex::Complex() : a(0), i(0) {
}
Complex::Complex(double a, double i) : a(a), i(i) {
}
double Complex::magnitude() const {
	return std::sqrt(a * a + i * i);
}
Complex operator+(const Complex& c1, const Complex& c2) {
	return Complex(c1.a + c2.a, c1.i + c2.i);
}
Complex Complex::squared() const {
	return Complex((a * a - i * i), 2 * a * i);
}
istream& operator>> (istream& is, Complex& c) {
	is >> c.stringA >> c.stringI;
	c.a = std::stod(c.stringA);
	c.i = std::stod(c.stringI);
	return is;
}
std::ostream& operator<<(std::ostream& os, const Complex& complex) {
	if (complex.stringA == "" || complex.stringI == "") //if the Complex wasn't piped in, pipe out the doubles direct
		os << complex.a << (complex.i >= 0 ? "+" : "-") << complex.i << "i";
	else //otherwise pipe out the same strings that were used as input
		os << complex.stringA << (complex.i >= 0 ? "+" : "-") << complex.stringI << "i";
	return os;
}