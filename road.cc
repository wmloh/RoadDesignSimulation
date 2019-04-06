#include "road.h"

Road::Road(int x, int y, int cap) : Traversable{x,y,cap} {}

Road::~Road() {}

Vec Road::toVector() {
	return {0, 0, 0, 0, static_cast<float>(getCapacity())};
}

std::string Road::print() {
	if(cars.empty()) {
		return "+";
	}
	return "@";
}

bool Road::traversable() {
	return true;
}