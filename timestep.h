#ifndef TIMESTEP_H
#define TIMESTEP_H

#include "trigger.h"

class CarAgent;

class TimeStep final : public Trigger {
	std::vector<CarAgent *> cars;
public:
	TimeStep(const int * const step);
	~TimeStep();
	void attach(CarAgent *);
	void detach(CarAgent *);
	void notifyObserver() override;
};

#endif