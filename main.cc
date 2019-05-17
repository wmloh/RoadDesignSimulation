#include "commandLoop.h"

int main() {
	Eigen::initParallel();
	CommandLoop cmd;
	cmd.loadGuide("guide.txt");
	cmd.loadLegend("legend.txt");
	cmd.loadFiles("./datasets/map1.txt", "./datasets/profile1.txt", "./datasets/order1.csv");
	cmd.run();
}