#ifndef TIMESTEP_H
#define TIMESTEP_H

#include "trigger.h"

class Car;

class TimeStep final : public Trigger {
	std::vector<Car *> cars;
public:
	TimeStep(const int * const step);
	~TimeStep();
	void attach(Car *);
	void detach(Car *);
	void notifyObserver() override;
	int getSize() override;

	std::ostream &print(std::ostream &) override;
};

#endif