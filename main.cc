#include "commandLoop.h"

int main() {
	CommandLoop cmd;
	cmd.loadGuide("guide.txt");
	cmd.loadLegend("legend.txt");
	cmd.run();
}