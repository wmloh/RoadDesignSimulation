#include "hub.h"

Hub::Hub(int x, int y, int cap) : Tile{x,y}, capacity{cap} {}

Hub::~Hub() {}

Vec Hub::toVector() {
	return {0, static_cast<float>(capacity), 0, 0, 0};
}

std::string Hub::print() {
	return "h";
}

bool Hub::traversable() {
	return false;
}