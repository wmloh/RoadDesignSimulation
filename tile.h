#include <iostream>

class Tile {
	int x, y;
	std::vector<Tile *> neighbours;
public:
	Tile(int, int);
	~Tile();
	std::vector<Tile *> getNeighbours();
private:
	void setNeighbours(std::vector<Tile *>);
};