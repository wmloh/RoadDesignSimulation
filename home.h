#ifndef HOME_H
#define HOME_H

#include "tile.h"

class Car;

class Home final : public Tile {
	std::queue<Car *> buffer;
public:
	Home(int, int);
	~Home();
	void sendCar();
	virtual std::string print() override;
};

#endif