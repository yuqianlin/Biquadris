CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = biquadris
OBJECTS = main.o board.o block.o iblock.o oblock.o jblock.o lblock.o sblock.o zblock.o tblock.o starblock.o command.o level.o level0.o level1.o level2.o level3.o level4.o game.o subject.o textObserver.o graphicObserver.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
