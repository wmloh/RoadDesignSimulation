CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD

### Categorization of scripts
# User interaction scripts
COMMAND = main.o commandLoop.o 

# Controller scripts
CONTROLLER = simulation.o map.o trigger.o timestep.o waiting.o

# Helper scripts
UTIL = constants.o csvParser.o

# Tile object script
TILES = tile.o traversable.o road.o car.o home.o hub.o obstacle.o empty.o 

# Pathing algorithm scripts
PATHING = pathFinder.o openElement.o 

# Convolutional Neural Network scripts
CNN_PATH = layer.o
CNN = $(addprefix cnn/, $(CNN_PATH))

### Combining and process script names
OBJECTS = $(COMMAND) $(CONTROLLER) $(UTIL) $(TILES) $(PATHING) $(CNN)
DEPENDS = ${OBJECTS:.o=.d}
EXEC = main

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -fopenmp -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS}

# https://codereview.stackexchange.com/questions/15724/improving-makefile-and-general-c-project-structure