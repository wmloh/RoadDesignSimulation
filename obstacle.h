#ifndef OBST_H
#define OBST_H

#include "tile.h"

class Obst final : public Tile {
public:
	Obst(int, int);
	~Obst();

	Eigen::Matrix<float, 5, 1> toVector() override;
	virtual std::string print() override;
	bool traversable() override;
};

#endif