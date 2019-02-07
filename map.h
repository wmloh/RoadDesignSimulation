#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include "tile.h"
#include "waiting.h"
#include <Eigen/Dense>

class Map {
	// path to map file
	std::string mapDir;

	// path to profile file
	std::string profDir;

	// path to order file
	std::string orderDir;

	// stored 1D array of Tile (for internal processing purposes)
	std::vector<Tile *> tileArray;

	// length of loaded tileArray
	int size;
public:
	Map(std::string, std::string, std::string);
	~Map();

	// loads mapDir file and returns Ground format
	Ground toTiles();

	// loads orderDir file into a Waiting object
	void toOrder(Waiting &);

	// returns the Ground as a matrix
	Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, 5> toMatrix();

	// getter method to get Tile *
	Tile *getTile(int, int);
};

#endif