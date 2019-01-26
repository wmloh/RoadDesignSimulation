#include "pathFinder.h"
#include "car.h"
#include "road.h"
#include <algorithm>
#include <iterator>
#include <set>
#include <memory>
#include <stack>
#include "constants.h"
#include "openElement.h"

PathFinder::PathFinder(const Ground &g, int(*funcH)(int, int, int, int)):
	g{g}, funcH{funcH} {}

PathFinder::~PathFinder() {}

std::queue<int> PathFinder::findPath(int x, int y, int desX, int desY, Car *car) {
	std::queue<int> container;
	// pair.first is f score; pair.second is Tile
	// invariant: sorted in increasing order
	// format: <fScore, gScore, current Tile *, previous openElement ptr, direction>
	auto firstNode = std::make_unique<OpenElement>(funcH(x, y, desX, desY), 0, car->getRoad(), nullptr, DEFAULT);
	OpenContainer open;
	open.emplace_back(std::move(firstNode));
	std::set<std::unique_ptr<OpenElement>> closed;
	
	// local variables
	int fScore, gScore;
	Tile *t;
	Tile *tile;
	int dir;
	int curX, curY;
	std::vector<Tile *> neighbours;
	OpenElement *prev;

	// child variables
	int fScoreChild, gScoreChild;
	int childX, childY;
	int childRelX, childRelY;
	
	//// DEV TEST ////
	int X, Y;
	std::string s;

	while(!open.empty()) {
		// selects the front of open set (which has lowest f-score based on invariant)
		auto node = std::move(open.front());
		OpenElement *nodePtr = node.get();
		open.pop_front();
		std::tie(fScore, gScore, t, prev, dir) = node->pack();
		closed.insert(std::move(node));
		
		std::tie(X, Y) = t->getCoord();
		std::cout << "New openElement selected: " << '(' << X << ',' << Y << ')' << std::endl;
		std::getline(std::cin, s);


		std::cout << "Current chain:" << std::endl;
		OpenElement *testNode = nodePtr;
		while(testNode) {
			int nodeX = testNode->t->getCoord().first;
			int nodeY = testNode->t->getCoord().second;
			std::cout << '(' << nodeX << ',' << nodeY << ')' << ' ';
			testNode = testNode->prev;
		}
		std::cout << "End chain" << std::endl;

		// checks if reached destination
		std::tie(curX, curY) = t->getCoord();
		if(curX == desX && curY == desY) {
			return backTrack(*nodePtr);
		}
		
		neighbours = t->getNeighbours();
		//std::cout << neighbours.size() << std::endl;
		for(int i = 0; i < 9; ++i) {
			tile = neighbours.at(i);

			// checks if tile is nullptr or in closed set
			if(!tile) continue;			
			if(std::find_if(closed.begin(), closed.end(),
				[&tile](const std::unique_ptr<OpenElement> &e) {
					return e->t == tile;
				}) != closed.end()) continue;

			std::tie(childX, childY) = tile->getCoord();
			if(!tile->traversable() && !(childX == desX && childY == desY)) continue; // destination is not traversable

			std::cout << "DIR: " << inverseMapping(i) << std::endl;
			if(tile) std::cout << *tile << std::endl;
			else std::cout << '0' << std::endl;

			std::tie(X, Y) = tile->getCoord();
			std::cout << '(' << X << ',' << Y << ')' << std::endl;
			std::getline(std::cin, s);			

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

			int num = i;
			if(num > 3) --num;

			insertSorted(open, fScoreChild, gScoreChild, tile, nodePtr, num);
			std::cout << '(' << X << ',' << Y << ')' << " inserted into open:" << fScoreChild << ' ' << gScoreChild << ' ' << i << std::endl;
			int nodeX = nodePtr->t->getCoord().first;
			int nodeY = nodePtr->t->getCoord().second;
			std::cout << "> child of :" << '(' << nodeX << ',' << nodeY << ')' << std::endl;
		}
	}
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
}

int PathFinder::getCost(int i) {
	if(i == 0 || i == 2 || i == 5 || i == 7) {
		return DIAG_COST;
	}
	return ORTHO_COST;
}

std::queue<int> PathFinder::backTrack(OpenElement &oe) {
	std::cout << "backtracking" << std::endl;
	std::stack<int> reversed;
	std::queue<int> directions;

	reversed.push(oe.dir);
	OpenElement *node = oe.prev;
	while(node) {
		reversed.push(node->dir);
		std::cout << node->dir << std::endl;
		node = node->prev;
	}

	while(!reversed.empty()) {
		directions.push(reversed.top());
		reversed.pop();
	}
	directions.pop(); // remove DEFAULT value
	return directions;
}