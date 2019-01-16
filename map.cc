#include "map.h"
#include "obstacle.h"
#include "empty.h"
#include "home.h"
#include "hub.h"
#include "road.h"
#include "car.h"
#include "csvParser.h"
#include <fstream>

Map::Map(std::string mapDir, std::string profDir, std::string orderDir) :
	mapDir{mapDir}, profDir{profDir}, orderDir{orderDir} {}

Map::~Map() {}

void attachNeighbours(Ground &g, int lenX, int lenY) {
	int x = 0;
	int y = 0;

	for(auto &r : g) {
		for(auto &c : r) {
			for(int i = x - 1; i <= x + 1; ++ i) {
				for(int j = y - 1; j <= y + 1; ++j) {
					if(i >= 0 && i < lenX && j >= 0 && j < lenY && (i != x || j != y)) {
						c->setNeighbours(g.at(i).at(j).get());
					} else {
						c->setNeighbours(nullptr);
					}
				}
			}
			x++;
		}
		y++;
		x = 0;
	}
}

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
		// create 2D array of Tiles
		while(std::getline(mapFs, line)) {
			std::getline(profFs, profile);
			len = line.size();
			row.clear();
			
			for(int i = 0; i < len; ++i) {
				if(line[i] == '%') {
					row.emplace_back(std::make_unique<Obst>(i, rowCount));
				} else if(line[i] == ' ') {
					row.emplace_back(std::make_unique<Empty>(i, rowCount));
				} else if(line[i] == 'H') {
					row.emplace_back(std::make_unique<Home>(i, rowCount, profile[i] - '0'));
				} else if(line[i] == 'h') {
					row.emplace_back(std::make_unique<Hub>(i, rowCount, profile[i] - '0'));
				} else if(line[i] == '+') {
					row.emplace_back(std::make_unique<Road>(i, rowCount, profile[i] - '0'));
				} else if(line[i] == '@') {
					row.emplace_back(std::make_unique<Car>(i, rowCount));
					std::cerr << "A car is detected on the map; this will cause simulation to not work as expected" << std::endl;
				} else if(line[i] != '\r') {
					throw std::string{"Unrecognized symbol detected on the map: " + std::string{1, line[i]}};
				}
			}
			g.emplace_back(std::move(row));
			++rowCount;

			mapFs.clear();
			profFs.clear();
		}

		// assigning pointers of neighbours
		attachNeighbours(g, len-1, rowCount);
		
	} catch(std::string s) {
		std::cerr << s << std::endl;
		throw;
	} catch(const std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
		throw;
	} catch(const std::exception &e) {
		std::cerr << e.what() << std::endl;
		throw;
	} catch(...) {
		std::cerr << "Unknown error occurred(1)" << std::endl;
		throw;
	}
	
	return std::move(g);
}