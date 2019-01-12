#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include "tile.h"

typedef std::vector<std::vector<TilePtr>> Ground;

class Map {
	std::string mapDir;
	std::string profDir;
public:
	Map(std::string, std::string);
	~Map();
	Ground toTiles();
	//void replaceTile();
};

#endif