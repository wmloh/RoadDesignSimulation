#include "timestep.h"
#include "car.h"

TimeStep::TimeStep(const int * const step) : Trigger{step}, cars{} {}

TimeStep::~TimeStep() {}

void TimeStep::attach(Car *c) {
	cars.emplace_back(c);
}

void TimeStep::detach(Car *c) {
	cars.erase(std::remove_if(cars.begin(), cars.end(), [&c](Car * a){return a == c;}));
}

void TimeStep::notifyObserver() {
	for(auto &c : cars) {
		c->move();
	}
}

std::ostream &TimeStep::print(std::ostream &out) {
	int len = cars.size();
	for(int i = 0; i < len; ++i) {
		out << '[' << i << ']' << std::endl;
		out << *cars.at(i);
	}
	return out;
}