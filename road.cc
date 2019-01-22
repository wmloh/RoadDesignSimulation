#include "road.h"

Road::Road(int x, int y, int cap) : Tile{x,y}, capacity{cap}, cars{} {}

Road::~Road() {}

void Road::moveCar() {
	// move car
}

void Road::acceptCar(Car *c) {
	cars.push(c);
}

int Road::getCapacity() {
	return capacity;
}

std::string Road::print() {
	return "+";
}

bool Road::traversable() {
	return true;
}