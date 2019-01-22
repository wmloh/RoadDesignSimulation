#ifndef CARAGENT_H
#define CARAGENT_H

#include <iostream>
#include <memory>
#include <queue>

class Road;
class Hub;

class Car {
	int x, y;
	std::queue<int> route;
	std::pair<int, int> dest;
	Hub *hub;
	Road *curRoad;
public:
	Car(int, int, int, int, Hub *);
	~Car();
	bool getRoute();
	void setRoad(Road *);
	Road *getRoad();
	bool move();
	friend std::ostream &operator<<(std::ostream &, Car &);
};

typedef std::unique_ptr<Car> CarPtr;

#endif