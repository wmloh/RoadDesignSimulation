#include "timestep.h"
#include "car.h"
#include "constants.h"

TimeStep::TimeStep(const int * const step) : Trigger{step}, cars{} {}

TimeStep::~TimeStep() {}

void TimeStep::attach(Car *c) {
	cars.emplace_back(c);
}

void TimeStep::detach(Car *c) {
	cars.erase(std::remove_if(cars.begin(), cars.end(), [&c](Car * a){return a == c;}));
}

void TimeStep::notifyObserver() {
	int state;
	for(auto &c : cars) {
		state = c->move();
		if(state == BLOCKED) {
			std::cout << "Traffic congestion!" << std::endl;
		} else if (state == REACHED) {
			detach(c);
		}
	}
}

int TimeStep::getSize() {
	return cars.size();
}

std::ostream &TimeStep::print(std::ostream &out) {
	int len = cars.size();
	for(int i = 0; i < len; ++i) {
		out << '[' << i << ']' << std::endl;
		out << *cars.at(i);
	}
	return out;
}