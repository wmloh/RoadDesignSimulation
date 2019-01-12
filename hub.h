#ifndef HUB_H
#define HUB_H

#include "tile.h"

class Car;

class Hub final : public Tile {
	std::queue<Car *> buffer;
public:
	Hub(int, int);
	~Hub();
	void sendCar();
};

#endif