# Makefile

GCC=g++ -std=c++11
EXE=dijkstra
RELEASE_NAME=proj4
RELEASE_FILES=\
	Makefile\
	LOG.txt\
	*.cpp\
	*.h\
	*.pdf


all: ${EXE}

${EXE}: dijkstra.o
	${GCC} -o ${EXE} dijkstra.o

dijkstra.o: dijkstra.cpp
	${GCC} -c dijkstra.cpp

clean:
	rm -f *.o *.exe *.tar dijkstra

release:
	@echo "Creating project tar for turn in..."
	tar cvf ${RELEASE_NAME}.tar ${RELEASE_FILES}
