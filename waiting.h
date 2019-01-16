#ifndef WAITING_H
#define WAITING_H

#include "trigger.h"
#include <vector>

class Home;

class Waiting final : public Trigger {
	std::vector<std::pair<int, Home *>> homes;
	std::vector<std::pair<int, Home *>> backup;
	bool fixed;
public:
	Waiting(const int * const step);
	~Waiting();
	void attach(int, Home *);
	Home * detach();
	void notifyObserver() override;

	// simulation optimization
	void fixState();
	void reset();
};

#endif