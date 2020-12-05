#include <iostream>
#include <vector>
#include "TimeParser.h"
using std::vector;
using std::string;
using std::cin;
using std::cout;

int main() {
	int numCases;
	cin >> numCases;
	cin.get();
	vector<string> unformattedTimes;
	for (int i = 0; i < numCases; i++) {
		string unformattedTime;
		std::getline(std::cin, unformattedTime);
		unformattedTimes.push_back(unformattedTime);
	}
	for (auto formattedTime : unformattedTimes) {
		cout << parseTime(formattedTime) << "\n";
	}
	//cin.get();
}