#ifndef HOME_H
#define HOME_H

#include "tile.h"

class Car;

class Home final : public Tile {
	std::queue<Car *> buffer;
	int capacity;
public:
	Home(int, int, int);
	~Home();
	void sendCar();
	virtual std::string print() override;
};

#endif