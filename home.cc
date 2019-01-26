#include "home.h"
#include "hub.h"

Home::Home(int x, int y, int cap) : Tile{x,y}, buffer{}, capacity{cap} {}

Home::~Home() {}

void Home::loadCar(int desX, int desY, PathFinder &pf, Hub *hub) {
	auto coord = getCoord();
	int x = coord.first;
	int y = coord.second;

	auto car = std::make_unique<Car>(x, y, desX, desY, hub, this);
	car->getRoute(pf);
	buffer.emplace(std::move(car));

	
}

void Home::clearBuffer() {
	while(!buffer.empty()) {
		buffer.pop();
	}
}

void Home::sendCar() {
	// send a car
	
}

std::string Home::print() {
	if(buffer.empty()) {
		return "H";
	}
	return "@";
}

bool Home::traversable() {
	return false;
}