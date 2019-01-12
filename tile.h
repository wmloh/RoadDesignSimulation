#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>
#include <queue>
#include <memory>

class Tile;

typedef std::unique_ptr<Tile> TilePtr;

class Tile {
	int x, y;
	std::vector<Tile *> neighbours;
public:
	Tile(int, int);
	~Tile();
	std::vector<Tile *> getNeighbours();
private:
	void setNeighbours(std::vector<Tile *>);
};

#endif