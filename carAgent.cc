#include "carAgent.h"
#include "car.h"

CarAgent::CarAgent(int x, int y, int desX, int desY) : 
	physCar{std::make_unique<Car>(x, y)}, dest{desX, desY} {}

CarAgent::~CarAgent() {}

bool CarAgent::getRoute() {
	return true;
}

bool CarAgent::move() {
	return true;
}