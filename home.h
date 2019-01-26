#ifndef HOME_H
#define HOME_H

#include "tile.h"
#include "car.h"

class Hub;
class PathFinder;
class CommandLoop;

class Home final : public Tile {
	std::queue<CarPtr> buffer;
	int capacity;
public:
	Home(int, int, int);
	~Home();
	void loadCar(int, int, PathFinder &, Hub *);
	void clearBuffer();
	void sendCar();
	virtual std::string print() override;
	bool traversable() override;
	friend class CommandLoop;
};

#endif