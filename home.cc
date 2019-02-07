#include "home.h"
#include "hub.h"

Home::Home(int x, int y, int cap) : Traversable{x,y,cap} {}

Home::~Home() {}

void Home::loadCar(int desX, int desY, PathFinder &pf, Hub *hub) {
	auto coord = getCoord();
	int x = coord.first;
	int y = coord.second;

	auto car = std::make_unique<Car>(x, y, desX, desY, hub, this);
	car->getRoute(pf);
	cars.emplace(std::move(car));
}

Eigen::Matrix<float, 5, 1> Home::toVector() {
	Eigen::Matrix<float, 5, 1> m;
	m << static_cast<float>(getCapacity()), 0, 0, 0, 0;
	return std::move(m);
}

Car * Home::getCar() {
	return cars.front().get();
}

std::string Home::print() {
	if(cars.empty()) {
		return "H";
	}
	return "@";
}

bool Home::traversable() {
	return false;
}