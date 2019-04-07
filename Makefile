CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD

### Categorization of scripts

COMMAND = main.o commandLoop.o 
CONTROLLER = simulation.o map.o trigger.o timestep.o waiting.o
UTIL = constants.o csvParser.o
TILES = tile.o traversable.o road.o car.o home.o hub.o obstacle.o empty.o 
PATHING = pathFinder.o openElement.o 

OBJECTS = $(COMMAND) $(CONTROLLER) $(UTIL) $(TILES) $(PATHING)

DEPENDS = ${OBJECTS:.o=.d}
EXEC = main

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS}

# https://codereview.stackexchange.com/questions/15724/improving-makefile-and-general-c-project-structure