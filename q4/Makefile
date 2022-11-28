CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla
EXEC = a4q4 -lX11
OBJECTS = studio.o asciiart.o blank.o decorator.o filledbox.o blinkingbox.o movingbox.o maskbox.o subject.o window.o main.o textob.o graphicalob.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
