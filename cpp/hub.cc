#include "hub.h"

Hub::Hub(int x, int y, int cap) : Tile{x,y}, capacity{cap} {}

Hub::~Hub() {}

std::string Hub::print() {
	return "h";
}

bool Hub::traversable() {
	return false;
}