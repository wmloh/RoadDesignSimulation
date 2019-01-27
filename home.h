#ifndef HOME_H
#define HOME_H

#include "traversable.h"
#include "car.h"

class Hub;
class PathFinder;
class CommandLoop;

class Home final : public Traversable {

public:
	Home(int, int, int);
	~Home();
	void loadCar(int, int, PathFinder &, Hub *);
	Car * getCar();
	virtual std::string print() override;
	bool traversable() override;
	friend class CommandLoop;
};

#endif