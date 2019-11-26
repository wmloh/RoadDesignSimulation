#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
#include <utility>
#include <algorithm>

// Directions
const int NW = 0;
const int N = 1;
const int NE = 2;
const int W = 3;
const int E = 4;
const int SW = 5;
const int S = 6;
const int SE = 7;
const std::pair<int, int> KEYMAPPING[8] = {
	{-1, -1},
	{0, -1},
	{1, -1},
	{-1, 0},
	{1, 0},
	{-1, 1},
	{0, 1},
	{1, 1}
};

// Cost values
const int DEFAULT = -1;
const int NUM_TILES = 8;
const int ORTHO_COST = 10;
const int DIAG_COST = 14;

// Car state values
const int STEPPED = 0;
const int BLOCKED = 1;
const int REACHED = 2;

// Cost function
int costFunc(int x, int y, int desX, int desY);

// Int to Direction mapping
std::string inverseMapping(int);

#endif
