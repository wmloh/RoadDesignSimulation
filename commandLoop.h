#ifndef COMMANDLOOP_H
#define COMMANDLOOP_H

#include "simulation.h"
#include <vector>

class CommandLoop {
	std::vector<std::string> guide;
	std::vector<std::string> legend;
	Simulation sim;
public:
	CommandLoop();
	~CommandLoop();
	void run();
	void loadGuide(std::string);
	void loadLegend(std::string);
	void loadFiles(std::string, std::string, std::string);
private:
	void help();
	void printLegend();
};

#endif