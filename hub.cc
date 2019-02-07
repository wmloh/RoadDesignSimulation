#include "hub.h"

Hub::Hub(int x, int y, int cap) : Tile{x,y}, capacity{cap} {}

Hub::~Hub() {}

Eigen::Matrix<float, 5, 1> Hub::toVector() {
	Eigen::Matrix<float, 5, 1> m;
	m << 0, static_cast<float>(capacity), 0, 0, 0;
	return std::move(m);
}

std::string Hub::print() {
	return "h";
}

bool Hub::traversable() {
	return false;
}