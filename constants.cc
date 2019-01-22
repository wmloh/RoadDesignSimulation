#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <utility>

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

#endif