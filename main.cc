#include "commandLoop.h"
#include <fstream>

int main() {
	CommandLoop cmd;
	cmd.loadGuide("guide.txt");
	cmd.loadLegend("legend.txt");
	cmd.loadFiles("./datasets/map1.txt", "./datasets/profile1.txt");
	cmd.run();
	
}