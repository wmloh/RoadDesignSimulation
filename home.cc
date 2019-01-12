#include "home.h"

Home::Home(int x, int y) : Tile{x,y} {}

Home::~Home() {}

void Home::sendCar() {
	// send a car
}

std::string Home::print() {
	return "H";
}