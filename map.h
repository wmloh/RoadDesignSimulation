#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include "tile.h"
#include "waiting.h"

class Map {
	std::string mapDir;
	std::string profDir;
	std::string orderDir;
	std::vector<Tile *> tileArray;
	int size;
public:
	Map(std::string, std::string, std::string);
	~Map();
	Ground toTiles();
	void toOrder(Waiting &);
	Tile *getTile(int, int);
};

#endif