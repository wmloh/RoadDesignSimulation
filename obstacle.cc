#include "obstacle.h"

Obst::Obst(int x, int y) : Tile{x,y} {}

Obst::~Obst() {}

Eigen::Matrix<float, 5, 1> Obst::toVector() {
	Eigen::Matrix<float, 5, 1> m;
	m << 0, 0, 0, 1, 0;
	return std::move(m);
}

std::string Obst::print() {
	return "%";
}

bool Obst::traversable() {
	return false;
}