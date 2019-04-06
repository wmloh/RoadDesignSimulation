#include "waiting.h"
#include "home.h"
#include <algorithm>
#include "constants.h" // using constFunc

Waiting::Waiting(const int * const step, Ground &g) : Trigger{step}, homes{},
	backup{}, fixed{false}, pf{g, costFunc} {}

Waiting::~Waiting() {}

void Waiting::attach(int ts, int desX, int desY, Home *h, Hub *hub) {
	if(!fixed) {
		homes.emplace_back(std::tuple<int, int, int, Home *, Hub *>(ts, desX, desY, h, hub));
	}
}

Home * Waiting::detach() {
	if(fixed) {
		Home *h = std::get<3>(homes.back());
		homes.pop_back();
		return h;
	}
	return nullptr;
}

void Waiting::notifyObserver() {}

void Waiting::notifyObserver(TimeStep &ts) {
	while(std::get<0>(homes.back()) == getStep()) {
		ts.attach(std::get<3>(homes.back())->getCar());		
		homes.pop_back();
	}
}

int Waiting::getSize() {
	return homes.size();
}

void Waiting::fixState() {
	//std::sort(homes.begin(), homes.end(), std::greater<std::tuple<int, int, int, Home *, Hub *>>());
	std::sort(homes.begin(), homes.end());
	backup = homes;
	fixed = true;

	// loading
	int ts, desX, desY;
	Home *h;
	Hub *hub;
	for(auto &tup : homes) {
		std::tie(ts, desX, desY, h, hub) = tup;
		h->loadCar(desX, desY, pf, hub);
	}
	
}

void Waiting::reset() {
	homes = backup;

	// clearing home buffers
	Home *h;
	for(auto &tup : homes) {
		h = std::get<3>(tup);
		h->clearCars();
	}
}

std::ostream &Waiting::print(std::ostream &out) {
	std::pair<int, int> p;
	for(auto &h : homes) {
		out << '[' << std::get<0>(h) << ']' << std::endl;
		p = std::get<3>(h)->getCoord();
		out << "Starts at: " << '(' << p.first << ',' << p.second << ')';
		out << " -> " << '(' << std::get<1>(h) << ',' << std::get<2>(h) << ')' << std::endl;
	}
	return out;
}