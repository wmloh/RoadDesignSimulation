#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include "tile.h"

class Map {
	std::string mapDir;
	std::string profDir;
	std::string orderDir;
public:
	Map(std::string, std::string, std::string);
	~Map();
	Ground toTiles();
	//toOrder();
};

#endif