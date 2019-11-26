#include "tile.h"

Tile::Tile(int x, int y) : x{x}, y{y}, neighbours{} {}

Tile::~Tile() {}

std::vector<Tile *> Tile::getNeighbours() {
	return neighbours;
}

void Tile::setNeighbours(Tile *t) {
	neighbours.emplace_back(t);
}

std::ostream &operator<<(std::ostream &out, Tile &t) {
	out << t.print();
	return out;
}

std::pair<int, int> Tile::getCoord() {
	return {x, y};
}