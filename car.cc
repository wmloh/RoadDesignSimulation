#include "car.h"
#include "road.h"
#include "hub.h"

Car::Car(int x, int y, int desX, int desY, Hub *hub) : 
	x{x}, y{y}, route{}, dest{desX, desY}, hub{hub}, curRoad{nullptr} {}

Car::~Car() {}

bool Car::getRoute() {
	return true;
}

void Car::setRoad(Road *r) {
	curRoad = r;
}

bool Car::move() {
	return true;
}