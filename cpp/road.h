#ifndef ROAD_H
#define ROAD_H

#include "traversable.h"
#include "car.h"

class Road final : public Traversable {

public:
	Road(int, int, int);
	~Road();
	virtual std::string print() override;
	bool traversable() override;
};

#endif