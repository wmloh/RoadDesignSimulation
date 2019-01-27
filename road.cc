#include "road.h"

Road::Road(int x, int y, int cap) : Traversable{x,y,cap} {}

Road::~Road() {}

std::string Road::print() {
	if(cars.empty()) {
		return "+";
	}
	return "@";
}

bool Road::traversable() {
	return true;
}