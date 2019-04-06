#include "empty.h"

Empty::Empty(int x, int y) : Tile{x, y} {}

Empty::~Empty() {}

Vec Empty::toVector() {
	return {0, 0, 1, 0, 0};
}

std::string Empty::print() {
	return " ";
}

bool Empty::traversable() {
	return false;
}