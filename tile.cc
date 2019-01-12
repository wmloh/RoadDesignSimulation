#include "tile.h"

Tile::Tile(int x, int y) : x{x}, y{y}, neighbours{} {}

Tile::~Tile() {}

std::vector<Tile *> Tile::getNeighbours() {
	return neighbours;
}

void Tile::setNeighbours(std::vector<Tile *> n) {
	neighbours = n;
}