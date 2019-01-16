#include "timestep.h"
#include "carAgent.h"

TimeStep::TimeStep(const int * const step) : Trigger{step}, cars{} {}

TimeStep::~TimeStep() {}

void TimeStep::attach(CarAgent *c) {
	cars.emplace_back(c);
}

void TimeStep::detach(CarAgent *c) {
	cars.erase(std::remove_if(cars.begin(), cars.end(), [&c](CarAgent * a){return a == c;}));
}

void TimeStep::notifyObserver() {
	for(auto &c : cars) {
		c->move();
	}
}