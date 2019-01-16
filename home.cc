#include "home.h"
#include "hub.h"

Home::Home(int x, int y, int cap) : Tile{x,y}, buffer{}, capacity{cap} {}

Home::~Home() {}

void Home::loadCar(int desX, int desY, Hub *h) {
	auto coord = getCoord();
	int x = coord.first;
	int y = coord.second;

	buffer.emplace(std::make_unique<Car>(x, y, desX, desY, h));
}

void Home::sendCar() {
	// send a car
}

std::string Home::print() {
	return "H";
}