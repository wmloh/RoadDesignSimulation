#include "constants.h"
#include <sstream>

int costFunc(int x, int y, int desX, int desY) {
	int cost = 0;

	// diagonal values
	int min = std::min(std::abs(x - desX), std::abs(y - desY));
	cost += min * DIAG_COST;

	// horizontal or vertical values
	int max = std::max(std::abs(x - desX), std::abs(y - desY));
	cost += (max - min) * ORTHO_COST;

	return cost;
}

std::string inverseMapping(int i) {
	switch(i) {
		case NW:
			return "NW";
		case N:
			return "N";
		case NE:
			return "NE";
		case W:
			return "W";
		case E:
			return "E";
		case SW:
			return "SW";
		case S:
			return "S";
		case SE:
			return "SE";
	}
	std::ostringstream oss;
	oss << i;
	return "Invalid key" + oss.str();
}