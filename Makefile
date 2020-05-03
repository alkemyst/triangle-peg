all: baseProblem fastestSolution

%.o: %.cpp %.h
	g++ -Werror -fmax-errors=1 -c $< -o $@

%: %.cpp Move.o Coordinate.o Triangle.o
	g++ -Werror -fmax-errors=1 $@.cpp Move.o Coordinate.o Triangle.o -o $@

clean:
	rm -f *~ baseProblem *.o

