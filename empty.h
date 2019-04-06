#ifndef EMPTY_H
#define EMPTY_H

#include "tile.h"

class Empty final : public Tile {
public:
	Empty(int, int);
	~Empty();
	
	Vec toVector() override;
	virtual std::string print() override;
	bool traversable() override;
};

#endif