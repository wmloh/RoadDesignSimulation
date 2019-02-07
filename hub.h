#ifndef HUB_H
#define HUB_H

#include "tile.h"

class Car;

class Hub final : public Tile {
	std::queue<Car *> buffer;
	int capacity;
public:
	Hub(int, int, int);
	~Hub();

	Eigen::Matrix<float, 5, 1> toVector() override;
	virtual std::string print() override;
	bool traversable() override;
};

#endif