#ifndef TRAVERSABLE_H
#define TRAVERSABLE_H

#include "tile.h"
#include "car.h"

class Traversable : public Tile {
protected:
	std::queue<CarPtr> cars;
	int capacity;
public:
	Traversable(int, int, int);
	~Traversable();
	void acceptCar(CarPtr);
	bool sendCar(int, Car &);
	int getNumCars();
	int getCapacity();
	void clearCars();
};

#endif