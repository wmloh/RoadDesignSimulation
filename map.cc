#include "map.h"
#include "obstacle.h"
#include "empty.h"
#include "home.h"
#include "hub.h"
#include "road.h"
#include "car.h"
#include <fstream>

Map::Map(std::string mapDir, std::string profDir): mapDir{mapDir}, profDir{profDir} {}

Map::~Map() {}

Ground Map::toTiles() {
	std::ifstream mapFs {mapDir};
	std::ifstream profFs {profDir};
	Ground g;
	std::string line;
	std::string profile;

	int rowCount = 0;
	int len;
	std::vector<TilePtr> row;

	try {
		while(std::getline(mapFs, line)) {
			std::getline(profFs, profile);
			len = line.length();
			row.clear();
			for(int i = 0; i < len; ++i) {
				if(line[i] == '%') {
					row.emplace_back(std::make_unique<Obst>(i, rowCount));
				} else if(line[i] == ' ') {
					row.emplace_back(std::make_unique<Empty>(i, rowCount));
				} else if(line[i] == 'H') {
					row.emplace_back(std::make_unique<Home>(i, rowCount));
				} else if(line[i] == 'h') {
					row.emplace_back(std::make_unique<Hub>(i, rowCount));
				} else if(line[i] == '+') {
					row.emplace_back(std::make_unique<Road>(i, rowCount, profile[i] - '0'));
				} else if(line[i] == '@') {
					row.emplace_back(std::make_unique<Car>(i, rowCount));
					std::cerr << "A car is detected on the map; this will cause simulation to not work as expected" << std::endl;
				} else if(line[i] != '\r') {
					throw "Unrecognized symbol detected on the map: " + line[i];
				}
			}
			g.emplace_back(std::move(row));
			++rowCount;
			mapFs.clear();
			profFs.clear();
		}
	} catch(std::string s) {
		std::cerr << "Error probably caused by map and profile .txt file not matching." << std::endl;
		throw;
	} catch(...) {
		std::cerr << "Unknown error occurred" << std::endl;
		throw;
	}
	
	return std::move(g);
}