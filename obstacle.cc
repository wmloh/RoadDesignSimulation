#include "obstacle.h"

Obst::Obst(int x, int y) : Tile{x,y} {}

Obst::~Obst() {}

std::string Obst::print() {
	return "%";
}