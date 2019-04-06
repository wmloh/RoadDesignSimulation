#ifndef TRIGGER_H
#define TRIGGER_H

#include <iostream>
#include <vector>
#include <algorithm>

class Trigger {
	// a const pointer to Simulation::step
	const int * const step;
public:
	Trigger(const int * const step);
	~Trigger();

	// activates any stored objects matching condition
	virtual void notifyObserver() = 0;

	// gets number of stored objects
	virtual int getSize() = 0;
protected:
	virtual std::ostream &print(std::ostream &) = 0;

	// getter method for value of step
	int getStep() const;
	friend std::ostream &operator<<(std::ostream &, Trigger &);
};

#endif