#include "IPaddress.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using std::string;
using std::vector;

IPaddress::IPaddress(): address(0) {
}
std::istream& operator>> (std::istream& is, IPaddress& ip) {
	vector<string> input(4);
	std::getline(std::cin, input[0], '.');
	std::getline(std::cin, input[1], '.');
	std::getline(std::cin, input[2], '.');
	std::getline(std::cin, input[3], '\n');

	unsigned long long bits = std::stoi(input[0]);
	ip.address += bits << 24;
	bits = std::stoi(input[1]);
	ip.address += bits << 16;
	bits = std::stoi(input[2]);
	ip.address += bits << 8;
	bits = std::stoi(input[3]);
	ip.address += bits;

	return is;
}
std::string IPaddress::CIDRrange(const std::vector<IPaddress>& addresses) {
	//find the number of matching bits
	int numBitsMatching = 0;
	bool match = true;
	for (int bitChecking = 31; bitChecking >= 0 && match == true; bitChecking--) {//bitChecking represents the MSB of the address when it is 32
		int bit = (addresses.begin()->getAddress() >> (bitChecking)) % 2;
		for (vector<IPaddress>::const_reverse_iterator it = addresses.rbegin(); it < addresses.rend() && match == true; it++) {
			if ((it->getAddress() >> (bitChecking)) % 2 == bit) {
			}
			else {
				match = false;
			}
		}
		if (match == true)
			numBitsMatching++;
	}
	//find the lowest ip address in the block
	unsigned long long address = addresses[0].getAddress();
	address = address >> (32 - numBitsMatching);
	address = address << (32 - numBitsMatching);//zero out all non matching bits
	return IPaddress(address).toString() + "/" + std::to_string((numBitsMatching));
}

unsigned long long IPaddress::getAddress() const {
	return address;
}
string IPaddress::toString() const {
	int bits1 = (address >> 24) % 256;
	int bits2 = (address >> 16) % 256;
	int bits3 = (address >> 8) % 256;
	int bits4 = (address) % 256;

	std::ostringstream out;
	out << bits1 << "." << bits2 << "." << bits3 << "." << bits4;
	return out.str();
}

IPaddress::IPaddress(unsigned long long address): address(address) {
}