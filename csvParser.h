#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <iostream>
#include <vector>

class CSVParser {
	// directory of csv file
	std::string dir;
public:
	CSVParser(std::string);
	~CSVParser();

	// parses dir into a vector of strings
	std::vector<std::vector<std::string>> toString(bool);

	// parses dir into a vector of ints
	std::vector<std::vector<int>> toInt(bool);
};

#endif