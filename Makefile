CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
OBJECTS = main.o commandLoop.o simulation.o map.o constants.o tile.o traversable.o \
		road.o car.o home.o hub.o obstacle.o empty.o trigger.o timestep.o waiting.o \
		csvParser.o pathFinder.o openElement.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = main

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS}

# https://codereview.stackexchange.com/questions/15724/improving-makefile-and-general-c-project-structure