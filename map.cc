#include "map.h"
#include "tile.h"
#include "obstacle.h"
#include "empty.h"
#include "home.h"
#include "hub.h"
#include "road.h"
#include "car.h"
#include <fstream>
#include <unique>

Map::Map(std::string mapDir, std::string profDir): mapDir{mapDir}, profDir{profDir} {}

Map::~Map() {}

Ground Map::toTiles() {
	std::ifstream mapFs {mapDir};
	std::ifstream profFs {profDir};
	Ground g;
	std::string line;
	std::string profile;

	int len;
	std::vector<Tile *> row;

	try {
		while(getline(mapFs, line)) {
			getline(profFs, profile);
			len = line.length();

			row.clear();
			for(int i = 0; i < len; ++i) {
				if(line[i] == '*') {
					row.push_back(std::make_unique<Obst>());
				} else if(line[i] == ' ') {
					row.push_back(std::make_unique<Empty>());
				} else if(line[i] == 'H') {
					row.push_back(std::make_unique<Home>());
				} else if(line[i] == 'h') {
					row.push_back(std::make_unique<Hub>());
				} else if(line[i] == '+') {
					row.push_back(std::make_unique<Road>());
				} else if(line[i] == '@') {
					row.push_back(std::make_unique<Car>());
					std::cerr << "A car is detected on the map; this will cause simulation to not work as expected" << std::endl;
				} else {
					throw "Unrecognized symbol detected on the map";
				}
			}
			g.push_back(row);
		}
	} catch(std::string s) {
		std::cerr << "Error probably caused by map and profile .txt file not matching." << std::endl
		throw;
	}
	
	return g;
}