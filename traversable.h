#ifndef TRAVERSABLE_H
#define TRAVERSABLE_H

#include "tile.h"
#include "car.h"

class Traversable : public Tile {
protected:
	// cars current on this Traversable
	std::queue<CarPtr> cars;

	// maximum number of cars can be on this Tile
	int capacity;
public:
	Traversable(int, int, int);
	~Traversable();

	// pushes a CarpPtr into the queue of cars
	void acceptCar(CarPtr);

	// sends the first car to a neighbour of this Traversable based on the direction
	int sendCar(int, Car &);

	// getter method for size of cars
	int getNumCars();

	// getter method for capacity
	int getCapacity();

	// clears all cars on this Traversable (frees the memory of cars)
	void clearCars();
};

#endif