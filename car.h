#ifndef CARAGENT_H
#define CARAGENT_H

#include <iostream>
#include <memory>
#include <queue>

const int NW = 0;
const int N = 1;
const int NE = 2;
const int W = 3;
const int E = 4;
const int SW = 5;
const int S = 6;
const int SE = 7;

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
	bool move();
};

typedef std::unique_ptr<Car> CarPtr;

#endif