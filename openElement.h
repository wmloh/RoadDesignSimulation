#ifndef OPENELEMENT_H
#define OPENELEMENT_H

#include <iostream>
#include <tuple>

class Tile;

struct OpenElement {
	int fScore;
	int gScore;
	Tile *t;
	OpenElement *prev;
	int dir;
	OpenElement(int, int, Tile *, OpenElement *, int);
	~OpenElement();
	std::tuple<int, int, Tile *, OpenElement *, int> pack();
};

#endif