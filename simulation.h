#ifndef SIMULATION_H
#define SIMULATION_H

#include "tile.h"
#include "timestep.h"
#include "waiting.h"

class CommandLoop;

class Simulation {
	// vector of vector of tiles loaded
	Ground tiles;

	// current step
	int steps;

	// number of roads on tiles (CURRENTLY NOT DEFINED)
	int numRoads;

	// arbitrary costs based on the number of roads (CURRENTLY NOT DEFINED)
	int roadCost;

	// preferred method of output (std::cout or write to file)
	std::string stream;

	// trigger objects to control movements of cars
	TimeStep ts;

	// trigger object to include cars into ts
	Waiting wt;
public:
	Simulation();
	~Simulation();

	// loads map file into tiles, order file into wt and prepares for init
	void load(std::string, std::string, std::string);

	// runs one round of simulation
	void init();

	// runs one step of simulation at a time
	bool stepRun();

	// calculates the performance of the design (CURRENTLY NOT DEFINED)
	float calculate();

	// sets the preferred stream
	void setStream(std::string);
	
	friend std::ostream &operator<<(std::ostream &, Simulation &);
	friend class CommandLoop;
};

#endif