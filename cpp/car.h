#ifndef CARAGENT_H
#define CARAGENT_H

#include <iostream>
#include <memory>
#include <queue>

class Road;
class Hub;
class PathFinder;
class Home;
class CommandLoop;
class Tile;
class Traversable;

class Car {
	// x, y coordinates
	int x, y;

	// queue of steps to take to reach destination
	std::queue<int> route;

	// x, y coordinates of destination
	std::pair<int, int> dest;

	// pointer to destination
	Hub *hub;

	// pointer to current Traversable
	Traversable *curRoad;
public:
	Car(int, int, int, int, Hub *, Traversable *);
	~Car();

	// getter method for route
	bool getRoute(PathFinder &);

	// setter method for curRoad
	void setRoad(Traversable *);

	// getter method for dest
	std::pair<int, int> getDest();

	// getter method for curRoad
	Traversable *getRoad();

	// moves in the direction specified by route
	//   mutates route and curRoad
	int move();

	// trigger call when destination is reached
	void reached();
	
	friend std::ostream &operator<<(std::ostream &, Car &);
	friend class CommandLoop;
};

typedef std::unique_ptr<Car> CarPtr;

#endif