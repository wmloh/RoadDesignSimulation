#include "empty.h"

Empty::Empty(int x, int y) : Tile{x, y} {}

Empty::~Empty() {}

Eigen::Matrix<float, 5, 1> Empty::toVector() {
	Eigen::Matrix<float, 5, 1> m;
	m << 0, 0, 1, 0, 0;
	return std::move(m);
}

std::string Empty::print() {
	return " ";
}

bool Empty::traversable() {
	return false;
}