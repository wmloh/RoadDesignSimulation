#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <iostream>
#include <vector>

class CSVParser {
	std::string dir;
public:
	CSVParser(std::string);
	~CSVParser();
	std::vector<std::vector<std::string>> toString(bool);
	std::vector<std::vector<int>> toInt(bool);
};

#endif