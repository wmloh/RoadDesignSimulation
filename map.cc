#include "map.h"
#include "obstacle.h"
#include "empty.h"
#include "home.h"
#include "hub.h"
#include "road.h"
#include "car.h"
#include "csvParser.h"
#include <fstream>
#include <sstream>

Map::Map(std::string mapDir, std::string profDir, std::string orderDir) :
	mapDir{mapDir}, profDir{profDir}, orderDir{orderDir}, tileArray{}, size{} {}

Map::~Map() {}

void attachNeighbours(Ground &g, int lenX, int lenY) {
	int x = 0;
	int y = 0;

	for(const auto &r : g) {
		for(auto &c : r) {
			for(int i = x - 1; i <= x + 1; ++i) {
				for(int j = y - 1; j <= y + 1; ++j) {
					if(i >= 0 && i < lenX && j >= 0 && j < lenY && (i != x || j != y)) {
						c->setNeighbours(g.at(i).at(j).get());
					} else {
						c->setNeighbours(nullptr);
					}
				}
			}
			y++;
		}
		x++;
		y = 0;
	}
}

Ground Map::toTiles() {
	std::ifstream mapFs {mapDir};
	std::ifstream profFs {profDir};
	Ground g;
	std::string line;
	std::string profile;
	tileArray.clear();

	int rowCount = 0;
	int len;
	std::vector<TilePtr> row;

	try {
		// create 2D array of Tiles
		while(std::getline(mapFs, line)) {
			std::getline(profFs, profile);
			len = line.size();
			row.clear();
			
			for(int i = 0; i < len; ++i) {
				if(line[i] == '%') {
					row.emplace_back(std::make_unique<Obst>(i, rowCount));
				} else if(line[i] == ' ') {
					row.emplace_back(std::make_unique<Empty>(i, rowCount));
				} else if(line[i] == 'H') {
					row.emplace_back(std::make_unique<Home>(i, rowCount, profile[i] - '0'));
				} else if(line[i] == 'h') {
					row.emplace_back(std::make_unique<Hub>(i, rowCount, profile[i] - '0'));
				} else if(line[i] == '+') {
					row.emplace_back(std::make_unique<Road>(i, rowCount, profile[i] - '0'));
				} else if(line[i] != '\r') {
					throw std::string{"Unrecognized symbol detected on the map: " + std::string{1, line[i]}};
				}
				if(line[i] != '\r') tileArray.emplace_back(row.back().get());

			}
			g.emplace_back(std::move(row));
			++rowCount;

			mapFs.clear();
			profFs.clear();
		}
		size = len-1;

		// assigning pointers of neighbours
		attachNeighbours(g, size, rowCount);
		
	} catch(std::string s) {
		std::cerr << s << std::endl;
		throw;
	} catch(const std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
		throw;
	} catch(const std::exception &e) {
		std::cerr << e.what() << std::endl;
		throw;
	} catch(...) {
		std::cerr << "Unknown error occurred(1)" << std::endl;
		throw;
	}
	
	return std::move(g);
}

void Map::toOrder(Waiting &wt) {
	CSVParser cp{orderDir};
	auto vec = cp.toInt(true);
	Home *h;
	Hub *hub;
	int x, y, desX, desY;

	for(auto &v : vec) {
		x = v.at(1);
		y = v.at(2);
		h = dynamic_cast<Home *>(getTile(x, y));
		if(!h) {
			std::ostringstream oss;
			oss << '(' << x << ',' << y << ')';
			std::cerr << "Origin of a Car must be a Home" + oss.str() << std::endl;
			throw "Origin of a Car must be a Home" + oss.str();
		}
		
		desX = v.at(3);
		desY = v.at(4);
		hub = dynamic_cast<Hub *>(getTile(desX, desY));
		if(!hub) {
			std::ostringstream oss;
			oss << '(' << desX << ',' << desY << ')';
			std::cerr << "Destination of a Car must be a Hub" + oss.str() << std::endl;
			throw "Destination of a Car must be a Hub" + oss.str();
		}

		//h->loadCar(desX, desY, hub);

		wt.attach(v.at(0), desX, desY, h, hub);
	}
}

Tensor Map::toMatrix(Ground &g) {
	Tensor tensor;

	int xLen = g.size();
	int yLen = g.at(0).size();

	std::unique_ptr<Eigen::MatrixXf> layer0 = std::make_unique<Eigen::MatrixXf>(xLen, yLen);
	std::unique_ptr<Eigen::MatrixXf> layer1 = std::make_unique<Eigen::MatrixXf>(xLen, yLen);
	std::unique_ptr<Eigen::MatrixXf> layer2 = std::make_unique<Eigen::MatrixXf>(xLen, yLen);
	std::unique_ptr<Eigen::MatrixXf> layer3 = std::make_unique<Eigen::MatrixXf>(xLen, yLen);
	std::unique_ptr<Eigen::MatrixXf> layer4 = std::make_unique<Eigen::MatrixXf>(xLen, yLen);

	float ele0, ele1, ele2, ele3, ele4;
	int i = 0;
	int j = 0;

	for(auto &r : g) {
		for(auto &c : r) {
			std::tie(ele0, ele1, ele2, ele3, ele4) = c->toVector();
			(*layer0)(j,i) = ele0;
			(*layer1)(j,i) = ele1;
			(*layer2)(j,i) = ele2;
			(*layer3)(j,i) = ele3;
			(*layer4)(j,i) = ele4;
			++i;
		}
		++j;
		i = 0;
	}

	tensor[0] = std::move(layer0);
	tensor[1] = std::move(layer1);
	tensor[2] = std::move(layer2);
	tensor[3] = std::move(layer3);
	tensor[4] = std::move(layer4);

	return tensor;
}

Tile *Map::getTile(int x, int y) {
	if(!tileArray.empty()) {
		return tileArray.at(y * size + x);
	}
	return nullptr;
}