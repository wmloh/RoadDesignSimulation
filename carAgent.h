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

class Car;

typedef std::unique_ptr<Car> CarPtr;

class CarAgent {
	CarPtr physCar;
	std::queue<int> route;
	std::pair<int, int> dest;
public:
	CarAgent(int, int, int, int);
	~CarAgent();
	bool getRoute();
	bool move();
};

#endif