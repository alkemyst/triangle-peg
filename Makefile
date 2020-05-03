all: baseProblem


Move.o: Move.cpp Move.h
	g++ -Werror -fmax-errors=1 -c Move.cpp -o Move.o

Coordinate.o: Coordinate.cpp Coordinate.h
	g++ -Werror -fmax-errors=1 -c Coordinate.cpp -o Coordinate.o

Triangle.o: Triangle.cpp Triangle.h
	g++ -Werror -fmax-errors=1 -c Triangle.cpp -o Triangle.o

baseProblem: baseProblem.cpp Move.o Coordinate.o Triangle.o
	g++ -Werror -fmax-errors=1 baseProblem.cpp Move.o Coordinate.o Triangle.o -o baseProblem

clean:
	rm -f *~ baseProblem *.o

