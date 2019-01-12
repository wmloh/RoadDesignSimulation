#include "tile.h"

class Car;

class Home final : public Tile {
	std::vector<Car *> buffer;
public:
	Home(int, int);
	~Home();
	void sendCar();
};