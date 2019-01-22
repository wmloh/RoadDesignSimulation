#include "empty.h"

Empty::Empty(int x, int y) : Tile{x, y} {}

Empty::~Empty() {}

std::string Empty::print() {
	return " ";
}

bool Empty::traversable() {
	return false;
}