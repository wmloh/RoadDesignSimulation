#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>
#include <queue>
#include <memory>

class Tile;

typedef std::unique_ptr<Tile> TilePtr;
typedef std::vector<std::vector<TilePtr>> Ground;

class Tile {
	int x, y;
	std::vector<Tile *> neighbours;
public:
	Tile(int, int);
	virtual ~Tile() = 0;
	std::vector<Tile *> getNeighbours();
	void setNeighbours(Tile *);
	friend std::ostream &operator<<(std::ostream &, Tile &);
protected:
	virtual std::string print() = 0;
};

#endif