#ifndef OBST_H
#define OBST_H

#include "tile.h"

class Obst final : public Tile {
public:
	Obst(int, int);
	~Obst();

	Vec toVector() override;
	virtual std::string print() override;
	bool traversable() override;
};

#endif