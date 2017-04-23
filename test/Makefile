# Makefile

GCC=g++ -std=c++11 -O3
EXE=generate-input.exe
DATA=./data
DIJ=../src/dijkstra
AP=./airport/

all: ${EXE}

${EXE}: generate-input.cpp
	${GCC} -o ${EXE} generate-input.cpp

big-input: ${EXE}
	./${EXE} 10 100000 100 > ${DATA}/big-input.txt
	@tail -1 ${DATA}/big-input.txt
	@du -h ${DATA}/big-input.txt

	@date +%s%N
big-test: ${DATA}/big-input.txt
	${DIJ} ${DATA}/big-input.txt > ${DATA}/big-output.txt 46kY Gs9R9n
	@date +%s%N

big-vars:
	@head -20 data/big-input.txt | tail -1 | awk '{print $$1}'
	@head -50 data/big-input.txt | tail -1 | awk '{print $$1}'

airport-input: ${AP

clean:
	rm -f *.o *.exe *.tar
