#ifndef ROAD_H
#define ROAD_H

#include "tile.h"

class Car;

class Road final : public Tile {
	int capacity;
	std::queue<Car *> cars;
public:
	Road(int, int, int);
	~Road();
	void moveCar();
	void acceptCar(Car *);
	int getCapacity();
	virtual std::string print() override;
	bool traversable() override;
};

#endif