#ifndef HOME_H
#define HOME_H

#include "tile.h"
#include "car.h"

class Hub;

class Home final : public Tile {
	std::queue<CarPtr> buffer;
	int capacity;
public:
	Home(int, int, int);
	~Home();
	void loadCar(int, int, Hub *);
	void sendCar();
	virtual std::string print() override;
};

#endif