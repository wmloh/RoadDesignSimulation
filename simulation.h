#ifndef SIMULATION_H
#define SIMULATION_H

#include "tile.h"
#include "timestep.h"
#include "waiting.h"

class Simulation {
	Ground tiles;
	int steps;
	int numRoads;
	int roadCost;
	std::string stream;
	TimeStep ts;
	Waiting wt;
public:
	Simulation();
	~Simulation();
	void load(std::string, std::string, std::string);
	void init();
	float calculate();
	void setStream(std::string);
	friend std::ostream &operator<<(std::ostream &, Simulation &);
};

#endif