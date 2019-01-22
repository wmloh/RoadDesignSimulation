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

void CommandLoop::dev() {
	std::cout << "### DEVELOPMENT MODE ACTIVATED ###" << std::endl;

	std::string command;
	std::string second;
	std::string third;

	try {
		while(std::cin >> command) {
			if(command == "get") {
				std::cin >> second;
				if(second == "timestep") {
					std::cout << sim.ts << std::endl;
				} else if(second == "waiting") {
					std::cout << sim.wt << std::endl;
				} else {
					std::cout << "Invalid command" << std::endl;
				}
			} else if (command == "show") {
				std::cout << sim;
			} else if(command == "stepRun") {
				std::cout << "Initialized step run" << std::endl;
				try {
					do {
						std::getline(std::cin, second);
						if(second.empty()) {
							continue;
						} else if(second == "stop") {
							break;
						} else if(second == "get") {
							std::cin >> third;
							if(third == "timestep") {
								std::cout << sim.ts << std::endl;
							} else if(third == "waiting") {
								std::cout << sim.wt << std::endl;
							} else {
								std::cout << "Invalid command" << std::endl;
							}
						}
					} while(sim.stepRun());
				} catch(std::string s) {
					std::cerr << s << std::endl;
					throw;
				} catch(const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
					throw;
				} catch(const std::exception &e) {
					std::cerr << e.what() << std::endl;
					throw;
				} catch(...) {
					std::cerr << "Unknown error occurred(1)" << std::endl;
					throw;
				}
				std::cout << "Step run terminated" << std::endl;

			} else if(command == "quit" || command == "q") {
				std::cout << "### DEVELOPMENT MODE SAFELY TERMINATED ###" << std::endl;
				break;
			} else {
				std::cout << "Invalid command" << std::endl;
			}
		}
	} catch(std::string s) {
		std::cerr << "Error occurred:" << std::endl << s << std::endl;
		throw s;
	} catch(...) {
		std::cerr << "Unknown error occurred(3)" << std::endl;
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