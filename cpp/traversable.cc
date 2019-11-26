#include "traversable.h"
#include "constants.h"

Traversable::Traversable(int x, int y, int cap) : Tile{x,y}, cars{}, capacity{cap} {}

Traversable::~Traversable() {}

void Traversable::acceptCar(CarPtr cp) {
	cars.push(std::move(cp));
}

int Traversable::sendCar(int dir, Car &car) {
	Tile *tile = getNeighbours().at(dir);

	int curX, curY;
	std::tie(curX, curY) = tile->getCoord();
	int desX, desY;
	std::tie(desX, desY) = car.getDest();
	if(curX == desX && curY == desY) {
		car.reached();
		cars.pop();
		return REACHED;
	}

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
		return STEPPED;
	}
	return BLOCKED;
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