#include "car.h"
#include "road.h"
#include "hub.h"
#include "constants.h"
#include "pathFinder.h"
#include "tile.h"
#include "traversable.h"

Car::Car(int x, int y, int desX, int desY, Hub *hub, Traversable *curRoad) : 
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

void Car::setRoad(Traversable *r) {
	curRoad = r;
}

std::pair<int, int> Car::getDest() {
	return dest;
}

Traversable *Car::getRoad() {
	return curRoad;
}

int Car::move() {
	int dir = route.front();
	
	int index = dir;
	if(index > 3) ++index; // adjusting index of neighbours vector
	
	int state = curRoad->sendCar(index, *this);
	if(state == STEPPED) {
		int deltaX, deltaY;
		route.pop();
		std::tie(deltaX, deltaY) = KEYMAPPING[dir];
		x += deltaX;
		y += deltaY;
	}
	return state;
}

void Car::reached() {
	// do something
	std::cout << "Reached destination!" << std::endl;
}

std::ostream &operator<<(std::ostream &out, Car &c) {
	out << "Coordinates: " << '(' << c.x << ',' << c.y << ')' << std::endl;
	out << "Destination: " << '(' << c.dest.first << ',' << c.dest.second << ')' << std::endl;
	out << "Path distance: " << c.route.size() << std::endl;
	return out;
}