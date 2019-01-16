#include "waiting.h"
#include "home.h"
#include <algorithm>

Waiting::Waiting(const int * const step) : Trigger{step}, homes{},
	backup{}, fixed{false} {}

Waiting::~Waiting() {}

void Waiting::attach(int ts, Home *h) {
	if(!fixed) {
		homes.emplace_back(std::pair<int, Home *>(ts, h));
	}
}

Home * Waiting::detach() {
	if(fixed) {
		Home *h = homes.back().second;
		homes.pop_back();
		return h;
	}
	return nullptr;
}

void Waiting::notifyObserver() {
	while(homes.back().first == getStep()) {
		homes.back().second->sendCar();
		homes.pop_back();
	}
}

void Waiting::fixState() {
	std::sort(homes.begin(), homes.end(), std::greater<std::pair<int, Home *>>());
	backup = homes;
	fixed = true;
}

void Waiting::reset() {
	homes = backup;
}