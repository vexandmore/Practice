#include"IPaddress.h"
#include <string>
#include<vector>
#include<iostream>
using std::string;
using std::cin;
using std::cout;
using std::vector;

int main() {
	vector<vector<IPaddress>> testCases;
	int numCases;
	cin >> numCases;
	for (int i = 0; i < numCases; i++) {
		testCases.emplace_back(vector<IPaddress>{});
		int numAddresses;
		cin >> numAddresses;
		for (int j = 0; j < numAddresses; j++) {
			IPaddress temp;
			cin >> temp;
			testCases[i].push_back(temp);
		}
	}
	cout << '\n';
	for (const vector<IPaddress>& list : testCases) {
		cout << IPaddress::CIDRrange(list) << "\n";
	}
}