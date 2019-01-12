#include <iostream>
#include <vector>

class Tile;

typedef std::vector<std::vector<Tile *>> Ground;

class Map {
	std::string mapDir;
	std::string profDir;
public:
	Map(std::string, std::string);
	~Map();
	Ground toTiles();
	//void replaceTile();
};