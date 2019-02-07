#include "road.h"

Road::Road(int x, int y, int cap) : Traversable{x,y,cap} {}

Road::~Road() {}

Eigen::Matrix<float, 5, 1> Road::toVector() {
	Eigen::Matrix<float, 5, 1> m;
	m << 0, 0, 0, 0, static_cast<float>(getCapacity());
	return std::move(m);
}

std::string Road::print() {
	if(cars.empty()) {
		return "+";
	}
	return "@";
}

bool Road::traversable() {
	return true;
}