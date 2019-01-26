#include "car.h"
#include "road.h"
#include "hub.h"
#include "constants.h"
#include "pathFinder.h"
#include "tile.h"

Car::Car(int x, int y, int desX, int desY, Hub *hub, Tile *curRoad) : 
	x{x}, y{y}, route{}, dest{desX, desY}, hub{hub}, curRoad{curRoad} {}

Car::~Car() {}

bool Car::getRoute(PathFinder &pf) {
	
	try {
		route = pf.findPath(x, y, dest.first, dest.second, this);
		return true;
	} catch(std::string s) {
		std::cerr << s << std::endl;
		std::cerr << "Please ensure that the specified cars has access to roads" << std::endl;
		throw;
	} catch(const std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
		throw;
	} catch(const std::exception &e) {
		std::cerr << e.what() << std::endl;
		throw;
	} catch(...) {
		std::cerr << "Unknown error (Car::getRoute)" << std::endl;
		throw "Unknown error (Car::getRoute)";
	} 
	return false;
}

void Car::setRoad(Road *r) {
	curRoad = r;
}

Tile *Car::getRoad() {
	return curRoad;
}

bool Car::move() {
	int dir = route.front();

	Tile *t = curRoad->getNeighbours().at(dir);
	Road *nextRoad = dynamic_cast<Road *>(t);

	if(nextRoad) {
		int cap = nextRoad->getCapacity();
		int curSize = nextRoad->getNumRoad();
		if(curSize < cap) {
			nextRoad->accept
		}
	} else {
		std::cerr << "Routing algorithm invalid (Car::move)" << std::endl;
		throw "Error";
	}
	return false;
}

std::ostream &operator<<(std::ostream &out, Car &c) {
	out << "Coordinates: " << '(' << c.x << ',' << c.y << ')' << std::endl;
	out << "Destination: " << '(' << c.dest.first << ',' << c.dest.second << ')' << std::endl;
	out << "Path distance: " << c.route.size() << std::endl;
	return out;
}