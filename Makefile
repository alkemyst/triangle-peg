all: baseProblem.exe flexiSearch.exe flexiSearchFast.exe

%.o: %.cpp %.h
	g++ -Werror -fmax-errors=1 -O3 -c $< -o $@

%.exe: %.cpp Move.o Coordinate.o Triangle.o
	g++ -Werror -fmax-errors=1 -O3 $< Move.o Coordinate.o Triangle.o -o $@

clean:
	rm -f *~ *.exe *.o

