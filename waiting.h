#ifndef WAITING_H
#define WAITING_H

#include "trigger.h"
#include <vector>
#include "pathFinder.h"
#include "tile.h"

class Home;
class Hub;

class Waiting final : public Trigger {
	std::vector<std::tuple<int, int, int, Home *, Hub *>> homes;
	std::vector<std::tuple<int, int, int, Home *, Hub *>> backup;
	bool fixed;
	PathFinder pf;
public:
	Waiting(const int * const step, Ground &g);
	~Waiting();
	void attach(int, int, int, Home *, Hub *);
	Home * detach();
	void notifyObserver() override;

	// simulation optimization
	void fixState();
	void reset();
	std::ostream &print(std::ostream &) override;
};

#endif