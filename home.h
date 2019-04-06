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

	// receives recipe for Car and creates a Car and stored in this Home
	// allocates heap-allocated memory for a Car
	// calls the getRoute method for Car
	void loadCar(int, int, PathFinder &, Hub *);

	Vec toVector() override;

	// getter method for first Car in queue
	Car * getCar();

	bool traversable() override;

	virtual std::string print() override;
	friend class CommandLoop;
};

#endif