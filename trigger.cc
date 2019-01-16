#include "trigger.h"

Trigger::Trigger(const int * const step) : step{step} {}

Trigger::~Trigger() {}

int Trigger::getStep() const {
	return *step;
}