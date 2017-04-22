# Makefile

GCC=g++ -std=c++11 -O3
EXE=generate-input.exe
DATA=./data
DIJ=../src/dijkstra

all: ${EXE}

${EXE}: generate-input.cpp
	${GCC} -o ${EXE} generate-input.cpp

big-input: ${EXE}
	./${EXE} 30 500000 100 > ${DATA}/big-input.txt
	@tail -1 ${DATA}/big-input.txt
	@du -h ${DATA}/big-input.txt

big-test: ${DATA}/big-input.txt
	@date +%s%N
	${DIJ} ${DATA}/big-input.txt > ${DATA}/big-output.txt G Jx5aM4G5H8h94P3z
	@date +%s%N

big-vars:
	@head -20 data/big-input.txt | tail -1 | awk '{print $$1}'
	@head -50 data/big-input.txt | tail -1 | awk '{print $$1}'

clean:
	rm -f *.o *.exe *.tar
