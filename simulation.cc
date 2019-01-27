#include "simulation.h"
#include "map.h"

Simulation::Simulation() : tiles{}, steps{0}, numRoads{0},
	roadCost{0}, stream{"cout"}, ts{&steps}, wt{&steps, tiles} {}

Simulation::~Simulation() {
	tiles.clear();
}

void Simulation::load(std::string map, std::string profile, std::string order) {
	auto m = Map{map, profile, order};
	tiles = m.toTiles();
	m.toOrder(wt);
	wt.fixState();
}

void Simulation::init() {
	// code
	while(stepRun()) {

	}

}

bool Simulation::stepRun() {
	std::cout << "stepped" << std::endl;
	wt.notifyObserver(ts);
	ts.notifyObserver();
	++steps;
	return true;
}

float Simulation::calculate() {
	return 0;
}

void Simulation::setStream(std::string s) {
	stream = s;
}

std::ostream &operator<<(std::ostream &out, Simulation &s) {
	for(auto &r : s.tiles) {
		for(auto &c: r) {
			out << *c << ' ';
		}
		out << std::endl;
	}
	return out;
}