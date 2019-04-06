#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include "tile.h"
#include "waiting.h"
#include <Eigen/Dense>
#include <array>

typedef std::array<std::unique_ptr<Eigen::MatrixXf>, 5> Tensor;
const int NUM_LAYER = 5;

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
	Tensor toMatrix(Ground &g);

	// getter method to get Tile *
	Tile *getTile(int, int);
};

#endif