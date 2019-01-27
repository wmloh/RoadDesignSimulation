#include "traversable.h"

Traversable::Traversable(int x, int y, int cap) : Tile{x,y}, cars{}, capacity{cap} {}

Traversable::~Traversable() {}

void Traversable::acceptCar(CarPtr cp) {
	cars.push(std::move(cp));
}

bool Traversable::sendCar(int dir, Car &car) {
	Tile *tile = getNeighbours().at(dir);
	Traversable *t = dynamic_cast<Traversable *>(tile);

	if(!t) {
		std::cerr << "Routing algorithm invalid (Traversable::sendCar)" << std::endl;
		throw "Error";
	}

	if(t->getNumCars() < t->getCapacity()) {
		std::unique_ptr<Car> c = std::move(cars.front());
		cars.pop();
		t->acceptCar(std::move(c));
		car.setRoad(t);
		return true;
	}
	return false;	
}

int Traversable::getNumCars() {
	return cars.size();
}

int Traversable::getCapacity() {
	return capacity;
}

void Traversable::clearCars() {
	while(!cars.empty()) {
		cars.pop();
	}
}