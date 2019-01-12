CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
OBJECTS = main.o commandLoop.o simulation.o map.o tile.o road.o car.o home.o hub.o obst.o empty.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = main

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS}