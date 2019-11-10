#ifndef TIMESTEP_H
#define TIMESTEP_H

#include "trigger.h"

class Car;

class TimeStep final : public Trigger {
	// cars currently in TimeStep phase
	std::vector<Car *> cars;
public:
	TimeStep(const int * const step);
	~TimeStep();

	// adds a Car * to cars
	void attach(Car *);

	// removes Car * from cars
	void detach(Car *);

	// calls Car::move() for each car and checks for end condition
	void notifyObserver() override;

	// getter method for car.size()
	int getSize() override;

	std::ostream &print(std::ostream &) override;
};

#endif