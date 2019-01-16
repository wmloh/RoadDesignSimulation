#include "commandLoop.h"
#include <fstream>

CommandLoop::CommandLoop(): guide{}, legend{}, sim{} {}

CommandLoop::~CommandLoop() {}

void CommandLoop::run() {
	std::string command;
	std::string second;

	try {
		while(std::cin >> command) {
			if(command == "help") {
				help();
			} else if (command == "legend") {
				printLegend();
			} else if (command == "init") {
				sim.init();
				std::cout << "Simulation ended" << std::endl;
			} else if (command == "setStream") {
				std::cin >> second;
				if(second == "cout") {
					sim.setStream(second);
				} else if(second == "file") {
					std::cin >> second;
					sim.setStream(second);
				} else {
					std::cout << "Invalid setStream command" << std::endl;
				}
			} else if (command == "dev") {
				dev();
			} else if (command == "show") {
				std::cout << sim;
			} else if (command == "quit" || command == "q") {
				break;
			} else {
				std::cout << "Invalid command; enter \"help\" for more information" << std::endl;
			}
		}
	} catch(std::string s) {
		std::cerr << "Error occurred:" << std::endl << s << std::endl;
		throw s;
	} catch(...) {
		std::cerr << "Unknown error occurred(2)" << std::endl;
		throw;
	}
}

void CommandLoop::help() {
	for(auto s: guide) {
		std::cout << s << std::endl;
	}
}

void CommandLoop::printLegend() {
	for(auto s : legend) {
		std::cout << s << std::endl;
	}
}

void CommandLoop::loadGuide(std::string fileName) {
	std::ifstream file {fileName};
	std::string line;
	if(!guide.empty()) guide.clear();

	while(std::getline(file, line)) {
		guide.push_back(line);
	}
}

void CommandLoop::loadLegend(std::string fileName) {
	std::ifstream file {fileName};
	std::string line;
	if(!legend.empty()) guide.clear();

	while(std::getline(file, line)) {
		legend.push_back(line);
	}
}

void CommandLoop::loadFiles(std::string map, std::string profile, std::string order) {
	sim.load(map, profile, order);
}