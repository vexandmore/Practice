#include<string>
#include<ctype.h>
#include<cstdio>
#include<sstream>
#include<iomanip>
#include "TimeParser.h"
using std::string;
using std::setw;

string parseTime(const string &in) {
	string out, numStr;
	int hour = 0, min = 0, sec = 0;

	for (size_t i = 0; i < in.size(); i++) {
		if (isdigit(in[i])) {
			numStr += in[i];
		}
		else if (numStr.size() > 0){ //once we've hit the non numerical part, loop until after numbner
			int extracted = std::stoi(numStr);
			numStr = string("");
			//read character after num, for h, m or s
			switch (in[i]) {
			case 'h':
				hour = extracted;
				break;
			case 'm':
				min = extracted;
				break;
			case 's':
				sec = extracted;
				break;
			}
		}
	}
	/*char buffer[10];
	snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", hour, min, sec);
	return string(buffer);*/

	//use ostringstream to format output instead of snprintf
	std::ostringstream buffer;
	buffer << std::setfill('0');
	buffer << setw(2) << hour << ":" << setw(2) << min << ":" << setw(2) << sec;
	return buffer.str();
}