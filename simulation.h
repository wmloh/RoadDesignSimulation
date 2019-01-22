#ifndef SIMULATION_H
#define SIMULATION_H

#include "tile.h"
#include "timestep.h"
#include "waiting.h"

class CommandLoop;

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
	bool stepRun();
	float calculate();
	void setStream(std::string);
	friend std::ostream &operator<<(std::ostream &, Simulation &);
	friend class CommandLoop;
};

#endif