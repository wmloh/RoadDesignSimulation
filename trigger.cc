#include "trigger.h"

Trigger::Trigger(const int * const step) : step{step} {}

Trigger::~Trigger() {}

int Trigger::getStep() const {
	return *step;
}

std::ostream &operator<<(std::ostream &out, Trigger &t) {
	return t.print(out);
}