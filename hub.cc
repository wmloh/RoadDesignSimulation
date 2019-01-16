#include "hub.h"

Hub::Hub(int x, int y, int cap) : Tile{x,y}, capacity{cap} {}

Hub::~Hub() {}

void Hub::sendCar() {
	// send a car
}

std::string Hub::print() {
	return "h";
}