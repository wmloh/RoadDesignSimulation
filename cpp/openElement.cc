#include "openElement.h"

OpenElement::OpenElement(int fScore, int gScore, Tile *t, OpenElement *prev, int dir) :
		fScore{fScore}, gScore{gScore}, t{t}, prev{prev}, dir{dir} {}

OpenElement::~OpenElement() {}

std::tuple<int, int, Tile *, OpenElement *, int> OpenElement::pack() {
	return std::make_tuple(fScore, gScore, t, prev, dir);
}