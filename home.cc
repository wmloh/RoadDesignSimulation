#include "home.h"

Home::Home(int x, int y, int cap) : Tile{x,y}, capacity{cap} {}

Home::~Home() {}

void Home::sendCar() {
	// send a car
}

std::string Home::print() {
	return "H";
}