#ifndef WAITING_H
#define WAITING_H

#include "trigger.h"
#include <vector>
#include "pathFinder.h"
#include "tile.h"
#include "timestep.h"

class Home;
class Hub;

class Waiting final : public Trigger {
	// vector of homes to be loaded with Cars at a particular timestep
	std::vector<std::tuple<int, int, int, Home *, Hub *>> homes;

	// backup vector of homes (registered when fixState is called)
	std::vector<std::tuple<int, int, int, Home *, Hub *>> backup;

	// switch of whether the backup is fixed
	bool fixed;

	// PathFinder object to get paths of Car
	PathFinder pf;
public:
	Waiting(const int * const step, Ground &g);
	~Waiting();

	// adds an element to homes
	void attach(int, int, int, Home *, Hub *);

	// removes element from homes
	Home * detach();
	
	// does nothing	(should not be called)
	void notifyObserver() override;

	// attaches Car of home into Timestep when conditions are matched
	void notifyObserver(TimeStep &);

	// getter method for homes.size()
	int getSize() override;

	/* Simulation optimization */
	// Sorts homes and stores a (shallow) copy in backup
	// loads Home * by calling the Home::loadCar
	void fixState();

	// replace homes with a copy of backup and clears Cars from home
	void reset();
	
	std::ostream &print(std::ostream &) override;
};

#endif