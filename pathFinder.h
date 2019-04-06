#ifndef PATHFINFER_H
#define PATHFINFER_H

#include <iostream>
#include <tuple>
#include <list>
#include "tile.h"

class Car;
class OpenElement;

typedef std::list<std::unique_ptr<OpenElement>> OpenContainer;

class PathFinder {
	// Ground reference
	const Ground &g;

	// function H
	int (*funcH)(int, int, int, int);
public:
	PathFinder(const Ground &g, int(*funcH)(int, int, int, int));
	~PathFinder();

	// generates a path for a car using A* Search Algorithm
	std::queue<int> findPath(int x, int y, int desX, int desY, Car *c);
private:
	// creates an OpenElement and inserts it into OpenContainer in a sorted
	//    manner based on fScore
	void insertSorted(OpenContainer &, int, int, Tile *, OpenElement *, int);

	// returns the cost based on the direction and constants defined
	int getCost(int);

	// returns a queue based on direction on OpenElement recursively
	std::queue<int> backTrack(OpenElement &);
};

// REFERENCE: https://en.wikipedia.org/wiki/A*_search_algorithm

#endif