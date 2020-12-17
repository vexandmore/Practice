#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::string;
using std::vector;

/**
* Represents a boarding pass, with a source and destination.
* Also has overloaded >>
*/
class BoardingPass {
public:
	string source, dest;
	BoardingPass() {
	}
	BoardingPass(string source, string dest) : source(source), dest(dest) {
	}
	BoardingPass(const BoardingPass& bp) = default;
	bool containsCity(string city) {
		return city == source || city == dest;
	}
	friend std::istream& operator>> (std::istream& is, BoardingPass& pass) {
		cin >> pass.source >> pass.dest;
		return is;
	}
};

/**
* Represents an itinerary composed of boarding passes.
* Can add a boarding pass to an itinerary only if it 'fits' on one end of the itinerary
*/
class Itinerary {
private:
	vector<BoardingPass> passes;
public:
	bool addPass(const BoardingPass& pass) {
		if (passes.size() == 0) {
			passes.push_back(pass);
			return true;
		}
		else {
			if (pass.dest == passes[0].source) {
				passes.insert(passes.begin(), pass);
				return true;
			}
			else if (pass.source == passes[passes.size()-1].dest) {
				passes.push_back(pass);
				return true;
			}
		}
		return false;
	}
	vector<string> toReverseCityList() const {
		vector<string> cities;
		if (passes.size() == 0) {
			return cities;
		}
		else {
			vector<BoardingPass>::const_reverse_iterator it;
			for (it = passes.rbegin(); it < passes.rend(); it++) {
				cities.push_back(it->dest);
			}
			cities.push_back(passes[0].source);

			return cities;
		}
	}
};

vector<string> reverseTrip(vector<BoardingPass> passes);

int main() {
	int numCases;
	cin >> numCases;
	vector<vector<string>> reverseTrips;

	for (int i = 0; i < numCases; i++) {
		vector<BoardingPass> passes;
		int numPasses;
		cin >> numPasses;

		for (int j = 0; j < numPasses; j++) {
			BoardingPass pass;
			cin >> pass;
			passes.push_back(pass);
		}
		reverseTrips.push_back(reverseTrip(passes));
	}

	for (auto reverseTrip : reverseTrips) {
		for (auto city : reverseTrip) {
			cout << city << "\n";
		}
	}
}

/*
* Exists for the reverseTrip function
*/
class MarkedBoardingPass : public BoardingPass {
public:
	bool used;
	MarkedBoardingPass(BoardingPass bp) : BoardingPass(bp), used(false) {
	}
};


vector<string> reverseTrip(vector<BoardingPass> passes) {
	Itinerary itn;
	bool done = false;

	//copies the vector into a vector of markedPasses so which ones have been added to the itinerary
	//is easy to keep track of
	vector<MarkedBoardingPass> markedPasses;
	for (vector<BoardingPass>::const_iterator it = passes.begin(); it < passes.end(); it++) {
		markedPasses.push_back(*it);
	}

	size_t numberAdded = 0;
	while (numberAdded < markedPasses.size()) { //loop until all boarding passes have been added
		for (vector<MarkedBoardingPass>::iterator it = markedPasses.begin(); it < markedPasses.end(); it++) {
			if (!(it->used)) {
				if (itn.addPass(*it)) { //if pass was added successfully mark it so it isn't added again 
					numberAdded++;
					it->used = true;
				}
			}
		}

	}
	return itn.toReverseCityList();
}