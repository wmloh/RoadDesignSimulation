#include "pathFinder.h"
#include "car.h"
#include "road.h"
#include <algorithm>
#include <iterator>
#include <set>
#include <memory> // unique_ptr to keep references to previous tuple
#include <stack>
#include "constants.cc"
#include "openElement.h"

PathFinder::PathFinder(const Ground &g, int(*funcH)(int, int, int, int)):
	g{g}, funcH{funcH} {}

PathFinder::~PathFinder() {}

std::queue<int> PathFinder::findPath(int x, int y, int desX, int desY, Car *car) {

	std::queue<int> container;
	// pair.first is f score; pair.second is Tile
	// invariant: sorted in increasing order
	// format: <fScore, gScore, previous tuple ptr, direction>
	auto firstNode = std::make_unique<OpenElement>(funcH(x, y, desX, desY), 0, car->getRoad(), nullptr, DEFAULT);
	OpenContainer open;
	open.push_back(std::move(firstNode));
	std::set<Tile *> closed;
	
	// local variables
	int fScore, gScore;
	Tile *t;
	Tile *tile;
	int dir;
	int curX, curY;
	std::vector<Tile *> neighbours;
	//OpenElement *node;
	OpenElement *prev;

	// child variables
	int fScoreChild, gScoreChild;
	int childRelX, childRelY;

	while(!container.empty()) {
		// selects the front of open set (which has lowest f-score based on invariant)
		auto node = std::move(open.front());
		open.pop_front();
		std::tie(fScore, gScore, t, prev, dir) = node->pack();
		closed.insert(t);

		// checks if reached destination
		std::tie(curX, curY) = t->getCoord();
		if(curX == desX && curY == desY) {
			return backTrack(*node);
		}

		neighbours = t->getNeighbours();
		for(int i = 0; i < NUM_TILES; ++i) {
			tile = neighbours.at(i);

			// checks if tile is nullptr or in closed set
			if(!tile) continue;
			if(closed.find(tile) != closed.end()) continue;

			gScoreChild = gScore + getCost(i);
			std::tie(childRelX, childRelY) = KEYMAPPING[i];
			fScoreChild = gScoreChild + funcH(childRelX + curX, childRelY + curY, desX, desY);

			auto it = std::find_if(open.begin(), open.end(), 
				[&tile](std::unique_ptr<OpenElement> &tup) {
					return tup->t == tile;
				});
			if(it != open.end() and gScoreChild > (*it)->gScore) {
				// if found, and if gScoreChild >= g-score of accessed element, then continue
				continue;
			}

			insertSorted(open, fScoreChild, gScoreChild, tile, node.get(), i);
		}
	}
	throw "No possible path can be found";
	return {};
}

void PathFinder::insertSorted(OpenContainer &open, int fScore, int gScore,
	Tile *t, OpenElement *prev, int dir) {
	auto oe = std::make_unique<OpenElement>(fScore, gScore, t, prev, dir);
	for(auto it = open.begin(); it != open.end(); ++it) {
		if(fScore <= (*it)->fScore) {
			open.insert(it, std::move(oe));
			return;
		}
	}
	open.push_back(std::move(oe));
	//open.insert(std::lower_bound(open.begin(), open.end(), tup), tup);
}

int PathFinder::getCost(int i) {
	if(i == 0 || i == 2 || i == 5 || i == 7) {
		return DIAG_COST;
	}
	return ORTHO_COST;
}

std::queue<int> PathFinder::backTrack(OpenElement &oe) {
	std::stack<int> reversed;
	std::queue<int> directions;

	OpenElement *node = oe.prev;
	while(node) {
		reversed.push(node->dir);
		node = node->prev;
	}

	while(!reversed.empty()) {
		directions.push(reversed.top());
		reversed.pop();
	}

	return directions;
}