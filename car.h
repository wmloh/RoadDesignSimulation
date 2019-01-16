#ifndef CAR_H
#define CAR_H

#include "tile.h"

class Road;

class Car final : public Tile {
	Road * curRoad;
public:
	Car(int, int);
	~Car();
	void setRoad(Road *);
private:
	virtual std::string print() override;
};

#endif