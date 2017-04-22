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

${EXE}: dijkstra.o Graph.o Vertex.o
	${GCC} -o ${EXE} dijkstra.o Graph.o Vertex.o

dijkstra.o: dijkstra.cpp Graph.h Vertex.h
	${GCC} -c dijkstra.cpp

Graph.o: Graph.cpp Graph.h Vertex.h
	${GCC} -c Graph.cpp

Vertex.o: Vertex.cpp Vertex.h
	${GCC} -c Vertex.cpp

clean:
	rm -f *.o *.exe *.tar dijkstra

release:
	@echo "Creating project tar for turn in..."
	tar cvf ${RELEASE_NAME}.tar ${RELEASE_FILES}

test: ${EXE}
	@echo -n 'test$$ '
	./${EXE} sample-input.txt f cd