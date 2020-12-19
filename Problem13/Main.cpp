#include<iostream>;
#include<vector>;
#include<string>;
#include"Complex.h";
using std::cin;
using std::cout;
using std::vector;

std::string mandelbrotColor(const Complex& num);

int main() {
	int numCases;
	cin >> numCases;
	vector<Complex> complexNumbers;

	for (int i = 0; i < numCases; i++) {
		Complex temp;
		cin >> temp;
		complexNumbers.push_back(temp);
	}
	for (const Complex& value : complexNumbers) {
		cout << value << " " << mandelbrotColor(value) << "\n";
	}
}

std::string mandelbrotColor(const Complex& num) {
	double divergeValue = 100;

	Complex current(0, 0);
	int n; //this n is the n in Zn from problem description
	for (n = 1; n <= 51 && current.magnitude() < divergeValue; n++) {
		current = current.squared() + num;
	}
	n--;//need to undo last n++
	if (n <= 10)
		return "RED";
	else if (n <= 20)
		return "ORANGE";
	else if (n <= 30)
		return "YELLOW";
	else if (n <= 40)
		return "GREEN";
	else if (n <= 50)
		return "BLUE";
	else
		return "BLACK";
}