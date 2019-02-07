#ifndef EMPTY_H
#define EMPTY_H

#include "tile.h"

class Empty final : public Tile {
public:
	Empty(int, int);
	~Empty();
	
	Eigen::Matrix<float, 5, 1> toVector() override;
	virtual std::string print() override;
	bool traversable() override;
};

#endif