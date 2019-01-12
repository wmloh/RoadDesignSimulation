#include "tile.h"

class Road;

class Car final : public Tile {
	Road * curRoad;
public:
	Car(int, int);
	~Car();
private:
	void setRoad(Road *);
};