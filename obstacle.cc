#include "obstacle.h"

Obst::Obst(int x, int y) : Tile{x,y} {}

Obst::~Obst() {}

Vec Obst::toVector() {
	return {0, 0, 0, 1, 0};
}

std::string Obst::print() {
	return "%";
}

bool Obst::traversable() {
	return false;
}