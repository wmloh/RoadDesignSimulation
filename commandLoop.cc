#include "commandLoop.h"
#include <fstream>

CommandLoop::CommandLoop(): guide{}, legend{}, sim{}, stream{"cout"} {}

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
				// sim.init();
			} else if (command == "setStream") {
				std::cin >> second;
				if(second == "cout") {
					stream = "cout";
				} else if(second == "file") {
					std::cin >> second;
					stream = second;
				}
			} else if (command == "exit") {
				break;
			} else {
				std::cout << "Incorrect command; enter \"help\" for more information" << std::endl;
			}
		}
	} catch(std::string s) {
		std::cout << "Error occurred:" << std::endl << s << std::endl;
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