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

class Car {
	int x, y;
	std::queue<int> route;
	std::pair<int, int> dest;
	Hub *hub;
	Tile *curRoad;
public:
	Car(int, int, int, int, Hub *, Tile *);
	~Car();
	bool getRoute(PathFinder &);
	void setRoad(Road *);
	Tile *getRoad();
	bool move();
	friend std::ostream &operator<<(std::ostream &, Car &);
	friend class CommandLoop;
};

typedef std::unique_ptr<Car> CarPtr;

#endif