CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD



### Combining and process script names
OBJECTS = layer.o convLayer.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = main

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -fopenmp -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS}

