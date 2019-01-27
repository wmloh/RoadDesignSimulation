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
	int x, y;
	std::queue<int> route;
	std::pair<int, int> dest;
	Hub *hub;
	Traversable *curRoad;
public:
	Car(int, int, int, int, Hub *, Traversable *);
	~Car();
	bool getRoute(PathFinder &);
	void setRoad(Traversable *);
	Traversable *getRoad();
	bool move();
	friend std::ostream &operator<<(std::ostream &, Car &);
	friend class CommandLoop;
};

typedef std::unique_ptr<Car> CarPtr;

#endif