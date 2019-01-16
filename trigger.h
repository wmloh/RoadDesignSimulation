#ifndef TRIGGER_H
#define TRIGGER_H

#include <iostream>
#include <vector>
#include <algorithm>

class Trigger {
	const int * const step;
public:
	Trigger(const int * const step);
	~Trigger();
	virtual void notifyObserver() = 0;
protected:
	int getStep() const;
};

#endif