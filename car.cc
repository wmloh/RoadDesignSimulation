#include "car.h"

Car::Car(int x, int y) : Tile{x, y} {}

Car::~Car() {}

void Car::setRoad(Road * r) {
	curRoad = r;
}

std::string Car::print() {
	return "@";
}