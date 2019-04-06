#ifndef COMMANDLOOP_H
#define COMMANDLOOP_H

#include "simulation.h"
#include <vector>

class CommandLoop {
	// stores guide instructions
	std::vector<std::string> guide;

	// stores legend information
	std::vector<std::string> legend;

	// stores simulation
	Simulation sim;
public:
	CommandLoop();
	~CommandLoop();

	// initiates the I/O command loop sequence
	void run();

	// initiates the I/O command loop for development purposes
	void dev();

	// loads guide from file
	void loadGuide(std::string);

	// loads legend from file
	void loadLegend(std::string);

	// wrapper method to load Map files into sim
	void loadFiles(std::string, std::string, std::string);
private:

	// prints guide
	void help();

	// prints legend
	void printLegend();
};

#endif