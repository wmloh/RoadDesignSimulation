#include "car.h"
#include "road.h"
#include "hub.h"
#include "constants.cc"
#include "pathFinder.h"

Car::Car(int x, int y, int desX, int desY, Hub *hub) : 
	x{x}, y{y}, route{}, dest{desX, desY}, hub{hub}, curRoad{nullptr} {}

Car::~Car() {}

bool Car::getRoute() {
	return true;
}

void Car::setRoad(Road *r) {
	curRoad = r;
}

Road *Car::getRoad() {
	return curRoad;
}

bool Car::move() {
	return true;
}

std::ostream &operator<<(std::ostream &out, Car &c) {
	out << "Coordinates: " << '(' << c.x << ',' << c.y << ')' << std::endl;
	out << "Destination: " << '(' << c.dest.first << ',' << c.dest.second << ')' << std::endl;
	out << "Path distance: " << c.route.size() << std::endl;
	return out;
}