#pragma once
#include <string>
#include <vector>
#include <istream>

class IPaddress {
private:
	unsigned long address;
public:
	unsigned long getAddress() const;
	IPaddress();
	IPaddress(unsigned long address);
	std::string toString() const;
	friend std::istream& operator>> (std::istream& is, IPaddress& ip);
	static std::string CIDRrange(const std::vector<IPaddress>& addresses);
};