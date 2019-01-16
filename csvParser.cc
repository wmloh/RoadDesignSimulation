#include "csvParser.h"
#include <fstream>
#include <sstream>
#include <algorithm>

CSVParser::CSVParser(std::string dir) : dir{dir} {}

CSVParser::~CSVParser() {}

std::vector<std::vector<std::string>> CSVParser::toString(bool sorted) {
	std::ifstream fs{dir};
	std::string line;

	std::vector<std::vector<std::string>> container;
	std::vector<std::string> row;
	
	while(std::getline(fs, line)) {
		std::istringstream ss{line};
		row.clear();

		while(std::getline(ss, line,',')) {
			row.emplace_back(line);
		}
		
		container.emplace_back(row);
		fs.clear();
	}
	if(sorted) {
		std::sort(container.begin(), container.end(),
			[](const std::vector<std::string>&a, const std::vector<std::string>&b) {
				return a[0] < b[0];
			});
	}

	return container;
}

std::vector<std::vector<int>> CSVParser::toInt(bool sorted) {
	std::ifstream fs{dir};
	std::string line;

	std::vector<std::vector<int>> container;
	std::vector<int> row;
	int i;

	while(std::getline(fs, line)) {
		std::istringstream ss{line};
		row.clear();

		while(std::getline(ss, line,',')) {
			std::istringstream iss{line};
			iss >> i;
			row.emplace_back(i);
		}
		
		container.emplace_back(row);
		fs.clear();
	}

	if(sorted) {
		std::sort(container.begin(), container.end(),
			[](const std::vector<int>&a, const std::vector<int>&b) {
				return a[0] < b[0];
			});
	}

	return container;
}