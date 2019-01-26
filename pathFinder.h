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
	const Ground &g;
	int (*funcH)(int, int, int, int);
public:
	PathFinder(const Ground &g, int(*funcH)(int, int, int, int));
	~PathFinder();
	std::queue<int> findPath(int x, int y, int desX, int desY, Car *c);
private:
	void insertSorted(OpenContainer &, int, int, Tile *, OpenElement *, int);
	int getCost(int);
	std::queue<int> backTrack(OpenElement &);
};

#endif