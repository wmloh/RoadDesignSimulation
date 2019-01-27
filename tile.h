#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>
#include <queue>
#include <memory>

class Tile;

typedef std::unique_ptr<Tile> TilePtr;
typedef std::vector<std::vector<TilePtr>> Ground;

class Simulation;

class Tile {
	// coordinates
	int x, y;

	// neighbours(child) of this Tile - neighbours.size() = 9
	std::vector<Tile *> neighbours;
public:
	Tile(int, int);
	virtual ~Tile() = 0;

	// getter method for neighbours
	std::vector<Tile *> getNeighbours();

	// setter method for neighbours
	void setNeighbours(Tile *);

	// getter method for x, y coordinates
	std::pair<int, int> getCoord();

	// checks if a Car can move to this Tile
	virtual bool traversable() = 0;

	friend std::ostream &operator<<(std::ostream &, Tile &);
	friend class Simulation;
protected:
	virtual std::string print() = 0;
};

#endif